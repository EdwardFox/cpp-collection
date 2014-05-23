#include "World.hpp"
#include <stdexcept>
#include <cmath>

World::World(int width, int height) :
mEntities()
, mStartNode(NULL)
, mGoalNode(NULL)
{
    createWorld(width, height);
}

void World::update(sf::Time dt)
{
    for(const auto& ent : mEntities)
    {
        ent.second->update(dt);
    }

}

void World::draw(sf::RenderTarget &target) const
{
    for(const auto& ent : mEntities)
    {
        ent.second->draw(target);
    }
}

void World::addEntity(std::string key, sf::Vector2f position, sf::Vector2f size, sf::Color fill, sf::Color outline, bool isStart, bool isEnd, bool isWall)
{
    mEntities[key] = std::unique_ptr<Entity>(new Entity(position, size, fill, outline, isStart, isEnd, isWall));
}

//std::map<std::string, std::unique_ptr<Entity>>& World::getEntities()
//{
    //return mEntities;
//}

void World::createWorld(int width, int height)
{
    int rows = width / (int)BOX_SIZE + 1;
    int columns = height / (int)BOX_SIZE + 1;

    for(int i = 0; i < columns; ++i)
    {
        for(int j = 0; j < rows; ++j)
        {
            sf::Vector2f position(j*BOX_SIZE, i*BOX_SIZE);
            sf::Vector2f size(BOX_SIZE, BOX_SIZE);
            sf::Color fill(255, 255, 255, 75);
            sf::Color outline(0, 0, 0, 75);
            std::string pos = std::to_string((int)position.x) + "_" + std::to_string((int)position.y);

            // Start && End
            if(i == columns/2) {
                if(j == rows/3) {
                    addEntity(pos, position, size, fill, outline, true, false, false);
                    mStartNode = mEntities.at(pos).get();
                } else if(j == (int)(rows/1.5)) {
                    addEntity(pos, position, size, fill, outline, false, true, false);
                    mGoalNode = mEntities.at(pos).get();
                } else {
                    addEntity(pos, position, size, fill, outline, false, false, false);
                }
            } else {
                addEntity(pos, position, size, fill, outline, false, false, false);
            }
        }
    }
}


Entity* const World::getEntityAtPosition(int x, int y) const {

    // Get amount of nodes up to mouse position
    int row = x / (int)BOX_SIZE;
    int column = y / (int)BOX_SIZE;

    // Calculate proper node position
    row *= BOX_SIZE;
    column *= BOX_SIZE;

    // Create map-key
    std::string pos = std::to_string(row) + "_" + std::to_string(column);

    // Return the entity at the found position
    // Or NULL if the there is no entity
    try {
        return mEntities.at(pos).get();    
    } catch(std::out_of_range c) {
        return NULL;
    }

}

void World::setStartNode(Entity* const ent)
{
    mStartNode = ent;
}

void World::setGoalNode(Entity* const ent)
{
    mGoalNode = ent;
}

