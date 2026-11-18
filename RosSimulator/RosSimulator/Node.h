#pragma once

#include <string>
#include "exceptions.h"

class Node {
public:
    explicit Node(const std::string& name)
        : name_(name), initialized_(false)
    {
        if (name.empty()) {
            throw NodeException("节点名不能为空");
        }
    }

    const std::string& GetName() const { return name_; }
    bool IsInitialized() const { return initialized_; }

    virtual void Init() = 0;
    virtual void Shutdown() = 0;

    virtual ~Node() = default;

protected:
    void SetInitialized(bool value) { initialized_ = value; }

private:
    std::string name_;
    bool initialized_ = false;
};
