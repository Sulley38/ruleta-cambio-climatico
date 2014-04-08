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

#ifndef CONTADOR_H_
#define CONTADOR_H_

#include "Common.h"

extern class CContador
{
private:
    /** Temporizador SDL **/
    SDL_TimerID m_tTemporizador;

    /** Variable que almacena el tiempo en texto **/
    std::string m_szContadorTexto;

    /** Indicador de pausa **/
    bool m_bPause;

public:
    /** Comienza a contar **/
    void Comenzar();

    /** Función a ejecutar cada segundo para que aumente el contador **/
    static Uint32 CallbackContador( Uint32 interval, void* param );
    void AvanzarContador();

    /** Muestra el contador en pantalla **/
    void Renderizar( SDL_Surface* pDestSurface );

    /** Obtiene si está pausado o no **/
    bool GetPauseFlag();

    /** Detiene el contador **/
    void Pausar( bool bPausar );

    /** Destruye el objeto contador **/
    void Detener();
} Contador;

#endif // CONTADOR_H_
