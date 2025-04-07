#pragma once

#include <grpcpp/grpcpp.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/impl/service_type.h>
#include <string>
#include <memory>
#include <vector>

#include "server/interceptors.hpp"

class Server
{
public:
    explicit Server(std::string server_address = "0.0.0.0:50051", std::shared_ptr<grpc::Service> service = nullptr, std::string server_name = "Server");

    void Start();
    void Stop();

private:
    std::unique_ptr<grpc::Server> server_;
    std::string server_address_;
    std::string server_name_;
    std::shared_ptr<grpc::Service> service_;
    std::vector<std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>> interceptors_creators_;
};