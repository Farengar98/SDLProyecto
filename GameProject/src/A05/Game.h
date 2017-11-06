#pragma once
#include "Menu.h"
#include "Play.h"
#include "Constants.h"

class Game 
{
public:
	Game();
	~Game();

	Scene *escena;
	bool imInGame;
	void Run();

};

