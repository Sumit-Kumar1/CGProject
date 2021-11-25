#include <string>
#include <cstdlib>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Enemy.h"
#include "AttackFlash.h"
#include "Hero.h"

// >>>>>>>>>>> DEFINE FOR IFDEF <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 1
#define BACKGROUND
#define WINDOW
#define HERO
#define ENEMY
#define ATTACKS
#define FONT
#endif
// <<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>> GLOBALS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 1
#ifdef WINDOW
sf::Vector2f viewSize(1280, 720); // window size
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "CG-Project By SUMIT & YASHARTH", sf::Style::Default);
#endif

#ifdef BACKGROUND
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
#endif

#ifdef HERO
	Hero hero;
#endif

#ifdef ENEMY
	std::vector<Enemy*> enemies;
#endif

#ifdef ATTACKS
	std::vector<AttackFlash*> attacks;
#endif

float currentTime;
float prevTime = 0.0f;
int score = 0;
bool isGameOver = false;
int health = 500;

sf::Font headingFont;
sf::Text headingText;
//sf::Font scoreFont;
sf::Text scoreText;
//sf::Font healthFont;
sf::Text healthText;
#endif
// >>>>>>>>>>>>>>>>>>>>>>>>> FUNCTION PROTOTYPES <<<<<<<<<<<<<<<<<<<<<
#if 1
void init();
void spawnEnemy();
void shoot();
bool checkCollision(sf::Sprite spriteA, sf::Sprite spriteB);
void reset();
void updateInput();
void update(float deltaTime);
void Draw();
#endif
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main()
{
	srand((unsigned int)time(0));
	sf::Clock clock;

	window.setFramerateLimit(60);
	init();
	while (window.isOpen())
	{
		//update the input
		updateInput();

		// update game
		sf::Time deltaTime = clock.restart();
		if(!isGameOver)
			update(deltaTime.asSeconds());

		window.clear(sf::Color::Cyan);
		Draw();

		//display the above scene
		window.display();
	}
	return 0;
}

// >>>>>>>>>>>>>>>>>> FUNCTIONS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 1
void init()
{
#ifdef BACKGROUND
	backgroundTexture.loadFromFile("./Assets/BGImage.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(sf::Vector2f(0.7f, 0.7f));
#endif

#ifdef HERO
	hero.init("./Assets/adventurer-idle-00.png", sf::Vector2f(viewSize.x * 0.2f, viewSize.y * 0.7f), 200);
#endif

#ifdef FONT
	// Game name font setup
	headingFont.loadFromFile("./Assets/Fonts/ROBOTOP.ttf");
	headingText.setFont(headingFont);
	headingText.setString("Village Defend");
	headingText.setCharacterSize(90);
	headingText.setFillColor(sf::Color::Red);
	sf::FloatRect headingbounds = headingText.getLocalBounds();
	headingText.setOrigin(headingbounds.width / 2,headingbounds.height / 2);
	headingText.setPosition(sf::Vector2f(viewSize.x * 0.5f,viewSize.y * 0.10f));


	//Score font setup
	//scoreFont.loadFromFile("./Assets/Fonts/Roboto-Black.ttf");
	scoreText.setFont(headingFont);
	scoreText.setString("Score: 0");
	scoreText.setCharacterSize(45);
	scoreText.setFillColor(sf::Color::Cyan);
	sf::FloatRect scorebounds = scoreText.getLocalBounds();
	scoreText.setOrigin(scorebounds.width / 2, scorebounds.height / 2);
	scoreText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y* 0.10f));

	//health font
	healthText.setFont(headingFont);
	healthText.setCharacterSize(45);
	healthText.setFillColor(sf::Color::Green);
	sf::FloatRect helathbounds = healthText.getLocalBounds();
	healthText.setOrigin(helathbounds.width / 2, scorebounds.height / 2);
	healthText.setPosition(sf::Vector2f(viewSize.x * 0.1, viewSize.y * 0.1));
