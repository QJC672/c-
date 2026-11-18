#include "Subscriber.h"
#include "ROS.h"
#include <iostream>
#include "Logger.h"

Subscriber::Subscriber(const std::string& name, const std::string& topic, Callback callback)
    : Node(name), topic_(topic), callback_(callback)
{
}

void Subscriber::Init()
{
    ROS::GetInstance().RegisterSubscriber(topic_, this);
    SetInitialized(true);
    Logger::GetInstance().Log("INFO ", GetName() + " 订阅了 " + topic_);
}

void Subscriber::OnMessage(const Message& msg)
{
    Logger::GetInstance().Log("INFO ",
        "[" + msg.GetTimestamp() + "] " + GetName() + " 收到: " + msg.GetContent());

    if (callback_) {
        callback_(msg);
    }
}

void Subscriber::Shutdown()
{
    Logger::GetInstance().Log("INFO ", GetName() + " 已停止订阅 " + topic_);
    SetInitialized(false);
}

const std::string& Subscriber::GetTopic() const
{
    return topic_;
}