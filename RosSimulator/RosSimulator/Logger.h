#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

inline std::string Now()
{
    auto tp = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::tm local{};
    localtime_s(&local, &t);
    std::ostringstream oss;
    oss << std::put_time(&local, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

class Logger {
public:
    static Logger& GetInstance()
    {
        static Logger inst;
        return inst;
    }

    // 分级便捷接口：Logger::GetInstance().Info("...") 等
    void Info(const std::string& msg)  { Log("INFO ", msg); }
    void Warn(const std::string& msg)  { Log("WARN ", msg); }
    void Error(const std::string& msg) { Log("ERROR", msg); }

    void Log(const std::string& level, const std::string& msg)
    {
        std::cout << "[" << level << "] " << Now() << " " << msg << std::endl;
        if (file_.is_open()) {
            file_ << "[" << level << "] " << Now() << " " << msg << '\n';
            file_.flush();
        }
    }

private:
    Logger()
    {
        file_.open("run.log", std::ios::app);
    }
    ~Logger() { if (file_.is_open()) file_.close(); }
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::ofstream file_;
};