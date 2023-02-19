#include "Ball.h"
#include <iostream>

Ball::Ball(sf::Vector2f pos, sf::Vector2f vel, sf::Color col, unsigned int i) {
	position = pos;
	velocity = vel;
	colour = col;
	index = i;
}

//Initialises the balls initial velocity
void Ball::SetVelocity(sf::Vector2f vel) {
	velocity = vel;
}

void Ball::SetColor(sf::Color col)
{
	colour = col;
}

//Updates the positon an velocity values every game update loop 
void Ball::Update() {
	position += velocity;
	velocity *= 0.9991f;
}

//Renders the ball(s) to the window
void Ball::Render(sf::RenderWindow& w) {
	sf::CircleShape circle(radius);
	circle.setPosition(position);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setFillColor(colour);

	w.draw(circle);
}

void Ball::SetPosition(sf::Vector2f pos)
{
	position = pos;
}

//Returns the magnitude of the velocity vector
float Ball::GetRawVLength()
{
	return std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));;
}