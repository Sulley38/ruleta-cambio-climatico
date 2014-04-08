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

#ifndef RULETA_H_
#define RULETA_H_

#include "Common.h"

extern class CRuleta
{
private:
    /** Imágenes e información para mostrarlas **/
    std::vector<SDL_Surface*> m_vSup;
    SDL_Rect m_rDestGajo;
    SDL_Rect m_rDestMarcador[RUL_PLAYERS];
    SDL_Rect m_rDestMarco;

    /** Sonidos de la ruleta **/
    Mix_Chunk* m_cSonidos[RUL_SONIDOS];

    /** La ruleta **/
    std::vector<int> m_vRuleta;

    /** Dinero que tenemos actualmente **/
    SInt m_iDinero[RUL_PLAYERS];
    std::string m_szDinero[RUL_PLAYERS];

    /** Cantidad de dinero acumulado y paneles resueltos al final **/
    SInt m_iDineroTotal[RUL_PLAYERS];
    SInt m_iPanelesResueltos[RUL_PLAYERS];

    /** Número de jugadores **/
    SInt m_iJugadores;

    /** Turno actual **/
    SInt m_iTurno;

    /** Jugador penalizado **/
    SInt m_iPenalizado;

    /** Indica si hemos tirado de la ruleta **/
    bool m_bTirada;

    /** Gajo en el que ha caído la ruleta **/
    SInt m_iGajo;

    /** Indicador de canal de sonido más alto usado **/
    int m_iCanal;

public:
    /** Carga los recursos y las imágenes de los gajos **/
    void Cargar();
    void CargarTraducciones();

    /** Resetea los marcadores y los indicadore de estado **/
    void NuevaPartida();

    /** Cambia el gajo en 10 ocasiones para acabar en uno aleatorio **/
    void Tirar();

    /** Muestra la ruleta en pantalla **/
    void Renderizar( SDL_Surface* pDestSurface );

    /** Devuelve el número de jugadores actualmente **/
    int GetJugadores();

    /** Establece el número de jugadores **/
    void SetJugadores( const int& iJugadores );

    /** Pasa el turno al siguiente jugador **/
    void PasarTurno();

    /** Marca el jugador que está penalizado **/
    void Penalizar( const bool& bActivar );

    /** Multiplica la cantidad de veces que está repetida una letra por la cantidad marcada en la ruleta **/
    void SumarDinero( const int& iRepeticiones );

    /** Resta la cantidad de dinero pasada como parámetro **/
    void RestarDinero( const int& iCantidad );

    /** Obtiene la cantidad actual **/
    int GetDinero();

    /** Devuelve si la ruleta ha sido tirada o no **/
    bool TiradaRealizada();

    /** Establece la ruleta como "No tirada" **/
    void EsperarTirada();

    /** Suma un panel y el dinero al marcador final del jugador que resuelve **/
    void SumarPanelDinero();
    /** Obtiene la cantidad total de dinero acumulado y paneles resueltos **/
    int GetDineroTotal( const int& iJugador );
    int GetPanelesTotales( const int& iJugador );

    /** Establece un gajo **/
    void SetGajo( const int& iGajo );

    /** Reproduce un sonido **/
    void ReproducirSonido( const int& iPista );

    /** Reinicia la ruleta y los marcadores completamente **/
    void Reiniciar();

    /** Libera los recursos utilizados **/
    void Limpiar();
} Ruleta;

#endif // RULETA_H_
