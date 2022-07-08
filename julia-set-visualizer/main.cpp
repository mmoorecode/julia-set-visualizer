#include <SFML\Graphics.hpp>

int main()
{
	int width = 800;
	int height = 800;

	sf::RenderWindow window(sf::VideoMode(width, height), "Julia Set Visualizer");
	sf::Event event;
	sf::Clock clock; // starts the clock
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		sf::Shader shader;
		if (!shader.loadFromFile("shaders/juliaset.frag", sf::Shader::Fragment))
		{
			printf("Could not load fragment shader.\n");
		}
		
		sf::Texture texture; 
		texture.create(width, height);
		sf::Sprite sprite; 
		sprite.setTexture(texture);

		shader.setUniform("texture", texture);
		shader.setUniform("time", (float)clock.getElapsedTime().asMilliseconds());

		window.clear();
		window.draw(sprite, &shader);
		window.display();
	}

	return 0;
}