#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(int width, int height) :
mWindow(sf::VideoMode(width, height, 32), "AIGames")
, mWorld(width, height)
, mInputState(InputState::NONE)
, mPreviousEnt(NULL)
, mHeuristic(Heuristic::NONE)
{
    
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();       
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::update(sf::Time dt)
{
    mWorld.update(dt);
    mWorld.findPath(mHeuristic);
}

void Game::render()
{
    mWindow.clear(sf::Color::White);
    mWorld.draw(mWindow);
    mWindow.display();
}

void Game::processInput()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        handleInput(event);

        if(event.type == sf::Event::Closed)
            mWindow.close();

        if(event.type == sf::Event::Resized) {
            mWindow.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
            mWorld.resetWorld(event.size.width, event.size.height);
        }
    }
}

void Game::handleInput(sf::Event event)
{
    // Keyboard Input Stuff
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
        mWorld.resetWorld(mWindow.getSize().x, mWindow.getSize().y);

    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H)
    {
        if(mHeuristic == Heuristic::NONE)
            mHeuristic = Heuristic::EUCLIDEAN;
        else
            mHeuristic = Heuristic::NONE;

        //mWorld.findPath(mHeuristic);
    }
        
    // Mouse Input Stuff
    // Get entity at current mouse position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
    Entity* ent = mWorld.getEntityAtPosition(mousePosition.x, mousePosition.y);

    // If we have found an entity, handle the different input states for left clicking
    if(ent != NULL) {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //mWorld.findPath(mHeuristic);

            switch(mInputState) {
                // Check which kind of node we have clicked and set state accordingly
                case InputState::NONE:
                    if(ent->node.isWall)
                        mInputState = InputState::REMOVE;
                    else
                        mInputState = InputState::ADD;

                    if(ent->node.isStart)
                        mInputState = InputState::MOVE_START;
                    if(ent->node.isGoal)
                        mInputState = InputState::MOVE_GOAL;
                    break;

                // Turn all free nodes into walls
                case InputState::ADD:
                    if(!ent->node.isWall && !ent->node.isStart && !ent->node.isGoal) {
                        ent->node.isWall = true;
                        ent->setColor(NODE_BLOCKED);
                    }
                    break;

                // Turn all walls into free nodes
                case InputState::REMOVE:
                    if(ent->node.isWall && !ent->node.isStart && !ent->node.isGoal) {
                        ent->node.isWall = false;
                        ent->setColor(NODE_FREE);
                    }
                    break;

                // Drag the start node around
                case InputState::MOVE_START:
                    if(mPreviousEnt == NULL) {
                        mPreviousEnt = ent;
                    }

                    // If the current node is not the old node,
                    // return the old one to its previous state
                    // and make the new node the start node
                    if(mPreviousEnt != ent && !ent->node.isGoal) {
                        mPreviousEnt->node.isStart = false;
                        if(mPreviousEnt->node.isWall) {
                            mPreviousEnt->setColor(NODE_BLOCKED);
                        } else {
                            mPreviousEnt->setColor(NODE_FREE);
                        }

                        mWorld.setStartNode(ent);
                        ent->node.isStart = true;
                        ent->setColor(NODE_START);
                        mPreviousEnt = ent;
                    }
                    break;

                // Drag the goal node around
                case InputState::MOVE_GOAL:
                    if(mPreviousEnt == NULL) {
                        mPreviousEnt = ent;
                    }

                    // If the current node is not the old node
                    // return the old one to its previous state
                    // and make the new node the goal node
                    if(mPreviousEnt != ent && !ent->node.isStart) {
                        mPreviousEnt->node.isGoal = false;
                        if(mPreviousEnt->node.isWall) {
                            mPreviousEnt->setColor(NODE_BLOCKED);
                        } else {
                            mPreviousEnt->setColor(NODE_FREE);
                        }

                        mWorld.setGoalNode(ent);
                        ent->node.isGoal = true;
                        ent->setColor(NODE_GOAL);
                        mPreviousEnt = ent;
                    }
                    break;

                // Reset state
                default:
                    mInputState = InputState::NONE;
                    break;
            }

        // Reset state and previous entity if we are not clicking
        } else {
            mInputState = InputState::NONE;
            mPreviousEnt = NULL;
        }
    }
}
