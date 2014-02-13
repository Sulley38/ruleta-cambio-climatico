#ifndef BOTONES_H_
#define BOTONES_H_

#include "Common.h"

extern class CBotones
{
private:
	/** Vector de superficies que contienen las letras y los botones **/
    std::vector<SDL_Surface*> m_vSup;

    /** Información para mostrar dichos elementos **/
    SDL_Rect m_rDestLetras;
    SDL_Rect m_rDestBotones;

    /** Indicador de imagen a copiar **/
    SInt m_iBotonResaltado;

    /** Letra que corresponde a cada código **/
    std::vector<char> m_vCode;

public:
    /** Carga las imágenes **/
    void Cargar();

    /** Muestra las letras y los botones en pantalla **/
    void Renderizar( SDL_Surface* pDestSurface );
    void BlitButton( SDL_Surface* pDestSurface, const int& iBoton );

    /** Indica el resalte al pasar el ratón por encima de un botón **/
    void MouseMovido( const int& iX, const int& iY );
    /** Devuelve el número del botón resaltado **/
    int GetResaltado();

    /** Libera los recursos usados **/
    void Limpiar();
} Botones;

#endif // BOTONES_H_
