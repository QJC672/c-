#include <iostream>
#include "Message.h"        // 双引号 = 在本目录找自己的头文件

int main()
{
    Message m("25.6 C");
    std::cout << "[" << m.GetTimestamp() << "] 消息内容: " << m.GetContent() << std::endl;
    return 0;
}
