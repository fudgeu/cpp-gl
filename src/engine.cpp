#include "engine.h"
#include "model/model.h"
#include "object/object.h"
#include "world/world.h"
#include "model/model_factory.h"
#include "texture/texture.h"
#include "model/bound_checker.h"

#include <utility>
#include <iostream>
#include <memory>
#include <filesystem>

static int WINDOW_FLAGS = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
static int WINDOW_POS = SDL_WINDOWPOS_CENTERED;
static int GL_MAJOR_VER = 4;
static int GL_MINOR_VER = 3;
static int GL_PROFILE = SDL_GL_CONTEXT_PROFILE_CORE;

Engine::Engine(const std::string &windowTitle, int screenW, int screenH) {
    this->windowTitle = windowTitle;
    this->screenWidth = screenW;
    this->screenHeight = screenH;

    bool initSucceeded =
            internalInitFramework() &&
            internalInitWindow(windowTitle, screenWidth, screenHeight) &&
            internalInitGL() &&
            internalInitShaders() &&
            internalInitMeshes() &&
            internalInitRenderSystem() &&
            internalInitEventSystem() &&
            internalInitCamera();

    initSuccessful = initSucceeded ? SUCCESS : ERROR;
}

Result Engine::initialize(const std::string &windowTitle, int screenW, int screenH) {
    instance = new Engine(windowTitle, screenW, screenH);

    if (instance->initSuccessful) {
        printf("[+] Engine init complete\n");
    } else {
        printf("[-] Engine init failed - see logs for more details\n");
    }

    return instance->initSuccessful;
}

Engine &Engine::getInstance() {
    assert(instance != nullptr);
    return *instance;
}

// Internal initializers

Result Engine::internalInitFramework() {
    int res = SDL_Init(SDL_INIT_VIDEO);

    if (res < 0) {
        printf("[-] SDL Base init failed: %s\n", SDL_GetError());
        return ERROR;
    }

    printf("[+] SDL Base init complete\n");
    return SUCCESS;
}

Result Engine::internalInitWindow(const std::string &title, int screenW, int screenH) {
    window = SDL_CreateWindow(
            title.c_str(),
            WINDOW_POS,
            WINDOW_POS,
            screenW,
            screenH,
            WINDOW_FLAGS
    );

    if (window == nullptr) {
        printf("[-] SDL Window init failed: %s\n", SDL_GetError());
        return ERROR;
    }

    printf("[+] SDL Window init complete\n");
    return SUCCESS;
}

Result Engine::internalInitGL() {
    // Init OpenGL + context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR_VER);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR_VER);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, GL_PROFILE);
    SDL_GL_SetSwapInterval(0); // Disable Vsync, for now

    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (glContext == nullptr) {
        printf("[-] OpenGL context creation failed: %s\n", SDL_GetError());
        return ERROR;
    }

    printf("[+] OpenGL context creation complete\n");

    // Init GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK) {
        printf("[-] GLEW init failed: %s\n", glewGetErrorString(glewError));
        return ERROR;
    }

    printf("[+] GLEW init complete\n");
    return SUCCESS;
}

Result Engine::internalInitRenderSystem() {
    renderSystem = new RenderSystem(*shaderRegistry); // init for first time
    return SUCCESS;
}

Result Engine::internalInitCamera() {
    currentCamera = new Camera(0, 0, -5, 65, screenWidth, screenHeight);
    currentCamera->attachToEntity(player);
    return SUCCESS;
}

Result Engine::internalInitShaders() {
    shaderRegistry = new ShaderRegistry();

    MeshShader::init();

    std::string vertexShader =
            "#version 330 core\n"
            "#extension GL_ARB_explicit_uniform_location: enable\n"

            "layout(location = 0) uniform mat4 perspectiveMat;\n"
            "layout(location = 1) uniform mat4 viewMat;\n"
            "layout(location = 2) uniform mat4 transformMat;\n"
            "layout(location = 0) in vec4 position;\n"
            "layout(location = 1) in vec2 uvIn;\n"

            "out vec2 uv;\n"

            "void main() {\n"
            " uv = uvIn;"
            " gl_Position = perspectiveMat * viewMat * transformMat * position;\n"
            "}\n";

    std::string fragmentShader =
            "#version 330 core\n"
            "#extension GL_ARB_explicit_uniform_location: enable\n"

            "layout(location = 3) uniform sampler2D texture1;\n"
            "in vec2 uv;\n"

            "out vec4 colorOut;\n"

            "void main() {\n"
            " colorOut = texture(texture1, uv);\n"
            " //colorOut = vec4(1.0,1.0,1.0,1.0);\n"
            "}\n";

    MeshShader basicShader; // make into opt
    basicShader.compile(vertexShader, fragmentShader);
    shaderRegistry->registerMeshShader("basic", basicShader);

    return SUCCESS;
}

