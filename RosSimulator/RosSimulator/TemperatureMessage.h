#pragma once

#include "Message.h"
#include <string>
#include <sstream>
#include <iomanip>

// 自定义消息类型：在 Message 基础上携带结构化的温度数据（加分项 10.3）
class TemperatureMessage : public Message {
public:
    TemperatureMessage(double value, const std::string& unit)
        : Message(FormatValue(value) + " " + unit)   // 内容字符串自动拼装
        , value_(value)
        , unit_(unit)
    {
    }

    double GetValue() const { return value_; }
    const std::string& GetUnit() const { return unit_; }

private:
    // 把 21.100000 格式化成 21.1
    static std::string FormatValue(double value)
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << value;
        return oss.str();
    }

    double value_;
    std::string unit_;
};
