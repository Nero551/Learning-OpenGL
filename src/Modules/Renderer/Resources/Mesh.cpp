#include <OpenGL.hpp>
#include "Mesh.hpp"

Mesh::Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) :
    Resource(name),
    Vertices(vertices), Indices(indices) {
    CreateVAO();
    CreateVBO();
    CreateEBO();
    SetupVertAttrPointers();
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &Id);
}

unsigned int Mesh::GetId() const {
    return Id;
}

void Mesh::Draw() {
    if (Wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glBindVertexArray(Id);
    glDrawElements(static_cast<int>(Topology), Indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::CreateVAO() {
    glGenVertexArrays(1, &Id);
    glBindVertexArray(Id);
}

void Mesh::CreateVBO() {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
}

void Mesh::CreateEBO() {
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);
}

void Mesh::SetupVertAttrPointers() {
    // Position
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, Position)));
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Color)));
    glEnableVertexAttribArray(1);

    // UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, UV)));
    glEnableVertexAttribArray(2);

    //Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));
    glEnableVertexAttribArray(3);
}
