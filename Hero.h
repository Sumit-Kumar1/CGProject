#pragma once
#include <SFML/Graphics.hpp>

class Hero
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;

	int jumpCount = 0;
	float m_velocity;
	bool m_grounded;

public :
	Hero();
	~Hero();

	void init(std::string textureName, sf::Vector2f position, float mass); // initalize texture and sprites, and other properties
	void update(float dt); // param dt is deltaTime
	void jump(float velocity);
	void flip();
	void scale(sf::Vector2f v);
	sf::Sprite getSprite(); // return sprite attached to this object
};