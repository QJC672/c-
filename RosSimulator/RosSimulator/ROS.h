#pragma once

#include <string>
#include <map>
#include <vector>

//前置说明
class Publisher;
class Subscriber;
class Message;

class ROS {
public:
    static ROS& GetInstance();

    void RegisterPublisher(const std::string& topic, Publisher* p);
    void RegisterSubscriber(const std::string& topic, Subscriber* s);

    void UnregisterPublisher(const std::string& topic, Publisher* p);
    void UnregisterSubscriber(const std::string& topic, Subscriber* s);

    void Publish(const std::string& topic, const Message& msg);

    void ShutdownAll();

private:
    ROS() = default;
    ~ROS() = default;
    ROS(const ROS&) = delete;
    ROS& operator=(const ROS&) = delete;

    std::map<std::string, std::vector<Publisher*>>  publishers_;
    std::map<std::string, std::vector<Subscriber*>> subscribers_;
};