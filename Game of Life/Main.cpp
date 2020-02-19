/*

	Cellular Automata - Conway's Game of Life
	
	Rules:
	1. Any live cell with two or three neighbors survives.
	2. Any dead cell with three live neighbors becomes a live cell.
	2. All other live cells die in the next generation. Similarly, all other dead cells stay dead.
*/

#include <SFML/Graphics.hpp>
#include <iostream>

class Cell
{
public:
	Cell()
	{
		alive = false;
		selected = false;
		cell = sf::RectangleShape(sf::Vector2f(1, 1));
		cell.setFillColor(sf::Color(175, 175, 175));
	}
	Cell(float scale, float x, float y)
		:
		Cell()
	{
		this->x = x;
		this->y = y;
		cell.setScale(scale, scale);
		cell.setPosition(x * scale, y * scale);
	}
	sf::RectangleShape& GetDrawable()
	{
		return cell;
	}
	int neighbours;
	float x, y;
	bool alive, selected;
private:
	sf::RectangleShape cell;
};


int main()
{
	const int SC_WIDTH = 800, SC_HEIGHT = 800;
	float scale = 8;
	sf::RenderWindow window(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "Game of Life");
	window.setFramerateLimit(60);
	bool update = true;
	bool mouse_left = false;
	bool mouse_right = false;
	bool reset = false;
	sf::Vector2f mouse;
	Cell *cells = new Cell[100 * 100];
	for(unsigned int i = 0; i < 100; i++)
	{
		for(unsigned int j = 0; j < 100; j++)
		{
			cells[i + j * 100] = Cell(scale, (float) i, (float) j);
		}
	}
	while(1)
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Space)
					update = false;
				if(event.key.code == sf::Keyboard::R)
					reset = true;
			}
			if(event.type == sf::Event::KeyReleased)
			{
				if(event.key.code == sf::Keyboard::Space)
					update = true;
			}
			if(event.type == sf::Event::MouseMoved)
			{
				mouse.x = event.mouseMove.x;
				mouse.y = event.mouseMove.y;
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
					mouse_left = true;
				if(event.mouseButton.button == sf::Mouse::Right)
					mouse_right = true;
			}
			if(event.type == sf::Event::MouseButtonReleased)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
					mouse_left = false;
				if(event.mouseButton.button == sf::Mouse::Right)
					mouse_right = false;
			}
		}
		if(update)
		{
			Cell *temp = new Cell[100 * 100];
			for(unsigned int i = 0; i < 100 * 100; i++)
			{
				temp[i] = cells[i];
			}
			for(unsigned int i = 0; i < 100 * 100; i++)
			{
				if(update)
				{
					cells[i].neighbours = 0;
					if(temp[i].x - 1 > 0 && temp[i].y - 1 > 0 &&
					   temp[i].x + 1 < 100 && temp[i].y + 1 < 100)
					{
						if(temp[i - 1].alive)
							cells[i].neighbours++;
						if(temp[i + 1].alive)
							cells[i].neighbours++;
						if(temp[i - 100].alive)
							cells[i].neighbours++;
						if(temp[i - 101].alive)
							cells[i].neighbours++;
						if(temp[i - 99].alive)
							cells[i].neighbours++;
						if(temp[i + 100].alive)
							cells[i].neighbours++;
						if(temp[i + 101].alive)
							cells[i].neighbours++;
						if(temp[i + 99].alive)
							cells[i].neighbours++;
					}
					if(cells[i].alive)
					{
						if(cells[i].neighbours >= 2 && cells[i].neighbours <= 3)
							cells[i].alive = true;
						else
							cells[i].alive = false;
					}
					else
					{
						if(cells[i].neighbours == 3)
							cells[i].alive = true;
					}
				}
				cells[i].GetDrawable().setFillColor(sf::Color(175, 175, 175));
				cells[i].selected = false;
			}
			delete[] temp;
		}
		else
		{
			for(unsigned int i = 0; i < 100 * 100; i++)
			{
				cells[i].GetDrawable().setFillColor(sf::Color(175, 175, 175));
				cells[i].selected = false;
			}
			if(cells[(((int) mouse.x / 8) + ((int) mouse.y / 8) * 100)].alive)
			{
				cells[(((int) mouse.x / 8) + ((int) mouse.y / 8) * 100)].GetDrawable().setFillColor(sf::Color(175, 175, 175, 200));
			}
			else
			{
				cells[(((int) mouse.x / 8) + ((int) mouse.y / 8) * 100)].GetDrawable().setFillColor(sf::Color(175, 175, 175, 100));
			}
			cells[(((int) mouse.x / 8) + ((int) mouse.y / 8) * 100)].selected = true;
			if(mouse_left)
				cells[(((int) mouse.x / 8) + ((int) mouse.y / 8) * 100)].alive = true;
			if(mouse_right)
				cells[(((int) mouse.x / 8) + ((int) mouse.y / 8) * 100)].alive = false;
		}
		if(reset)
		{
			for(unsigned int i = 0; i < 100 * 100; i++)
			{
				cells[i].alive = false;
				reset = false;
			}
		}
		window.clear();
		for(unsigned int i = 0; i < 100 * 100; i++)
		{
			if(cells[i].alive || cells[i].selected)
				window.draw(cells[i].GetDrawable());
		}
		window.display();
	}
}