#pragma once

#include <stdexcept>
#include <string>

// ① 基类
class RosException : public std::runtime_error {
public:
    explicit RosException(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

// ② 空名、重复注册、空指针
class NodeException : public RosException {
public:
    explicit NodeException(const std::string& msg)
        : RosException(msg)
    {
    }
};

// ③ 空话题名
class TopicException : public RosException {
public:
    explicit TopicException(const std::string& msg)
        : RosException(msg)
    {
    }
};

// ④ 空内容
class MessageException : public RosException {
public:
    explicit MessageException(const std::string& msg)
        : RosException(msg)
    {
    }
};