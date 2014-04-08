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

#include "ObjBotones.h"
#include "ObjContador.h"
#include "ObjPanel.h"
#include "ObjRuleta.h"
#include "ScrJugar.h"
#include "ScrRecuento.h"

void CJugar::Cargar()
{
    // Carga el fondo
    SDL_Surface* Temp = IMG_Load( "data/img/jugar/fondo.png" );
    if( Temp != NULL ) {
        m_pFondo = SDL_DisplayFormatAlpha( Temp );
        SDL_FreeSurface( Temp );
    } else {
        Juego.Error( IMG_GetError() );
    }

    // Carga los objetos
    Botones.Cargar();
    Panel.Cargar();
    Ruleta.Cargar();
}

void CJugar::NuevaPartida()
{
    m_iEstado = 0;
    m_bSalir = false;
    Panel.NuevoPanel();
    Ruleta.NuevaPartida();
    Contador.Comenzar();
    m_szInfo = " ";
}

void CJugar::Renderizar( SDL_Surface* pDestSurface )
{
    SDL_BlitSurface( m_pFondo, NULL, pDestSurface, NULL );
    Botones.Renderizar( pDestSurface );
    if( m_bSalir )
        FEras.EscribirCentrado( pDestSurface, Traduccion.String( "STATUS_SEGURO" ), 150, 1 );
    else
        Panel.Renderizar( pDestSurface );
    FBerlin.EscribirCentradoRelativo( pDestSurface, m_szInfo, 450, 570, 0 );
    Ruleta.Renderizar( pDestSurface );
    Contador.Renderizar( pDestSurface );
}

void CJugar::TeclaPulsada( const int& iTecla )
{
    m_szInfo = " ";
    switch ( iTecla )
    {
    case SDLK_a:
        LetraPulsada('A');
      break;
    case SDLK_b:
        LetraPulsada('B');
      break;
    case SDLK_c:
        LetraPulsada('C');
      break;
    case SDLK_d:
        LetraPulsada('D');
      break;
    case SDLK_e:
        LetraPulsada('E');
      break;
    case SDLK_f:
        LetraPulsada('F');
      break;
    case SDLK_g:
        LetraPulsada('G');
      break;
    case SDLK_h:
        LetraPulsada('H');
      break;
    case SDLK_i:
        LetraPulsada('I');
      break;
    case SDLK_j:
        LetraPulsada('J');
      break;
    case SDLK_k:
        LetraPulsada('K');
      break;
    case SDLK_l:
        LetraPulsada('L');
      break;
    case SDLK_m:
        LetraPulsada('M');
      break;
    case SDLK_n:
        LetraPulsada('N');
      break;
    case SDLK_SEMICOLON:
        LetraPulsada('\xD1');
      break;
    case SDLK_o:
        LetraPulsada('O');
      break;
    case SDLK_p:
        LetraPulsada('P');
      break;
    case SDLK_q:
        LetraPulsada('Q');
      break;
    case SDLK_r:
        LetraPulsada('R');
      break;
    case SDLK_s:
        LetraPulsada('S');
      break;
    case SDLK_t:
        LetraPulsada('T');
      break;
    case SDLK_u:
        LetraPulsada('U');
      break;
    case SDLK_v:
        LetraPulsada('V');
      break;
    case SDLK_w:
        LetraPulsada('W');
      break;
    case SDLK_x:
        LetraPulsada('X');
      break;
    case SDLK_y:
        LetraPulsada('Y');
      break;
    case SDLK_z:
        LetraPulsada('Z');
      break;
    case SDLK_1:
        // PRIMER BOTÓN
        if( m_iEstado == 0 )
        {
            // Sólo en modo normal
            if( Panel.ComprobarResuelto() ) {
                // Si ya está resuelto
                m_szInfo = Traduccion.String( "STATUS_DEBE_RESOLVER" );
            } else if( !Ruleta.TiradaRealizada() ) {
                // Si la ruleta no ha sido tirada: tirar
                Contador.Detener();
                Ruleta.Tirar();
                Contador.Comenzar();
            } else {
                // Si ya ha tirado: escoger consonante
                m_szInfo = Traduccion.String( "STATUS_ESCOGE_CONSONANTE" );
            }
        }
      break;
    case SDLK_2:
        // SEGUNDO BOTÓN
        if( m_bSalir )
        {
            // En modo salir: Avanzar al recuento
            Contador.Detener();
            Recuento.ObtenerDatos();
            Juego.SetCurrentScreen(3);
        }
        else if( m_iEstado == 0 && ( !Panel.ComprobarLetra('A') || !Panel.ComprobarLetra('E') || !Panel.ComprobarLetra('I') || !Panel.ComprobarLetra('O') || !Panel.ComprobarLetra('U') ) )
        {
            // En modo normal y con vocales sin comprar
            if( Panel.ComprobarResuelto() ) // Si ya está resuelto
                m_szInfo = Traduccion.String( "STATUS_DEBE_RESOLVER" );
            else if( Ruleta.TiradaRealizada() ) // Mensaje: Has tirado de la ruleta, debe escoger una consonante
                m_szInfo = Traduccion.String( "STATUS_ESCOGE_CONSONANTE" );
            else if( Ruleta.GetDinero() < JUG_VOCAL ) // Mensaje: no tienes suficiente dinero
                m_szInfo = Traduccion.String( "STATUS_DINERO_INSUFICIENTE" );
            else // Entrar en modo "Comprar vocal"
            {
                Contador.Comenzar();
                m_iEstado = 1;
            }
        }
      break;
    case SDLK_3:
        // TERCER BOTÓN
        if( m_bSalir )
        {
            // En modo salir: reactivar el contador y no salir
            Contador.Pausar( false );
            m_bSalir = false;
        }
        else if( m_iEstado == 1 )
        {
            // En modo "comprar vocal": cancelar
            m_iEstado = 0;
        }
        else if( m_iEstado == 2 || m_iEstado == 3 )
        {
            // En modo resolver o resuelto: reiniciar o volver a jugar, misma acción
            NuevaPartida();
        }
        else if( m_iEstado == 0 )
        {
            // En modo normal
            if( Panel.ComprobarResuelto() ) {
                // Si ya está resuelto
                Contador.Detener();
                Ruleta.ReproducirSonido( 4 );
                Ruleta.SetGajo( 41 );
                Ruleta.Penalizar( false );
                Ruleta.SumarPanelDinero();
                m_iEstado = 3;
                m_szInfo = Traduccion.String( "STATUS_CONGRATS" );
            } else if( Ruleta.TiradaRealizada() ) {
                // Si ha tirado: mensaje: primero escoge consonante
                m_szInfo = Traduccion.String( "STATUS_ESCOGE_CONSONANTE" );
            } else {
                // Si no ha tirado: entrar en modo "resolver"
                Contador.Detener();
                Ruleta.SetGajo( 40 );
                m_iEstado = 2;
            }
        }
      break;
    case SDLK_4:
    case SDLK_ESCAPE:
        // CUARTO BOTÓN
        // Si no estamos en modo salir: entrar en modo salir
        if( !m_bSalir )
        {
            Contador.Pausar( true );
            m_bSalir = true;
        }
      break;
    }
}

