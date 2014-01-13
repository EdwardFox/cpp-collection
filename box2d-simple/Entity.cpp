#include "Entity.hpp"
#include "World.hpp"

Entity::Entity() :
mBox()
, mBodyDef()
, mBody(nullptr)
, mBodyShape()
, mFixtureDef()
{
}

Entity::Entity(b2World &world, float x, float y)
{
    Entity();
    createBox(world, x, y);
}

void Entity::update(sf::Time dt) 
{
    float x = mBody->GetPosition().x;
    float y = mBody->GetPosition().y;
    float angle = mBody->GetAngle() * 180.f / 3.14f;

    mBox.setPosition(x*World::Scale, y*World::Scale);
    mBox.setRotation(angle);
}

void Entity::draw(sf::RenderTarget &target) const
{
    target.draw(mBox);
}

void Entity::createBox(b2World &world, float x, float y)
{
    mBox.setPosition(x, y);
    mBox.setSize(sf::Vector2f(32.f, 32.f));
    mBox.setOrigin(sf::Vector2f(16.f, 16.f));

    mBodyDef.type = b2_dynamicBody;
    mBodyDef.position.Set(x/World::Scale, y/World::Scale);
    mBody = world.CreateBody(&mBodyDef);
    mBodyShape.SetAsBox(16.f/World::Scale, 16.f/World::Scale);
    mFixtureDef.shape = &mBodyShape;
    mFixtureDef.density = 1.0f;
    mFixtureDef.friction = 0.3f;
    mBody->CreateFixture(&mFixtureDef);
}
