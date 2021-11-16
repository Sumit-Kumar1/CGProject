#include "Header.h"

#define BACKGROUND
#define PLAYER
#define WINDOW

enum class direction
{
	negative = -1,
	positive = 1
};
// ------------ window setting up--------------
#ifdef WINDOW
sf::Vector2f viewSize(1280, 720);
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
void init()
{
#ifdef BACKGROUND
	backgroundTexture.loadFromFile("../Assets/BGImage.png");
	backgroundSprite.setTexture(backgroundTexture);
#endif
#ifdef PLAYER
	playerTexture.loadFromFile("../Assets/adventurer-idle-00.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(sf::Vector2f(3.0f, 3.0f)); // scale up the player sprite
	playerSprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
#endif
}
void updateInput(direction &_direction)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		//setting up input
		if (event.type == sf::Event::KeyPressed)
		{
			playerMoving = true;
			if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
			{
				_direction = direction::positive;
			}
			else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
			{
				_direction = direction::negative;
			}
			/*else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
				_direction = direction::positive;
			}
			else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
				_direction = direction::negative;
			}*/
		}

		if (event.type == sf::Event::KeyReleased)
		{
			playerMoving = false;
		}
		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}
void update(direction _direction, float deltaTime)
{
	float moveSpeed = 50;
	if (_direction == direction::negative && playerMoving)
	{
		playerSprite.move(-50.0f * deltaTime, 0.0f);
	}
	else
	{
		playerSprite.move(50.0f * deltaTime, 0.0f);
	}
}
void Draw(sf::Sprite p)
{
	window.draw(p);
}

int main()
{
	init();
	sf::Clock clock;
	direction dir;

	while (window.isOpen())
	{
		//update the input
		updateInput(dir);

		// update game
		sf::Time deltaTime = clock.restart();
		update(dir, deltaTime.asSeconds());

		window.clear(sf::Color::Cyan);
		//setting up scene
		Draw(backgroundSprite);
		Draw(playerSprite);

		//display the above scene
		window.display();
	}
	return 0;
}