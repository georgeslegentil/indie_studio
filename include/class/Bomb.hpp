#ifndef BOMB_HPP
#define BOMB_HPP

#include <chrono>
#include <vector>
#include <memory>
#include "Entity.hpp"

class Explosion;
class Player;

class Bomb : public Entity {
public:
    explicit Bomb(Player &owner, irr::IrrlichtDevice *device);
    std::vector<std::shared_ptr<Explosion>> createExplosion();
    bool hasExploded();
    type getType() const override;
    Player &getOwner() const;
    int getCountdown() const;
    int getRange() const;
    const std::chrono::time_point<std::chrono::system_clock> &getCreationTime() const;
protected:
    void create3dModel(std::string modelFilePath, std::string textureFilePath) override;
private:
    Player &_owner;
    int _countdown = 2000;
    int _range = 1;
    int _damage = 1;
    std::chrono::time_point<std::chrono::system_clock> _creationTime = std::chrono::system_clock::now();
};

#endif
