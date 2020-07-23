#pragma once

#include <graphics/bitmap.h>

#include <filesystem>
#include <memory>

namespace tg
{
    class BitmapLoader
    {
    public:
        static std::unique_ptr<Bitmap> load(const std::filesystem::path& p_path);

    private:
        BitmapLoader() = delete;
    };
}
