#include "Game.h"
#include "Constants.h"
#include <iostream>
#include <string>
#include <thread>

namespace game
{
	Game::Game()
	{
		m_frameRate = FRAME_RATE_LIMIT;
		isRunning = false;
	}

	void Game::Start()
	{
		m_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "CellularAutomata!");
		m_window.setFramerateLimit(m_frameRate);
		
		m_output = new int[ScreenWidth() * ScreenHeight()];
		m_state = new int[ScreenWidth() * ScreenHeight()];

		memset(m_output, 0, ScreenWidth() * ScreenHeight() * sizeof(int));
		memset(m_state, 0, ScreenWidth() * ScreenHeight() * sizeof(int));

		// Pour chaque caractère '#' à l'intérieur de la string remplace le 0 par un 1 pour une cellule
		auto set = [&](int x, int y, std::wstring s)
		{
			int p = 0;
			for (auto c : s)
			{
				m_state[y * ScreenWidth() + x + p] = c == L'#' ? 1 : 0;
				p++;
			}
		};
		for (int i = 0; i < ScreenWidth() * ScreenHeight(); i++)
		{
			m_state[i] = rand() % 2;
		}
		//set(10, ScreenHeight() / 2, L"########-#####---###------######-#####");

		isRunning = true;
		Update();
	}

	void Game::Update()
	{		
		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();

				// Inputs
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
				{
					m_frameRate += m_frameRate + 5 < 200 ? 5 : 0;
					m_window.setFramerateLimit(m_frameRate);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
				{
					m_frameRate -= m_frameRate - 5 > 0 ? 5 : 0;
					m_window.setFramerateLimit(m_frameRate);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					isRunning = !isRunning;
					std::this_thread::sleep_for(std::chrono::milliseconds(250));
				}
			}

			if (isRunning)
			{
				m_window.clear(sf::Color::Magenta);
				UpdateGame();
				m_window.display();
			}
			else
				std::this_thread::sleep_for(std::chrono::milliseconds(1));

		}
	}

	// Update du jeu
	void Game::UpdateGame()
	{
		auto cell = [&](int x, int y)
		{
			return m_output[y * ScreenWidth() + x];
		};

		for (int i = 0; i < ScreenWidth() * ScreenHeight(); i++)
			m_output[i] = m_state[i];

		// Action à réaliser dans la fenêtre de jeu à part en bordure 
		for (int x = 1; x < ScreenWidth() - 1; x++)
			for (int y = 1; y < ScreenHeight() - 1; y++)
			{
				// Nombre de voisins autour d'une cellule
				int nNeighbours = cell(x - 1, y - 1) + cell(x, y - 1) + cell(x + 1, y - 1)+
								  cell(x - 1, y)	 +		0		  + cell(x + 1, y) +
								  cell(x - 1, y + 1) + cell(x, y + 1) + cell(x + 1, y + 1);

				if (cell(x, y) == 1)
					m_state[y * ScreenWidth() + x] = nNeighbours == 2 || nNeighbours == 3;
				else
					m_state[y * ScreenWidth() + x] = nNeighbours == 3;

				if (cell(x, y) == 1)
				{
					sf::RectangleShape pixel = sf::RectangleShape(sf::Vector2f(1.0f * PIXEL_SIZE, 1.0f * PIXEL_SIZE));
					pixel.setPosition((float)x * PIXEL_SIZE, (float)y * PIXEL_SIZE);
					pixel.setFillColor(sf::Color::White);
					m_window.draw(pixel);
				}
				else
				{
					sf::RectangleShape pixel = sf::RectangleShape(sf::Vector2f(1.0f * PIXEL_SIZE, 1.0f * PIXEL_SIZE));
					pixel.setPosition((float)x * PIXEL_SIZE, (float)y * PIXEL_SIZE);
					pixel.setFillColor(sf::Color::Black);
					m_window.draw(pixel);
				}				
			}
	}
}
