#pragma once

#include "ShaderSource.hpp"
#include "../Uniform.hpp"
#include "Core/OuterCore/Resource.hpp"
#include "Utilities/CheckedPtr.hpp"

namespace E {
template <typename T>
concept UniformType = std::derived_from<T, Uniform>;

/**
 * @brief Represents an OpenGL shader program.
 * manages the lifetime and use of an OpenGL shader program,
 * including its source files and pending uniform values.
 */
struct Shader : Resource {
    /**
     * @brief Whether the shader supports hot reloading.
     * When enabled, the shader can be reloaded when its source changes.
     */
    bool HotReload = false;

    /**
     * @brief Creates a shader resource.
     * @param name Name used to identify the shader resource.
     */
    Shader(const std::string& name);

    /** @brief Destroys the shader and releases its OpenGL program. */
    ~Shader() override;

    /**
     * @brief Gets the OpenGL shader program ID.
     * @return OpenGL program ID.
     */
    unsigned int GetId() const;

    /** @brief Activates the shader and uploads pending uniforms. */
    void Use();

    /**
     * @brief Queues a uniform for upload.
     *
     * @tparam T Uniform type derived from @ref Uniform.
     * @param uniform Uniform to queue.
     *
     * @note Queued uniforms are uploaded every time the shader is used.
     */
    template <UniformType T> void SetUniform(const T& uniform) {
        PendingUniforms[GetUniformLocation(uniform.Name)] =
            std::make_unique<T>(uniform);
    }

    void AssignSource(ShaderSource& source);

    /**
     * @brief Rebuilds the shader program from its assigned sources.
     * Recompiles and relinks the shader program using the currently
     * assigned shader sources.
     */
    void Reload();

    std::vector<CheckedPtr<ShaderSource>>& GetSources();

private:
    /** @brief OpenGL handle for the shader program. */
    unsigned int Id = 0;

    std::unordered_map<std::string, unsigned int> UniformLocations;

    /**
     * @brief Uniforms waiting to be uploaded to the GPU.
     * Uniforms are stored by their OpenGL uniform location until
     * @ref UploadUniforms() is called.
     */
    std::unordered_map<unsigned int, std::unique_ptr<Uniform>> PendingUniforms;

    std::vector<CheckedPtr<ShaderSource>> Sources;

    void CreateProgram();

    /**
     * @brief Gets and caches the OpenGL location of a uniform.
     * @param name Name of the shader uniform.
     * @return OpenGL uniform location.
     */
    int GetUniformLocation(const std::string& name);

    void UploadUniforms();
};
}
