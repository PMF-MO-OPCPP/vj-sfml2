#include "entities.h"

// Dopuniti po potrebi.

Entity::Entity(sf::Texture const & texture){
    mSprite.setTexture(texture);
    auto lb = mSprite.getLocalBounds();
    mSprite.setOrigin(lb.width/2, lb.height/2);
    mVelocity.x=mVelocity.y = 30.0f; 
    isAlive = true;

    mRadius = 1.0*std::min(lb.width/2,lb.height/2);
    mCircle.setRadius(mRadius);
    mCircle.setFillColor(sf::Color(0, 255, 0, 0));
    mCircle.setOutlineThickness(1);
    mCircle.setOutlineColor(sf::Color::Yellow);
    mCircle.setOrigin(mRadius, mRadius);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(mSprite, states);
//    target.draw(mCircle, states);
}

void Entity::update(sf::Time dt){
    auto pos = getPosition();
    float x = pos.x + mVelocity.x*dt.asSeconds();
    float y = pos.y + mVelocity.y*dt.asSeconds();
    setPosition(x,y);
}

Animation::Animation(sf::Texture const & texture, int rows, int cols, int width, int height, float vel) :
  Entity(texture), mRows(rows), mCols(cols), mWidth(width/cols), mHeight(height/rows), mSpeed(vel),
  mCurrentCol(0.0f),  mCurrentRow(0) {

  }

 void Animation::update(sf::Time dt){
    if(!isAlive) return;
    mCurrentCol += mSpeed;
    if(static_cast<int>(mCurrentCol) == mCols){
        mCurrentCol = 0.0f;
        ++mCurrentRow;
    }
    if(mCurrentRow == mRows){
        mCurrentCol = 0.0f;
        mCurrentRow = 0;
        isAlive = false;
        return;
    }

    int i = mCurrentCol;
    int j = mCurrentRow; 
    mSprite.setTextureRect(sf::IntRect(i*mWidth, j*mHeight, mWidth, mHeight));
 } 
