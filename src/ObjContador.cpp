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

#include "ObjContador.h"
#include "ScrJugar.h"

void CContador::Comenzar()
{
    if( m_tTemporizador != 0 )
        SDL_RemoveTimer( m_tTemporizador );

    // Reestablece los minutos y los segundos a 8
    m_szContadorTexto = "08";

    // Marca como no pausado
    m_bPause = false;

    // Guarda el valor actual del contador en la variable m_szContadorTexto y lo escribe usando la fuente
    m_tTemporizador = SDL_AddTimer( 1000, CallbackContador, 0 );
    if( m_tTemporizador == NULL )
        Juego.Advertencia( "No se ha podido iniciar el contador de tiempo." );
}

Uint32 CContador::CallbackContador( Uint32 interval, void* param )
{
    Uint32 Start = SDL_GetTicks();
    Contador.AvanzarContador();
    Uint32 End = SDL_GetTicks();
    return interval - End + Start;
}

void CContador::AvanzarContador()
{
    if( !m_bPause ) {
        // Reduce el contador en 1 segundo, a no ser que esté en pausa
        m_szContadorTexto[1]--;
        if( m_szContadorTexto[1] == '0'-1 )
            // Si se acabó el tiempo, pasar el turno
            Principal.TiempoAgotado();
    }
}

void CContador::Renderizar( SDL_Surface* pDestSurface )
{
    // Muestra en pantalla la variable m_szContadorTexto usando la fuente
    FCalibri.Escribir( pDestSurface, m_szContadorTexto, 20, 571, 3 );
}

bool CContador::GetPauseFlag()
{
    return m_bPause;
}

void CContador::Pausar( bool bPausar )
{
    // Establece la variable de pausa al valor que corresponda
    m_bPause = bPausar;
}

void CContador::Detener()
{
    // Quita el temporizador
    SDL_RemoveTimer( m_tTemporizador );
    m_szContadorTexto = " ";
}
