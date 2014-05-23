#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

static const float BOX_SIZE = 32.0f;
static const sf::Color NODE_FREE = sf::Color::White;
static const sf::Color NODE_BLOCKED = sf::Color(155, 155, 155, 255);
static const sf::Color NODE_START = sf::Color::Green;
static const sf::Color NODE_GOAL = sf::Color::Red;

enum class InputState
{
    NONE,
    ADD,
    REMOVE,
    MOVE_START,
    MOVE_GOAL
};

enum class Heuristic
{
    NONE,
    EUCLIDEAN,
    CLUSTER
};

enum class NodeState
{
    UNVISITED,
    OPEN,
    CLOSED
};

#endif
