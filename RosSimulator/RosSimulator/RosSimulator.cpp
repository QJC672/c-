#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "Publisher.h"
#include "Subscriber.h"
#include "ROS.h"
#include "TemperatureMessage.h"
#include "Logger.h"

int main()
{
    Publisher tempPub("温度传感器", "sensor/temperature");
    Publisher humPub("湿度传感器", "sensor/humidity");
    Publisher presPub("气压传感器", "sensor/pressure");

    Subscriber tempDisplay("温度显示器A", "sensor/temperature",
        [](const Message& m) {
            if (const auto* t = dynamic_cast<const TemperatureMessage*>(&m)) {
                std::cout << "    -> 显示器A 处理: " << t->GetValue() << " " << t->GetUnit()
                          << (t->GetValue() > 25 ? " (高温!)" : " (正常)") << std::endl;
            }
            else {
                std::cout << "    -> 显示器A 处理: " << m.GetContent() << std::endl;
            }
        });

    Subscriber tempRecorder("温度记录器B", "sensor/temperature",
        [](const Message& m) {
            std::cout << "    -> 记录器B 存档: " << m.GetContent() << std::endl;
        });

    Subscriber humDisplay("湿度显示器", "sensor/humidity",
        [](const Message& m) {
            std::cout << "    -> 湿度显示: " << m.GetContent() << std::endl;
        });

    tempDisplay.Init();
    tempRecorder.Init();
    humDisplay.Init();

    tempPub.Init();
    humPub.Init();
    presPub.Init();

    for (int i = 1; i <= 3; ++i) {
        tempPub.Publish(TemperatureMessage(20 + i + i / 10.0, "C"));
        humPub.Publish(std::to_string(40 + i) + " %");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    presPub.Publish("1013 hPa");

    // 异常演示
    std::cout << "\n===== 异常处理演示 =====" << std::endl;

    // 1：空节点名
    try {
        Publisher badNode("", "sensor/x");
        std::cout << "这行不该出现" << std::endl;
    }
    catch (const RosException& e) {
        Logger::GetInstance().Error(std::string("已拦截 -> ") + e.what());
    }

    // 2：空消息内容
    try {
        tempPub.Publish("");
    }
    catch (const RosException& e) {
        Logger::GetInstance().Error(std::string("已拦截 -> ") + e.what());
    }

    // 3：重复注册
    try {
        tempPub.Init();
    }
    catch (const RosException& e) {
        Logger::GetInstance().Error(std::string("已拦截 -> ") + e.what());
    }

    ROS::GetInstance().ShutdownAll();

    return 0;
}