#pragma once
#include "../Vertex.hpp"
#include "Core/OuterCore/Resource.hpp"


#include "../Enums/Topology.hpp"

struct Mesh : Resource {
    bool Wireframe = false;
    Topology Topology = Topology::Triangles;

    Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    ~Mesh() override;

    [[nodiscard]] unsigned int GetId() const;

    void Draw();

private:
    unsigned int Id = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    void CreateVAO();

    void CreateVBO();

    void CreateEBO();

    void SetupVertAttrPointers();
};
