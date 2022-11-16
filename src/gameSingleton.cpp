//
// Created by dflynn on 19/09/2022.
//

#include "gameSingleton.h"
void gameSingleton::gameLoop()
{

    while (this->window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        //ToDo: Poll events
        {
            // "close requested" event: we close the window
            //ToDo: if close event then close
        }
    }


}

gameSingleton::gameSingleton()
{
    window = new sf::Window(sf::VideoMode(800,600),"My window");
}

//bool gameSingleton::????? = false;
//ToDo implment the rest of the above here
//gameSingleton* gameSingleton::something??? = NULL;
//ToDo implement the above.