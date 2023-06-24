#pragma once

#include <glm/vec3.hpp>
#include <unordered_map>
#include <optional>
#include <memory>
#include "../object/object.h"
#include "../entity/entity.h"

class World {
public:
    int addObject(const Object &obj);
    int addObject(const Model &model, double x, double y);
    std::optional<std::reference_wrapper<const Object>> getObject(int id) const;
    const std::unordered_map<int, Object> &getObjects() const;


    int addEntity(const std::shared_ptr<Entity> &);
    std::optional<std::shared_ptr<Entity>> getEntity(int id);
    const std::unordered_map<int, std::shared_ptr<Entity>> &getEntities() const;


private:
    std::unordered_map<int, Object> worldObjects;
    std::unordered_map<int, std::shared_ptr<Entity>> entities;
    int currentObjectId = 0;
    int currentEntityId = 0;
};