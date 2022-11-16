#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <box2d/box2d.h>
using namespace sf;
using namespace std;


const int gameWidth = 1000;
const int gameHeight = 800;

b2World* world;

std::vector<b2Body*> bodies;
std::vector<RectangleShape*> sprites;


//main.cpp
// 1 sfml unit = 30 physics units
const float physics_scale = 30.0f;
// inverse of physics_scale, useful for calculations
const float physics_scale_inv = 1.0f / physics_scale;
// Magic numbers for accuracy of physics simulation
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

//Convert from b2Vec2 to a Vector2f
inline const Vector2f bv2_to_sv2(const b2Vec2& in) {
    return Vector2f(in.x * physics_scale, (in.y * physics_scale));
}
//Convert from Vector2f to a b2Vec2
inline const b2Vec2 sv2_to_bv2(const Vector2f& in) {
    return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
}
//Convert from screenspace.y to physics.y (as they are the other way around)
inline const Vector2f invert_height(const Vector2f& in) {
    return Vector2f(in.x, gameHeight - in.y);
}

//Create a Box2D body with a box fixture
b2Body* CreatePhysicsBox(b2World& World, const bool dynamic, const Vector2f& position, const Vector2f& size) {
    b2BodyDef BodyDef;
    //Is Dynamic(moving), or static(Stationary)
    BodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
    BodyDef.position = sv2_to_bv2(position);
    //Create the body
    b2Body* body = World.CreateBody(&BodyDef);

    //Create the fixture shape
    b2PolygonShape Shape;
    Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    b2FixtureDef FixtureDef;
    //Fixture properties
    FixtureDef.density = dynamic ? 10.f : 0.f;
    FixtureDef.friction = dynamic ? 0.8f : 1.f;
    FixtureDef.restitution = 1.0;
    FixtureDef.shape = &Shape;
    //Add to body
    body->CreateFixture(&FixtureDef);
    return body;
}

// Create a Box2d body with a box fixture, from a sfml::RectangleShape
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const RectangleShape& rs) {
    return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}

void init() {
    const b2Vec2 gravity(0.0f, -10.0f);

    // Construct a world, which holds and simulates the physics bodies.
    world = new b2World(gravity);
    //ToDO

    for (int i =1; i<11; ++i){
        auto s = new RectangleShape();
                s->setPosition(Vector2f(i* (gameWidth/12.), gameHeight * .7));
                s->setSize(Vector2f(50, 50));
                s->setOrigin(Vector2f(25, 25) );
                s->setFillColor(Color::White);
                sprites.push_back(s);

                auto b = CreatePhysicsBox(*world, true, *s);
                b->ApplyAngularImpulse(5.0, true);
                bodies.push_back(b);

    }

    //wall dimensions
    Vector2f walls[]= {
            //top
            Vector2f(gameWidth * 0.5f, 5.f), Vector2f(gameWidth, 10.f),
            //bottom
            Vector2f(gameWidth * 0.5f, gameHeight - 5.f), Vector2f(gameWidth, 10.f),
            //left
            Vector2f(5.f, gameHeight * 0.5f), Vector2f(10.f, gameHeight),
            //right
            Vector2f(gameWidth - 5.f, gameHeight * 0.5f), Vector2f(10.f, gameHeight)
    };

    //build walls
    for (int i = 0; i < 7; i += 2) {
        auto s = new RectangleShape();
        s->setPosition(walls[i]);
        s->setSize(walls[i + 1]);
        s->setOrigin(walls[i + 1] * 0.5f);
        s->setFillColor(Color::White);
        sprites.push_back(s);

        auto b = CreatePhysicsBox(*world, false, *s);
        //create boxes
        bodies.push_back(b);
    }
}
void Update()
{
    static sf::Clock clock;
    float dt = clock.restart().asSeconds();

    world->Step(dt, velocityIterations, positionIterations);

    for (int i = 0; i < bodies.size(); ++i)
    {
       //sync sprites to phusics position
        sprites[i]->setPosition(invert_height(bv2_to_sv2(bodies[i]->GetPosition())));

        sprites[i]->setRotation(bodies[i]->GetAngle() * 180 / b2_pi);
    }
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