#endif
}
void spawnEnemy()
{
	int randLoc = rand() % 3;
	sf::Vector2f enemyPos;
	float speed = 0;
	switch (randLoc)
	{
	case 0: enemyPos = sf::Vector2f(viewSize.x,viewSize.y * 0.75f); speed = -300; break;
	case 1: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f); speed = -400; break;
	case 2: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f); speed = -550; break;
	default: std::cout << "Incorrect value of y\n";
		break;
	}
	Enemy* enemy = new Enemy();
	enemy->init("Assets/enemy.png", sf::Vector2f(enemyPos.x, rand()%650+50), speed);
	enemy->resize(sf::Vector2f(0.2f, 0.2f));
	enemy->flip();
	enemies.push_back(enemy);
}
void shoot() {
	AttackFlash* attack = new AttackFlash();
	attack->init("./Assets/attack.png", hero.getSprite().getPosition(), 400.0f);
	attacks.push_back(attack);
}
bool checkCollision(sf::Sprite spriteA, sf::Sprite spriteB) {
	sf::FloatRect shape1 = spriteA.getGlobalBounds();
	sf::FloatRect shape2 = spriteB.getGlobalBounds();

	if (shape1.intersects(shape2)) {
		return true;
	}
	else {
		return false;
	}
}
void reset() {
	score = 0;
	currentTime = 0.0f;
	prevTime = 0.0f;
	health = 500;
	scoreText.setString("Score : 0");
	for (Enemy* enemy : enemies) {
		delete(enemy);
	}

	for (AttackFlash* attack : attacks) {
		delete(attack);
	}

	attacks.clear();
	enemies.clear();
}
void updateInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		//setting up input
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
				hero.jump(-250.0f);
			}else if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down){
				hero.jump(250.0f);
			}

			if (event.key.code == sf::Keyboard::C) {
				if (isGameOver) {
					isGameOver = false;
					reset();
				}
				else {
					shoot();
				}
			}
			if (event.key.code == sf::Keyboard::Q) {
				if (!isGameOver)
					isGameOver = true;
			}

			if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}
void update(float deltaTime)
{
	hero.update(deltaTime);
	currentTime += deltaTime;

#ifdef FONT
	//score update 
	std::string finalScore = "Score : " + std::to_string(score);
	scoreText.setString(finalScore);
	sf::FloatRect scorebounds = scoreText.getLocalBounds();
	scoreText.setPosition(sf::Vector2f(viewSize.x * 0.5, viewSize.y * 0.05f));

	//health Text update
	std::string finalHealth = "Health : " + std::to_string(health);
	healthText.setString(finalHealth);
	sf::FloatRect healthbounds = healthText.getLocalBounds();
	healthText.setPosition(sf::Vector2f(viewSize.x * 0.05, viewSize.y * 0.05));
	healthText.setFillColor(sf::Color::Red);
#endif

	//spawn enemies
	if (currentTime >= prevTime + 1.125f) {
		spawnEnemy();
		prevTime = currentTime;
	}

	for (int i = 0; i < (int)enemies.size(); i++) {
		Enemy* enemy = enemies[i];
		enemy->update(deltaTime);
		if (enemy->getSprite().getPosition().x < 0) { // if enemy goes out of screen in left side
			enemies.erase(enemies.begin() + i);
			delete(enemy);
			if (health <= 0)
				isGameOver = true;
			else
				health -= 50;
		}
	}
	for (int i = 0; i < (int)attacks.size(); i++) {
		AttackFlash* attack = attacks[i];
		attack->update(deltaTime);

		if (attack->getSprite().getPosition().x > viewSize.x) { // if attack goes out in right side of screen
			attacks.erase(attacks.begin() + i);
			delete(attack);
		}
	}
	for (int i = 0; i < (int)attacks.size(); i++) {
		AttackFlash* attack = attacks[i];
		for (int j = 0; j < (int)enemies.size(); j++) {
			Enemy* enemy = enemies[j];
			if (checkCollision(attack->getSprite(), enemy->getSprite())) {
				score += 10;
				attacks.erase(attacks.begin() + i);
				enemies.erase(enemies.begin() + j);
				delete(enemy);
				delete(attack);
				std::cout << "Its A Hit\n";
			}
		}
	}
}
void Draw()
{
	window.draw(backgroundSprite);
	window.draw(hero.getSprite());
	for (Enemy* enemy : enemies) {
		window.draw(enemy->getSprite());
	}

	for (AttackFlash* attack : attacks) {
		window.draw(attack->getSprite());
	}
	if (isGameOver) {
		window.draw(headingText);
	}
	else {
		window.draw(scoreText);
		window.draw(healthText);
	}
}
#endif