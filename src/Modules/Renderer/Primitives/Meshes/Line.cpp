#include "../Primitives.hpp"
#include "Core/InnerCore/Engine.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Utilities/Math/Color.hpp"


Mesh& Primitives::CreateLine(const std::string& name) {
    std::vector<Vertex> vertices = {
        Vertex({0, 0, 0, 1}, {1}, {0}, {0, 0, 1}), Vertex({0, 0, 1, 1}, {1}, {0}, {0, 0, 1})
    };
    std::vector<unsigned int> indices = {0, 1};

    Mesh& mesh = ServiceStore::Ins->Get<ResourceManager>().Load<Mesh>(name, vertices, indices);
    mesh.Topology = Topology::Lines;
    return mesh;
}
