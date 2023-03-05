#pragma once

#include "Mint/Core/Base.h"

#include <string>

namespace mint
{

    class Texture
    {
      public:
        virtual ~Texture() = default;

        virtual uint32_t getWidth() const                     = 0;
        virtual uint32_t getHeight() const                    = 0;
        virtual std::pair<uint32_t, uint32_t> getSize() const = 0;

        virtual void setData(void* data, size_t size) = 0;

        virtual void bind(uint32_t slot = 0) const = 0;

        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture
    {
      public:
        static Ref<Texture2D> create(uint32_t width, uint32_t height);
        static Ref<Texture2D> create(const std::string& path);
    };


} // namespace mint
