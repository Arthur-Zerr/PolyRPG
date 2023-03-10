//
// Created by Arthur Zerr on 06.02.23.
//

#include "Mesh.h"

Engine::Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    this->vao.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    Engine::Core::VBO vbo(vertices);
    // Generates Element Buffer Object and links it to indices
    Engine::Core::EBO ebo(indices);

    // Links vbo to this->vao
    this->vao.LinkAttribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *) 0);
    this->vao.LinkAttribute(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void *) (3 * sizeof(float)));
    this->vao.LinkAttribute(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void *) (6 * sizeof(float)));
    this->vao.LinkAttribute(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void *) (9 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    vao.UnBind();
    vbo.UnBind();
    ebo.UnBind();
}

void Engine::Mesh::Draw(
        Shader &shader,
        Camera &camera,
        glm::mat4 matrix,
        glm::vec3 translation,
        glm::quat rotation,
        glm::vec3 scale
)
{
    shader.Activate();
    this->vao.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i = 0; i < textures.size(); ++i)
    {
        Texture texture = textures[i];

        std::string num;
        std::string type = texture.type;

        if (type == "diffuse")
        {
            num = std::to_string(numDiffuse++);
        } else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        texture.textUnit(shader, (type + num).c_str(), i);
        texture.Bind();
    }
    glUniform3f(glGetUniformLocation(shader.Id, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    // Initialize matrices
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    // Transform the matrices to their correct form
    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

    // Push the matrices to the vertex shader
    glUniformMatrix4fv(glGetUniformLocation(shader.Id, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.Id, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(shader.Id, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
    glUniformMatrix4fv(glGetUniformLocation(shader.Id, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
