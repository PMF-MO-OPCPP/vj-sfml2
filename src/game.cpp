#include "game.h"
#include <stdexcept>

// Kod dopuniti/promijeniti po potrebi. 

Game::Game() : mWindow(sf::VideoMode(1280, 1024), "SFML window") {
    mBackgroundSprite.setTexture(mTextureHolder.getTexture(Textures::background));
    mSprite.setTexture(mTextureHolder.getTexture(Textures::player));
    mAsteroid.setTexture(mTextureHolder.getTexture(Textures::meteorBig1));
    mAsteroid.setOrigin(mAsteroid.getLocalBounds().width/2, mAsteroid.getLocalBounds().height/2);

    mAsteroid.setPosition(200,300);
    
    mSprite.setOrigin(mSprite.getLocalBounds().width/2, mSprite.getLocalBounds().height/2);
    mSprite.setPosition(mSprite.getLocalBounds().width/2, mSprite.getLocalBounds().height/2);
    mDtFixed = sf::seconds(1.0f/60.0f);

    mEntity.reset(new Entity(mTextureHolder.getTexture(Textures::meteorMedium1)));
    mEntity->setPosition(500,700);

    mExplosion.reset(
        new Animation(mTextureHolder.getTexture(Textures::explosion), 4, 4, 256, 256, 0.2f)
                    );
    mExplosion->setPosition(200,700);
}

void Game::run(){
    // Start the game loop
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate >= mDtFixed){
            timeSinceLastUpdate -= mDtFixed;
            processEvents();
            update(mDtFixed);
        }       
        render();
    }

}

void Game::processEvents(){
        // Process events
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            // Close window : exit
            switch(event.type){
                case sf::Event::Closed: 
                    mWindow.close();
                    break;
                case sf::Event::KeyPressed:
                    handlePlayerInput(event.key.code, true);
                    break;
                case sf::Event::KeyReleased:
                    handlePlayerInput(event.key.code, false);
                    break;
                case sf::Event::MouseButtonPressed:
                    mMouseButtonPressed = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    mMouseButtonPressed = false;
                    break;
            }
            
        }
}

void Game::update(sf::Time dt){
    sf::Vector2f velocity(0.f,0.f);
    if(mIsMovingUp)
        velocity.y -= mVelocity;
    if(mIsMovingDown)
        velocity.y += mVelocity;    
    if(mIsMovingLeft)
        velocity.x -= mVelocity;
    if(mIsMovingRight)
        velocity.x += mVelocity;

    mSprite.move(velocity*dt.asSeconds());

    mAsteroid.rotate(40*dt.asSeconds());

    mEntity->update(dt);

    mExplosion->update();
}

void Game::render(){
       // Clear screen
        mWindow.clear();
        mWindow.draw(mBackgroundSprite);
        mWindow.draw(mAsteroid);
        // Draw the sprite
        mWindow.draw(mSprite);
        mWindow.draw(*mEntity);
        mWindow.draw(*mExplosion);
        // Update the window
        mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key code, bool isPressed){
    if(code == sf::Keyboard::Key::Up)
        mIsMovingUp = isPressed;
    if(code == sf::Keyboard::Key::Down)
        mIsMovingDown = isPressed;
    if(code == sf::Keyboard::Key::Left)
        mIsMovingLeft = isPressed;
    if(code == sf::Keyboard::Key::Right)
        mIsMovingRight = isPressed;            
}
