#include "Menu.h"



Menu::Menu()
{
	estadoVar = estadoDeJuego::MENU;
	imTapped = false;
	
	contenedorDeRects["bg"] = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };
	Vector2 aux = Renderer::Instance()->GetTextureSize("textoPlay");
	contenedorDeRects["Start"] = { 0,0,aux.x ,aux.y };
	aux = Renderer::Instance()->GetTextureSize("textoExit");
	contenedorDeRects["Exit"] = { 0,0,aux.x ,aux.y };
	
	contenedorDeRects["cursor"] = { 0,0,100 ,50 }; 
	contenedorDeRects["cursor_target"] = { 0,0,100,100 };
}


Menu::~Menu()
{

}

void Menu::eventHandler()
{
	while (SDL_PollEvent(&manejador)) {
		switch (manejador.type) 
		{
			case SDL_MOUSEMOTION:
				contenedorDeRects["cursor_target"].x = manejador.motion.x - contenedorDeRects["cursor"].w / 2;
				contenedorDeRects["cursor_target"].y = manejador.motion.y - contenedorDeRects["cursor"].h / 2;
				break;
			case SDL_MOUSEBUTTONDOWN:
				imTapped= true;
				break;
			case SDL_MOUSEBUTTONUP:
				imTapped = false;
				break;
			default:
				break;
		}
	}
}

void Menu::Update()
{
	contenedorDeRects["cursor"].x += (contenedorDeRects["cursor_target"].x - contenedorDeRects["cursor"].x) / 10;
	contenedorDeRects["cursor"].y += (contenedorDeRects["cursor_target"].y - contenedorDeRects["cursor"].y) / 10;
	if (imTapped)
	{

		if (manejador.motion.x >= 350 && manejador.motion.y >= 150 && manejador.motion.x <= 350 + contenedorDeRects["Start"].w && manejador.motion.y <= 150 + contenedorDeRects["Start"].h)
		{
			estadoVar = estadoDeJuego::TRANSICION1;
		}
		if (manejador.motion.x >= 350 && manejador.motion.y >= 250 && manejador.motion.x <= 350 + contenedorDeRects["Exit"].w&& manejador.motion.y <= 250 + contenedorDeRects["Exit"].h)
		{
			estadoVar = estadoDeJuego::TRANSICION2;
		}
	}
}

void Menu::Draw()
{
	Renderer::Instance()->Clear();

	Renderer::Instance()->PushImage("BG1", contenedorDeRects["bg"]);
	Renderer::Instance()->PushImage("textoPlay", contenedorDeRects["Start"]);
	Renderer::Instance()->PushImage("textoExit", contenedorDeRects["Exit"]);
	Renderer::Instance()->PushImage("Cloud", contenedorDeRects["cursor"]);
	Renderer::Instance()->Render();
}
