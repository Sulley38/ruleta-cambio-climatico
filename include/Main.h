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

#ifndef MAIN_H_
#define MAIN_H_

#include "Common.h"

extern class CApp
{
private:
    /** Posición de la ventana **/
    int m_iXPos;
    int m_iYPos;
	/** Ancho de la ventana **/
	int m_iWidth;
	/** Alto de la ventana **/
	int m_iHeight;

    /** Información sobre la ventana **/
    SDL_SysWMinfo m_wmWindow;
    /** Indicador de ventana minimizada **/
	bool m_bPausa;

    /** Superficie de pantalla **/
	SDL_Surface* m_pScreen;

    /** Pantalla en la que estamos **/
    int m_iPantallaActual; // 0 = IDIOMA; 1 = INICIO; 2 = JUEGO; 3 = RECUENTO;

    /** Indicador de fin del bucle principal **/
	bool m_bTerminar;

    /** Variables para calcular frame rate **/
	int m_iFPSActual;
    int m_iTicksActual;
    int m_iTicksPerdidos;

	/** Variables para mantener el frame rate **/
	const int m_iTicksNecesarios;
    int m_iTicksInicial;
    int m_iTicksFinal;
    int m_iTicksEmpleados;

    /** Código con el que acaba el programa -> 0 = Todo ha ido bien **/
    int m_iExitCode;

protected:
    /** Funciones de creación de la ventana **/
    void SetScreen( const int& iWidth, const int& iHeight );
	void SetPosition( const int& iX, const int& iY );
    /** Carga las imágenes, fuentes, etc. **/
    void CargarRecursos();

    /** Controla teclado y ratón **/
    void Teclas( const int& iTecla );
	void MovimientoRaton( const int& iX, const int& iY );
	void PulsacionRaton( const int& iBoton, const int& iX, const int& iY );
    /** Pausa o reanuda el juego al minimizar o maximizar **/
	void VentanaInactiva();
	void VentanaActiva();

    /** Funciones auxiliares **/
    void SetIcon();
    void SetTitle( const std::string& Titulo );
	/** Control del framerate **/
	void ControlFPS();

    /** Libera los recursos utilizados **/
	void Terminar();

public:
    /** Constructor y destructor de la clase **/
    CApp();
    ~CApp();

    /** Carga del programa **/
    void Cargar();
    /** Función auxiliar para cargar muchas imágenes **/
    void CargarImagenes( std::vector<SDL_Surface*>& Superficie, std::vector<std::string> Ruta );

    /** Comienzo de la ejecución **/
	void Comenzar();

    /** Renderizado **/
	void Renderizar();
	/** Proceso de entrada **/
	void LeerEntrada();

    /** Funciones auxiliares **/
    void SetCurrentScreen( const int& iScreen );
	void SetQuitFlag();
	int GetRandom();
	std::string IntToString( const int& i );

	/** Manejo de errores **/
	void Advertencia( const std::string& Mensaje );
	void Error( const std::string& Mensaje );
	/** Devuelve el código con el que terminará el programa **/
	int GetExitCode();
} Juego;

#endif // MAIN_H_