Result Engine::internalInitMeshes() {
    Texture testTexture("resources/obama.png");
    Texture testTexture2("resources/grass.png");

    auto shaderOpt = shaderRegistry->getMeshShader("basic");
    if (!shaderOpt.has_value()) {
        printf("[-] Failed to create test model, could not load shader required\n");
        return ERROR;
    }
    const MeshShader& shader = shaderOpt.value().get(); // unpack optional, then reference wrapper

    testWorld = new World();

    //Model rectModel = ModelFactory::create(1, 5, shader, testTexture);
    //testWorld->addObject(rectModel, -25, 4);
    //testWorld->addObject(rectModel, 24, 4);

    Model rectModel2 = ModelFactory::create(50, 50, shader, testTexture2);
    testWorld->addObject(rectModel2, 0, -50);

    Model rectModel3 = ModelFactory::create(15, 15, shader, testTexture2);
    testWorld->addObject(rectModel3, 25, 25);

    player = std::make_shared<Player>();

    testWorld->addEntity(player);

    // add model to player
    Model playerModel = ModelFactory::create(10, 20, shader, testTexture);
    player->setModel(playerModel);

    return SUCCESS;
}

Result Engine::internalInitEventSystem() {
    keyEventHandler = new KeyEventHandler();
    return SUCCESS;
}

void Engine::startLoop() {
    // Ensure all systems are loaded
    running = true;
    loopStart = SDL_GetPerformanceCounter();
    while (running) {
        doLoop();
    }
}

