#pragma once

#include <string>
#include "Core/Resource.hpp"
#include "OpenGL.hpp"

struct Texture : Resource
{
    Texture(const std::string& name, int width, int height, unsigned char pixels[]);

    Texture(const std::string& name, const std::string& imagePath);
    
    ~Texture() override;

    unsigned int GetId() const;

    void Bind(unsigned int unit) const;

private:
    void SetParameters() const;

    unsigned int Id = 0;
};
