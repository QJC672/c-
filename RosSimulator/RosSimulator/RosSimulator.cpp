#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "Publisher.h"
#include "Subscriber.h"
#include "ROS.h"

int main()
{
    Publisher tempPub("温度传感器", "sensor/temperature");
    Publisher humPub("湿度传感器", "sensor/humidity");
    Publisher presPub("气压传感器", "sensor/pressure");

    Subscriber tempDisplay("温度显示器A", "sensor/temperature",
        [](const Message& m) {
            std::cout << "    -> 显示器A 处理: " << m.GetContent() << std::endl;
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
        tempPub.Publish(std::to_string(20 + i) + "." + std::to_string(i) + " C");
        humPub.Publish(std::to_string(40 + i) + " %");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    presPub.Publish("1013 hPa");

    ROS::GetInstance().ShutdownAll();

    return 0;
}