/*
  Games Development with C++ GAV1031-N
  Snake ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include <iostream>

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include "Ball.h"

struct Boundary {
public:
    sf::Vector2f pointOne;
    sf::Vector2f pointTwo;
    sf::Vector2f BoundaryDirection;
    std::pair<sf::Vector2f, sf::Vector2f> normals;
};

bool PlaceIsTaken(sf::Vector2f pos1, sf::Vector2f pos2);
bool CheckForStaticCollision(Ball& b1, Ball& b2, sf::Vector2f v, float r1, float r2);
void CalculateCollision(Ball& b1, Ball& b2, sf::Vector2f v, float r1, float r2);
bool CheckForSideCollision(Ball& b, Boundary& w);
bool CheckForMovingCollision(Ball& b1, Ball& b2);
void CalculateMovingCollision(Ball& b1, Ball& b2);
void TakeShot(sf::Vector2f m, Ball& b1);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Cue Ball Ricochet");

    sf::Vector2f(100.0f, 100.0f);
    std::srand((unsigned int)time(NULL));
    sf::Font font;

    if (!font.loadFromFile("Data\\Fonts\\Nasa21-l23X.ttf")) {
        return 0;
    }

    std::vector<Ball> balls;
    std::vector<Boundary> Boundaries;

    //Creates the balls and puts them at specified positions on the screen. Player ball is at positions 200/200 and the rest are at random points on the screen.
    balls.push_back(Ball(sf::Vector2f(200.0f, 200.0f), sf::Vector2f(0.0f, 0.0f), sf::Color::Black, 0));

    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 1));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 2));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 3));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 4));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 5));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 6));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 7));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 8));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 9));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 10));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 11));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 12));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 13));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 14));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 15));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 16));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 17));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 18));
    balls.push_back(Ball(sf::Vector2f((float)(rand() % 965), (float)(rand() % 565)), sf::Vector2f(0.0f, 0.0f), sf::Color::White, 19));

    //Creates the boundaries for the playboard (area in which the balls are to prevent them going out of reach)
    Boundary BoundaryOne;
    BoundaryOne.pointOne = sf::Vector2f(5.0f, 5.0f);
    BoundaryOne.pointTwo = sf::Vector2f(995.0f, 5.0f);
    BoundaryOne.BoundaryDirection = BoundaryOne.pointTwo - BoundaryOne.pointOne;
    Boundary BoundaryTwo;
    BoundaryTwo.pointOne = sf::Vector2f(5.0f, 5.0f);
    BoundaryTwo.pointTwo = sf::Vector2f(5.0f, 595.0f);
    BoundaryTwo.BoundaryDirection = BoundaryTwo.pointTwo - BoundaryTwo.pointOne;
    Boundary BoundaryThree;
    BoundaryThree.pointOne = sf::Vector2f(995.0f, 5.0f);
    BoundaryThree.pointTwo = sf::Vector2f(995.0f, 595.0f);
    BoundaryThree.BoundaryDirection = BoundaryThree.pointTwo - BoundaryThree.pointOne;
    Boundary BoundaryFour;
    BoundaryFour.pointOne = sf::Vector2f(5.0f, 595.0f);
    BoundaryFour.pointTwo = sf::Vector2f(995.0f, 595.0f);
    BoundaryFour.BoundaryDirection = BoundaryFour.pointTwo - BoundaryFour.pointOne;

    float dx = BoundaryOne.pointTwo.x - BoundaryOne.pointOne.x;
    float dy = BoundaryOne.pointTwo.y - BoundaryOne.pointOne.y;
    BoundaryOne.normals.first = sf::Vector2f(-dy, dx);
    BoundaryOne.normals.second = -BoundaryOne.normals.first;

    dx = BoundaryTwo.pointTwo.x - BoundaryTwo.pointOne.x;
    dy = BoundaryTwo.pointTwo.y - BoundaryTwo.pointOne.y;
    BoundaryTwo.normals.first = sf::Vector2f(-dy, dx);
    BoundaryTwo.normals.second = -BoundaryTwo.normals.first;

    dx = BoundaryThree.pointTwo.x - BoundaryThree.pointOne.x;
    dy = BoundaryThree.pointTwo.y - BoundaryThree.pointOne.y;
    BoundaryThree.normals.first = sf::Vector2f(dy, -dx);
    BoundaryThree.normals.second = -BoundaryThree.normals.first;

    dx = BoundaryFour.pointTwo.x - BoundaryFour.pointOne.x;
    dy = BoundaryFour.pointTwo.y - BoundaryFour.pointOne.y;
    BoundaryFour.normals.first = sf::Vector2f(dy, -dx);
    BoundaryFour.normals.second = -BoundaryFour.normals.first;

    Boundaries.push_back(BoundaryOne);
    Boundaries.push_back(BoundaryTwo);
    Boundaries.push_back(BoundaryThree);
    Boundaries.push_back(BoundaryFour);

    sf::Color playboardColour = sf::Color(25, 115, 49);
    sf::RectangleShape playboard(sf::Vector2f(1000.0f, 600.0f));
    playboard.setPosition(sf::Vector2f(0, 0));
    playboard.setFillColor(playboardColour);


    //Checks to for collissions with the player ball in each frame of the program
    std::vector<bool> hasBallCollided;

    for (size_t i = 0; i < balls.size(); i++)
    {
        hasBallCollided.push_back(false);
    }

    bool shotPlayed{ false };
    bool gameOver{ false };

    //Main loop that continues until window is closed
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
            case sf::Event::MouseButtonPressed:
                //Fires starter ball if the shot has yet to be taken
                if (shotPlayed == false) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
                        TakeShot(mousePos, balls[0]);
                        shotPlayed = true;
                    }
                }
                break;
            case sf::Event::KeyReleased:
                //Resets the game state with the balls at a random position on the screen
                if (shotPlayed == true) {
                    if (event.key.code == sf::Keyboard::R) {
                        for (size_t i = 0; i < balls.size(); i++)
                        {
                            std::cout << "Ball " << i << std::endl;
                            bool placeOkay{ false };
                            while (placeOkay == false) {
                                balls[i].SetVelocity(sf::Vector2f(0.0f, 0.0f));
                                balls[i].SetPosition(sf::Vector2f((float)(std::rand() % 720) + 60, (float)(std::rand() % 520) + 60));
                                if (i == 0) {
                                    balls[i].SetColor(sf::Color::Black);
                                }
                                else {
                                    balls[i].SetColor(sf::Color::White);
                                }

                                for (size_t j = 0; j < balls.size(); j++) {
                                    if (balls[j].GetIndex() == balls[i].GetIndex()) {
                                        continue;
                                    }
                                    float rad = balls[j].GetRadius() + balls[i].GetRadius();
                                    sf::Vector2f diff = balls[j].GetPosition() - balls[i].GetPosition();
                                    float diffLength = std::sqrt((diff.x * diff.x) + (diff.y * diff.y));

                                    if (diffLength > rad) {
                                        std::cout << "No Overlap" << std::endl;
                                        placeOkay = true;
                                    }
                                    else {
                                        placeOkay = false;
                                        std::cout << "Overlap" << std::endl;
                                        break;
                                    }
                                }
                            }
                        }
                        shotPlayed = false;
                        gameOver = false;
                    }
                }
                break;
            default:
                break;
            }
        }

        bool collisionMade{ false };
        int playerScore{ 0 };

        //Main simulation
        if (shotPlayed == true && gameOver == false) {
            for (size_t i = 0; i < balls.size(); i++) {
                //Checks collisions for each moving ball against every other ball that isn't itself
                if (balls[i].GetVelocity().x != 0.0f || balls[i].GetVelocity().y != 0.0f) {
                    for (size_t j = 0; j < balls.size(); j++) {
                        if ((balls[i].GetIndex() != balls[j].GetIndex()) && hasBallCollided[j] == false) {
                            //If the other ball isn't moving, a moving collision is checked
                            if (balls[j].GetVelocity().x >= 0.0001f || balls[j].GetVelocity().y >= 0.0001f || balls[j].GetVelocity().x <= -0.0001f || balls[j].GetVelocity().y <= -0.0001f) {
                                bool collision = CheckForMovingCollision(balls[i], balls[j]);
                                hasBallCollided[i] = collision;

                                if (collision == true) {
                                    /*system.Reset();*/
                                    sf::Vector2f particlePos = (balls[j].GetPosition() - balls[i].GetPosition()) / 2.0f;
                                    particlePos = balls[i].GetPosition() + particlePos;
                                    /*system.SetRootPosition(particlePos);*/

                                    if (balls[i].GetColor() == sf::Color::Black && balls[j].GetColor() == sf::Color::White) {
                                        balls[j].SetColor(sf::Color::Black);
                                    }
                                    else if (balls[i].GetColor() == sf::Color::White && balls[j].GetColor() == sf::Color::Black) {
                                        balls[i].SetColor(sf::Color::Black);
                                    }
                                }
                            }
                            else { //Otherwise, a static collision is checked
                                bool collision = CheckForStaticCollision(balls[i], balls[j], balls[i].GetVelocity(), balls[i].GetRadius(), balls[j].GetRadius());
                                if (collision == true) {
                                    /*system.Reset();*/
                                    sf::Vector2f particlePos = (balls[j].GetPosition() - balls[i].GetPosition()) / 2.0f;
                                    particlePos = balls[i].GetPosition() + particlePos;
                                    /*system.SetRootPosition(particlePos);*/

                                    if (balls[i].GetColor() == sf::Color::Black && balls[j].GetColor() == sf::Color::White) {
                                        balls[j].SetColor(sf::Color::Black);
                                    }
                                    else if (balls[i].GetColor() == sf::Color::White && balls[j].GetColor() == sf::Color::Black) {
                                        balls[i].SetColor(sf::Color::Black);
                                    }
                                }
                            }
                        }
                    }
                    //If the ball has not hit another ball, a Boundary collision is checked
                    if (hasBallCollided[i] == false) {
                        for (size_t j = 0; j < Boundaries.size(); j++)
                        {
                            hasBallCollided[i] = CheckForSideCollision(balls[i], Boundaries[j]);
                        }
                    }
                }
            }

            for (size_t i = 0; i < balls.size(); i++) {
                balls[i].Update();
                hasBallCollided[i] = false;
                if (balls[i].GetColor() == sf::Color::Black) {
                    playerScore = playerScore + 10;
                }
            }

            gameOver = true;

            //Ends the game if all balls have reached a near stationary point
            for (size_t i = 0; i < balls.size(); i++) {
                if ((balls[i].GetVelocity().x <= 0.00001f && balls[i].GetVelocity().x >= -0.00001f && balls[i].GetVelocity().y <= 0.00001f && balls[i].GetVelocity().y >= -0.00001f) == false) {
                    gameOver = false;
                    break;
                }
            }

            //Prints the score to the console after the game is over. 10 points are given per ball changed to black
            if (gameOver == true) {
                std::cout << "Game Over. Score = " << playerScore - 10 << std::endl;
            }
        }

        /*system.Update();*/

        window.clear();

        //Draws the playboard (background)
        window.draw(playboard);

        //Uses the balls render function to draw them to the window
        for (size_t i = 0; i < balls.size(); i++)
        {
            balls[i].Render(window);
        }

        //Draws the board's boundaries
        for (size_t i = 0; i < Boundaries.size(); i++)
        {
            sf::VertexArray line(sf::LinesStrip, 2);

            line[0].position = Boundaries[i].pointOne;
            line[1].position = Boundaries[i].pointTwo;
            window.draw(line);
        }

        //Renders aiming reticle if the shot hasn't been taken
        if (shotPlayed == false) {
            sf::CircleShape aim(10.0f);
            aim.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
            aim.setOrigin(aim.getRadius(), aim.getRadius());
            aim.setFillColor(sf::Color::Transparent);
            aim.setOutlineColor(sf::Color::White);
            aim.setOutlineThickness(2.0f);

            window.draw(aim);

            sf::Vector2f distance(sf::Vector2f(sf::Mouse::getPosition(window)) - balls[0].GetPosition());
            float length = std::sqrt((distance.x * distance.x) + (distance.y * distance.y));

            sf::VertexArray line(sf::LinesStrip, 2);
            line[0].position = balls[0].GetPosition();
            line[1].position = sf::Vector2f(sf::Mouse::getPosition(window));

            window.draw(line);
        }

        //Displays a message when the game is over
        if (gameOver == true) {
            sf::Text text;
            text.setFont(font);
            text.setString("Game over");
            text.setCharacterSize(32);
            text.setFillColor(sf::Color::Blue);
            text.setPosition(400.0f, 200.0f);
            window.draw(text);

            sf::Text score;
            score.setFont(font);
            score.setString("Check your score in the console");
            score.setCharacterSize(32);
            score.setFillColor(sf::Color::Blue);
            score.setPosition(270.0f, 230.0f);
            window.draw(score);
        }

        //Display all of the drawn objects on the screen
        window.display();
    }

    return 0;
}

