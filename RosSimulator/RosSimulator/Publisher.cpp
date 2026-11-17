#include "Publisher.h"
#include "ROS.h"
#include "Message.h"
#include <iostream>

Publisher::Publisher(const std::string& name, const std::string& topic)
    : Node(name), topic_(topic)
{
}

void Publisher::Init()
{
    ROS::GetInstance().RegisterPublisher(topic_, this);
    SetInitialized(true);
    std::cout << "[INFO ] " << GetName() << " 发布话题 " << topic_ << std::endl;
}

void Publisher::Publish(const std::string& data)
{
    if (!IsInitialized()) {
        std::cout << "[WARN ] " << GetName() << " 尚未 Init，消息被丢弃" << std::endl;
        return;
    }
    Message msg(data);
    std::cout << "[INFO ] " << GetName() << " 发布 -> " << topic_ << " : " << data << std::endl;
    ROS::GetInstance().Publish(topic_, msg);
}

void Publisher::Shutdown()
{
    std::cout << "[INFO ] " << GetName() << " 已停止发布 " << topic_ << std::endl;
    SetInitialized(false);
}

const std::string& Publisher::GetTopic() const
{
    return topic_;
}