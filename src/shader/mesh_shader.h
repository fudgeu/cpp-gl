#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include "shader.h"

class MeshShader : Shader {
  static GLuint vaoId;

  public:
    static void init();
    static void cleanUp();
    
    void compile(const std::string &vertexSource, const std::string &fragmentSource);
    void use(const Mesh& mesh, const glm::mat4 &transformMatrix) const override;

  private:
    GLuint programHandle = -1;
    static GLuint createProgram(const std::string &vertexSource, const std::string &fragmentSource);
    static GLuint createShader(GLenum shaderType, const std::string &source);
};