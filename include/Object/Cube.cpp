#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader/shader.hpp"
#include "Object/Drawable.hpp"

class Cube : public Drawable
{
protected:
    GLuint _vao;
    GLuint _vbo_pos;      // 顶点数据
    GLuint _vbo_sur_norm; // 顶点法向量
    GLuint _num_indices;
    GLuint _num_vertices;
    glm::vec3 _color;
    Shader *_cubeShader;
public:
    void init(Shader *shader)
    {
        _cubeShader = shader;
        _sid = shader->ID;
        if (_sid == 0)
        {
            std::cerr << "create water shader create failed" << std::endl;
            exit(-1);
        }
        glUseProgram(_sid);
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        GLfloat indexed_position[] = {
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f};

        GLuint index[] = {
            0, 1, 2, // front
            0, 2, 3,
            1, 5, 6, // right
            1, 6, 2,
            5, 4, 7, // back
            5, 7, 6,
            4, 0, 3, // left
            4, 3, 7,
            3, 2, 6, // top
            3, 6, 7,
            1, 0, 4, // bottom
            1, 4, 5};

        // we need to generate positions one by one in order to have per surface vertex
        GLfloat position[36 * 3];
        for (size_t i = 0; i < 36; i++)
        {
            position[i * 3 + 0] = indexed_position[index[i] * 3 + 0];
            position[i * 3 + 1] = indexed_position[index[i] * 3 + 1];
            position[i * 3 + 2] = indexed_position[index[i] * 3 + 2];
        }
        //为每个顶点设置法向量，顶点着色器后会为每个片段的法向量进行线性插值
        GLfloat per_surface_normals[] = {
            0, 0, 1, 0, 0, 1, 0, 0, 1,
            0, 0, 1, 0, 0, 1, 0, 0, 1,
            1, 0, 0, 1, 0, 0, 1, 0, 0,
            1, 0, 0, 1, 0, 0, 1, 0, 0,
            0, 0, -1, 0, 0, -1, 0, 0, -1,
            0, 0, -1, 0, 0, -1, 0, 0, -1,
            -1, 0, 0, -1, 0, 0, -1, 0, 0,
            -1, 0, 0, -1, 0, 0, -1, 0, 0,
            0, 1, 0, 0, 1, 0, 0, 1, 0,
            0, 1, 0, 0, 1, 0, 0, 1, 0,
            0, -1, 0, 0, -1, 0, 0, -1, 0,
            0, -1, 0, 0, -1, 0, 0, -1, 0};

        glGenBuffers(1, &_vbo_pos);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo_pos);
        glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

        GLuint id_pos = glGetAttribLocation(_sid, "position");




    }
};


