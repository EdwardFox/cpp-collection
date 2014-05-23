C++ Code Collection
==============

This repository is a collection of useful modern c++11 concepts and implementations mostly related to game development. Quite a few of the concepts were and will be taken from the SFML Game Development book.
The current selection includes:

* **Simple Box2D Implementation**
    - A simple implementation of Box2D 2.3.0 using SFML 2.1
    - Includes a proper gameloop with unlimited frames and an update rate of 60 times per second
    - Memory management via smart pointers

* **Pathfinding example**
    - An example implementation of Dijkstra and A\* Pathfinding algorithms
    - Uses SFML for input and visualization
    - Controls:
        - Drag&Drop start and end nodes
        - Click&Drag to create/remove walls
        - H key will toggle between Dijkstra and A\*
        - Visual updates occur when creating/removing walls and toggling between the pathfinding algorithms
