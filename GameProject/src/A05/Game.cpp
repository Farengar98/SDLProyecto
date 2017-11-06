#include "Game.h"



Game::Game()
{
	imInGame = true;
	//FUENTES
	Renderer::Instance()->LoadFont({ "FuenteDragonBall", "../../res/ttf/saiyan.ttf", 80 });
	Renderer::Instance()->LoadFont({ "FuenteLuigi", "../../res/ttf/MarioLuigi2.ttf", 80 });
	//TEXTO
	Text textoPlay{ "textoPlay", "PLAY", {0,255,0, 255}, 123,81 };
	Text textoExit{ "textoExit", "EXIT", {255, 0, 0, 255}, 123,81 };
	Text textPj1{ "textoPj1", "PJ 1: ", {0,0,0,255}, 123,81 };
	Text textPj2{ "textoPj2", "PJ 2: ",{ 0,0,0,255 }, 123,81 };
	Renderer::Instance()->LoadTextureText("FuenteDragonBall", textoPlay);
	Renderer::Instance()->LoadTextureText("FuenteDragonBall", textoExit);
	Renderer::Instance()->LoadTextureText("FuenteLuigi", textPj1);
	Renderer::Instance()->LoadTextureText("FuenteLuigi", textPj2);
	//TEXTURAS
	Renderer::Instance()->LoadTexture("Player", "../../res/img/spCastle.png");
	Renderer::Instance()->LoadTexture("Cloud", "../../res/img/kintoun2.png");
	Renderer::Instance()->LoadTexture("Gold", "../../res/img/gold.png");
	Renderer::Instance()->LoadTexture("BG1", "../../res/img/bgCastle.jpg");
	Renderer::Instance()->LoadTexture("BG2", "../../res/img/bg2.jpg");

	escena = new Menu();

};
	



Game::~Game()
{
}

void Game::Run()
{
	
	while (imInGame == true)
	{
		switch (escena->estadoVar)
		{
		case estadoDeJuego::MENU:
				escena->eventHandler();
				escena->Update();
				escena->Draw();
			break;
		case estadoDeJuego::TRANSICION1:
				delete escena;
				escena = new Play();
			break;
		case estadoDeJuego::JUEGO:
				escena->eventHandler();
				escena->Update();
				escena->Draw();
			 break;
		case estadoDeJuego::TRANSICION2:
			delete escena;
			imInGame = false;
			break;

		default:
			break;
		}

	}
}