void Engine::doLoop() {
    // Start performance measuring
    Uint64 lastLoopStart = loopStart;
    loopStart = SDL_GetPerformanceCounter();

    double delta = ((loopStart - lastLoopStart)) / (double) SDL_GetPerformanceFrequency();
    // Process through all events in queue
    SDL_Event lastEvent;
    while (SDL_PollEvent(&lastEvent)) {

        if (lastEvent.type == SDL_QUIT) {
            running = false;
        }

        if (lastEvent.type == SDL_KEYDOWN && !lastEvent.key.repeat) {
            //std::cout << lastEvent.key.keysym.sym << std::endl;
            keyEventHandler->eventKeyDown(lastEvent.key.keysym.sym);

            if (lastEvent.key.keysym.sym == SDLK_a) {
                player->addHorizontalVelocity(-1 * player->getWalkingSpeed());
            }

            if (lastEvent.key.keysym.sym == SDLK_d) {
                player->addHorizontalVelocity(player->getWalkingSpeed());
            }

            if (lastEvent.key.keysym.sym == SDLK_h) {
                player->setX(3.0);
                player->setY(50.0);
            }
        }

        if (lastEvent.type == SDL_KEYUP) {
            keyEventHandler->eventKeyUp(lastEvent.key.keysym.sym);

            if (lastEvent.key.keysym.sym == SDLK_a) {
                player->addHorizontalVelocity(player->getWalkingSpeed());
            }

            if (lastEvent.key.keysym.sym == SDLK_d) {
                player->addHorizontalVelocity(-1 * player->getWalkingSpeed());
            }
        }
    }

    // Process player movement
    keyEventHandler->processKeyCooldowns();

    if (keyEventHandler->isKeyDown(SDLK_d)) {
        //player->walkRight(1 * delta);
    }

    if (keyEventHandler->isKeyDown(SDLK_a)) {
        //player->walkLeft(1 * delta);
    }

    if (keyEventHandler->isKeyDown(SDLK_w)) {
        player->moveY(-0.1 * delta);
    }

    if (keyEventHandler->isKeyDown(SDLK_s)) {
        player->moveY(0.1 * delta);
    }

    if (keyEventHandler->isKeyDown(SDLK_SPACE) && !player->isJumping()) {
        player->setJumping(true);
        player->addVerticalVelocity(50);
    }

    /////////////////////
    // Process physics //
    /////////////////////

    for (const auto& entityPair : testWorld->getEntities()) {
        std::shared_ptr<Entity> entity = entityPair.second;

        // Gravity
        if (entity->hasGravity()) {
            entity->addVerticalVelocity(-1);
        }

        // Apply movements
        //entity->moveX(entity->getHorizontalVelocity() * delta);
        //entity->moveY(entity->getVerticalVelocity() * delta);

        // Check vertical collisions - heavily optimize later
        double requestedY = entity->getY() + entity->getVerticalVelocity() * delta;
        double settledY   = requestedY;
        for (auto & objectPair : testWorld->getObjects()) {
            Object object = objectPair.second;

            if (requestedY < entity->getY()) { // down moving
                if (object.getY() > entity->getY())
                    continue;
                auto result = BoundChecker::check(player->getModel(), player->getX(), requestedY, object.getModel(),object.getX(), object.getY(), BoundChecker::INTO_TOP);
                if (result.boundFound && result.newActorPos > settledY)
                    settledY = result.newActorPos;

            } else if (requestedY > entity->getY()) { // up moving
                if (object.getY() < entity->getY())
                    continue;
                auto result = BoundChecker::check(player->getModel(), player->getX(), requestedY, object.getModel(),object.getX(), object.getY(), BoundChecker::INTO_BOTTOM);
                if (result.boundFound && result.newActorPos < settledY)
                    settledY = result.newActorPos;

            }
        }

        // Check horizontal collisions
        double requestedX = entity->getX() + entity->getHorizontalVelocity() * delta;
        double settledX   = requestedX;
        for (auto &objectPair: testWorld->getObjects()) {
            Object object = objectPair.second;

            if (requestedX < entity->getX()) { // left moving
                if (object.getX() > entity->getX())
                    continue;
                auto result = BoundChecker::check(entity->getModel(), requestedX, entity->getY(), object.getModel(),
                                                      object.getX(), object.getY(), BoundChecker::INTO_LEFT);
                if (result.boundFound && result.newActorPos > settledX)
                    settledX = result.newActorPos;

            } else if (requestedX > entity->getX()) { // right moving
                if (object.getX() < entity->getX())
                    continue;
                auto result = BoundChecker::check(entity->getModel(), requestedX, entity->getY(), object.getModel(),
                                                      object.getX(), object.getY(), BoundChecker::INTO_RIGHT);
                if (result.boundFound && result.newActorPos < settledX)
                    settledX = result.newActorPos;
            }
        }

        // If player has collided vertically
        if (settledY != requestedY) {
            if (entity->isJumping() && requestedY < entity->getY()) {
                entity->setJumping(false);
                keyEventHandler->applyKeyCooldown(SDLK_SPACE);
            }
            entity->setVerticalVelocity(0);
        } else { // free-falling
            entity->setJumping(true);
        }

        player->setY(settledY);
        //printf("setting x to %lf\n", settledX);
        player->setX(settledX);

        /*if (entity->getY() < 0) {
            if (entity->isJumping()) {
                entity->setJumping(false);
                keyEventHandler->applyKeyCooldown(SDLK_SPACE);
            }
            entity->setY(0);
            entity->setVerticalVelocity(0);
        }*/
    }

    // Check window dimensions
    int windowWidth = 0;
    int windowHeight = 0;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    if (windowWidth != lastKnownWidth || windowHeight != lastKnownHeight) {
        lastKnownWidth = windowWidth;
        lastKnownHeight = windowHeight;
        currentCamera->updateScreenSize(windowWidth, windowHeight);
    }

    ///////////////////////////////
    // Add items to render queue //
    ///////////////////////////////

    for (auto & object : testWorld->getObjects()) {
        renderSystem->addToQueue(object.second);
    }

    for (auto & entityPair : testWorld->getEntities()) {
        std::shared_ptr<Entity> entity = entityPair.second;
        renderSystem->addToQueue(Object(entity->getModel(), entity->getX(), entity->getY()));
        //printf("entity x: %lf\n", entity->getX());
    }

    //renderSystem->addToQueue(*testMesh);
    renderSystem->render(*currentCamera);

    SDL_GL_SwapWindow(window);

    // End performance measuring
    Uint64 loopEnd = SDL_GetPerformanceCounter();
    double processingTime = (loopEnd - loopStart) / (double) SDL_GetPerformanceFrequency();
    //printf("FPS: %.1f\n", 1.0 / processingTime);
}

void Engine::cleanUp() {
    printf("[i] Starting engine cleanup...\n");
    MeshShader::cleanUp();
    printf("[+] Engine cleanup successful\n");
    delete instance;
}

Engine::~Engine() {
    printf("[i] Starting engine shutdown...\n");
    delete shaderRegistry;
    delete renderSystem;
    delete keyEventHandler;
    delete testWorld;
    printf("[+] Engine shutdown successful\n");
}