void CJugar::MouseMovido( const int& iX, const int& iY )
{
    Botones.MouseMovido( iX, iY );
}

void CJugar::MousePulsado( const int& iX, const int& iY )
{
    int iResalte = Botones.GetResaltado();
    m_szInfo = " ";
    // LETRAS
    if( iResalte == 1 ) {
        LetraPulsada('A');
    } else if( iResalte == 2 ) {
        LetraPulsada('B');
    } else if( iResalte == 3 ) {
        LetraPulsada('C');
    } else if( iResalte == 4 ) {
        LetraPulsada('D');
    } else if( iResalte == 5 ) {
        LetraPulsada('E');
    } else if( iResalte == 6 ) {
        LetraPulsada('F');
    } else if( iResalte == 7 ) {
        LetraPulsada('G');
    } else if( iResalte == 8 ) {
        LetraPulsada('H');
    } else if( iResalte == 9 ) {
        LetraPulsada('I');
    } else if( iResalte == 10 ) {
        LetraPulsada('J');
    } else if( iResalte == 11 ) {
        LetraPulsada('K');
    } else if( iResalte == 12 ) {
        LetraPulsada('L');
    } else if( iResalte == 13 ) {
        LetraPulsada('M');
    } else if( iResalte == 14 ) {
        LetraPulsada('N');
    } else if( iResalte == 15 ) {
        LetraPulsada('\xD1');
    } else if( iResalte == 16 ) {
        LetraPulsada('O');
    } else if( iResalte == 17 ) {
        LetraPulsada('P');
    } else if( iResalte == 18 ) {
        LetraPulsada('Q');
    } else if( iResalte == 19 ) {
        LetraPulsada('R');
    } else if( iResalte == 20 ) {
        LetraPulsada('S');
    } else if( iResalte == 21 ) {
        LetraPulsada('T');
    } else if( iResalte == 22 ) {
        LetraPulsada('U');
    } else if( iResalte == 23 ) {
        LetraPulsada('V');
    } else if( iResalte == 24 ) {
        LetraPulsada('W');
    } else if( iResalte == 25 ) {
        LetraPulsada('X');
    } else if( iResalte == 26 ) {
        LetraPulsada('Y');
    } else if( iResalte == 27 ) {
        LetraPulsada('Z');
    } else if( iResalte == 28 ) {
        // PRIMER BOTÓN
        if( m_iEstado == 0 )
        {
            // Sólo en modo normal
            if( Panel.ComprobarResuelto() ) {
                // Si ya está resuelto
                m_szInfo = Traduccion.String( "STATUS_DEBE_RESOLVER" );
            } else if( !Ruleta.TiradaRealizada() ) {
                // Si la ruleta no ha sido tirada: tirar
                Contador.Detener();
                Ruleta.Tirar();
                Contador.Comenzar();
            } else {
                // Si ya ha tirado: escoger consonante
                m_szInfo = Traduccion.String( "STATUS_ESCOGE_CONSONANTE" );
            }
        }
    } else if( iResalte == 29 ) {
        // SEGUNDO BOTÓN
        if( m_bSalir )
        {
            // En modo salir: Avanzar al recuento
            Contador.Detener();
            Recuento.ObtenerDatos();
            Juego.SetCurrentScreen(3);
        }
        else if( m_iEstado == 0 && ( !Panel.ComprobarLetra('A') || !Panel.ComprobarLetra('E') || !Panel.ComprobarLetra('I') || !Panel.ComprobarLetra('O') || !Panel.ComprobarLetra('U') ) )
        {
            // En modo normal y con vocales sin comprar
            if( Panel.ComprobarResuelto() ) // Si ya está resuelto
                m_szInfo = Traduccion.String( "STATUS_DEBE_RESOLVER" );
            else if( Ruleta.TiradaRealizada() ) // Mensaje: Has tirado de la ruleta, debe escoger una consonante
                m_szInfo = Traduccion.String( "STATUS_ESCOGE_CONSONANTE" );
            else if( Ruleta.GetDinero() < JUG_VOCAL ) // Mensaje: no tienes suficiente dinero
                m_szInfo = Traduccion.String( "STATUS_DINERO_INSUFICIENTE" );
            else  // Entrar en modo "Comprar vocal"
            {
                Contador.Comenzar();
                m_iEstado = 1;
            }
        }
    } else if( iResalte == 30 ) {
        // TERCER BOTÓN
        if( m_bSalir )
        {
            // En modo salir: reactivar el contador y no salir
            Contador.Pausar( false );
            m_bSalir = false;
        }
        else if( m_iEstado == 1 )
        {
            // En modo "comprar vocal": cancelar
            m_iEstado = 0;
        }
        else if( m_iEstado == 2 || m_iEstado == 3 )
        {
            // En modo resolver o resuelto: reiniciar o volver a jugar, misma acción
            NuevaPartida();
        }
        else if( m_iEstado == 0 )
        {
            // En modo normal
            if( Panel.ComprobarResuelto() ) {
                // Si ya está resuelto
                Contador.Detener();
                Ruleta.ReproducirSonido( 4 );
                Ruleta.SetGajo( 41 );
                Ruleta.Penalizar( false );
                Ruleta.SumarPanelDinero();
                m_iEstado = 3;
                m_szInfo = Traduccion.String( "STATUS_CONGRATS" );
            } else if( Ruleta.TiradaRealizada() ) {
                // Si ha tirado: mensaje: primero escoge consonante
                m_szInfo = Traduccion.String( "STATUS_ESCOGE_CONSONANTE" );
            } else {
                // Si no ha tirado: entrar en modo "resolver"
                Contador.Detener();
                Ruleta.SetGajo( 40 );
                m_iEstado = 2;
            }
        }
    } else if( iResalte == 31 ) {
        // CUARTO BOTÓN
        // Si no estamos en modo salir: entrar en modo salir
        if( !m_bSalir )
        {
            Contador.Pausar( true );
            m_bSalir = true;
        }
    }
}

