#pragma once
#include <iostream>

class Dimensions
{
  public:
    uint m_width;
    uint m_height;

    explicit Dimensions() = default;
    Dimensions(const Dimensions &) = delete;
    Dimensions(uint width, uint height) : m_width(width), m_height(height)
    {
    }
};
