#pragma once

#include "Node.h"
#include <string>

class Publisher : public Node {
public:
    Publisher(const std::string& name, const std::string& topic);

    void Init() override;
    void Publish(const std::string& data);
    void Shutdown() override;

    const std::string& GetTopic() const;

private:
    std::string topic_;
};