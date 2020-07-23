#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace tg
{
    class Bitmap
    {
    public:
        enum class EPixelFormat
        {
            RGB = 3,
            RGBA = 4
        };

    public:
        Bitmap(std::int32_t              p_rows,
               std::int32_t              p_cols,
               EPixelFormat              p_format,
               std::vector<std::uint8_t> p_data,
               std::size_t               p_stride)
            : m_rows(p_rows)
            , m_cols(p_cols)
            , m_format(p_format)
            , m_data(std::move(p_data))
            , m_stride(p_stride)
        {}

        std::int32_t        rows() const { return m_rows; }
        std::int32_t        cols() const { return m_cols; }
        EPixelFormat        format() const { return m_format; }
        const std::uint8_t* data() const { return m_data.data(); }
        std::size_t         stride() const { return m_stride; }

        std::uint8_t  at(std::int32_t p_row, std::int32_t p_col, std::int32_t p_comp) const;
        std::uint8_t& at(std::int32_t p_row, std::int32_t p_col, std::int32_t p_comp);

    private:
        std::int32_t              m_rows;
        std::int32_t              m_cols;
        EPixelFormat              m_format;
        std::vector<std::uint8_t> m_data;
        std::size_t               m_stride;
    };
}
