#pragma once

#include <glad/glad.h>

#include <vector>

#include "fileloader.h"
#include "texture.h"

#define CUBEMAP_SUFFIX_RIGHT "_rt"
#define CUBEMAP_SUFFIX_LEFT "_lf"
#define CUBEMAP_SUFFIX_TOP "_up"
#define CUBEMAP_SUFFIX_BOTTOM "_dn"
#define CUBEMAP_SUFFIX_FRONT "_ft"
#define CUBEMAP_SUFFIX_BACK "_bk"

class Cubemap : public Texture {
   public:
    Cubemap() = delete;
    Cubemap(std::string const& path, std::string const& fileType);

    // Binds this cubemap to the specified texture slot
    Texture* bind(uint32_t t = 0) override;

    /* - Parameter Setters - */

    Texture* setMinMagFilter(GLenum val) override;
    Texture* setWrap(GLenum val) override;

   private:
    void _loadCubemap(std::string const& path, std::string const& fileType);
};