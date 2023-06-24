#include "world.h"

#include <utility>

int World::addObject(const Object &obj) {
    worldObjects.insert({currentObjectId, obj});
    return currentObjectId++;
}

int World::addObject(const Model &model, double x, double y) {
    Object object(model, x, y);
    return addObject(object);
}

std::optional<std::reference_wrapper<const Object>> World::getObject(int id) const {
    if (worldObjects.count(id) == 0) {
        return std::nullopt;
    }
    return worldObjects.at(id);
}

const std::unordered_map<int, Object> &World::getObjects() const {
    return worldObjects;
}

int World::addEntity(const std::shared_ptr<Entity> &entity) {
    entities.insert({currentEntityId, entity});
    return currentEntityId++;
}

std::optional<std::shared_ptr<Entity>> World::getEntity(int id) {
    if (entities.count(id) == 0) {
        return std::nullopt;
    }
    return entities.at(id);
}

const std::unordered_map<int, std::shared_ptr<Entity>> &World::getEntities() const {
    return entities;
}

