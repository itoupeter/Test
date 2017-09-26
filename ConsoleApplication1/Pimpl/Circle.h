#pragma once

#include <memory>

class Circle
{
public:
    Circle(const double radius);
    ~Circle(); // dtor has to be defined manually in cpp (even default), or unique_ptr to Impl doesn't compile

    Circle(const Circle&) = delete;
    Circle& operator=(Circle&) = delete;

    const double GetRadius() const;
    void SetRadius(const double radius);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};