#include <SFML\Graphics.hpp>

int main()
{
	int width = 800;
	int height = 800;

	sf::RenderWindow window(sf::VideoMode(width, height), "Julia Set Visualizer");
	sf::Event event;
	sf::Clock clock; // starts the clock

	sf::Shader shader;
	if (!shader.loadFromFile("shaders/juliaset.frag", sf::Shader::Fragment))
	{
		printf("Could not load fragment shader.\n");
	}

	sf::Texture texture;
	texture.create(width, height);
	sf::Sprite sprite;
	sprite.setTexture(texture);

	shader.setUniform("u_time", (float)clock.getElapsedTime().asSeconds());
	shader.setUniform("u_resolution", sf::Vector2f(width, height));

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

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		shader.setUniform("u_time", (float)clock.getElapsedTime().asSeconds());
		shader.setUniform("u_resolution", sf::Vector2f(width, height));
		shader.setUniform("u_mouse", sf::Vector2f(mousePos.x, mousePos.y - height / 2));

		window.clear();
		window.draw(sprite, &shader);
		window.display();
	}

	return 0;
}