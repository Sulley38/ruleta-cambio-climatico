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
