#pragma once
#include <SFML/Graphics.hpp>

namespace game
{
	class Game
	{
	public:
		Game();
		void Start();
	private:
		sf::RenderWindow m_window;
		int* m_output;
		int* m_state;
	protected:
		void Update();
		void UpdateGame();
	};
}


