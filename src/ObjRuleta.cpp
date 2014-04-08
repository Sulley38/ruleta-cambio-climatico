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

void CRuleta::Cargar()
{
    // Inicializar variables y clases
    for( int i = 0; i < RUL_PLAYERS; i++ )
    {
        m_iDinero[i] = 0;
        m_iDineroTotal[i] = 0;
        m_iPanelesResueltos[i] = 0;
        m_rDestMarcador[i].y = 531;
        m_rDestMarcador[i].w = 267;
        m_rDestMarcador[i].h = 34;
    }
    m_rDestMarcador[0].x = 0;
    m_rDestMarcador[1].x = 267;
    m_rDestMarcador[2].x = 532;
    m_rDestMarcador[1].w = 266;
    m_rDestGajo.x = 531;
    m_rDestGajo.y = 356;
    m_rDestGajo.w = 255;
    m_rDestGajo.h = 125;
    m_rDestMarco.x = 0;
    m_rDestMarco.y = 531;
    m_rDestMarco.w = 268;
    m_rDestMarco.h = 36;

    m_iGajo = 0;
    m_iJugadores = 1;
    m_iTurno = -1;
    m_iPenalizado = 0;
    m_bTirada = false;

    // Monta la ruleta: del 0 al 39 los gajos normales, del 40 al 43 los especiales
    // Probabilidades: Q/PT -> 10% / 25 -> 10% / 50 -> 15% / 75 -> 17.5% / 100 -> 20% / 150 -> 15% / 200 -> 10% / 1000 -> 2.5%
    m_vRuleta.resize(44);
    m_vRuleta[0] = 16; m_vRuleta[1] = 12; m_vRuleta[2] = 6; m_vRuleta[3] = 10; m_vRuleta[4] = 5; m_vRuleta[5] = 7; m_vRuleta[6] = 14; m_vRuleta[7] = 9; m_vRuleta[8] = 5; m_vRuleta[9] = 4;
    m_vRuleta[10] = 17; m_vRuleta[11] = 9; m_vRuleta[12] = 8; m_vRuleta[13] = 11; m_vRuleta[14] = 13; m_vRuleta[15] = 4; m_vRuleta[16] = 9; m_vRuleta[17] = 5; m_vRuleta[18] = 7; m_vRuleta[19] = 11;
    m_vRuleta[20] = 16; m_vRuleta[21] = 12; m_vRuleta[22] = 5; m_vRuleta[23] = 9; m_vRuleta[24] = 8; m_vRuleta[25] = 15; m_vRuleta[26] = 10; m_vRuleta[27] = 4; m_vRuleta[28] = 6; m_vRuleta[29] = 8;
    m_vRuleta[30] = 17; m_vRuleta[31] = 9; m_vRuleta[32] = 7; m_vRuleta[33] = 14; m_vRuleta[34] = 11; m_vRuleta[35] = 4; m_vRuleta[36] = 13; m_vRuleta[37] = 9; m_vRuleta[38] = 8; m_vRuleta[39] = 12;
    m_vRuleta[40] = 18; m_vRuleta[41] = 19; m_vRuleta[42] = 20; m_vRuleta[43] = 21;

    // Carga los sonidos
    const char* szPaths[RUL_SONIDOS] = { "data/sound/giroruleta.wav", "data/sound/letrabad.wav", "data/sound/letraok.wav", "data/sound/panelbad.wav", "data/sound/panelok.wav", "data/sound/quiebra.wav" };
    Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024 );
    for( int i = 0; i < RUL_SONIDOS; i++ ) {
        m_cSonidos[i] = Mix_LoadWAV( szPaths[i] );
        if( m_cSonidos[i] == NULL )
            Juego.Advertencia( Mix_GetError() );
    }
}

void CRuleta::CargarTraducciones()
{
    // Carga los marcadores y los gajos de la ruleta acorde con el idioma
    std::string Lang = Traduccion.GetLang();
    m_vSup.resize(RUL_GAJOS);
    std::vector<std::string> vRutas(RUL_GAJOS);
    vRutas[0] = "data/img/jugar/marcador1.png";
    vRutas[1] = "data/img/jugar/marcador2.png";
    vRutas[2] = "data/img/jugar/marcador3.png";
    vRutas[3] = "data/img/jugar/marcoboton.png";
    vRutas[4] = "data/img/jugar/ruleta/25a.png";
    vRutas[5] = "data/img/jugar/ruleta/50r.png";
    vRutas[6] = "data/img/jugar/ruleta/50v.png";
    vRutas[7] = "data/img/jugar/ruleta/75a.png";
    vRutas[8] = "data/img/jugar/ruleta/75m.png";
    vRutas[9] = "data/img/jugar/ruleta/100v.png";
    vRutas[10] = "data/img/jugar/ruleta/100y.png";
    vRutas[11] = "data/img/jugar/ruleta/150r.png";
    vRutas[12] = "data/img/jugar/ruleta/150a.png";
    vRutas[13] = "data/img/jugar/ruleta/200y.png";
    vRutas[14] = "data/img/jugar/ruleta/200m.png";
    vRutas[15] = "data/img/jugar/ruleta/1000.png";
    vRutas[16] = "data/img/jugar/ruleta/" + Lang + "/00n.png";
    vRutas[17] = "data/img/jugar/ruleta/" + Lang + "/00p.png";
    vRutas[18] = "data/img/jugar/ruleta/" + Lang + "/00a.png";
    vRutas[19] = "data/img/jugar/ruleta/" + Lang + "/00v.png";
    vRutas[20] = "data/img/jugar/ruleta/" + Lang + "/00r.png";
    vRutas[21] = "data/img/jugar/ruleta/" + Lang + "/00b.png";
    Juego.CargarImagenes( m_vSup, vRutas );
}

