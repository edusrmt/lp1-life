#include <iostream>
#include <vector>
#include <cstring>

#include "../include/common.hpp"
#include "../include/lodepng.h"
#include "../include/canvas.hpp"

namespace life
{
    void Canvas::pixel(const Point2 &point, const Color &color)
    {
        for (int j = 0; j < m_block_size; j++)
        {
            for (int i = 0; i < m_block_size; i++)
            {
                const int indexZero = point.x * image_depth * m_block_size + point.y * m_width * image_depth * m_block_size + i * image_depth + j * m_width * image_depth;
                m_pixels[indexZero] = color.channels[0];
                m_pixels[indexZero + 1] = color.channels[1];
                m_pixels[indexZero + 2] = color.channels[2];
                m_pixels[indexZero + 3] = 255;
            }
        }
    }

    
} // namespace life