#pragma once
#include <SFML/Graphics.hpp>
#include "textureHolder.h"
#include "entities.h"


// Klasu dopuniti po potrebi.

class Game{
public:
    Game();
    void run();
private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void handlePlayerInput(sf::Keyboard::Key code, bool isPressed);

    sf::RenderWindow mWindow;
    TextureHolder mTextureHolder;  
    sf::Sprite mSprite;
    sf::Sprite mBackgroundSprite;
    sf::Sprite mAsteroid;
    std::unique_ptr<Entity> mEntity;
    std::unique_ptr<Animation> mExplosion;

    bool mIsMovingUp    = false;
    bool mIsMovingDown  = false;
    bool mIsMovingLeft  = false;
    bool mIsMovingRight = false;

    bool mMouseButtonPressed = false;

    float mVelocity = 120.0f; // pixel/sec
    sf::Time mDtFixed;
};
