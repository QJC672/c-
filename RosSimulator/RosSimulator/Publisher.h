#pragma once

#include "Node.h"
#include <string>

class Message;          // 前置声明：Publish 的重载参数用到
class Publisher : public Node {
public:
    Publisher(const std::string& name, const std::string& topic);

    void Init() override;
    void Publish(const std::string& data);
    void Publish(const Message& msg);      // 重载：直接发送已构造好的消息
    void Shutdown() override;

    const std::string& GetTopic() const;

private:
    std::string topic_;
};