void World::findPath(Heuristic heu)
{
    // Reset previously found path and open/closed nodes
    clearPath();

    // Set up start node
    Entity* start = mStartNode;
    start->node.state = NodeState::OPEN;

    // Set up open list and add start node
    std::map<std::string, Entity*> openList;
    openList[start->getIndex()] = start;

    // The last node which was processed before temrinating the algorithm
    Entity* current = NULL;

    // As long as we have nodes in our open list,
    // and no stop criteria occured, proccess the nodes
    // to find the best path
    while(openList.size() > 0)
    {
        // Find the node with the best score (cost)
        current = getLowestScore(openList, heu);

        // If the chosen node is our goal, terminate
        if(current == mGoalNode)
            break;

        // Get all valid neighbors (adjacent nodes)
        auto neighbors = getValidNodes(current, false);

        // Process all neighbors
        for(auto& neighbor : neighbors)
        {
            // Get reference to our entity
            // Make sure we do not go out of bounds
            Entity* neigh = NULL;
            try 
            {
                neigh = mEntities.at(neighbor).get();
            }
            catch(std::out_of_range ex)
            {
                continue; 
            }

            // If the node is closed already, conitnue with the next neighbor
            if(neigh->node.state == NodeState::CLOSED)
                continue;

            // If it is already open, check if our current score (cost) is better (lower)
            // than the one in the open node. If it is, replace the cost and parent node
            if(neigh->node.state == NodeState::OPEN)
            {
                float currentScore = current->node.costSoFar+1;
                if(currentScore < neigh->node.costSoFar)
                {
                    neigh->node.costSoFar = currentScore;
                    neigh->node.parent = current;
                }
            }

            // If it has not been visited yet, add it to the open list
            if(neigh->node.state == NodeState::UNVISITED)
            {
                openList[neigh->getIndex()] = neigh;
                neigh->node.costSoFar = current->node.costSoFar + 1;
                neigh->node.parent = current;
                if(!neigh->node.isStart && !neigh->node.isGoal)
                {
                    neigh->setColor(sf::Color(0, 200, 0, 100));
                }
            }
        }

        // All neighbors have been processed, put our current node into the closed list
        // and remove it from the open list
        if(!current->node.isStart && !current->node.isGoal)
        {
            current->setColor(sf::Color(0, 200, 200, 100));
        }
        current->node.state = NodeState::CLOSED;
        openList.erase(current->getIndex());
    }

    // If our current node is not the goal, there is no solution
    if(current != mGoalNode)
    {
        // No solution

    // If it is, find the correct path via the parent of each node
    } else {
        while(current != mStartNode)
        {
            if(current != mGoalNode)
            {
                current->setColor(sf::Color::Yellow);
                current->node.isPath = true;
            }
            current = current->node.parent;
        }
    }
}

Entity* World::getLowestScore(std::map<std::string, Entity*> openList, Heuristic heu) const
{

    // Iterate over all nodes in the open list
    // and find the one with the lowest score (cost)
    Entity* result = NULL;
    for(auto& ent : openList)
    {
        if(result == NULL)
        {
            result = ent.second;
        }

        // Get the Heuristic values
        float entHeu = (getHeuristicValue(heu, ent.second));
        float resultHeu = (getHeuristicValue(heu, result));

        if(ent.second->node.costSoFar + entHeu < result->node.costSoFar + resultHeu)
            result = ent.second;
    }

    return result;
}

float World::getHeuristicValue(Heuristic heu, const Entity* const ent) const
{
    float result = 0;

    // Switch for the different Heuristic algorithms
    switch(heu)
    {
        // No Heuristic, return 0
        // It's basically a Dijkstra
        case Heuristic::NONE:
            break;
        // Euclidean Heuristic
        // Get the air-line distance between the current node and the goal
        case Heuristic::EUCLIDEAN:
        {
            sf::Vector2f entPos = ent->getPosition();
            sf::Vector2f goalPos = mGoalNode->getPosition();
            float distX = abs(entPos.x - goalPos.x);
            float distY = abs(entPos.y - goalPos.y);
            result = sqrt(pow(distX, 2) + pow(distY, 2)) / (BOX_SIZE/2);
            break;
        }
        default:
            break;
    }

    return result;
}

std::vector<std::string> World::getValidNodes(const Entity* const ent, bool dia) const
{
    std::vector<std::string> neighbors = ent->getNeighbors(dia);

    std::vector<std::string> valid;

    for(auto& neigh : neighbors)
    {
        Entity* current = NULL;

        try
        {
            current = mEntities.at(neigh).get();
        }
        catch (std::out_of_range ex)
        {
            continue;
        }
        
        if(!current->node.isWall)
            valid.push_back(neigh);
    }

    return valid;
}

void World::resetWorld(int width, int height)
{
    mEntities.clear();
    createWorld(width, height);
}

void World::clearPath()
{
    for(auto& ent : mEntities)
    {
        ent.second->node.costSoFar = 0;
        ent.second->node.parent = NULL;
        ent.second->node.state = NodeState::UNVISITED;

        if(ent.second->node.isPath && !ent.second->node.isWall)
            ent.second->setColor(NODE_FREE);
        else if(!ent.second->node.isPath && !ent.second->node.isWall && !ent.second->node.isStart && !ent.second->node.isGoal)
            ent.second->setColor(NODE_FREE);
    }
}
