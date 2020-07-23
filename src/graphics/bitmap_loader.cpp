#include <graphics/bitmap_loader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <cstdint>

using namespace tg;

std::unique_ptr<Bitmap> BitmapLoader::load(const std::filesystem::path& p_path)
{
    std::int32_t reqFormat = STBI_rgb_alpha;
    std::int32_t width;
    std::int32_t height;
    std::int32_t origFormat;

    std::uint8_t* imageData = stbi_load(p_path.u8string().c_str(), &width, &height, &origFormat, reqFormat);

    if (!imageData)
    {
        return nullptr;
    }

    std::int32_t         stride;
    Bitmap::EPixelFormat pixelFormat;

    if (reqFormat == STBI_rgb)
    {
        stride = 3 * width;
        pixelFormat = Bitmap::EPixelFormat::RGB;
    }
    else
    {
        stride = 4 * width;
        pixelFormat = Bitmap::EPixelFormat::RGBA;
    }

    std::vector<std::uint8_t> bitmapData(imageData, imageData + stride * height);

    auto result = std::make_unique<Bitmap>(height, width, pixelFormat, std::move(bitmapData), stride);

    stbi_image_free(imageData);

    return result;
}
