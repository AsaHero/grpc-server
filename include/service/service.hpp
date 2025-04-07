#pragma once

#include <unordered_map>
#include <vector>
#include <mutex>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <time.h>

#include <grpcpp/grpcpp.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/server_interface.h>

#include <google/protobuf/map.h>

#include "order_service/order.grpc.pb.h"
#include "order_service/order.pb.h"

namespace os = order_service::v1;

using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerWriter;
using grpc::Status;

class OrderService final : public os::OrderService::Service
{
public:
    OrderService();

    Status Get(ServerContext *ctx, const os::GetRequest *request, os::GetResponse *response) override;
    Status List(ServerContext *ctx, const os::ListRequest *request, os::ListResponse *response) override;
    Status Create(ServerContext *ctx, const os::CreateRequest *request, os::CreateResponse *response) override;
    Status Update(ServerContext *ctx, const os::UpdateRequest *request, os::UpdateResponse *response) override;
    Status StreamOrderUpdated(ServerContext *ctx, const os::StreamOrderUpdateRequest *request, ServerWriter<os::StreamOrderUpdateResponse> *writer) override;

private:
    // Mock the orders
    std::unordered_map<std::string, os::Order> orders_;
    std::unordered_map<std::string, std::vector<std::string>> user_orders_;
    std::mutex mutex_;

    static std::string generate_id();
    static int64_t get_current_timestamp();
};