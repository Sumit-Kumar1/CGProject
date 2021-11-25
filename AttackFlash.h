#pragma once
#include <SFML/Graphics.hpp>

class AttackFlash
{
public : 
	AttackFlash();
	~AttackFlash();
	void init(std::string textureName, sf::Vector2f position, float _speed);
	void update(float dt);
	sf::Sprite getSprite();

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	float m_speed = 0.0f;
};