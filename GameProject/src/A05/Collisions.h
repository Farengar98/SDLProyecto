#pragma once
#include <SDL.h>
#include <iostream>

namespace Collisions
{

	bool OnCollisionWalls(SDL_Rect &contenido, SDL_Rect contenedor) {

		if (contenido.y < contenedor.y) // arriba
		{
			std::cout << "Colision arriba" << std::endl;
			contenido.y = 1;
			return true;
		}
		else if (contenido.x < contenedor.x) //izquierda  
		{
			std::cout << "Colision izquierda" << std::endl;
			contenido.x = 1;
			return true;
		}
		else if (contenido.x + contenido.w > contenedor.x + contenedor.w) //derecha  
		{
			std::cout << "Colision derecha" << std::endl;
			contenido.x = contenedor.w-1;
			return true;
		}
		else if (contenido.y + contenido.h > contenedor.y + contenedor.h) //abajo  
		{
			std::cout << "Colision abajo" << std::endl;
			contenido.y = contenedor.h-1;
			return true;
		}
		else 
		{
			return false; 
		}
	}
}