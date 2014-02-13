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
