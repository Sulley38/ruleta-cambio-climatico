/*  Copyright 2009, 2010 Iván Matellanes
 *
 *  This file is part of La ruleta del cambio climático.
 *
 *  La ruleta del cambio climático is free software: you can redistribute
 *  it and/or modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  La ruleta del cambio climático is distributed in the hope that it will
 *  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with La ruleta del cambio climático is distributed. 
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BOTONES_H_
#define BOTONES_H_

#include "Common.h"

extern class CBotones
{
private:
	/** Vector de superficies que contienen las letras y los botones **/
    std::vector<SDL_Surface*> m_vSup;

    /** Información para mostrar dichos elementos **/
    SDL_Rect m_rDestLetras;
    SDL_Rect m_rDestBotones;

    /** Indicador de imagen a copiar **/
    SInt m_iBotonResaltado;

    /** Letra que corresponde a cada código **/
    std::vector<char> m_vCode;

public:
    /** Carga las imágenes **/
    void Cargar();

    /** Muestra las letras y los botones en pantalla **/
    void Renderizar( SDL_Surface* pDestSurface );
    void BlitButton( SDL_Surface* pDestSurface, const int& iBoton );

    /** Indica el resalte al pasar el ratón por encima de un botón **/
    void MouseMovido( const int& iX, const int& iY );
    /** Devuelve el número del botón resaltado **/
    int GetResaltado();

    /** Libera los recursos usados **/
    void Limpiar();
} Botones;

#endif // BOTONES_H_
