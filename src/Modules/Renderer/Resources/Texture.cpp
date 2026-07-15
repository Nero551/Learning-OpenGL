#include <OpenGL.hpp>
#include "Texture.hpp"
#include <iostream>
#include <string>
#include "Utilities/Image/Image.hpp"
#include "Utilities/Logger.hpp"

Texture::Texture(const std::string& name, int width, int height, unsigned char pixels[]) :
    Resource(name) {
    glGenTextures(1, &Id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Id);

    SetParameters();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string& name, const std::string& imagePath) :
    Resource(name) {
    glGenTextures(1, &Id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Id);

    SetParameters();

    Image image(imagePath, true);

    GLenum format = GL_RED;

    switch (image.NrChannels) {
    case 1: format = GL_RED;
        break;
    case 3: format = GL_RGB;
        break;
    case 4: format = GL_RGBA;
        break;
    default: Logger::Error("Unsupported Texture Channel Count");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), image.Width, image.Height, 0, format, GL_UNSIGNED_BYTE,
        image.Data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &Id);
}

unsigned int Texture::GetId() const { return Id; }

void Texture::Bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, Id);
}

void Texture::SetParameters() const {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
