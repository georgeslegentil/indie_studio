#ifndef GAME_HPP
#define GAME_HPP

#include <irrlicht/irrlicht.h>
#include "iostream"
#include "class/PauseMenu.hpp"
#include "class/Map.hpp"
#include "class/Player.hpp"
#include "class/Explosion.hpp"

class PauseMenu;

class Game {
public:
    Game(irr::IrrlichtDevice *device, size_t playerNbr, int mapSize, int YmapPos, int WallDensity);

    void save();
    void loadSave();
    void gameLoop();
    bool eventKey(irr::EKEY_CODE keyCode);
    void LaunchPauseMenu();
    bool canMoveHere(const std::shared_ptr<Entity> item);

private:
    void createPlayers(size_t playerNbr);
    void setGround(float scaleY);
    void playerMovement();
    void bomb();
    void collision();
    void groundCollision(irr::scene::ISceneManager *manager, irr::scene::IMetaTriangleSelector *meta);
    void bombExplosion();
private:
    PauseMenu *_pauseMenu;
    Map _map;
    irr::scene::ITerrainSceneNode *_terrain;
    std::vector<Player> _players;
    std::vector<std::shared_ptr<Bomb>> _bombs;
    std::vector<std::shared_ptr<Explosion>> _explosions;
    irr::IrrlichtDevice *_device;
    int _wallDensity;
    int _mapSize;
    float _scale = 10;
    bool _collisionUpdated = false;
};

#endif
