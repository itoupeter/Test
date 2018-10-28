
#include <iostream>
#include <memory>

struct Data
{
    int apple = 1;
    double banana = 3.;
    bool orange = false;
};

std::ostream& operator<<(std::ostream& out, const Data& data)
{
    return out << "apple: " << data.apple
        << "\nbanana: " << data.banana
        << "\norange: " << data.orange;
};

int main()
{
    std::cout << "hello world!" << std::endl;

    auto ptr = std::make_unique<Data>();

    std::cout << *ptr << std::endl;

    return 0;
}