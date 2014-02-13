#ifndef RECUENTO_H_
#define RECUENTO_H_

#include "Common.h"

extern class CRecuento
{
private:
    /** Superficie y rectángulo del boton "Continuar" **/
    std::vector<SDL_Surface*> m_vSup;
    SDL_Rect m_rDestBoton;

    /** Controla el resalte del boton **/
    SInt m_iResalte;

    /** Cantidad de dinero acumulado y paneles resueltos de cada jugador **/
    SInt m_iDinero[RUL_PLAYERS];
    SInt m_iPaneles[RUL_PLAYERS];
    std::string m_szDinero[RUL_PLAYERS];
    std::string m_szPaneles[RUL_PLAYERS];

    /** Dinero, paneles y nombre del ganador **/
    SInt m_iGanador;
    std::string m_szGanador;

public:
    /** Carga las estructuras básicas necesarias **/
    void Cargar();

    /** Muestra todo en pantalla **/
    void Renderizar( SDL_Surface* pDestSurface );

    /** Recopila los resultados de los jugadores y determina el ganador **/
    void ObtenerDatos();

    /** Gestiona los métodos de entrada **/
    void TeclaPulsada( const int& iTecla );
    void MouseMovido( const int& iX, const int& iY );
    void MousePulsado( const int& iX, const int& iY );

    /** Libera la memoria usada por las estructuras básicas **/
    void Limpiar();
} Recuento;

#endif // RECUENTO_H_
