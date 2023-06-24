#pragma once

#include <string>
#include <GL/gl.h>

class Texture {
public:
    explicit Texture(const std::string& location);
    ~Texture();

    void use(unsigned int slot = 0) const;
    static void unbind();

private:
    GLuint textureId = 0;
    int    width     = 0;
    int    height    = 0;
    int    channels  = 0;
};