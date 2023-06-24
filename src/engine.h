#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

#include "render/render_system.h"
#include "camera/camera.h"
#include "shader/shader_registry.h"
#include "entity/player.h"
#include "event/key_event_handler.h"
#include "enum/result.h"
#include "world/world.h"

class Engine {
  private:
    Engine(const std::string& windowTitle, int screenW, int screenH);
    inline static Engine* instance;
    ~Engine();

  public:
    static Result  initialize(const std::string& windowTitle, int screenW, int screenH);
    static Engine& getInstance();
    static void    cleanUp();

    // Subsystem references
    ShaderRegistry*  shaderRegistry;
    RenderSystem*    renderSystem;
    KeyEventHandler* keyEventHandler;

    SDL_Window* window        = nullptr;
    Camera*     currentCamera = nullptr;
    World*      testWorld     = nullptr;
    std::shared_ptr<Player> player = nullptr;

    void startLoop();

    // Singleton pattern
    Engine(Engine const&)         = delete;
    void operator=(Engine const&) = delete;

  private:
    std::string windowTitle;
    int         screenWidth;
    int         screenHeight;

    Result initSuccessful  = ERROR;
    bool   running         = false;
    int    lastKnownWidth  = 0;
    int    lastKnownHeight = 0;
    Uint64 loopStart       = 0;

    Result internalInitFramework();
    Result internalInitWindow(const std::string& title, int screenW, int screenH);
    Result internalInitGL();
    Result internalInitRenderSystem();
    Result internalInitCamera();
    Result internalInitShaders();
    Result internalInitMeshes();
    Result internalInitEventSystem();
    void   doLoop();
};