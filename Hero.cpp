#include "Hero.h"
Hero::Hero() {
	m_position = sf::Vector2f(0.0f, 0.0f);
	m_grounded = false;
	m_velocity = 0.0f;
}
Hero::~Hero() {

}
void Hero::init(std::string textureName, sf::Vector2f position, float mass) {
	m_position = position;
	m_grounded = false;
	//loading hero texture
	m_texture.loadFromFile(textureName.c_str());
	//creating sprite and attaching the texture
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(2.0f, 2.0f));
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}
void Hero::update(float dt) {
	m_position.y += m_velocity * dt;	// as distance = speed * time
	if (m_position.y > 768 * 0.9f) {
		m_position.y = 768 * 0.9f;
	}
	else if (m_position.y < 768 * 0.1) {
		m_position.y = 768 * 0.1;
	}
	m_sprite.setPosition(m_position);
}
void Hero::jump(float velocity) {
	m_grounded = true;
	m_velocity = velocity;
}
sf::Sprite Hero::getSprite() {
	return m_sprite;
}
void Hero::scale(sf::Vector2f _scale) {
	m_sprite.setScale(_scale);
}
void Hero::flip() {
	m_sprite.scale(sf::Vector2f(-1.0, 1.0));
}