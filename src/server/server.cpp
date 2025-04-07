#include "server/server.hpp"

Server::Server(std::string server_address, std::shared_ptr<grpc::Service> service, std::string server_name) : server_address_(server_address), service_(service), server_name_(server_name)
{
    this->interceptors_creators_.emplace_back(std::make_unique<LoggerInterceptorFactory>());
}

void Server::Start()
{
    grpc::ServerBuilder builder;

    // Adding the listening port
    builder.AddListeningPort(this->server_address_, grpc::InsecureServerCredentials());

    // Registering the service
    builder.RegisterService(this->service_.get());

    // Setting interceptors for the server
    builder.experimental().SetInterceptorCreators(std::move(this->interceptors_creators_));

    // Building and starting the server
    this->server_ = builder.BuildAndStart();

    std::cout << this->server_name_ << " listening on " << this->server_address_ << std::endl;

    // Waiting for the server to shutdown
    this->server_->Wait();
}

void Server::Stop()
{
    std::cout << this->server_name_ << " shutting down, please wait..." << std::endl;
    this->server_->Shutdown();
    std::cout << this->server_name_ << " shutdown" << std::endl;
}