bool PlaceIsTaken(sf::Vector2f pos1, sf::Vector2f pos2)
{
    if (pos1 == pos2) {
        return true;
    }
    else {
        return false;
    }
}

//Checks to see if a collision between a moving and stationary ball is possible
bool CheckForStaticCollision(Ball& b1, Ball& b2, sf::Vector2f v, float r1, float r2) {
    //Calculates vector between the two balls
    sf::Vector2f a;

    a.x = b2.GetPosition().x - b1.GetPosition().x;
    a.y = b2.GetPosition().y - b1.GetPosition().y;

    //Gets the length of A and the length of the velocity of the moving ball
    //Then makes them unit length
    float lengthV = std::sqrt((v.x * v.x) + (v.y * v.y));
    float lengthA = std::sqrt((a.x * a.x) + (a.y * a.y));

    a.x /= lengthA;
    a.y /= lengthA;

    v.x /= lengthV;
    v.y /= lengthV;

    //Dot product of unit vectors
    float dot = (a.x * v.x) + (a.y * v.y);

    //Takes the dot product and calculates the angle between the two vectors
    float q = std::acos(dot);

    float sinQ = std::sin(q);

    //Calculates the distance between the centre of the stationary ball, and the nearest point of the moving balls velocity
    float d = sinQ * lengthA;

    //If d is not smaller than the combined radi of the two balls, there is no collision. Otherwise, the program moves to the next stage
    if (d < (r1 + r2)) {
        float r = r1 + r2;
        float e = std::sqrt((r * r) - (d * d));

        //Calculates the length of vc + e, which can then tell us the length of vc by taking away e
        float vceSum = std::cos(q) * lengthA;
        float vc = vceSum - e;

        //If the length of vc is larger than 0 and withing the length of the velocity vector, a collision is made
        if (vc <= lengthV && vc >= 0.0f) {
            //Moving ball takes in the collision point
            sf::Vector2f newPos = b1.GetPosition();

            newPos.x += (v.x * vc) * 0.99f;
            newPos.y += (v.y * vc) * 0.99f;

            b1.SetPosition(newPos);

            //Calculates the impulse of the collision
            CalculateCollision(b1, b2, v, r1, r2);
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }


}

//Calculates the impulse of a static collision for the two balls that collide
void CalculateCollision(Ball& b1, Ball& b2, sf::Vector2f v, float r1, float r2) {
    //Calculates the direction of the force acting upon the static ball
    sf::Vector2f fd;
    fd.x = b2.GetPosition().x - b1.GetPosition().x;
    fd.y = b2.GetPosition().y - b1.GetPosition().y;

    //The direction is converted to a unit vector for ease of use
    float fdLength = std::sqrt((fd.x * fd.x) + (fd.y * fd.y));
    fd.x /= fdLength;
    fd.y /= fdLength;

    //Calculates a unit vector from the velocity of the moving ball
    sf::Vector2f vd = v;
    float vLength = std::sqrt((vd.x * vd.x) + (vd.y * vd.y));
    vd.x /= vLength;
    vd.y /= vLength;

    //Both unit vectors are used to find the angle of the collision by finding the dot product of the two vectors
    float dot = (fd.x * vd.x) + (fd.y * vd.y);
    float cosA = dot;

    //v1 = velocity of the moving ball
    //v2 = velocity of the static ball
    sf::Vector2f v1;
    sf::Vector2f v2;

    //Uses the cosine of the angle and the force direction to calculate the impulse of the static ball
    v2.x = cosA * fd.x;
    v2.y = cosA * fd.y;

    //Because of the conservation of mass, we can assume that the moving balls new trajectory will be the the remaining force that wasn't transferWhite to the static ball
    v1.x = vd.x - v2.x;
    v1.y = vd.y - v2.y;

    //Multiplies the new velocities by the magnitude of the old velocities to keep them consistant with eachother
    v1 *= b1.GetRawVLength();
    v2 *= b1.GetRawVLength();

    //Sets the new velocities
    b1.SetVelocity(v1);
    b2.SetVelocity(v2);
}

bool CheckForSideCollision(Ball& b, Boundary& w) {

    bool hasCollided{ false };

    //Takes a point on the Boundary, which for this is always the center point
    sf::Vector2f k = w.pointOne + (w.BoundaryDirection / 2.0f);

    //Decides which normal to use based on which side of the Boundary the ball is on
    sf::Vector2f ballToN1 = (k + w.normals.first) - b.GetPosition();
    sf::Vector2f ballToN2 = (k + w.normals.second) - b.GetPosition();
    float firstLength = std::sqrt((ballToN1.x * ballToN1.x) + (ballToN1.y * ballToN1.y));
    float secondLength = std::sqrt((ballToN2.x * ballToN2.x) + (ballToN2.y * ballToN2.y));
    sf::Vector2f n;

    if (firstLength < secondLength) {
        n = w.normals.first;
    }
    else {
        n = w.normals.second;
    }

    //sf::Vector2f n = w.normals.first;
    float nLength = std::sqrt((n.x * n.x) + (n.y * n.y));
    n /= nLength;
    sf::Vector2f p = b.GetPosition() - k;
    float pLength = std::sqrt((p.x * p.x) + (p.y * p.y));
    float dot = (p.x * n.x) + (p.y * n.y);
    //Gets the cosine of the angle between the normal and the balls trajectory
    float cosQ1 = dot / pLength;
    float q1 = std::acos(cosQ1);
    //Finds the angle between the plane and the trajectory of the ball in radians
    float q2 = 1.5708f - q1;

    //q1 and q2 should sum up to 90 degrees. If it doesn't, we know the ball is on the opposite side to the normal, so we try again with the opposite normal
    if ((q1 + q2) >= 1.571f || (q1 + q2) <= 1.5706f) {
        n = w.normals.second;
        nLength = std::sqrt((n.x * n.x) + (n.y * n.y));
        n /= nLength;
        p = b.GetPosition() - k;
        pLength = std::sqrt((p.x * p.x) + (p.y * p.y));
        dot = (p.x * n.x) + (p.y * n.y);
        cosQ1 = dot / pLength;
        q1 = std::acos(cosQ1);
        q2 = 1.5708f - q1;
    }

    //Finds the distance between the ball and the closest point on the Boundary
    float d = std::sin(q2) * pLength;
    sf::Vector2f v = b.GetVelocity();
    float vLength = std::sqrt((v.x * v.x) + (v.y * v.y));
    //Finds the cosine of the angle between the balls trajectory and the direction to the nearest point of the Boundary
    float cosS = ((v.x * -n.x) + (v.y * -n.y)) / vLength;
    //Gives the magnitude of the vector that will bring the ball into contact with the Boundary
    float vcLength = (d - b.GetRadius()) / cosS;

    //If the magnitude of vc falls withing the magnitude of the balls velocity, then a collision will take place this update
    if (vcLength <= vLength && vcLength >= 0.0f) {
        //Calculates the vector to the collision point (vc) and moves the ball to it
        sf::Vector2f vc = (v / vLength) * vcLength;
        sf::Vector2f position = b.GetPosition() + vc;

        float BoundaryLength = std::sqrt((w.BoundaryDirection.x * w.BoundaryDirection.x) + (w.BoundaryDirection.y * w.BoundaryDirection.y));
        sf::Vector2f BoundariestartToBall = position - w.pointOne;
        sf::Vector2f BoundaryEndToBall = position - w.pointTwo;
        float startToBallLength = std::sqrt((BoundariestartToBall.x * BoundariestartToBall.x) + (BoundariestartToBall.y * BoundariestartToBall.y));
        float endToBallLength = std::sqrt((BoundaryEndToBall.x * BoundaryEndToBall.x) + (BoundaryEndToBall.y * BoundaryEndToBall.y));

        if (startToBallLength > BoundaryLength + b.GetRadius() || endToBallLength > BoundaryLength + b.GetRadius()) {
            return false;
        }

        //Reflects the balls velocity about the normal of the game's boundary
        sf::Vector2f reflectedVector;
        float reflectedDot = (v.x * n.x) + (v.y * n.y);
        reflectedVector = v - 2 * reflectedDot * n;

        if (reflectedVector != v) {
            b.SetVelocity(reflectedVector);
            hasCollided = true;
        }
    }

    return hasCollided;
}

//Checks if a moving collision is possible
bool CheckForMovingCollision(Ball& ball1, Ball& ball2) {
    //Grabs positions and velocities for each.
    sf::Vector2f p1 = ball1.GetPosition();
    sf::Vector2f v1 = ball1.GetVelocity();

    sf::Vector2f p2 = ball2.GetPosition();
    sf::Vector2f v2 = ball2.GetVelocity();

    float combinedRadius{ ball1.GetRadius() + ball2.GetRadius() };

    float xPos = p1.x - p2.x;
    float yPos = p1.y - p2.y;
    float xVel = v1.x - v2.x;
    float yVel = v1.y - v2.y;

    //Calculates a b and c values for quadratic equation.
    float a = (xVel * xVel) + (yVel * yVel);
    float b = (2 * xPos * xVel) + (2 * yPos * yVel);
    float c = (xPos * xPos) + (yPos * yPos) - (combinedRadius * combinedRadius);

    if ((b * b) < (4 * a * c)) {
        return false;
    }

    //Calculates both possible results from the quadratic
    float positiveT = (-b + std::sqrt((b * b) - (4 * a * c))) / (2 * a);
    float negativeT = (-b - std::sqrt((b * b) - (4 * a * c))) / (2 * a);

    //Collision takes place if either result from the quadratic falls between 0 and 1.
    if ((positiveT >= 0.0f && positiveT <= 1.0f) || (negativeT >= 0.0f && negativeT <= 1.0f)) {
        CalculateMovingCollision(ball1, ball2);

        return true;
    }
    else {
        return false;
    }
}

//Calculates the impulse of a moving collision
void CalculateMovingCollision(Ball& ball1, Ball& ball2) {
    sf::Vector2f p1 = ball1.GetPosition();
    sf::Vector2f v1 = ball1.GetVelocity();

    sf::Vector2f p2 = ball2.GetPosition();
    sf::Vector2f v2 = ball2.GetVelocity();

    //Generates vector from ball 1 to ball 2 and vice-versa
    sf::Vector2f ballOneToBallTwo = p2 - p1;
    sf::Vector2f ballTwoToBallOne = p1 - p2;

    //Length of both velocities and the vectors between balls
    float distanceLength = std::sqrt((ballOneToBallTwo.x * ballOneToBallTwo.x) + (ballOneToBallTwo.y * ballOneToBallTwo.y));
    float v1Length = std::sqrt((v1.x * v1.x) + (v1.y * v1.y));
    float v2Length = std::sqrt((v2.x * v2.x) + (v2.y * v2.y));

    //Calculates cosines of angles between ball 1 velocity and vector from ball 1 to ball 2
    float cosA = (ballOneToBallTwo.x * v1.x) + (ballOneToBallTwo.y * v1.y);
    cosA /= (distanceLength * v1Length);
    float cosB = (ballTwoToBallOne.x * v2.x) + (ballTwoToBallOne.y * v2.y);
    cosB /= (distanceLength * v2Length);

    //Normalizes vector between balls to unit vectors
    sf::Vector2f fd1 = ballOneToBallTwo / (std::sqrt((ballOneToBallTwo.x * ballOneToBallTwo.x) + (ballOneToBallTwo.y * ballOneToBallTwo.y)));
    sf::Vector2f fd2 = -fd1;

    //Calculation for the impulse force of the balls (assuming that mass is 1 in this case)
    sf::Vector2f forceOnB2 = cosA * v1Length * fd1;
    sf::Vector2f forceOnB1 = cosB * v2Length * fd2;

    //Calculation for the new velocities
    sf::Vector2f newV2 = v2 + forceOnB2 - forceOnB1;
    sf::Vector2f newV1 = v1 + forceOnB1 - forceOnB2;

    ball1.SetVelocity(newV1);
    ball2.SetVelocity(newV2);
}

//Sets the velocity of the cue ball based on the position of the mouse
void TakeShot(sf::Vector2f m, Ball& ball) {
    sf::Vector2f direction = m - ball.GetPosition();
    float dLength = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
    direction /= dLength;
    float power = dLength / 100.0f;
    if (power > 1.0f) {
        power = 1.0f;
    }
    direction *= power;

    ball.SetVelocity(direction);
}
