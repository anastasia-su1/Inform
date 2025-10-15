#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), L"Матрица");

	const int cellSize = 50;
	const int gridSize = 10;
	const int radius = 2;

	sf::RectangleShape cells[gridSize][gridSize];

	for (int i = 0; i < gridSize; ++i) {
		for (int j = 0; j < gridSize; ++j) {
			cells[i][j].setSize(sf::Vector2f(cellSize - 2, cellSize - 2));
			cells[i][j].setPosition(i * cellSize+1, j * cellSize+1);
			cells[i][j].setFillColor(sf::Color::White);
			if ((i >= gridSize/2 - 1 && j >= gridSize / 2 - 1) && (i <= gridSize / 2 && j <= gridSize / 2)) {
				cells[i][j].setFillColor(sf::Color::Green);
			}
			cells[i][j].setOutlineColor(sf::Color::Black);
			cells[i][j].setOutlineThickness(1);
		}
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);

		for (int i = 0; i < gridSize; ++i) {
			for (int j = 0; j < gridSize; ++j) {
				window.draw(cells[i][j]);
			}
		}
		window.display();
	}

	return 0;
}