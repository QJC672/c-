#include <iostream>
#include "Node.h"

class TestNode : public Node {
public:
    explicit TestNode(const std::string& n) : Node(n) {}

    void Init() override {
        SetInitialized(true);
        std::cout << GetName() << " 已启动" << std::endl;
    }
    void Shutdown() override {
        SetInitialized(false);
        std::cout << GetName() << " 已关闭" << std::endl;
    }
};

int main()
{
    TestNode t("测试节点");
    std::cout << "名字: " << t.GetName() << "，已启动? " << t.IsInitialized() << std::endl;
    t.Init();
    t.Shutdown();
    return 0;
}
