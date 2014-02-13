#ifndef IDIOMA_H_
#define IDIOMA_H_

#include "Common.h"

extern class CIdioma
{
    /** Superficies **/
    std::vector<SDL_Surface*> m_vSup;
    SDL_Rect m_rDestBoton;

    /** Controla el resalte de los botones **/
    SInt m_iResalte;

public:
    /** Carga las estructuras básicas necesarias **/
    void Cargar();

    /** Muestra todo en pantalla **/
    void Renderizar( SDL_Surface* pDestSurface );

    /** Gestiona los métodos de entrada **/
    void TeclaPulsada( const int& iTecla );
    void MouseMovido( const int& iX, const int& iY );
    void MousePulsado( const int& iX, const int& iY );

    /** Libera la memoria usada por las estructuras básicas **/
    void Limpiar();
} Idioma;

#endif // IDIOMA_H_

