#include <iostream>
#include "texture.h"
#include "../extern/stb_image/stb_image.h"

Texture::Texture(const std::string& location) {
    // load texture
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(location.c_str(), &width, &height, &channels, 4);

    if (data == nullptr) {
        printf("[-] Error loading image for texture: %s\n", stbi_failure_reason());
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    if (data) {
        stbi_image_free(data);
    }
}

Texture::~Texture() {
    // implement smart pointers first
    //glDeleteTextures(1, &textureId);
}

void Texture::use(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
