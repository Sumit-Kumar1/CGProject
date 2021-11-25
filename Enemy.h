#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	float m_speed;
public:
	Enemy();
	~Enemy();
	void init(std::string textureName, sf::Vector2f position, float _speed);
	void update(float dt);
	void resize(sf::Vector2f v);
	void flip();
	sf::Sprite getSprite();
};