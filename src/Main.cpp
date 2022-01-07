
#include "Utility/Game.h"

int main()
{

#if defined(_DEBUG)
	std::cout << "Opening Game." << std::endl;
#endif
	//init rand
	std::srand(static_cast<unsigned>(time(NULL)));

	//init game engine
	Game game;

	//game loop
	while (game.running() && !game.getEndGame())
	{

		//update
		game.update();
		//render
		game.render();
	}

	return 0;
}
