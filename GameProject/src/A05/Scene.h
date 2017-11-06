#pragma once
#include "Renderer.h"

enum estadoDeJuego { MENU, JUEGO, TRANSICION1, TRANSICION2 }; //Transicion1 es de Menu a Juego Transicion2 es de Juego a Exit

class Scene 
{
public:
	Scene();
	~Scene();
	estadoDeJuego estadoVar;

	virtual void eventHandler();
	virtual void Update();
	virtual void Draw();
};

