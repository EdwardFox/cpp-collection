#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Entity
{
    public:
        /**
        * @brief Default constructor
        */
        Entity();

        /**
        * @brief Explicit constructor that calls createBox to fully initialize the entity
        *
        * @param world Reference to the physics world
        * @param x X coordinate for initial position
        * @param y Y coordinate for initial position
        */
        explicit Entity(b2World &world, float x, float y);

        /**
        * @brief Updates the entity's position and sets the visual representation accordingly
        *
        * @param dt Time between 2 update ticks
        */
        void update(sf::Time dt);

        /**
        * @brief Draws the entity
        *
        * @param target The target surface to draw on (most likely the render window)
        */
        void draw(sf::RenderTarget &target) const;

        /**
        * @brief Creates the entity's physical and graphical representation
        *
        * @param world Reference to the physics world
        * @param x X coordinate for initial position
        * @param y Y coordinate for initial position
        */
        void createBox(b2World &world, float x, float y);

    private:
        /**
        * @brief The graphical representation (a square)
        */
        sf::RectangleShape mBox;

        /**
        * @brief The physical body definition
        */
        b2BodyDef mBodyDef;

        /**
        * @brief The actual physical body
        */
        b2Body* mBody;

        /**
        * @brief The physical body's shape
        */
        b2PolygonShape mBodyShape;

        /**
        * @brief The physical body's fixture definition
        */
        b2FixtureDef mFixtureDef;
};

#endif
