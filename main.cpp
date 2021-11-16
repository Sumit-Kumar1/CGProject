#include "Header.h"

sf::Vector2f viewSize(1280, 720);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "CG-Project By SUMIT & YASHARTH", sf::Style::Default);
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;

void init()
{
	backgroundTexture.loadFromFile("./Assets/graphics/BGImage.png");
	backgroundSprite.setTexture(backgroundTexture);
}
void draw()
{
	window.draw(backgroundSprite);
}
int main()
{
	init();
	int t = 0;
	while (window.isOpen())
	{
		window.clear(sf::Color::Cyan);
		draw();
		window.display();
		
		std::cin >> t;
		if (t == 0)
			window.close();
	}
	return 0;
}