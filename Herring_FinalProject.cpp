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
    Vector2f newPos(paddle.getCenter());
    if (Keyboard::isKeyPressed(Keyboard::W) && newPos.y > 50) {
        newPos.y = newPos.y - (KB_SPEED * elapsedMS);
        paddle.setCenter(newPos);
    }
    if (Keyboard::isKeyPressed(Keyboard::S) && newPos.y < 550) {
        newPos.y = newPos.y + (KB_SPEED * elapsedMS);
        paddle.setCenter(newPos);
    }
}

void MovePaddle2(PhysicsSprite& paddle, int elapsedMS) {
    Vector2f newPos(paddle.getCenter());
    if (Keyboard::isKeyPressed(Keyboard::Up) && newPos.y > 50) {
        newPos.y = newPos.y - (KB_SPEED * elapsedMS);
        paddle.setCenter(newPos);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && newPos.y < 550) {
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
    RenderWindow window(VideoMode(800, 600), "Pong");
    World world(Vector2f(0, 0));
    int score1(0);
    int score2(0);
    Vector2f currentVelo(.20, .20);

    PhysicsCircle ball;
    ball.setRadius(25);
    ball.setCenter(Vector2f(400, 300));
    ball.setVelocity(currentVelo);
    world.AddPhysicsBody(ball);

    PhysicsSprite paddle1;
    Texture paddleTex;
    LoadTex(paddleTex, "paddle.png");
    paddle1.setTexture(paddleTex);
    paddle1.setCenter(Vector2f(50, 300));
    paddle1.setStatic(true);
    world.AddPhysicsBody(paddle1);
    paddle1.onCollision = [&ball, &currentVelo](PhysicsBodyCollisionResult result) {
        currentVelo.x = -(currentVelo.x);
        ball.setVelocity(currentVelo);
        };

    PhysicsSprite paddle2;
    paddle2.setTexture(paddleTex);
    paddle2.setCenter(Vector2f(750, 300));
    paddle2.setStatic(true);
    world.AddPhysicsBody(paddle2);
    paddle2.onCollision = [&ball, &currentVelo](PhysicsBodyCollisionResult result) {
        currentVelo.x = -(currentVelo.x);
        ball.setVelocity(currentVelo);
        };


    PhysicsRectangle top;
    top.setSize(Vector2f(800, 10));
    top.setCenter(Vector2f(400, 5));
    top.setStatic(true);
    world.AddPhysicsBody(top);
    top.onCollision = [&ball, &currentVelo](PhysicsBodyCollisionResult result) {
        currentVelo.y = -(currentVelo.y);
        ball.setVelocity(currentVelo);
        };

    PhysicsRectangle bottom;
    bottom.setSize(Vector2f(800, 10));
    bottom.setCenter(Vector2f(400, 595));
    bottom.setStatic(true);
    world.AddPhysicsBody(bottom);
    bottom.onCollision = [&ball, &currentVelo](PhysicsBodyCollisionResult result) {
        currentVelo.y = -(currentVelo.y);
        ball.setVelocity(currentVelo);
        };


    PhysicsRectangle left;
    left.setSize(Vector2f(10, 600));
    left.setCenter(Vector2f(5, 300));
    left.setStatic(true);
    world.AddPhysicsBody(left);
    left.onCollision = [&ball, &score2, &currentVelo](PhysicsBodyCollisionResult result) {
        if (result.object2 == ball) {
            score2++;
            if (score2 < 3) {
                ball.setCenter(Vector2f(400, 300));
                currentVelo = Vector2f(-.20, .20);
                ball.setVelocity(currentVelo);
            }
        }
        };


    PhysicsRectangle right;
    right.setSize(Vector2f(10, 600));
    right.setCenter(Vector2f(795, 300));
    right.setStatic(true);
    world.AddPhysicsBody(right);
    right.onCollision = [&ball, &score1, &currentVelo](PhysicsBodyCollisionResult result) {
        if (result.object2 == ball) {
            score1++;
            if (score1 < 3) {
                ball.setCenter(Vector2f(400, 300));
                currentVelo = Vector2f(.20, .20);
                ball.setVelocity(currentVelo);
            }
        }
        };




   





    Font fnt;
    if (!fnt.loadFromFile("arial.ttf")) {
        cout << "Could not load font." << endl;
        exit(3);
    }
    Clock clock;
    Time lastTime(clock.getElapsedTime());
    Time currentTime(lastTime);
    while (score1 < 3 && score2 < 3) {
        currentTime = clock.getElapsedTime();
        Time deltaTime = currentTime - lastTime;
        long deltaMS = deltaTime.asMilliseconds();
        if (deltaMS > 9) {

            lastTime = currentTime;
            world.UpdatePhysics(deltaMS);
            MovePaddle1(paddle1, deltaMS);
            MovePaddle2(paddle2, deltaMS);

            

           
        }

        

        window.clear();



        window.draw(paddle1);
        window.draw(paddle2);
        window.draw(ball);
        window.draw(top);
        window.draw(bottom);
        window.draw(left);
        window.draw(right);
       
        Text score1Text;
        score1Text.setString(to_string(score1));
        score1Text.setFont(fnt);
        score1Text.setPosition(Vector2f(300, 30));
        window.draw(score1Text);
        Text score2Text;
        score2Text.setString(to_string(score2));
        score2Text.setFont(fnt);
        score2Text.setPosition(Vector2f(480, 30));
        window.draw(score2Text);
        //world.VisualizeAllBounds(window);


        window.display();
        if (score1 >= 3) {
            cout << "Player 1 Wins!" << endl;
            window.close();
            break;
        }
        else if (score2 >= 3) {
            cout << "Player 2 Wins!" << endl;
            window.close();
            break;
        }

    }
}

   

