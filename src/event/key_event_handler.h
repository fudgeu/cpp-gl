#pragma once

#include <SDL_keycode.h>
#include <unordered_map>

class KeyEventHandler {
public:
    bool isKeyDown(SDL_Keycode keyCode);
    void eventKeyDown(SDL_Keycode keyCode);
    void eventKeyUp(SDL_Keycode keyCode);
    void applyKeyCooldown(SDL_Keycode keyCode);
    void processKeyCooldowns();

private:
    std::unordered_map<SDL_Keycode, bool>   keyDownMap;
    std::unordered_map<SDL_Keycode, Uint64> cooldownMap;

};