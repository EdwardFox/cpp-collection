#ifndef GAME_HPP
#define GAME_HPP

#include "World.hpp"
#include "Data.hpp"

class Game
{
    public:
        /**
         * @brief Default constructor
         */
        Game(int width, int height);

        /**
         * @brief Entry point for the game to run
         */
        void run();

        /**
         * @brief Renders all the elements on the screen
         */
        void render();

        /**
         * @brief Defines how many updates per second are made
         */
        static const sf::Time TimePerFrame;

    private:
        /**
        * @brief Updates the game
        *
        * @param dt Time passed between 2 update ticks
        */
        void update(sf::Time dt);

        /**
        * @brief Process events (user input, closing, etc.)
        */
        void processInput();
        
        /**
        * @brief React to player input (keyboard only right now)
        *
        * @param key The pressed key
        * @param isPressed Pressed or released
        */
        void handleInput(sf::Event event);

        /**
        * @brief The SFML window
        */
        sf::RenderWindow mWindow;

        /**
        * @brief The World which contains our entities
        */
        World mWorld;

        /**
        * @brief Tracks the current input state to handle adding/removing blocks etc.
        */
        InputState mInputState;

        /**
        * @brief Tracks the previous entity when moving goal / start nodes
        */
        Entity* mPreviousEnt;

        /**
        * @brief Keep track of current heuristic to toggle inbetween
        */
        Heuristic mHeuristic;
};

#endif
