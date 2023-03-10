//
// Created by Arthur Zerr on 04.02.23.
//

#include "EBO.h"

Engine::Core::EBO::EBO(std::vector<GLuint> &indices) {
    glGenBuffers(1, &Id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id); // Bind the EBO as the current buffer to modify
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(),
                 GL_STATIC_DRAW); // Binds the indicies to the current bind buffer
}


void Engine::Core::EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id); // Bind the EBO as the current buffer to modify

}

void Engine::Core::EBO::UnBind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind after VAO !
}

void Engine::Core::EBO::Dispose() {
    glDeleteBuffers(1, &Id);
}

