#include "Header.h"

#define BACKGROUND
#define PLAYER
#define WINDOW


// ------------ window setting up--------------
#ifdef WINDOW
sf::Vector2f viewSize(1280,720);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "CG-Project By SUMIT & YASHARTH", sf::Style::Default);
#endif
 

//------------setting up background globals------------
#ifdef BACKGROUND
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
#endif

 // ------------------ Setting up player Globals------------
#ifdef PLAYER
sf::Texture playerTexture;
sf::Sprite playerSprite;
sf::Vector2f playerPostion;
bool playerMoving = false;
#endif

//---------------- initializing the various Textures and sprites --------
void init(){
#ifdef BACKGROUND
	backgroundTexture.loadFromFile("../Assets/graphics/BGImage.png");
	backgroundSprite.setTexture(backgroundTexture);
#endif
#ifdef PLAYER
	playerTexture.loadFromFile("../Assets/graphics/player/adventurer-idle-00.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(sf::Vector2f(3.0f, 3.0f));// scale up the player sprite
	playerSprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
#endif
}

void updateInput() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Right) {
				playerMoving = true;
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Right) {
				playerMoving == false;
			}
		}
		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
			window.close();
		}
	}
}
void update(float deltaTime) {
	if (playerMoving) {
		playerSprite.move(50.0f * deltaTime, 0);
	}
}
void Draw(sf::Sprite p) {
	window.draw(p);
}

int main()
{
	init();
	sf::Clock clock;
	while (window.isOpen())
	{
		//update the input
		updateInput();

		// update game
		sf::Time deltaTime = clock.restart();
		update(deltaTime.asSeconds());



		window.clear(sf::Color::Cyan);
		//setting up scene
		Draw(backgroundSprite);
		Draw(playerSprite);

		//display the above scene
		window.display();

	}
	return 0;
}