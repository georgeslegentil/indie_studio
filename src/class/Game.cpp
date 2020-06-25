#include "class/Game.hpp"
#include "class/GameEvent.hpp"
#include "class/Bomb.hpp"
#include "class/PauseMenu.hpp"

Game::Game(irr::IrrlichtDevice *device, size_t playerNbr, int mapSize, int YmapPos, int WallDensity) : _device(device),
    _map(Map(device, mapSize, mapSize, 2)), _wallDensity(WallDensity), _mapSize(mapSize)
{
    irr::scene::ISceneManager *manager = device->getSceneManager();

    this->setGround(0);
    device->setEventReceiver(new GameEvent(*this));
    this->createPlayers(playerNbr);
    this->collision();
    manager->addCameraSceneNode(0, irr::core::vector3df(this->_map.getWidth() / 2 * 10, YmapPos,
        this->_map.getHeight() / 2 * 10 - 60),
        irr::core::vector3df(this->_map.getWidth() / 2 * 10, 0,
            this->_map.getHeight() / 2 * 10 - 15));
}

void Game::createPlayers(size_t playerNbr)
{
    if (playerNbr >= 1) {
        Player player(this->_device, std::string("Player ", 0));
        player.setPosition(1, 10, 1);
        player.setKeys(irr::KEY_KEY_Z, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_KEY_D, irr::KEY_KEY_E);
        this->_players.push_back(player);
    }
    if (playerNbr >= 2) {
        Player player(this->_device, std::string("Player ", 1));
        player.setPosition(this->_map.getWidth() - 2, 15, this->_map.getHeight() - 2);
        player.setKeys(irr::KEY_UP, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_RIGHT, irr::KEY_SPACE);
        this->_players.push_back(player);
    }
    if (playerNbr >= 3) {
        Player player(this->_device, std::string("Player ", 2));
        player.setPosition(this->_map.getWidth() - 2, 20, 1);
        player.setKeys(irr::KEY_KEY_O, irr::KEY_KEY_L, irr::KEY_KEY_K, irr::KEY_KEY_M, irr::KEY_KEY_P);
        this->_players.push_back(player);
    }
    if (playerNbr >= 4) {
        Player player(this->_device, std::string("Player ", 3));
        player.setPosition(1, 25, this->_map.getHeight() - 2);
        player.setKeys(irr::KEY_KEY_G, irr::KEY_KEY_V, irr::KEY_KEY_C, irr::KEY_KEY_B, irr::KEY_KEY_H);
        this->_players.push_back(player);
    }
}

void Game::setGround(float scaleY)
{
    irr::scene::ISceneManager *manager = this->_device->getSceneManager();
    irr::video::IVideoDriver *driver = this->_device->getVideoDriver();

    irr::scene::ITerrainSceneNode *terrain = manager->addTerrainSceneNode(
        "media/img/terrain_heightmap.bmp", nullptr, -1,
        irr::core::vector3df(0, -1 * this->_scale / this->_wallDensity, 0), irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(this->_mapSize*0.04, scaleY, this->_mapSize*0.04), irr::video::SColor(255, 255, 255, 255));
    terrain->setMaterialTexture(0, driver->getTexture("media/img/ground_texture.jpg"));
    terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->_terrain = terrain;
}

void Game::gameLoop()
{
    this->playerMovement();
    this->bomb();
    this->bombExplosion();
    this->_map.process();
    if (!this->_collisionUpdated)
        this->collision();
}

