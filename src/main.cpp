#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <box2d/box2d.h>
using namespace sf;
using namespace std;


const int gameWidth = 1000;
const int gameHeight = 800;

b2World* world;

std::vector<b2Body*> bodies;
//Sprites


//main.cpp
// 1 sfml unit = 30 physics units
//Todo



//Create a Box2D body with a box fixture
b2Body* CreatePhysicsBox(b2World& World, const bool dynamic, const Vector2f& position, const Vector2f& size) {
  //todo
}

// Create a Box2d body with a box fixture, from a sfml::RectangleShape


void init() {
    const b2Vec2 gravity(0.0f, -10.0f);

    // Construct a world, which holds and simulates the physics bodies.
    world = new b2World(gravity);
    //ToDO

    

    //wall dimensions - ToDo
 

    //build walls ToDo
    
}
void Update()
{
    //clock stuff
    static sf::Clock clock;
    float dt = ...
//todo
        
}
int main()
{
    RenderWindow window(VideoMode(gameWidth, gameHeight), "SFML works!");
    init();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        Update();
        for (auto s : sprites)
            window.draw(*s);
        window.display();
    }
    return 0;
}
