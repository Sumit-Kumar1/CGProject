#include "AttackFlash.h"

AttackFlash::AttackFlash() {}
AttackFlash::~AttackFlash() {}

void AttackFlash::init(std::string textureName, sf::Vector2f position, float _speed) {
	m_speed = _speed;
	m_position = position;
	m_texture.loadFromFile(textureName.c_str());
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin((float)m_texture.getSize().x / 2,(float)m_texture.getSize().y / 2);
}

void AttackFlash::update(float dt) {
	m_sprite.move(m_speed * dt, 0);
}

sf::Sprite AttackFlash::getSprite() {
	return m_sprite;
}