void CJugar::LetraPulsada( const char& ID )
{
    if( !m_bSalir ) {
        // En modo normal
        if( m_iEstado == 0 )
        {
            // Si se trata de una vocal
            if( ID == 'A' || ID == 'E' || ID == 'I' || ID == 'O' || ID == 'U' )
            {
                // Si la ruleta ha sido tirada, debe escoger la consonante
                if( Ruleta.TiradaRealizada() )
                    m_szInfo = Traduccion.String( "STATUS_ESCOGE_CONSONANTE" );
                // De lo contrario, debe pulsar en comprar vocal
                else
                    m_szInfo = Traduccion.String( "STATUS_DEBE_COMPRAR" );
            }
            // Si se trata de una consonante
            else
            {
                // Si la ruleta ha sido tirada y la consonante no estaba comprada
                if( Ruleta.TiradaRealizada() && !Panel.ComprobarLetra(ID) )
                {
                    Panel.MarcarLetra(ID);
                    SInt Apariciones = Panel.BuscarLetra(ID);
                    // Si la consonante está en el panel
                    if( Apariciones > 0 )
                    {
                        Ruleta.ReproducirSonido( 2 );
                        Ruleta.SumarDinero( Apariciones );
                        m_szInfo = " ";
                    }
                    // Si la consonante no está en el panel
                    else
                    {
                        Ruleta.ReproducirSonido( 1 );
                        Ruleta.PasarTurno();
                        m_szInfo = Traduccion.String( "STATUS_CONSONANTE_ERRONEA" );
                    }
                    Ruleta.EsperarTirada();
                    Contador.Comenzar();
                }
                // Si aún no ha tirado
                else if( !Ruleta.TiradaRealizada() )
                {
                    m_szInfo = Traduccion.String( "STATUS_PRIMERO_TIRA" );
                }
            }
        }
        // En modo "comprar vocal"
        else if( m_iEstado == 1 )
        {
            // Si se trata de una vocal
            if( ID == 'A' || ID == 'E' || ID == 'I' || ID == 'O' || ID == 'U' )
            {
                // Si no estaba comprada
                if( !Panel.ComprobarLetra(ID) )
                {
                    Panel.MarcarLetra(ID);
                    Ruleta.RestarDinero( JUG_VOCAL );
                    if( !Panel.BuscarLetra(ID) )
                    {
                        // Si la vocal no está en el panel
                        Ruleta.ReproducirSonido( 1 );
                        Ruleta.PasarTurno();
                        m_szInfo = Traduccion.String( "STATUS_VOCAL_ERRONEA" );
                    }
                    else
                    {
                        // Si la vocal está en el panel
                        Ruleta.ReproducirSonido( 2 );
                        m_szInfo = " ";
                    }
                    m_iEstado = 0;
                    Contador.Comenzar();
                }
            }
            // Si se trata de una consonante
            else
            {
                m_szInfo = Traduccion.String( "STATUS_SELECCIONA_VOCAL" );
            }
        }
        // En modo "resolver"
        else if( m_iEstado == 2 )
        {
            // Si la consonante no estaba comprada
            if( !Panel.ComprobarLetra(ID) )
            {
                Panel.MarcarLetra(ID);
                // Si la consonante no está en el panel
                if( !Panel.BuscarLetra(ID) )
                {
                    Panel.MarcarTodo();
                    Ruleta.ReproducirSonido( 3 );
                    Ruleta.SetGajo( 42 );
                    Ruleta.Penalizar( true );
                    m_iEstado = 3;
                    if( Ruleta.GetJugadores() > 1 )
                        m_szInfo = Traduccion.String( "STATUS_EQUIVOCADO" );
                    else
                        m_szInfo = Traduccion.String( "STATUS_EQUIVOCADO_SOLO" );
                }
                else if( Panel.ComprobarResuelto() ) {
                    // Si era la última letra que faltaba: panel resuelto correctamente
                    Ruleta.ReproducirSonido( 4 );
                    Ruleta.SetGajo( 41 );
                    Ruleta.Penalizar( false );
                    Ruleta.SumarPanelDinero();
                    m_iEstado = 3;
                    m_szInfo = Traduccion.String( "STATUS_CONGRATS" );
                }
            }
        }
    }
}

void CJugar::TiempoAgotado()
{
    Contador.Comenzar();
    Ruleta.PasarTurno();
    Ruleta.EsperarTirada();
    m_iEstado = 0;
    m_szInfo = Traduccion.String( "STATUS_TIEMPO_AGOTADO" );
}

int CJugar::Estado()
{
    return m_iEstado;
}

bool CJugar::Salida()
{
    return m_bSalir;
}

void CJugar::Limpiar()
{
    // Libera la memoria utilizada
    SDL_FreeSurface( m_pFondo );
    Contador.Detener();
    Botones.Limpiar();
    Panel.Limpiar();
    Ruleta.Limpiar();
}