void CRuleta::NuevaPartida()
{
    m_bTirada = false;
    m_iDinero[0] = 0;
    m_szDinero[0] = "0 £";
    m_iDinero[1] = 0;
    m_szDinero[1] = "0 £";
    m_iDinero[2] = 0;
    m_szDinero[2] = "0 £";
    m_iGajo = 43;
    if( m_iPenalizado != 0 )
        m_szDinero[m_iPenalizado-1] = "-";
    PasarTurno();
}

void CRuleta::Tirar()
{
    // Mientras la ruleta gira, ignorar eventos de ratón y teclado
    SDL_EventState( SDL_KEYDOWN, SDL_IGNORE );
    SDL_EventState( SDL_KEYUP, SDL_IGNORE );
    SDL_EventState( SDL_MOUSEBUTTONDOWN, SDL_IGNORE );
    SDL_EventState( SDL_MOUSEBUTTONUP, SDL_IGNORE );
    ReproducirSonido(0);
    // Hace girar a la ruleta pasando por 12 casillas hasta una obtenida aleatoriamente
    for( int i = 0; i < 12; i++ ) {
        if( m_iGajo >= 39 )
            m_iGajo = 0;
        else
            m_iGajo++;
        Juego.Renderizar();
        Juego.LeerEntrada();
        SDL_Delay( 150 );
    }
    m_iGajo = Juego.GetRandom() % 40;
    if( m_iGajo == 0 || m_iGajo == 20 ) {
        // Si caemos en quiebra, reproducir sonido, quitar todo el dinero y pasar turno
        ReproducirSonido(5);
        m_iDinero[m_iTurno] = 0;
        m_szDinero[m_iTurno] = "0 £";
        PasarTurno();
    } else if( m_iGajo == 10 || m_iGajo == 30 ) {
        // Si caemos en pierde turno, reproducir sonido y pasar el turno
        PasarTurno();
    } else {
        // Establece el indicador de tirada a verdadero para esperar una letra
        m_bTirada = true;
    }
    // Volver a aceptar eventos de ratón y teclado
    SDL_EventState( SDL_KEYDOWN, SDL_ENABLE );
    SDL_EventState( SDL_KEYUP, SDL_ENABLE );
    SDL_EventState( SDL_MOUSEBUTTONDOWN, SDL_ENABLE );
    SDL_EventState( SDL_MOUSEBUTTONUP, SDL_ENABLE );
}

void CRuleta::Renderizar( SDL_Surface* pDestSurface )
{
    SDL_BlitSurface( m_vSup[m_vRuleta[m_iGajo]], NULL, pDestSurface, &m_rDestGajo );
    // Dibuja los marcadores de cada jugador, en caso de que esté jugando
    SDL_BlitSurface( m_vSup[0], NULL, pDestSurface, &m_rDestMarcador[0] );
    FTrebuchet.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_PLAYER1" ), 87, 535, 1 );
    FTrebuchet.EscribirCentradoRelativo( pDestSurface, m_szDinero[0], 220, 535, 0 );
    if( m_iJugadores > 1 )
    {
        SDL_BlitSurface( m_vSup[1], NULL, pDestSurface, &m_rDestMarcador[1] );
        FTrebuchet.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_PLAYER2" ), 354, 535, 1 );
        FTrebuchet.EscribirCentradoRelativo( pDestSurface, m_szDinero[1], 487, 535, 0 );
        if( m_iJugadores > 2 )
        {
            SDL_BlitSurface( m_vSup[2], NULL, pDestSurface, &m_rDestMarcador[2] );
            FTrebuchet.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_PLAYER3" ), 619, 535, 1 );
            FTrebuchet.EscribirCentradoRelativo( pDestSurface, m_szDinero[2], 754, 535, 0 );
        }
    }

    if( m_iJugadores > 1 ) {
        if( m_iTurno == 0 )
            m_rDestMarco.x = 0;
        else if( m_iTurno == 1 )
            m_rDestMarco.x = 266;
        else if( m_iTurno == 2 )
            m_rDestMarco.x = 532;
        SDL_BlitSurface( m_vSup[3], NULL, pDestSurface, &m_rDestMarco );
    }
}

