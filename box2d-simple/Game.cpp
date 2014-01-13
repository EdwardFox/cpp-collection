#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game() :
mWindow(sf::VideoMode(800, 600, 32), "Box2D Simple")
, mWorld()
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
            processEvents();
            update(TimePerFrame);
            timeSinceLastUpdate -= TimePerFrame;
        }
        render();
    }
}

void Game::update(sf::Time dt)
{
    mWorld.update(dt);
}

void Game::render()
{
    mWindow.clear();
    mWorld.draw(mWindow);
    mWindow.display();
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::W && isPressed)
    {
        mWorld.addEntity(400.f, 100.f);
    }
}
