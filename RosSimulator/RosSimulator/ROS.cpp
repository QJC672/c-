#include "ROS.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "Message.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

ROS& ROS::GetInstance()
{
    static ROS instance;
    return instance;
}

void ROS::RegisterPublisher(const std::string& topic, Publisher* p)
{
    if (topic.empty()) {
        throw std::invalid_argument("话题名不能为空");
    }
    if (p == nullptr) {
        throw std::invalid_argument("发布者指针不能为空");
    }

    std::vector<Publisher*>& list = publishers_[topic];

    for (Publisher* item : list) {
        if (item == p) {
            throw std::invalid_argument("同一发布者不能重复注册同一话题");
        }
    }
    list.push_back(p);
}

void ROS::RegisterSubscriber(const std::string& topic, Subscriber* s)
{
    if (topic.empty()) {
        throw std::invalid_argument("话题名不能为空");
    }
    if (s == nullptr) {
        throw std::invalid_argument("订阅者指针不能为空");
    }

    std::vector<Subscriber*>& list = subscribers_[topic];

    for (Subscriber* item : list) {
        if (item == s) {
            throw std::invalid_argument("同一订阅者不能重复注册同一话题");
        }
    }
    list.push_back(s);
}

void ROS::UnregisterPublisher(const std::string& topic, Publisher* p)
{
    auto it = publishers_.find(topic);
    if (it == publishers_.end()) {
        return;
    }

    std::vector<Publisher*>& list = it->second;
    list.erase(std::remove(list.begin(), list.end(), p), list.end());

    if (list.empty()) {
        publishers_.erase(it);
    }
}

void ROS::UnregisterSubscriber(const std::string& topic, Subscriber* s)
{
    auto it = subscribers_.find(topic);
    if (it == subscribers_.end()) {
        return;
    }

    std::vector<Subscriber*>& list = it->second;
    list.erase(std::remove(list.begin(), list.end(), s), list.end());

    if (list.empty()) {
        subscribers_.erase(it);
    }
}

void ROS::Publish(const std::string& topic, const Message& msg)
{
    auto it = subscribers_.find(topic);

    if (it == subscribers_.end() || it->second.empty()) {
        std::cout << "[WARN ] 话题 " << topic
            << " 暂无订阅者，消息丢弃: " << msg.GetContent() << std::endl;
        return;
    }

    for (Subscriber* sub : it->second) {
        if (sub != nullptr) {
            sub->OnMessage(msg);
        }
    }
}

void ROS::ShutdownAll()
{
    for (auto& pair : publishers_) {
        for (Publisher* p : pair.second) {
            if (p != nullptr) {
                p->Shutdown();
            }
        }
    }

    for (auto& pair : subscribers_) {
        for (Subscriber* s : pair.second) {
            if (s != nullptr) {
                s->Shutdown();
            }
        }
    }

    publishers_.clear();
    subscribers_.clear();
    std::cout << "[INFO ] 中枢已关闭，注册表已清空" << std::endl;
}