int CRuleta::GetJugadores()
{
    return m_iJugadores;
}

void CRuleta::SetJugadores( const int& iJugadores )
{
    m_iJugadores = iJugadores;
}

void CRuleta::PasarTurno()
{
    if( m_iTurno+1 < m_iJugadores )
        m_iTurno++;
    else
        m_iTurno = 0;
    // Vuelve a pasar si el jugador está penalizado
    if( m_iTurno+1 == m_iPenalizado )
        PasarTurno();
}

void CRuleta::Penalizar( const bool& bActivar )
{
    // Marca la penalizacion si no se está jugando solo
    if( m_iJugadores > 1 ) {
        if( bActivar ) {
            m_iPenalizado = m_iTurno+1;
        } else {
            m_iPenalizado = 0;
        }
    }
}

void CRuleta::SumarDinero( const int& iRepeticiones )
{
    SInt iCantidad = 0;
 /// ARREGLAR
    if( m_vRuleta[m_iGajo] == 4 )
        iCantidad = 25;
    else if( m_vRuleta[m_iGajo] == 5 || m_vRuleta[m_iGajo] == 6 )
        iCantidad = 50;
    else if( m_vRuleta[m_iGajo] == 7 || m_vRuleta[m_iGajo] == 8 )
        iCantidad = 75;
    else if( m_vRuleta[m_iGajo] == 9 || m_vRuleta[m_iGajo] == 10 )
        iCantidad = 100;
    else if( m_vRuleta[m_iGajo] == 11 || m_vRuleta[m_iGajo] == 12 )
        iCantidad = 150;
    else if( m_vRuleta[m_iGajo] == 13 || m_vRuleta[m_iGajo] == 14 )
        iCantidad = 200;
    else if( m_vRuleta[m_iGajo] == 15 )
        iCantidad = 1000;

    m_iDinero[m_iTurno] += iCantidad * iRepeticiones;
    if( m_iDinero[m_iTurno] >= RUL_DINERO )
        m_iDinero[m_iTurno] = RUL_DINERO-1;
    m_szDinero[m_iTurno] = Juego.IntToString( m_iDinero[m_iTurno] ) + " £";
}

void CRuleta::RestarDinero( const int& iCantidad )
{
    m_iDinero[m_iTurno] -= iCantidad;
    m_szDinero[m_iTurno] = Juego.IntToString( m_iDinero[m_iTurno] ) + " £";
}

int CRuleta::GetDinero()
{
    return m_iDinero[m_iTurno];
}

void CRuleta::SumarPanelDinero()
{
    m_iPanelesResueltos[m_iTurno]++;
    m_iDineroTotal[m_iTurno] += m_iDinero[m_iTurno];
}

int CRuleta::GetDineroTotal( const int& iJugador )
{
    if( iJugador < m_iJugadores ) {
        return m_iDineroTotal[iJugador];
    } else {
        return RUL_DINERO;
    }
}

int CRuleta::GetPanelesTotales( const int& iJugador )
{
    if( iJugador < m_iJugadores ) {
        return m_iPanelesResueltos[iJugador];
    } else {
        return RUL_DINERO;
    }
}

bool CRuleta::TiradaRealizada()
{
    return m_bTirada;
}

void CRuleta::EsperarTirada()
{
    m_bTirada = false;
}

void CRuleta::SetGajo( const int& iGajo )
{
    m_iGajo = iGajo;
}

void CRuleta::ReproducirSonido( const int& iPista )
{
    m_iCanal = Mix_PlayChannel( -1, m_cSonidos[iPista], 0 );
}

void CRuleta::Reiniciar()
{
    m_iGajo = 43;
    m_iTurno = -1;
    m_iPenalizado = 0;
    m_bTirada = false;

    m_iDinero[0] = 0;
    m_szDinero[0] = "0 £";
    m_iDineroTotal[0] = 0;
    m_iPanelesResueltos[0] = 0;
    m_iDinero[1] = 0;
    m_szDinero[1] = "0 £";
    m_iDineroTotal[1] = 0;
    m_iPanelesResueltos[1] = 0;
    m_iDinero[2] = 0;
    m_szDinero[2] = "0 £";
    m_iDineroTotal[2] = 0;
    m_iPanelesResueltos[2] = 0;
}

void CRuleta::Limpiar()
{
    if( m_vSup.size() == RUL_GAJOS )
        for( int i = 0; i < RUL_GAJOS; i++ )
            SDL_FreeSurface( m_vSup[i] );

    if( m_cSonidos[RUL_SONIDOS-1] != 0 )
        for( int i = 0; i < RUL_SONIDOS; i++ )
            Mix_FreeChunk( m_cSonidos[i] );
    Mix_CloseAudio();
}
