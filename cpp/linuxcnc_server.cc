#include <any>
#include <iostream>
#include <string>
#include <map>
#include <thread>

#include <grpcpp/grpcpp.h>

#include "status_reader.hh"
#include "command_writer.hh"

#ifdef BAZEL_BUILD
#include "proto/linuxcnc.grpc.pb.h"
#else
#include "proto/linuxcnc.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;
using grpc::StatusCode;
using linuxcnc::CncStatus;
using linuxcnc::CreateComponentRequest;
using linuxcnc::CreatePinRequest;
using linuxcnc::GetComponentsRequest;
using linuxcnc::GetComponentsResponse;
using linuxcnc::GetPinsResponse;
using linuxcnc::HalComponent;
using linuxcnc::HalPin;
using linuxcnc::HalPinDir;
using linuxcnc::HalPinType;
using linuxcnc::HomeAxisRequest;
using linuxcnc::JogAbsoluteRequest;
using linuxcnc::JogContinuousRequest;
using linuxcnc::JogIncrementalRequest;
using linuxcnc::JogStopRequest;
using linuxcnc::LinuxCnc;
using linuxcnc::OverrideLimitsRequest;
using linuxcnc::ReadStatusRequest;
using linuxcnc::SendCommandResponse;
using linuxcnc::SetTaskModeRequest;
using linuxcnc::SetTaskStateRequest;
using linuxcnc::TaskAbortRequest;
using linuxcnc::UnhomeAxisRequest;
using std::any;
using std::cout;
using std::map;
using std::string;
using std::unique_ptr;

// Logic and data behind the server's behavior.
class LinuxCncServiceImpl final : public LinuxCnc::Service
{

private:
  StatusReader statusReader;
  CommandWriter commandWriter;
  map<string, HalComponent> componentsMap;

public:
  Status GetComponents(ServerContext *context, const GetComponentsRequest *request,
                       GetComponentsResponse *response) override
  {
    cout << "Get Components received" << std::endl;
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
    cout << "Create Component received" << std::endl;
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
    cout << "Get Pins received";
    // todo
    return Status::OK;
  }

  Status CreatePin(ServerContext *context, const CreatePinRequest *request,
                   HalPin *response) override
  {
    cout << "Create Pin received" << std::endl;
    // todo
    response->set_name("test_pin");
    response->set_type(HalPinType::FLOAT);
    response->set_dir(HalPinDir::IN);
    response->set_component_id(0);
    response->set_component_name("test_comp");
    return Status::OK;
  }

  Status ReadStatus(ServerContext *context, const ReadStatusRequest *request,
                    CncStatus *response) override
  {
    cout << "Read status received" << std::endl;

    cout << "Refreshing status" << std::endl;

    int result = statusReader.refreshStatus();
    if (result < 0)
    {
      return Status(StatusCode::INTERNAL, "Failed to refresh status " + std::to_string(result));
    }

    statusReader.setStatus(response);
    return Status::OK;
  }

  Status SetTaskMode(ServerContext *context,
                     const SetTaskModeRequest *request,
                     SendCommandResponse *response) override
  {
    int result = commandWriter.setTaskMode(request->task_mode());
    response->set_result(result);
    return Status::OK;
  }

  Status SetTaskState(ServerContext *context,
                      const SetTaskStateRequest *request,
                      SendCommandResponse *response) override
  {
    int result = commandWriter.setTaskState(request->task_state());
    response->set_result(result);
    return Status::OK;
  }

  Status TaskAbort(ServerContext *context,
                   const TaskAbortRequest *request,
                   SendCommandResponse *response) override
  {
    int result = commandWriter.taskAbort();
    response->set_result(result);
    return Status::OK;
  }

  // home/unhome
  Status HomeAxis(ServerContext *context,
                  const HomeAxisRequest *request,
                  SendCommandResponse *response) override
  {
    int result = commandWriter.homeAxis(request->joint_number());
    response->set_result(result);
    return Status::OK;
  }

  Status UnhomeAxis(ServerContext *context,
                    const UnhomeAxisRequest *request,
                    SendCommandResponse *response) override
  {
    int result = commandWriter.unhomeAxis(request->joint_number());
    response->set_result(result);
    return Status::OK;
  }

  Status OverrideLimits(ServerContext *context,
                        const OverrideLimitsRequest *request,
                        SendCommandResponse *response) override
  {
    int result = commandWriter.overrideLimits(request->joint_number());
    response->set_result(result);
    return Status::OK;
  }

  // jog
  Status JogContinuous(ServerContext *context,
                       const JogContinuousRequest *request,
                       SendCommandResponse *response) override
  {
    int result = commandWriter.jogContinuos(request);
    response->set_result(result);
    return Status::OK;
  }

  Status JogIncremental(ServerContext *context,
                        const JogIncrementalRequest *request,
                        SendCommandResponse *response) override
  {
    int result = commandWriter.jogIncremental(request);
    response->set_result(result);
    return Status::OK;
  }

  Status JogAbsolute(ServerContext *context,
                     const JogAbsoluteRequest *request,
                     SendCommandResponse *response) override
  {
    int result = commandWriter.jogAbsolute(request);
    response->set_result(result);
    return Status::OK;
  }

  Status JogStop(ServerContext *context,
                 const JogStopRequest *request,
                 SendCommandResponse *response) override
  {
    int result = commandWriter.jogStop(request);
    response->set_result(result);
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
