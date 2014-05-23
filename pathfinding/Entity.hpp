#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include "Data.hpp"

class Entity
{
    public:
        /**
        * @brief Default constructor
        */
        Entity();

        /**
        * @brief 
        *
        * @param position
        * @param size
        * @param fill
        * @param outline
        * @param isStart
        * @param isGoal
        * @param isWall
        */
        Entity(sf::Vector2f position, sf::Vector2f size, sf::Color fill, sf::Color outline, bool isStart, bool isGoal, bool isWall); 

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
        * @brief Set fill color
        *
        * @param c
        */
        void setColor(sf::Color c);

        /**
        * @brief Set border color
        *
        * @param c
        */
        void setBorderColor(sf::Color c);

        /**
        * @brief Returns a list of all adjacent neighbors
        *
        * @param diagonal Diagonal neighbors enabled
        *
        * @return 
        */
        std::vector<std::string> getNeighbors(bool diagonal = false) const;

        /**
        * @brief Returns the index key for the map container
        *
        * @return 
        */
        std::string getIndex();

        /**
        * @brief Returns the x,y position in the world
        *
        * @return 
        */
        sf::Vector2f getPosition() const;

        /**
        * @brief Structure containing all relevant node information for pathfinding
        */
        struct 
        {
            NodeState state;
            Entity* parent;
            float costSoFar;
            bool isPath;
            bool isWall;
            bool isStart;
            bool isGoal;
        } node;

    private:
        /**
        * @brief The graphical representation
        */
        sf::RectangleShape mShape;
};

#endif
