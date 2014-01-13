#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Entity.hpp"

class World
{
    private:
        typedef std::unique_ptr<Entity> entPtr;

    public:
        /**
        * @brief Default constructor
        */
        World();

        /**
        * @brief Updates the world and all its entities
        *
        * @param dt Time passed between 2 update ticks
        */
        void update(sf::Time dt);

        /**
        * @brief Draws the world and all entities
        *
        * @param target
        */
        void draw(sf::RenderTarget &target) const;

        /**
        * @brief Adds an entity at position x/y
        *
        * @param x X coordinate
        * @param y Y coordinate
        */
        void addEntity(float x, float y);

        /**
        * @brief Overloaded version of addEntity(float, float)
        *
        * @param pos X/Y coordinate pair
        */
        void addEntity(sf::Vector2f pos);

    private:
        /**
        * @brief Contains all entities
        */
        std::vector<entPtr> mEntities;

        /**
        * @brief Physics world representation
        */
        b2World mPhysWorld;

        /**
        * @brief Body definition for the ground
        */
        b2BodyDef mGroundBodyDef;

        /**
        * @brief The actual ground body
        */
        b2Body* mGroundBody;

        /**
        * @brief The shape of the ground body
        */
        b2PolygonShape mGroundShape;

    public:
        /**
        * @brief The scaling factor required by Box2D
        */
        static const float Scale;
};

#endif
