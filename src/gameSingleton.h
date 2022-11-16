//
// Created by dflynn on 19/09/2022.
//

#ifndef CMAKESFMLPROJECT_GAMESINGLETON_H
#define CMAKESFMLPROJECT_GAMESINGLETON_H

#include <SFML/Window.hpp>


class gameSingleton
{
public:
    ~gameSingleton()
    {
        delete window;
        //ToDo initialise flag
    }

    void gameLoop();
    static gameSingleton* getInstance(){
        //ToDo: check if instance has been created before or not.
        //If not then create it.
        if (!bCheckFlag)
            {
                s_singleInstance = new gameSingleton();
                bCheckFlag = true;
                return s_singleInstance;
            }
            else {
                return s_singleInstance;
            }
    }
private:
    //flag checking for single instance
    static bool bCheckFlag;
    //Static pointer to instance
    static gameSingleton *s_singleInstance;

    sf::Event event;
    sf::Window *window;
    //Very important Singleton implementation part
    gameSingleton() //private constructor
    {

    }
};


#endif //CMAKESFMLPROJECT_GAMESINGLETON_H
