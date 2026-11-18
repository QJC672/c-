#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "exceptions.h"

class Message {
public:
    explicit Message(const std::string& content)
        : content_(content), timestamp_(Now())
    {
        if (content_.empty()) {
            throw MessageException("消息内容不能为空");
        }
    }

    const std::string& GetContent() const { return content_; }
    const std::string& GetTimestamp() const { return timestamp_; }

    virtual ~Message() = default;   // 虚析构：允许派生消息类型被正确析构

private:
    static std::string Now()
    {
        auto tp = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(tp);
        std::tm local{};
        localtime_s(&local, &t);
        std::ostringstream oss;
        oss << std::put_time(&local, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    std::string content_;
    std::string timestamp_;
};