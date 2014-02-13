#ifndef PANELES_H_
#define PANELES_H_

#include "Common.h"

extern class CPanel
{
private:
    /** Mapa de caracteres del panel **/
    std::vector<SDL_Surface*> m_vSup;

    /** Información para dibujar las letras **/
    SDL_Rect m_rOrig;
    SDL_Rect m_rDest;
    SDL_Rect m_rDestMarco;

    /** Paneles y pistas **/
    std::vector<std::string> m_vPaneles;
    std::vector<std::string> m_vPistas;
    /** Carácteres válidos en el panel **/
    static const std::string m_szValidos;

    /** Indicador de paneles ya jugados **/
    std::vector<bool> m_vPanelesJugados;

    /** Número del panel actualmente en juego **/
    SInt m_iPanelActual;

    /** Relaciona cada letra con su estado de compra **/
    std::map<char,bool> m_dCompradas;

public:
    /** Carga el mapa de caracteres, los paneles y las pistas **/
    void Cargar();
    void CargarPaneles();
    std::string ComponerLinea( std::string& szData, const SInt& i, const std::string& szOrden, const SInt& iMax );

    /** Escoge otro panel y reinicia las letras compradas **/
    void NuevoPanel();

    /** Muestra el panel en pantalla **/
    void Renderizar( SDL_Surface* pDestSurface );

    /** Comprueba si el panel está resuelto **/
    bool ComprobarResuelto();
    /** Establece y obtiene las variables de letras compradas **/
    bool ComprobarLetra( const char& ID );
    void MarcarLetra( const char& ID );
    void MarcarTodo();

    /** Busca el número de veces que está una letra en el panel **/
    int BuscarLetra( const char& ID );

    /** Libera los recursos utilizados por el panel **/
    void Limpiar();
} Panel;

#endif // PANELES_H_
