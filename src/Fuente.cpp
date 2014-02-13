#include "Fuente.h"

void CFuente::Escanear( const std::string& szPath, int iPixelSombreado, Uint8 R, Uint8 G, Uint8 B, Uint8 A )
{
    // Inicializa las variables
    for( int i = 0; i < MAX_LETRAS; i++ )
    {
        m_iInicioLetras[i] = 0;
        m_iFinalLetras[i] = 0;
    }

    Uint32 pixel;
    Uint8 r = 0, g = 0, b = 0, a = 0;
    int x = 0, y = 0, i = 1, BuscamosFinalLetra = 0;

    // Carga la imagen
    SDL_Surface* TempImagen = IMG_Load( szPath.c_str() );
    if( TempImagen == NULL )
    {
         Juego.Error( IMG_GetError() );
    }
    else
    {
        m_sImagen = SDL_DisplayFormatAlpha( TempImagen );
        SDL_FreeSurface( TempImagen );
        SDL_LockSurface( m_sImagen );

        // Determina el principio y el fin de cada letra
        while( x < m_sImagen->w )
        {
            while( y < m_sImagen->h )
            {
                pixel = ObtenerPixel( m_sImagen, x, y );
                SDL_GetRGBA( pixel, m_sImagen->format, &r, &g, &b, &a );
                if( r == R && g == G && b == B && a == A )
                {
                    if( BuscamosFinalLetra != 1 )
                    {
                        m_iInicioLetras[i] = x - iPixelSombreado;
                        BuscamosFinalLetra = 1;
                    }
                    y = m_sImagen->h;
                }
                else
                {
                    if( y == (m_sImagen->h)-1 && BuscamosFinalLetra == 1 )
                    {
                        m_iFinalLetras[i] = x + iPixelSombreado;
                        BuscamosFinalLetra = 0;
                        i++;
                    }
                }
                y++;
            }
            x++;
            y = 0;
        }

        if( m_iInicioLetras[1] == 0 )
        {
            // Si no se han detectado letras
            Juego.Error( "No se han podido leer las letras de la fuente \"" + szPath + "\". Compruebe el par\xE1metro color RGBA." );
        }
        else
        {
            // Establece el final del espacio en blanco
            m_iFinalLetras[0] = m_iInicioLetras[1] - 1;
        }

        SDL_UnlockSurface( m_sImagen );
    }
}

Uint32 CFuente::ObtenerPixel(SDL_Surface *pSurface, Sint32 X, Sint32 Y)
{
    Uint32 Bpp = pSurface->format->BytesPerPixel;
    Uint8 *bits = ((Uint8 *)pSurface->pixels)+Y*pSurface->pitch+X*Bpp;
    return *(Uint32 *)bits;
}

void CFuente::Escribir( SDL_Surface* pDestSurface, const std::string& szTexto, int X, int Y, int Gap )
{
    if( szTexto == "" )
    {
        Juego.Error( "Intento de escritura sin texto especificado." );
    }
    else
    {
        SDL_Rect Orig = { 0, 1, 0, m_sImagen->h };
        SDL_Rect Dest = { X, Y, 0, 0 };

        for( int i = 0; szTexto[i] != 0; i++ )
        {
            if( szTexto[i] >= 32 && szTexto[i] <= 126 )
            {
                // Caracter ASCII
                Orig.x = m_iInicioLetras[szTexto[i]-32];
                Orig.w = m_iFinalLetras[szTexto[i]-32] - Orig.x;
            }
            else
            {
                // Otros ASCII extendido
                switch( szTexto[i] )
                {

                case '\xBF': // ¿
                    Orig.x = m_iInicioLetras[95];
                    Orig.w = m_iFinalLetras[95] - Orig.x;
                  break;
                case '\xA1': // ¡
                    Orig.x = m_iInicioLetras[96];
                    Orig.w = m_iFinalLetras[96] - Orig.x;
                  break;

                case '\xC1': // Á
                    Orig.x = m_iInicioLetras[97];
                    Orig.w = m_iFinalLetras[97] - Orig.x;
                  break;
                case '\xC9': // É
                    Orig.x = m_iInicioLetras[98];
                    Orig.w = m_iFinalLetras[98] - Orig.x;
                  break;
                case '\xCD': // Í
                    Orig.x = m_iInicioLetras[99];
                    Orig.w = m_iFinalLetras[99] - Orig.x;
                  break;
                case '\xD3': // Ó
                    Orig.x = m_iInicioLetras[100];
                    Orig.w = m_iFinalLetras[100] - Orig.x;
                  break;
                case '\xDA': // Ú
                    Orig.x = m_iInicioLetras[101];
                    Orig.w = m_iFinalLetras[101] - Orig.x;
                  break;

                case '\xE1': // á
                    Orig.x = m_iInicioLetras[102];
                    Orig.w = m_iFinalLetras[102] - Orig.x;
                  break;
                case '\xE9': // é
                    Orig.x = m_iInicioLetras[103];
                    Orig.w = m_iFinalLetras[103] - Orig.x;
                  break;
                case '\xED': // í
                    Orig.x = m_iInicioLetras[104];
                    Orig.w = m_iFinalLetras[104] - Orig.x;
                  break;
                case '\xF3': // ó
                    Orig.x = m_iInicioLetras[105];
                    Orig.w = m_iFinalLetras[105] - Orig.x;
                  break;
                case '\xFA': // ú
                    Orig.x = m_iInicioLetras[106];
                    Orig.w = m_iFinalLetras[106] - Orig.x;
                  break;

                case '\xD1': // Ñ
                    Orig.x = m_iInicioLetras[107];
                    Orig.w = m_iFinalLetras[107] - Orig.x;
                  break;
                case '\xF1': // ñ
                    Orig.x = m_iInicioLetras[108];
                    Orig.w = m_iFinalLetras[108] - Orig.x;
                  break;

                case '\xA3': // Sol (GBP)
                    Orig.x = m_iInicioLetras[109];
                    Orig.w = m_iFinalLetras[109] - Orig.x;
                  break;

                default:
                    Orig.x = 0;
                    Orig.w = 0;
                  break;
                }
            }

            SDL_BlitSurface( m_sImagen, &Orig, pDestSurface, &Dest );
            Dest.x += Orig.w + Gap;
        }
    }
}

