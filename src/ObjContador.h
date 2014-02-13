#ifndef CONTADOR_H_
#define CONTADOR_H_

#include "Common.h"

extern class CContador
{
private:
    /** Temporizador SDL **/
    SDL_TimerID m_tTemporizador;

    /** Variable que almacena el tiempo en texto **/
    std::string m_szContadorTexto;

    /** Indicador de pausa **/
    bool m_bPause;

public:
    /** Comienza a contar **/
    void Comenzar();

    /** Función a ejecutar cada segundo para que aumente el contador **/
    static Uint32 CallbackContador( Uint32 interval, void* param );
    void AvanzarContador();

    /** Muestra el contador en pantalla **/
    void Renderizar( SDL_Surface* pDestSurface );

    /** Obtiene si está pausado o no **/
    bool GetPauseFlag();

    /** Detiene el contador **/
    void Pausar( bool bPausar );

    /** Destruye el objeto contador **/
    void Detener();
} Contador;

#endif // CONTADOR_H_
