#include <graphics/bitmap.h>

#include <cassert>

using namespace tg;

std::uint8_t Bitmap::at(std::int32_t p_row, std::int32_t p_col, std::int32_t p_comp) const
{
    assert(p_row < m_rows);
    assert(p_col < m_cols);
    assert(p_comp < static_cast<std::int32_t>(m_format));
    return m_data[p_row * m_stride + p_col * static_cast<std::int32_t>(m_format) + p_comp];
}

std::uint8_t& Bitmap::at(std::int32_t p_row, std::int32_t p_col, std::int32_t p_comp)
{
    assert(p_row < m_rows);
    assert(p_col < m_cols);
    assert(p_comp < static_cast<std::int32_t>(m_format));
    return m_data[p_row * m_stride + p_col * static_cast<std::int32_t>(m_format) + p_comp];
}
