/*
    Font Engine - Sistema de fuentes

    Las fuentes deben estar en formato .png y tener las siguientes características:
    - Las letras deben ser todas del mismo color. Se pueden usar sombreados de otros colores especificando su grosor mediante iPixelSombreado.
    - Como mínimo, debe haber 1 columna de separación entre cada letra.
    - Deben contener el siguiente texto (110 caracteres, EN ESTE ORDEN):
       !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~¿¡ÁÉÍÓÚáéíóúÑñ£
    - La primera línea horizontal de la imagen se puede usar para anexionar letras usando el mismo color que éstas.

    Pasa como argumentos de "Escanear()" la ruta a la imgaen, los píxeles de sombreado y el color de las letras.
*/

#ifndef FUENTE_H_
#define FUENTE_H_

#include "Common.h"

extern class CFuente
{
private:
    /** Superficie que contiene la imagen fuente a escanear y el texto a escribir **/
    SDL_Surface* m_sImagen;

    /** Los rangos de cada letra **/
    SInt m_iInicioLetras[MAX_LETRAS];
    SInt m_iFinalLetras[MAX_LETRAS];

public:
    /** Escanea la imagen para determinar el espacio de cada letra **/
    void Escanear( const std::string& szPath, int iPixelSombreado, Uint8 R, Uint8 G, Uint8 B, Uint8 A );
    Uint32 ObtenerPixel(SDL_Surface *Surface, Sint32 X, Sint32 Y);

    /** Escribe el texto con la fuente escaneada en la superficie y posición especificadas **/
    void Escribir( SDL_Surface* pDestSurface, const std::string& szTexto, int X, int Y, int Gap );

    /** Escribe el texto con la fuente escaneada en la superficie especificada
        y centrado a la pantalla o a una coordenada
    **/
    void EscribirCentrado( SDL_Surface* pDestSurface, const std::string& szTexto, int Y, int Gap );
    void EscribirCentradoRelativo( SDL_Surface* pDestSurface, const std::string& szTexto, int X, int Y, int Gap );

    /** Obtiene el ancho que va a ocupar el texto **/
    int AnchoTexto( const std::string& szTexto, int Gap );

    /** Libera la imagen **/
    void Terminar();
} FBerlin, FCalibri, FEras, FFranklin, FShowcard, FTrebuchet;

#endif // FUENTE_H_
