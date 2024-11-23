#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
using namespace sfp;

const float KB_SPEED = 0.2;

void LoadTex(Texture& tex, string filename) {
    if (!tex.loadFromFile(filename)) {
        cout << "Could not load " << filename << endl;
    }
}

void MovePaddle1(PhysicsSprite& paddle, int elapsedMS) {
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        Vector2f newPos(paddle.getCenter());
        newPos.y = newPos.y - (KB_SPEED * elapsedMS);
        paddle.setCenter(newPos);
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        Vector2f newPos(paddle.getCenter());
        newPos.y = newPos.y + (KB_SPEED * elapsedMS);
        paddle.setCenter(newPos);
    }
}

void MovePaddle2(PhysicsSprite& paddle, int elapsedMS) {
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        Vector2f newPos(paddle.getCenter());
        newPos.y = newPos.y - (KB_SPEED * elapsedMS);
        paddle.setCenter(newPos);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        Vector2f newPos(paddle.getCenter());
        newPos.y = newPos.y + (KB_SPEED * elapsedMS);
        paddle.setCenter(newPos);
    }
}

Vector2f GetTextSize(Text text) {
    FloatRect r = text.getGlobalBounds();
    return Vector2f(r.width, r.height);
}



int main()
{
    RenderWindow window(VideoMode(800, 600), "Balloon Buster");
    World world(Vector2f(0, 0));
    int score1(0);
    int score2(0);



    PhysicsSprite paddle1;
    Texture paddleTex;
    LoadTex(paddleTex, "paddle.png");
    paddle1.setTexture(paddleTex);
    paddle1.setCenter(Vector2f(30, 300));
    world.AddPhysicsBody(paddle1);

    PhysicsSprite paddle2;
    paddle2.setTexture(paddleTex);
    paddle2.setCenter(Vector2f(770, 300));
    world.AddPhysicsBody(paddle2);

    PhysicsCircle ball;
    ball.setSize(Vector2f(50, 50));
    ball.setCenter(Vector2f(400, 300));
    world.AddPhysicsBody(ball);

    PhysicsRectangle top;
    top.setSize(Vector2f(800, 10));
    top.setCenter(Vector2f(400, 5));
    top.setStatic(true);
    world.AddPhysicsBody(top);

    PhysicsRectangle left;
    left.setSize(Vector2f(10, 600));
    left.setCenter(Vector2f(5, 300));
    left.setStatic(true);
    world.AddPhysicsBody(left);

    PhysicsRectangle right;
    right.setSize(Vector2f(10, 600));
    right.setCenter(Vector2f(795, 300));
    right.setStatic(true);
    world.AddPhysicsBody(right);
    right.onCollision = [&ball](PhysicsBodyCollisionResult result) {
        
    };


    PhysicsShapeList<PhysicsSprite> ducks;





    Font fnt;
    if (!fnt.loadFromFile("arial.ttf")) {
        cout << "Could not load font." << endl;
        exit(3);
    }
    Clock clock;
    Time lastTime(clock.getElapsedTime());
    Time currentTime(lastTime);
    Time lastDuckTime(clock.getElapsedTime());
    while (score1 == 0) {
        currentTime = clock.getElapsedTime();
        Time deltaTime = currentTime - lastTime;
        long deltaMS = deltaTime.asMilliseconds();
        if (deltaMS > 9) {

            lastTime = currentTime;
            world.UpdatePhysics(deltaMS);
            MovePaddle1(paddle1, deltaMS);
            MovePaddle2(paddle2, deltaMS);

            

           
        }
        



        window.draw(paddle1);
        window.draw(paddle2);
       
        Text score1Text;
        score1Text.setString(to_string(score1));
        score1Text.setFont(fnt);
        window.draw(score1Text);
        Text score2Text;
        score2Text.setString(to_string(score2));
        score2Text.setFont(fnt);
        //world.VisualizeAllBounds(window);

        window.display();

    }
}

   

