#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable {
public:
    Entity(sf::Texture const & texture);
    void setVelocity(sf::Vector2f const &  vel) { mVelocity = vel;}
    virtual void update(sf::Time dt = sf::Time::Zero); 
    virtual ~Entity() {}
    bool isAlive;
protected:
    sf::Sprite mSprite;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Vector2f mVelocity;
    sf::CircleShape mCircle;
    float mRadius;
};

class Animation : public Entity{
public:
    Animation(sf::Texture const & texture, int rows, int cols, int width, int height, float vel);
    virtual void update(sf::Time dt = sf::Time::Zero)  override; 
private:
    int mRows, mCols, mWidth, mHeight;
    float mSpeed;
    float mCurrentCol;
    int   mCurrentRow;
};

// dopuniti
class Asteroid : public Entity{
};


// dopuniti
class Player : public Entity{
};
