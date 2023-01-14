#include <any>
#include <iostream>
#include <string>
#include <map>
#include <thread>

#include <grpcpp/grpcpp.h>

#include "status_reader.hh"

#ifdef BAZEL_BUILD
#include "proto/linuxcnc.grpc.pb.h"
#else
#include "proto/linuxcnc.grpc.pb.h"
#endif

#include "emc_nml.hh"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;
using grpc::StatusCode;
using linuxcnc::CreateComponentRequest;
using linuxcnc::CreatePinRequest;
using linuxcnc::GetComponentsRequest;
using linuxcnc::GetComponentsResponse;
using linuxcnc::GetPinsResponse;
using linuxcnc::HalComponent;
using linuxcnc::HalPin;
using linuxcnc::HalPinDir;
using linuxcnc::HalPinType;
using linuxcnc::LinuxCnc;
using linuxcnc::ReadStatusRequest;
using linuxcnc::ReadStatusResponse;
using linuxcnc::status::ActiveCodes;
using linuxcnc::status::InterpreterState;
using linuxcnc::status::TaskExecState;
using linuxcnc::status::TaskMode;
using linuxcnc::status::TaskState;
using linuxcnc::status::TaskStatus;
using std::any;
using std::cout;
using std::map;
using std::string;
using std::unique_ptr;

TaskMode getTaskMode(EMC_TASK_MODE_ENUM mode)
{
  return TaskMode(mode - 1);
}

TaskState getTaskState(EMC_TASK_STATE_ENUM mode)
{
  return TaskState(mode - 1);
}

TaskExecState getTaskExecState(EMC_TASK_EXEC_ENUM mode)
{
  return TaskExecState(mode - 1);
}

InterpreterState getInterpreterState(EMC_TASK_INTERP_ENUM mode)
{
  return InterpreterState(mode - 1);
}

ActiveCodes *getActiveCodes(int gCodes[], int mCodes[])
{
  ActiveCodes *codes = new ActiveCodes();

  // gCodes
  for (int i = 0; i < sizeof(gCodes); ++i)
  {
    codes->add_gcodes(gCodes[i]);
  }

  // mCodes
  for (int i = 0; i < sizeof(mCodes); ++i)
  {
    codes->add_mcodes(mCodes[i]);
  }
  return codes;
}

TaskStatus *getTaskStatus(EMC_TASK_STAT task)
{
  TaskStatus *status = new TaskStatus();
  status->set_taskmode(getTaskMode(task.mode));
  status->set_taskstate(getTaskState(task.state));
  status->set_execstate(getTaskExecState(task.execState));
  status->set_interpreterstate(getInterpreterState(task.interpState));
  status->set_allocated_activecodes(getActiveCodes(task.activeGCodes, task.activeMCodes));
  // todo set fields
  return status;
}

// Logic and data behind the server's behavior.
class LinuxCncServiceImpl final : public LinuxCnc::Service
{

private:
  StatusReader statusReader;
  map<string, HalComponent> componentsMap;

public:
  Status GetComponents(ServerContext *context, const GetComponentsRequest *request,
                       GetComponentsResponse *response) override
  {
    // todo
    for (const auto &[key, value] : componentsMap)
    {
      const auto component = response->add_components();
      component->CopyFrom(value);
    }
    return Status::OK;
  }

  Status CreateComponent(ServerContext *context, const CreateComponentRequest *request,
                         HalComponent *response) override
  {
    // todo
    string compName = request->name();
    response->set_name(request->name());
    response->set_component_id(1);
    componentsMap[compName] = *response;
    return Status::OK;
  }

  Status GetPins(ServerContext *context, const HalComponent *request,
                 GetPinsResponse *response) override
  {
    // todo
    return Status::OK;
  }

  Status CreatePin(ServerContext *context, const CreatePinRequest *request,
                   HalPin *response) override
  {
    // todo
    response->set_name("test_pin");
    response->set_type(HalPinType::FLOAT);
    response->set_dir(HalPinDir::IN);
    response->set_component_id(0);
    response->set_component_name("test_comp");
    return Status::OK;
  }

  Status ReadStatus(ServerContext *context, const ReadStatusRequest *request,
                    ReadStatusResponse *response) override
  {
    // todo
    int result = statusReader.refreshStatus();
    if (result != 0)
    {
      return Status(StatusCode::INTERNAL, "Failed to refresh status " + std::to_string(result));
    }

    auto status = std::any_cast<EMC_STAT>(statusReader.getStatus());

    TaskStatus *taskStatus = getTaskStatus(status.task);

    response->set_allocated_taskstatus(taskStatus);
    return Status::OK;
  }
};

int main(int argc, char **argv)
{
  StatusReader statusReader;

  string address = "0.0.0.0";
  string port = "50051";
  string server_address = address + ":" + port;

  LinuxCncServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  unique_ptr<Server> server(builder.BuildAndStart());
  cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();

  return 0;
}
