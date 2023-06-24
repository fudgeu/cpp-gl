#include <SDL_timer.h>
#include <vector>
#include "key_event_handler.h"

static double KEY_COOLDOWN_DURATION = 0.05;

bool KeyEventHandler::isKeyDown(SDL_Keycode keyCode) {
    if (cooldownMap.count(keyCode) != 0) {
        return false;
    }
    return keyDownMap[keyCode];
}

void KeyEventHandler::eventKeyDown(SDL_Keycode keyCode) {
    keyDownMap[keyCode] = true;
}

void KeyEventHandler::eventKeyUp(SDL_Keycode keyCode) {
    keyDownMap[keyCode] = false;
}

void KeyEventHandler::applyKeyCooldown(SDL_Keycode keyCode) {
    cooldownMap[keyCode] = SDL_GetPerformanceCounter() + KEY_COOLDOWN_DURATION * SDL_GetPerformanceFrequency();
}

void KeyEventHandler::processKeyCooldowns() {
    std::vector<SDL_Keycode> trashList;

    for (const auto & entry : cooldownMap) {
        SDL_Keycode key = entry.first;
        Uint64 expirationTime = entry.second;
        if (expirationTime <= SDL_GetPerformanceCounter()) {
            trashList.push_back(key);
        }
    }

    for (const auto &key : trashList) {
        cooldownMap.erase(key);
    }
}