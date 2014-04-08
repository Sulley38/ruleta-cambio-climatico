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

#ifndef JUGAR_H_
#define JUGAR_H_

#include "Common.h"

extern class CJugar
{
private:
    /** Imagen de fondo **/
    SDL_Surface* m_pFondo;

    /** Indicador de estado -> 0 = Tirar; 1 = Comprar vocal; 2 = Resolver; 3 = Resuelto **/
    SInt m_iEstado;

    /** Indicador de salida **/
    bool m_bSalir;

    /** String que contiene la información de la barra inferior **/
    std::string m_szInfo;

public:
    /** Inicializa e invoca el resto de clases y carga los recursos necesarios **/
    void Cargar();

    /** Comienza una nueva partida **/
    void NuevaPartida();

    /** Renderiza la interfaz y el resto de las clases subordinadas **/
    void Renderizar( SDL_Surface* pDestSurface );

    /** Gestiona los métodos de entrada **/
    void TeclaPulsada( const int& iTecla );
    void MouseMovido( const int& iX, const int& iY );
    void MousePulsado( const int& iX, const int& iY );

    /** Gestiona las letras pulsadas y su efecto **/
    void LetraPulsada( const char& ID );

    /** Operaciones si se ha pasado el tiempo **/
    void TiempoAgotado();

    /** Devuelve el estado del juego **/
    int Estado();
    bool Salida();

	/** Libera los recursos usados **/
    void Limpiar();
} Principal;

#endif // JUGAR_H_
