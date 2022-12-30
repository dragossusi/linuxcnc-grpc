#include <iostream>
#include <string>
#include <map>

#include <grpcpp/grpcpp.h>

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
using linuxcnc::CreateComponentRequest;
using linuxcnc::CreateHalPinRequest;
using linuxcnc::GetComponentsRequest;
using linuxcnc::GetComponentsResponse;
using linuxcnc::GetPinsResponse;
using linuxcnc::HalComponent;
using linuxcnc::HalPin;
using linuxcnc::HalPinDir;
using linuxcnc::HalPinType;
using linuxcnc::LinuxCnc;

std::map<std::string, HalComponent> componentsMap;

// Logic and data behind the server's behavior.
class LinuxCncServiceImpl final : public LinuxCnc::Service
{

  Status GetComponents(ServerContext *context, const GetComponentsRequest *request,
                       ServerWriter<GetComponentsResponse> *writer) override
  {
    // todo
    GetComponentsResponse response = GetComponentsResponse();

    for (const auto &[key, value] : componentsMap)
    {
      const auto component = response.add_components();
      component->CopyFrom(value);
    }
    writer->Write(response);
    return Status::OK;
  }

  Status CreateComponent(ServerContext *context, const CreateComponentRequest *request,
                         HalComponent *response) override
  {
    // todo
    std::string compName = request->name();
    response->set_name(request->name());
    response->set_component_id(1);
    componentsMap[compName] = *response;
    return Status::OK;
  }

  Status GetPins(ServerContext *context, const HalComponent *request,
                 ServerWriter<GetPinsResponse> *writer) override
  {
    // todo
    return Status::OK;
  }

  Status CreatePin(ServerContext *context, const CreateHalPinRequest *request,
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
};

int main(int argc, char **argv)
{
  std::string address = "0.0.0.0";
  std::string port = "50051";
  std::string server_address = address + ":" + port;

  LinuxCncServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();

  return 0;
}
