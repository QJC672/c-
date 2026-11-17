#include "Subscriber.h"
#include "ROS.h"
#include <iostream>

Subscriber::Subscriber(const std::string& name, const std::string& topic, Callback callback)
    : Node(name), topic_(topic), callback_(callback)
{
}

void Subscriber::Init()
{
    ROS::GetInstance().RegisterSubscriber(topic_, this);
    SetInitialized(true);
    std::cout << "[INFO ] " << GetName() << " 订阅了 " << topic_ << std::endl;
}

void Subscriber::OnMessage(const Message& msg)
{
    std::cout << "[" << msg.GetTimestamp() << "] " << GetName()
        << " 收到: " << msg.GetContent() << std::endl;

    if (callback_) {
        callback_(msg);
    }
}

void Subscriber::Shutdown()
{
    std::cout << "[INFO ] " << GetName() << " 已停止订阅 " << topic_ << std::endl;
    SetInitialized(false);
}

const std::string& Subscriber::GetTopic() const
{
    return topic_;
}