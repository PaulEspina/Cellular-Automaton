/*

	Cellular Automata - Conway's Game of Life
	
	Rules:
	1. Any live cell with two or three neighbors survives.
	2. Any dead cell with three live neighbors becomes a live cell.
	2. All other live cells die in the next generation. Similarly, all other dead cells stay dead.
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

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
	srand((unsigned int) time(0));
	const int SC_WIDTH = 640, SC_HEIGHT = 480;
	int scale = 8;
	unsigned int n_cell_x = SC_WIDTH / scale, n_cell_y = SC_HEIGHT / scale;
	sf::RenderWindow window(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "Game of Life");
	bool update = true;
	bool mouse_left = false;
	bool mouse_right = false;
	bool reset = false;
	bool random = false;
	sf::Vector2f mouse;
	Cell *cells = new Cell[n_cell_x * n_cell_y];
	for(unsigned int i = 0; i < n_cell_x; i++)
	{
		for(unsigned int j = 0; j < n_cell_y; j++)
		{
			cells[i + j * n_cell_x] = Cell(scale, (float) i, (float) j);
		}
	}
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Space)
					if(update)
						update = false;
					else
						update = true;
				if(event.key.code == sf::Keyboard::R)
					reset = true;
				if(event.key.code == sf::Keyboard::T)
					random = true;
			}
			if(event.type == sf::Event::MouseMoved)
			{
				mouse.x = event.mouseMove.x;
				mouse.y = event.mouseMove.y;
				if(mouse.x > SC_WIDTH - 1)
					mouse.x = SC_WIDTH - 1;
				if(mouse.x < 0)
					mouse.x = 0;
				if(mouse.y > SC_HEIGHT - 1)
					mouse.y = SC_HEIGHT - 1;
				if(mouse.y < 0)
					mouse.y = 0;
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
			Cell *temp = new Cell[n_cell_x * n_cell_y];
			for(unsigned int i = 0; i < n_cell_x * n_cell_y; i++)
			{
				temp[i] = cells[i];
			}
			for(unsigned int i = 0; i < n_cell_x * n_cell_y; i++)
			{
				if(update)
				{
					cells[i].neighbours = 0;
					if(temp[i].x - 1 > 0 && temp[i].y - 1 > 0 &&
					   temp[i].x + 1 < n_cell_x && temp[i].y + 1 < n_cell_y)
					{
						if(temp[i - 1].alive)
							cells[i].neighbours++;
						if(temp[i + 1].alive)
							cells[i].neighbours++;
						if(temp[i - n_cell_x].alive)
							cells[i].neighbours++;
						if(temp[i - (n_cell_x + 1)].alive)
							cells[i].neighbours++;
						if(temp[i - (n_cell_x - 1)].alive)
							cells[i].neighbours++;
						if(temp[i + n_cell_x].alive)
							cells[i].neighbours++;
						if(temp[i + (n_cell_x + 1)].alive)
							cells[i].neighbours++;
						if(temp[i + (n_cell_x - 1)].alive)
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
			for(unsigned int i = 0; i < n_cell_x * n_cell_y; i++)
			{
				cells[i].GetDrawable().setFillColor(sf::Color(175, 175, 175));
				cells[i].selected = false;
			}
			if(cells[(((int) mouse.x / scale) + ((int) mouse.y / scale) * n_cell_x)].alive)
			{
				cells[(((int) mouse.x / scale) + ((int) mouse.y / scale) * n_cell_x)].GetDrawable().setFillColor(sf::Color(175, 175, 175, 200));
			}
			else
			{
				cells[(((int) mouse.x / scale) + ((int) mouse.y / scale) * n_cell_x)].GetDrawable().setFillColor(sf::Color(175, 175, 175, 100));
			}
			cells[(((int) mouse.x / scale) + ((int) mouse.y / scale) * n_cell_x)].selected = true;
			if(mouse_left)
				cells[(((int) mouse.x / scale) + ((int) mouse.y / scale) * n_cell_x)].alive = true;
			if(mouse_right)
				cells[(((int) mouse.x / scale) + ((int) mouse.y / scale) * n_cell_x)].alive = false;
		}
		if(reset)
		{
			for(unsigned int i = 0; i < n_cell_x * n_cell_y; i++)
			{
				cells[i].alive = false;
				reset = false;
			}
		}
		if(random)
		{
			for(unsigned int i = 0; i < n_cell_x * n_cell_y; i++)
			{
				cells[i].alive = rand() % 2;
				random = false;
			}
		}
		window.clear();
		for(unsigned int i = 0; i < n_cell_x * n_cell_y; i++)
		{
			if(cells[i].alive || cells[i].selected)
				window.draw(cells[i].GetDrawable());
		}
		window.display();
	}
}