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
		int m_frameRate;
	protected:
		void Update();
		void UpdateGame();
	};
}


