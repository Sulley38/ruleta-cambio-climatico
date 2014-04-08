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

#ifndef INICIO_H_
#define INICIO_H_

#include "Common.h"

extern class CInicio
{
private:
    /** Superficies **/
    std::vector<SDL_Surface*> m_vSup;
    SDL_Rect m_rDestFlechas;
    SDL_Rect m_rDestBoton;

    /** Indicador de imagen a resaltar **/
    SInt m_iResalte;

    /** Indicador de número de jugadores **/
    std::string m_szJugadores;

public:
    /** Carga la imagen **/
    void Cargar();

    /** Muestra la imagen en pantalla **/
    void Renderizar( SDL_Surface* pDestSurface );

    /** Gestiona las teclas pulsadas y las acciones del ratón **/
    void TeclaPulsada( const int& iTecla );
    void MouseMovido( const int& iX, const int& iY );
    void MousePulsado( const int& iX, const int& iY );

    /** Libera la memoria **/
    void Limpiar();
} Inicio;

#endif // INICIO_H_
