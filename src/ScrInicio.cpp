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

#include "ObjRuleta.h"
#include "ScrInicio.h"
#include "ScrJugar.h"

void CInicio::Cargar()
{
    m_iResalte = 0;
    m_szJugadores = "1";

    m_rDestFlechas.x = 0;
    m_rDestFlechas.y = 367;
    m_rDestFlechas.w = 38;
    m_rDestFlechas.h = 70;
    m_rDestBoton.x = 0;
    m_rDestBoton.y = 450;
    m_rDestBoton.w = 102;
    m_rDestBoton.h = 100;

    m_vSup.resize(4);
    std::vector<std::string> vRutas(4);
    vRutas[0] = "data/img/inicio/background.png";
    vRutas[1] = "data/img/inicio/flechaizq.png";
    vRutas[2] = "data/img/inicio/flechader.png";
    vRutas[3] = "data/img/inicio/boton.png";
    Juego.CargarImagenes( m_vSup, vRutas );
}

void CInicio::Renderizar( SDL_Surface* pDestSurface )
{
    SDL_BlitSurface( m_vSup[0], NULL, pDestSurface, NULL );
    if( m_iResalte == 1 )
        SDL_BlitSurface( m_vSup[1], NULL, pDestSurface, &m_rDestFlechas );
    else if( m_iResalte == 2 )
        SDL_BlitSurface( m_vSup[2], NULL, pDestSurface, &m_rDestFlechas );
    else if( m_iResalte == 3 )
        SDL_BlitSurface( m_vSup[3], NULL, pDestSurface, &m_rDestBoton );
    else if( m_iResalte == 4 )
        SDL_BlitSurface( m_vSup[3], NULL, pDestSurface, &m_rDestBoton );

    FShowcard.Escribir( pDestSurface, Traduccion.String( "START_TITLE1" ), 80, 140, 2 );
    FShowcard.Escribir( pDestSurface, Traduccion.String( "START_TITLE2" ), 170, 200, 2 );
    FEras.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "START_PLAYERS" ), 400, 320, 0 );
    FEras.EscribirCentradoRelativo( pDestSurface, m_szJugadores, 400, 382, 0 );
    FEras.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "START_JUGAR" ), 300, 480, 0 );
    FEras.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "START_SALIR" ), 500, 480, 0 );
}

void CInicio::TeclaPulsada( const int& iTecla )
{
    if( iTecla == SDLK_1 )
        m_szJugadores[0] = '1';
    else if( iTecla == SDLK_2 )
        m_szJugadores[0] = '2';
    else if( iTecla == SDLK_3 )
        m_szJugadores[0] = '3';
    else if( iTecla == SDLK_RETURN ) {
        Ruleta.SetJugadores( m_szJugadores[0]-'0' );
        Principal.NuevaPartida();
        Juego.SetCurrentScreen(2);
    } else if( iTecla == SDLK_ESCAPE )
        Juego.SetQuitFlag();
}

void CInicio::MouseMovido( const int& iX, const int& iY )
{
    if( iY >= 367 && iY < 437 )
    {
        if( iX >= 302 && iX < 340 )
        {
            m_rDestFlechas.x = 302;
            m_iResalte = 1;
        }
        else if( iX >= 460 && iX < 498 )
        {
            m_rDestFlechas.x = 460;
            m_iResalte = 2;
        }
        else
        {
            m_iResalte = 0;
        }
    }
    else if( iY >= 450 && iY < 550 )
    {
        if( iX >= 250 && iX < 350 )
        {
            m_rDestBoton.x = 250;
            m_iResalte = 3;
        }
        else if( iX >= 450 && iX < 550 )
        {
            m_rDestBoton.x = 450;
            m_iResalte = 4;
        }
        else
        {
            m_iResalte = 0;
        }
    }
    else
    {
        m_iResalte = 0;
    }
}

void CInicio::MousePulsado( const int& iX, const int& iY )
{
    if( m_iResalte == 1 && m_szJugadores[0] > '1' ) {
        m_szJugadores[0]--;
    } else if( m_iResalte == 2 && m_szJugadores[0] < '3'  ) {
        m_szJugadores[0]++;
    } else if( m_iResalte == 3 ) {
        Ruleta.SetJugadores( m_szJugadores[0]-'0' );
        Principal.NuevaPartida();
        Juego.SetCurrentScreen(2);
    } else if( m_iResalte == 4 ) {
        Juego.SetQuitFlag();
    }
}

void CInicio::Limpiar()
{
    SDL_FreeSurface( m_vSup[0] );
    SDL_FreeSurface( m_vSup[1] );
    SDL_FreeSurface( m_vSup[2] );
    SDL_FreeSurface( m_vSup[3] );
}