void Game::playerMovement()
{
    GameEvent &event = *dynamic_cast<GameEvent *>(this->_device->getEventReceiver());
    static irr::u32 then = this->_device->getTimer()->getTime();
    const irr::u32 now = this->_device->getTimer()->getTime();
    const irr::f32 frameDeltaTime = (now - then) / 1000.f; // In seconds
    irr::core::vector3df nodePosition;

    then = now;
    for (Player &player : this->_players) {
        nodePosition = player.getPosition();
        if (event.pressedKey(player.moveUpKey)) {
            nodePosition.Z += frameDeltaTime * this->_scale;
            player.getNode()->setRotation({0, -90, 0});
        } else if (event.pressedKey(player.moveDownKey)) {
            nodePosition.Z -= frameDeltaTime * this->_scale;
            player.getNode()->setRotation({0, 90, 0});
        }
        if (event.pressedKey(player.moveLeftKey)) {
            nodePosition.X -= frameDeltaTime * this->_scale;
            player.getNode()->setRotation({0, -180, 0});
        } else if (event.pressedKey(player.moveRightKey)) {
            nodePosition.X += frameDeltaTime * this->_scale;
            player.getNode()->setRotation({0, 0, 0});
        }
        player.setPosition(nodePosition);
        if (event.pressedKey(player.moveUpKey) || event.pressedKey(player.moveDownKey) ||
            event.pressedKey(player.moveLeftKey) || event.pressedKey(player.moveRightKey))
            player.setRunAnimation();
        else
            player.setStandAnimation();

        player.process();
    }
}

bool Game::canMoveHere(const std::shared_ptr<Entity> item)
{
    if (item->getType() != IEntity::type::WALL && item->getType() != IEntity::type::BOMB)
        return true;
    return false;
}

void Game::collision()
{
    irr::scene::ITriangleSelector *selector = nullptr;
    irr::scene::ISceneManager *manager = this->_device->getSceneManager();
    irr::scene::IMetaTriangleSelector *meta = manager->createMetaTriangleSelector();

    for (auto &cell : this->_map.getCases()) {
        for (const auto &item : cell.getEntities()) {
            if (canMoveHere(item))
                continue;
            irr::scene::ISceneNode *node = item->getNode();
            selector = manager->createOctreeTriangleSelector(item->getMesh(), node, 128);
            if (!selector)
                continue;
            node->setTriangleSelector(selector);
            meta->addTriangleSelector(selector);
            selector->drop();
        }
    }
    groundCollision(manager, meta);
    this->_collisionUpdated = true;
}

void Game::groundCollision(irr::scene::ISceneManager *manager, irr::scene::IMetaTriangleSelector *meta)
{
    irr::scene::ITriangleSelector *selector = manager->createTerrainTriangleSelector(this->_terrain,
        0);
    irr::scene::ISceneNodeAnimator *anim = nullptr;

    meta->addTriangleSelector(selector);
    for (const auto &player : this->_players) {
        anim = manager->createCollisionResponseAnimator(meta, player.getNode(),
            irr::core::vector3df(2, 5, 2), irr::core::vector3df(0, -10, 0));
        player.getNode()->removeAnimators();
        player.getNode()->addAnimator(anim);
        anim->drop();
    }
    selector->drop();
}

void Game::LaunchPauseMenu()
{
    std::cout << "Pause Key pressed !" << std::endl;
    // this->_pauseMenu = new PauseMenu(this->_device);
}

bool Game::eventKey(irr::EKEY_CODE keyCode)
{
    for (auto &player : this->_players) {
        if (keyCode == player.plantBombKey && player.getBombRemaining()) {
            auto bomb = player.plantBomb();
            this->_map.pushEntity(bomb);
            this->_bombs.push_back(bomb);
            return true;
        } else if (keyCode == irr::KEY_KEY_P) {
            LaunchPauseMenu();
        }
    }
    return false;
}

void Game::bomb()
{
    for (auto it = this->_bombs.begin(); it != this->_bombs.end();) {
        auto bomb = (*it);
        if (bomb->hasExploded()) {
            auto explosionList = bomb->createExplosion();
            for (auto &explosion : explosionList) {
                this->_explosions.push_back(explosion);
                this->_map.pushEntity(explosion);
            }
            bomb->destroy();
            this->_bombs.erase(it);
            this->_collisionUpdated = false;
            continue;
        }
        it++;
    }
}

void Game::bombExplosion()
{
    for (auto it = this->_explosions.begin(); it != this->_explosions.end();) {
        auto explosion = (*it);
        if (explosion->end()) {
            this->_map.getCase(explosion->getX(), explosion->getZ()).removeWalls();
            explosion->destroy();
            this->_explosions.erase(it);
            this->_collisionUpdated = false;
            continue;
        }
        it++;
    }
}
