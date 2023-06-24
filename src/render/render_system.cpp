#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "render_system.h"

static int U_MESH_PERSPECTIVE_LOCATION = 0;
static int U_MESH_VIEW_LOCATION = 1;

RenderSystem::RenderSystem(ShaderRegistry &shaderRegistry) :
        shaderReg(shaderRegistry) {}

void RenderSystem::render(Camera &camera) {
    int windowWidth = camera.getScreenWidth();
    int windowHeight = camera.getScreenHeight();

    // Clear screen
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0, 0, 0, 1);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Pass in camera uniform

    glUniformMatrix4fv(U_MESH_PERSPECTIVE_LOCATION, 1, GL_FALSE, glm::value_ptr(camera.getPerspectiveMatrix())); // perspective
    glUniformMatrix4fv(U_MESH_VIEW_LOCATION, 1, GL_FALSE, glm::value_ptr(camera.getTransformMatrix())); // view
    // model


    for (const auto& object: renderQueue) {

        //glBindVertexBuffer(0, mesh.positionsVBOHandle, 0, mesh.positionsVBOStride);
        //glBindVertexBuffer(1, mesh.colorsVBOHandle, 0, mesh.colorsVBOStride);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indicesIBOHandle);

        // Create and upload transform matrix for object
        double x = object.getX() * SCREEN_SPACE_SCALE;
        double y = object.getY() * SCREEN_SPACE_SCALE;
        glm::mat4 transformMat = glm::mat4x4(1.0);
        transformMat = glm::translate(transformMat, glm::vec3(x, y, 0.0));

        //glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(transformMat));

        for (const auto& shadedMesh : object.getModel().getShadedMeshes()) {
            //const string& shaderId = shadedMesh.getShaderId();
            const MeshShader& shader = shadedMesh.getShader();
            const Mesh& mesh = shadedMesh.getMesh();
            const Texture& texture = shadedMesh.getTexture();

            /*std::optional<MeshShader> shaderOpt = shaderReg.getMeshShader(shaderId);
            assert(shaderOpt.has_value());
            MeshShader shader = shaderOpt.value();
            shader.use(mesh);*/

            shader.use(mesh, transformMat);
            texture.use();

            glDrawElements(GL_TRIANGLES, mesh.countIndices, GL_UNSIGNED_INT, nullptr);
        }

        //basicShader.use(mesh);

        //printf("%d\n", mesh.countIndices);
        //glDrawElements(GL_TRIANGLES, mesh.countIndices, GL_UNSIGNED_INT, nullptr);
    }

    // End render
    renderQueue.clear();
}

void RenderSystem::addToQueue(const Object &object) {
    renderQueue.push_back(object);
}