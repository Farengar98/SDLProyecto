#pragma once
#include "Scene.h"
class Menu :	public Scene
{
public:
	Menu();
	~Menu();

	std::unordered_map<std::string, SDL_Rect> contenedorDeRects;

	SDL_Event manejador;

	bool imTapped;

	void eventHandler() override;
	void Update() override;
	void Draw() override;

};

