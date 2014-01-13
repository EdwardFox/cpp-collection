#include "World.hpp"
#include "Game.hpp"

const float World::Scale = 32.f;

World::World() :
mEntities()
, mPhysWorld(b2Vec2(0.f, 10.f))
, mGroundBodyDef()
, mGroundBody(nullptr)
, mGroundShape()
{
    mGroundBodyDef.position.Set(400.f/Scale, 600.f/Scale);
    mGroundBody = mPhysWorld.CreateBody(&mGroundBodyDef);
    mGroundShape.SetAsBox(400.f/Scale, 20.f/Scale);
    mGroundBody->CreateFixture(&mGroundShape, 0.f);
}

void World::update(sf::Time dt)
{
    mPhysWorld.Step(Game::TimePerFrame.asSeconds(), 6, 2);

    for(const entPtr& ent : mEntities)
    {
        ent->update(dt);
    }
}

void World::draw(sf::RenderTarget &target) const
{
    for(const entPtr& ent : mEntities)
    {
        ent->draw(target);
    }
}

void World::addEntity(float x, float y)
{
    entPtr ent(new Entity(mPhysWorld, x, y));
    mEntities.push_back(std::move(ent));
}

void World::addEntity(sf::Vector2f pos)
{
    addEntity(pos.x, pos.y);
}
