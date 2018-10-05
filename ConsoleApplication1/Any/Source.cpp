
#include <optional>
#include <exception>
#include <iostream>

int main()
{
    std::optional<int> a;

    static_assert(std::is_same<decltype(a), std::optional<int> >::value);

    try
    {
        if (a == std::nullopt)
        {
            throw std::exception("a is null");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}