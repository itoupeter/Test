
#include "Circle.h"

#include <iostream>

// ---Impl---
class Circle::Impl
{
public:
    const auto GetRadius() const;
    void SetRadius(const double radius);

private:
    double m_radius;
};

const auto Circle::Impl::GetRadius() const
{
    return m_radius;
}

void Circle::Impl::SetRadius(const double radius)
{
    m_radius = radius;
}

// ---Circle---
Circle::Circle(const double radius) 
    : pImpl{std::make_unique<Impl>()}
{
    SetRadius(radius);
}

Circle::~Circle() = default;

const double Circle::GetRadius() const
{
    return pImpl->GetRadius();
}

void Circle::SetRadius(const double radius)
{
    pImpl->SetRadius(radius);
}