void CFuente::EscribirCentrado( SDL_Surface* pDestSurface, const std::string& szTexto, int Y, int Gap )
{
    if( szTexto == "" )
    {
        Juego.Error( "Intento de escritura sin texto especificado." );
    }
    else
    {
        int iFinalX = 0, iAncho = 0;
        iAncho = AnchoTexto( szTexto, Gap );
        iFinalX = ( pDestSurface->w / 2 ) - ( iAncho / 2 );

        Escribir( pDestSurface, szTexto, iFinalX, Y, Gap );
    }
}

void CFuente::EscribirCentradoRelativo( SDL_Surface* pDestSurface, const std::string& szTexto, int X, int Y, int Gap )
{
    if( szTexto == "" )
    {
        Juego.Error( "Intento de escritura sin texto especificado." );
    }
    else
    {
        int iFinalX = 0, iAncho = 0;
        iAncho = AnchoTexto( szTexto, Gap );
        iFinalX = X - ( iAncho / 2 );

        Escribir( pDestSurface, szTexto, iFinalX, Y, Gap );
    }
}

int CFuente::AnchoTexto( const std::string& szTexto, int Gap )
{
    int Width = 0;

    for( int i = 0; szTexto[i] != 0; i++ )
    {
        if( szTexto[i] >= 32 && szTexto[i] <= 126 )
        {
            // Caracter ASCII
            Width += m_iFinalLetras[szTexto[i]-32] - m_iInicioLetras[szTexto[i]-32] + Gap;
        }
        else
        {
            // Otros no-ASCII
            switch( szTexto[i] )
            {

            case '\xBF': // ¿
                Width += m_iFinalLetras[95] - m_iInicioLetras[95] + Gap;
              break;
            case '\xA1': // ¡
                Width += m_iFinalLetras[96] - m_iInicioLetras[96] + Gap;
              break;

            case '\xC1': // Á
                Width += m_iFinalLetras[97] - m_iInicioLetras[97] + Gap;
              break;
            case '\xC9': // É
                Width += m_iFinalLetras[98] - m_iInicioLetras[98] + Gap;
              break;
            case '\xCD': // Í
                Width += m_iFinalLetras[99] - m_iInicioLetras[99] + Gap;
              break;
            case '\xD3': // Ó
                Width += m_iFinalLetras[100] - m_iInicioLetras[100] + Gap;
              break;
            case '\xDA': // Ú
                Width += m_iFinalLetras[101] - m_iInicioLetras[101] + Gap;
              break;

            case '\xE1': // á
                Width += m_iFinalLetras[102] - m_iInicioLetras[102] + Gap;
              break;
            case '\xE9': // é
                Width += m_iFinalLetras[103] - m_iInicioLetras[103] + Gap;
              break;
            case '\xED': // í
                Width += m_iFinalLetras[104] - m_iInicioLetras[104] + Gap;
              break;
            case '\xF3': // ó
                Width += m_iFinalLetras[105] - m_iInicioLetras[105] + Gap;
              break;
            case '\xFA': // ú
                Width += m_iFinalLetras[106] - m_iInicioLetras[106] + Gap;
              break;

            case '\xD1': // Ñ
                Width += m_iFinalLetras[107] - m_iInicioLetras[107] + Gap;
              break;
            case '\xF1': // ñ
                Width += m_iFinalLetras[108] - m_iInicioLetras[108] + Gap;
              break;

            case '\xA3': // Sol
                Width += m_iFinalLetras[109] - m_iInicioLetras[109] + Gap;
              break;

            default:
                Width += 0;
              break;
            }
        }
    }

    return Width;
}

void CFuente::Terminar()
{
    SDL_FreeSurface( m_sImagen );
}
