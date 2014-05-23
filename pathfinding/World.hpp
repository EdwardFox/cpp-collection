#ifndef WORLD_HPP
#define WORLD_HPP

#include <map>
#include <vector>
#include "Data.hpp"
#include "Entity.hpp"

class World
{
    /*** Typedefs ***/
    public:
        typedef std::unique_ptr<Entity> entPtr;


    /*** Methods ***/
        /**
        * @brief Default constructor
        */
        World(int width, int height);

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
        void addEntity(std::string key, sf::Vector2f position, sf::Vector2f size, sf::Color fill, sf::Color outline, bool isStart, bool isEnd, bool isWall);

        //std::map<std::string, std::unique_ptr<Entity>>& getEntities();

        /**
        * @brief Returns a pointer to the entity at the given coordinates
        *
        * @param x Coordinate
        * @param y Coordinate
        *
        * @return Pointer to the found entity or NULL
        */
        Entity* const getEntityAtPosition(int x, int y) const;

        /**
        * @brief Creates a grid of nodes according to the given dimensions
        *
        * @param width
        * @param height
        */
        void createWorld(int width, int height);

        /**
        * @brief Clears the map and calls createWorld again
        *
        * @param width
        * @param height
        */
        void resetWorld(int width, int height);

        /**
        * @brief Resets all node states for nodes on the open & closed list as well as
        * the nodes that make up the path
        */
        void clearPath();

        /**
        * @brief Sets a pointer to the start node
        *
        * @param ent Pointer to the start node
        */
        void setStartNode(Entity* const ent);

        /**
        * @brief Sets a pointer to the goal node
        *
        * @param ent Pointer to the goal node
        */
        void setGoalNode(Entity* const ent);

        /**
        * @brief Finds the path from the start to the goal node and highlights the processed nodes
        *
        * @param heu Determines which heuristic algorithm is being used. No heuristic changes the pathfinding Algorithm from A* to Dijkstra.
        */
        void findPath(Heuristic heu);


    private:
        /**
        * @brief Returns a pointer to an entity from the openlist with the lowest score
        *
        * @param openList The list of entities to evaluate the score from
        * @param heu The heuristic method used to help determine the score
        *
        * @return 
        */
        Entity* getLowestScore(std::map<std::string, Entity*> openList, Heuristic heu) const;

        /**
        * @brief Returns a vector of valid nodes which are adjacent to the the given entity
        *
        * @param ent The entity to start from
        * @param dia Allow diagonal connections
        *
        * @return Vector of valid nodes
        */
        std::vector<std::string> getValidNodes(const Entity* const ent, bool dia) const;

        /**
        * @brief Returns the heuristic score value for the given heuristic method and entity
        *
        * @param heu Heuristic method
        * @param ent Entity to evaluate
        *
        * @return 
        */
        float getHeuristicValue(Heuristic heu, const Entity* const ent) const;


    /*** Attributes ***/
        /**
        * @brief Map containing the node grid
        */
        std::map<std::string, entPtr> mEntities;

        /**
        * @brief Pointer to the start node
        */
        Entity* mStartNode;

        /**
        * @brief Pointer to the goal node
        */
        Entity* mGoalNode;
};

#endif
