#pragma once

#include "Node.h"
#include "Message.h"
#include <string>
#include <functional>

class Subscriber : public Node {
public:
    using Callback = std::function<void(const Message&)>;

    Subscriber(const std::string& name, const std::string& topic, Callback callback);

    void Init() override;
    void Shutdown() override;

    void OnMessage(const Message& msg);

    const std::string& GetTopic() const;

private:
    std::string topic_;
    Callback callback_;
};