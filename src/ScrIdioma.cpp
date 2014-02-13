#include "ObjPanel.h"
#include "ObjRuleta.h"
#include "ScrIdioma.h"

void CIdioma::Cargar()
{
    m_rDestBoton.x = 250;
    m_rDestBoton.y = 0;
    m_rDestBoton.w = 300;
    m_rDestBoton.h = 60;
    m_iResalte = 0;

    std::vector<std::string> vRutas(2);
    vRutas[0] = "data/img/idioma/background.png";
    vRutas[1] = "data/img/idioma/boton.png";
    m_vSup.resize(2);
    Juego.CargarImagenes( m_vSup, vRutas );
}

void CIdioma::Renderizar( SDL_Surface* pDestSurface )
{
    SDL_BlitSurface( m_vSup[0], NULL, pDestSurface, NULL );
    if( m_iResalte == 1 )
        SDL_BlitSurface( m_vSup[1], NULL, pDestSurface, &m_rDestBoton );
    else if( m_iResalte == 2 )
        SDL_BlitSurface( m_vSup[1], NULL, pDestSurface, &m_rDestBoton );
    else if( m_iResalte == 3 )
        SDL_BlitSurface( m_vSup[1], NULL, pDestSurface, &m_rDestBoton );
    FEras.EscribirCentrado( pDestSurface, "English", 350, 1 );
    FEras.EscribirCentrado( pDestSurface, "Espa\xF1ol", 430, 1 );
    FEras.EscribirCentrado( pDestSurface, "Euskara", 510, 1 );
}

void CIdioma::TeclaPulsada( const int& iTecla )
{
    if( iTecla == SDLK_ESCAPE ) {
        Juego.SetQuitFlag();
    } else if( iTecla == SDLK_1 || iTecla == SDLK_2 || iTecla == SDLK_3 ) {
        if( iTecla == SDLK_1 )
            Traduccion.Load("en");
        else if( iTecla == SDLK_2 )
            Traduccion.Load("es");
        else if( iTecla == SDLK_3 )
            Traduccion.Load("eu");
        Panel.CargarPaneles();
        Ruleta.CargarTraducciones();
        Juego.SetCurrentScreen(1);
    }
}

void CIdioma::MouseMovido( const int& iX, const int& iY )
{
    if( iX >= 250 && iX <= 550 ) {
        if( iY >= 340 && iY <= 400 ) {
            m_rDestBoton.y = 340;
            m_iResalte = 1;
        } else if( iY >= 420 && iY <= 480 ) {
            m_rDestBoton.y = 420;
            m_iResalte = 2;
        } else if( iY >= 500 && iY <= 560 ) {
            m_rDestBoton.y = 500;
            m_iResalte = 3;
        } else {
            m_iResalte = 0;
        }
    }
    else
    {
        m_iResalte = 0;
    }
}

void CIdioma::MousePulsado( const int& iX, const int& iY )
{
    if( m_iResalte != 0 ) {
        if( m_iResalte == 1 )
            Traduccion.Load("en");
        else if( m_iResalte == 2 )
            Traduccion.Load("es");
        else if( m_iResalte == 3 )
            Traduccion.Load("eu");
        Panel.CargarPaneles();
        Ruleta.CargarTraducciones();
        Juego.SetCurrentScreen(1);
    }
}

void CIdioma::Limpiar()
{
    SDL_FreeSurface( m_vSup[0] );
    SDL_FreeSurface( m_vSup[1] );
}
