#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "mesh_shader.h"

GLuint MeshShader::vaoId = -1;

static int A_POSITIONS_LOCATION = 0;
static int A_UV_LOCATION = 1;
static int U_TRANSFORM_LOCATION = 2;
static int U_SAMPLER_2D_LOCATION = 3;

void MeshShader::init() {
    // Check if already initialized
    if (MeshShader::vaoId != -1) return;

    // Create VAO
    glGenVertexArrays(1, &MeshShader::vaoId);

    glBindVertexArray(MeshShader::vaoId);

    glEnableVertexAttribArray(A_POSITIONS_LOCATION);
    glEnableVertexAttribArray(A_UV_LOCATION);

    glVertexAttribFormat(A_POSITIONS_LOCATION, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(A_POSITIONS_LOCATION, 0);

    glVertexAttribFormat(A_UV_LOCATION, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(A_UV_LOCATION, 1);

    glBindVertexArray(0);
}

void MeshShader::cleanUp() {
    if (MeshShader::vaoId < 0) return;
    glDeleteVertexArrays(1, &MeshShader::vaoId);
    MeshShader::vaoId = -1;
}

void MeshShader::compile(const std::string &vertexSource, const std::string &fragmentSource) {
    programHandle = createProgram(vertexSource, fragmentSource);
}

void MeshShader::use(const Mesh& mesh, const glm::mat4 &transformMatrix) const {
    glBindVertexArray(vaoId); // change to check first before binding
    glUseProgram(programHandle);

    // Upload transform matrix
    glUniformMatrix4fv(U_TRANSFORM_LOCATION, 1, GL_FALSE, glm::value_ptr(transformMatrix));

    // Upload attributes
    glBindVertexBuffer(A_POSITIONS_LOCATION, mesh.positionsVBOHandle, 0, mesh.positionsVBOStride);
    glBindVertexBuffer(A_UV_LOCATION, mesh.uvVBOHandle, 0, mesh.uvVBOStride);

    // Set Sampler2D uniform
    glUniform1i(U_SAMPLER_2D_LOCATION, 0);

    // Use indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indicesIBOHandle);
}

GLuint MeshShader::createProgram(const std::string &vertexSource, const std::string &fragmentSource) {
    GLuint programHandle = glCreateProgram();

    GLuint vertexShaderHandle = createShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragShaderHandle = createShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(programHandle, vertexShaderHandle);
    glAttachShader(programHandle, fragShaderHandle);

    glLinkProgram(programHandle);
    glValidateProgram(programHandle);

    glDeleteShader(vertexShaderHandle);
    glDeleteShader(fragShaderHandle);

    return programHandle;
}

GLuint MeshShader::createShader(GLenum shaderType, const std::string &source) {
    GLuint shaderHandle = glCreateShader(shaderType);
    const char *src = source.c_str();
    glShaderSource(shaderHandle, 1, &src, nullptr);
    glCompileShader(shaderHandle);

    int compileResult;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileResult);
    if (!compileResult) {
        int length;
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(shaderHandle, length, &length, message);
        printf("[-] Shader compilation failed: %s\n", message);
        return 0;
    }

    printf("[+] Shader compilation completed\n");

    return shaderHandle;
}