#pragma once
#include <SFML/Graphics.hpp>

namespace game
{
	class Game
	{
	public:
		Game();
		bool isRunning;
		void Start();
	private:
		sf::RenderWindow m_window;
		int* m_output;
		int* m_state;
		int  m_frameRate;
		sf::Vector2i m_previousMousePos;
	protected:
		void Update();
		void UpdateGame();
		void PauseGame();
		void EditCell(int x, int y);
		void ClearCells();
	};
}


