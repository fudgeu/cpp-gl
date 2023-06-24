#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string>

#include "engine.h"
#include "render/render_system.h"
#include "shader/mesh_shader.h"

bool initGL();
GLuint createProgram(std::string vertexSource, std::string fragmentSource);
GLuint createShader(GLenum shaderType, std::string source);

const std::string WINDOW_TITLE = "ooie gooie";
const int SCREEN_W = 1280;
const int SCREEN_H = 720;

int lastKnownWidth  = SCREEN_W;
int lastKnownHeight = SCREEN_H;

struct VAOConfig {
  int     positionsAttribLoc;
  int     colorsAttribLoc;
  GLuint  VAOHandle;
};

//static Engine engine;

int main() {

  Result initSucceeded = Engine::initialize(
    WINDOW_TITLE,
    SCREEN_W,
    SCREEN_H
  );

  if (!initSucceeded) {
    printf("[-] Fatal error, closing application");
    return 1;
  }

  Engine& engine = Engine::getInstance();

  engine.startLoop();

  // Exit

  Engine::cleanUp();
  SDL_DestroyWindow(engine.window);
  SDL_Quit();

  return 0;
}