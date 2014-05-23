#include "Entity.hpp"

Entity::Entity() :
node()
, mShape()
{
    node.state = NodeState::UNVISITED;
    node.parent = NULL;
    node.costSoFar = 0;
    node.isPath = false;
    node.isWall = false;
    node.isStart = false;
    node.isGoal = false;
}

    
Entity::Entity(sf::Vector2f position, sf::Vector2f size, sf::Color fill, sf::Color outline, bool isStart, bool isGoal, bool isWall) {
    mShape.setSize(size);
    mShape.setPosition(position.x, position.y);
    mShape.setFillColor(fill);
    mShape.setOutlineColor(outline);
    mShape.setOutlineThickness(1.0f);

    node.state = NodeState::UNVISITED;
    node.parent = NULL;
    node.costSoFar = 0;
    node.isPath = false;

    node.isWall = isWall;
    node.isStart = isStart;
    node.isGoal = isGoal;

    if(isStart)
        setColor(NODE_START);

    if(isGoal)
        setColor(NODE_GOAL);
}

void Entity::update(sf::Time dt) 
{

}

void Entity::draw(sf::RenderTarget &target) const
{
    target.draw(mShape);
}

void Entity::setColor(sf::Color c) 
{
    mShape.setFillColor(c);
}

void Entity::setBorderColor(sf::Color c)
{
    mShape.setOutlineColor(c);
}

std::vector<std::string> Entity::getNeighbors(bool diagonal) const
{
    std::vector<std::string> neighbors;

    // Top
    neighbors.push_back(std::to_string((int)mShape.getPosition().x) + "_" + std::to_string((int)mShape.getPosition().y - (int)BOX_SIZE));

    // Top Right
    if(diagonal)
        neighbors.push_back(std::to_string((int)mShape.getPosition().x + (int)BOX_SIZE) + "_" + std::to_string((int)mShape.getPosition().y - (int)BOX_SIZE));

    // Right
    neighbors.push_back(std::to_string((int)mShape.getPosition().x + (int)BOX_SIZE) + "_" + std::to_string((int)mShape.getPosition().y));

    // Right Bottom
    if(diagonal)
        neighbors.push_back(std::to_string((int)mShape.getPosition().x + (int)BOX_SIZE) + "_" + std::to_string((int)mShape.getPosition().y + (int)BOX_SIZE));

    // Bottom
    neighbors.push_back(std::to_string((int)mShape.getPosition().x) + "_" + std::to_string((int)mShape.getPosition().y + (int)BOX_SIZE));

    // Bottom Left
    if(diagonal)
        neighbors.push_back(std::to_string((int)mShape.getPosition().x - (int)BOX_SIZE) + "_" + std::to_string((int)mShape.getPosition().y + (int)BOX_SIZE));

    // Left
    neighbors.push_back(std::to_string((int)mShape.getPosition().x - (int)BOX_SIZE) + "_" + std::to_string((int)mShape.getPosition().y));

    // Left Top
    if(diagonal)
        neighbors.push_back(std::to_string((int)mShape.getPosition().x - (int)BOX_SIZE) + "_" + std::to_string((int)mShape.getPosition().y - (int)BOX_SIZE));

    return neighbors;
}

std::string Entity::getIndex()
{
    return (std::to_string((int)mShape.getPosition().x) + "_" + std::to_string((int)mShape.getPosition().y));
}

sf::Vector2f Entity::getPosition() const
{
    return mShape.getPosition();
}
