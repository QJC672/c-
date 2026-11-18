#include "Publisher.h"
#include "ROS.h"
#include "Message.h"
#include <iostream>
#include "Logger.h"

Publisher::Publisher(const std::string& name, const std::string& topic)
    : Node(name), topic_(topic)
{
}

void Publisher::Init()
{
    ROS::GetInstance().RegisterPublisher(topic_, this);
    SetInitialized(true);
    Logger::GetInstance().Log("INFO ", GetName() + " 发布话题 " + topic_);
}

void Publisher::Publish(const std::string& data)
{
    Publish(Message(data));        // 复用重载版本：字符串先包装成 Message
}

void Publisher::Publish(const Message& msg)
{
    if (!IsInitialized()) {
        Logger::GetInstance().Log("WARN ", GetName() + " 尚未 Init，消息被丢弃");
        return;
    }
    Logger::GetInstance().Log("INFO ", GetName() + " 发布 -> " + topic_ + " : " + msg.GetContent());
    ROS::GetInstance().Publish(topic_, msg);
}

void Publisher::Shutdown()
{
    Logger::GetInstance().Log("INFO ", GetName() + " 已停止发布 " + topic_);
    SetInitialized(false);
}

const std::string& Publisher::GetTopic() const
{
    return topic_;
}