#include "Enemy.h"

Enemy::Enemy(){
	m_speed = 0.0f;
}
Enemy::~Enemy(){}

void Enemy::init(std::string textureName, sf::Vector2f position, float _speed) {
	m_speed = _speed;
	m_position = position;
	m_texture.loadFromFile(textureName.c_str());
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}

void Enemy::update(float dt) {
	m_sprite.move(m_speed * dt, 0);
}

sf::Sprite Enemy::getSprite() {
	return m_sprite;
}

void Enemy::resize(sf::Vector2f v) {
	m_sprite.setScale(v);
}

void Enemy::flip() {
	m_sprite.scale(sf::Vector2f(-1.0f, 1.0f));
}