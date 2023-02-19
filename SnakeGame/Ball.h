#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Color colour;
	float radius{ 15 };
	unsigned int index;
public:
	Ball(sf::Vector2f pos, sf::Vector2f vel, sf::Color col, unsigned int i);
	void SetVelocity(sf::Vector2f v);
	sf::Vector2f& GetVelocity() { return velocity; };
	sf::Vector2f& GetPosition() { return position; };
	float GetRadius() { return radius; };
	unsigned int GetIndex() { return index; };
	sf::Color& GetColor() { return colour; };
	void SetColor(sf::Color col);
	void Update();
	void Render(sf::RenderWindow& window);
	void SetPosition(sf::Vector2f pos);
	float GetRawVLength();
};