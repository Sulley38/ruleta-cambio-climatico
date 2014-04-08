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
#include "ScrRecuento.h"

void CRecuento::Cargar()
{
    for( int i = 0; i < RUL_PLAYERS; i++ )
    {
        m_iDinero[i] = 0;
        m_iPaneles[i] = 0;
        m_szDinero[i] = "";
        m_szPaneles[i] = "";
    }

    m_iResalte = 0;
    m_rDestBoton.x = 250;
    m_rDestBoton.y = 500;
    m_rDestBoton.w = 300;
    m_rDestBoton.h = 60;

    m_vSup.resize(2);
    std::vector<std::string> vRutas(2);
    vRutas[0] = "data/img/recuento/background.png";
    vRutas[1] = "data/img/recuento/boton.png";
    Juego.CargarImagenes( m_vSup, vRutas );
}

void CRecuento::Renderizar( SDL_Surface* pDestSurface )
{
    SDL_BlitSurface( m_vSup[0], NULL, pDestSurface, NULL );
    if( m_iResalte == 1 ) SDL_BlitSurface( m_vSup[1], NULL, pDestSurface, &m_rDestBoton );
    FShowcard.EscribirCentrado( pDestSurface, Traduccion.String( "SCORE_TITLE" ), 60, 2 );
    FEras.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "SCORE_PANELES" ), 400, 150, 0 );
    FEras.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "SCORE_PUNTOS" ), 650, 150, 0 );
    FEras.Escribir( pDestSurface, Traduccion.String( "PLAY_PLAYER1" ), 60, 230, 0 );
    FEras.Escribir( pDestSurface, Traduccion.String( "PLAY_PLAYER2" ), 60, 310, 0 );
    FEras.Escribir( pDestSurface, Traduccion.String( "PLAY_PLAYER3" ), 60, 390, 0 );
    FEras.EscribirCentradoRelativo( pDestSurface, m_szPaneles[0], 400, 230, 0 );
    FEras.EscribirCentradoRelativo( pDestSurface, m_szPaneles[1], 400, 310, 0 );
    FEras.EscribirCentradoRelativo( pDestSurface, m_szPaneles[2], 400, 390, 0 );
    FEras.EscribirCentradoRelativo( pDestSurface, m_szDinero[0], 650, 230, 0 );
    FEras.EscribirCentradoRelativo( pDestSurface, m_szDinero[1], 650, 310, 0 );
    FEras.EscribirCentradoRelativo( pDestSurface, m_szDinero[2], 650, 390, 0 );
    FEras.EscribirCentrado( pDestSurface, m_szGanador, 450, 0 );
    FEras.EscribirCentrado( pDestSurface, Traduccion.String( "SCORE_CONTINUAR" ), 510, 0 );
}

void CRecuento::ObtenerDatos()
{
    // Obtiene las variables de la ruleta
    for( int i = 0; i < RUL_PLAYERS; i++ )
    {
        m_iDinero[i] = Ruleta.GetDineroTotal(i);
        m_iPaneles[i] = Ruleta.GetPanelesTotales(i);
        if( m_iDinero[i] == RUL_DINERO )
            m_szDinero[i] = "-";
        else
            m_szDinero[i] = Juego.IntToString( m_iDinero[i] ) + " £";
        if( m_iPaneles[i] == RUL_DINERO )
            m_szPaneles[i] = "-";
        else
            m_szPaneles[i] = Juego.IntToString( m_iPaneles[i] );
    }
    // Compara los resultados para determinar el ganador, o un posible empate
    bool bEmpate = false;
    m_iGanador = 0;
    m_szGanador = Traduccion.String( "SCORE_GANADOR" );
    if( m_iDinero[1] != RUL_DINERO ) {
        if( m_iDinero[1] > m_iDinero[m_iGanador] )
            m_iGanador = 1;
        else if( m_iDinero[1] == m_iDinero[m_iGanador] && m_iPaneles[1] > m_iPaneles[m_iGanador] )
            m_iGanador = 1;
        else if( m_iDinero[1] == m_iDinero[m_iGanador] && m_iPaneles[1] == m_iPaneles[m_iGanador] )
            bEmpate = true;

        if( m_iDinero[2] != RUL_DINERO ) {
            if( m_iDinero[2] > m_iDinero[m_iGanador] )
                m_iGanador = 2;
            else if( m_iDinero[2] == m_iDinero[m_iGanador] && m_iPaneles[2] > m_iPaneles[m_iGanador] )
                m_iGanador = 2;
            else if( m_iDinero[2] == m_iDinero[m_iGanador] && m_iPaneles[2] == m_iPaneles[m_iGanador] )
                bEmpate = true;
        }
    }

    if( bEmpate )
        m_szGanador += Traduccion.String( "SCORE_EMPATE" );
    else if( m_iGanador == 2 )
        m_szGanador += Traduccion.String( "PLAY_PLAYER3" );
    else if( m_iGanador == 1 )
        m_szGanador += Traduccion.String( "PLAY_PLAYER2" );
    else if( m_iPaneles[0] == 0 )
        m_szGanador += Traduccion.String( "SCORE_NINGUNO" );
    else
        m_szGanador += Traduccion.String( "PLAY_PLAYER1" );
}

void CRecuento::TeclaPulsada( const int& iTecla )
{
    if( iTecla == SDLK_RETURN || iTecla == SDLK_ESCAPE ) {
        Ruleta.Reiniciar();
        Juego.SetCurrentScreen(1);
    }
}

void CRecuento::MouseMovido( const int& iX, const int& iY )
{
    if( iX >= 250 && iX < 550 ) {
        if( iY >= 500 && iY < 560 )
            m_iResalte = 1;
        else
            m_iResalte = 0;
    }
    else
        m_iResalte = 0;
}

void CRecuento::MousePulsado( const int& iX, const int& iY )
{
    if( m_iResalte == 1 ) {
        Ruleta.Reiniciar();
        Juego.SetCurrentScreen(1);
    }
}

void CRecuento::Limpiar()
{
    SDL_FreeSurface( m_vSup[0] );
    SDL_FreeSurface( m_vSup[1] );
}
