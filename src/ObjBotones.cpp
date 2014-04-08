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
#include "ObjPanel.h"
#include "ScrJugar.h"

void CBotones::Cargar()
{
    // Inicializar las variables
    m_iBotonResaltado = 0;
    m_rDestLetras.x = 12;
    m_rDestLetras.y = 356;
    m_rDestLetras.w = 56;
    m_rDestLetras.h = 42;
    m_rDestBotones.x = 0;
    m_rDestBotones.y = 488;
    m_rDestBotones.w = 170;
    m_rDestBotones.h = 34;

    m_vCode.resize( 27 );
    m_vCode[0] = 'A'; m_vCode[1] = 'B'; m_vCode[2] = 'C'; m_vCode[3] = 'D'; m_vCode[4] = 'E'; m_vCode[5] = 'F'; m_vCode[6] = 'G'; m_vCode[7] = 'H'; m_vCode[8] = 'I';
    m_vCode[9] = 'J'; m_vCode[10] = 'K'; m_vCode[11] = 'L'; m_vCode[12] = 'M'; m_vCode[13] = 'N'; m_vCode[14] = '\xD1'; m_vCode[15] = 'O'; m_vCode[16] = 'P'; m_vCode[17] = 'Q';
    m_vCode[18] = 'R'; m_vCode[19] = 'S'; m_vCode[20] = 'T'; m_vCode[21] = 'U'; m_vCode[22] = 'V'; m_vCode[23] = 'W'; m_vCode[24] = 'X'; m_vCode[25] = 'Y'; m_vCode[26] = 'Z';
    // Cargar las imágenes de letras y botones
    m_vSup.resize( 83 );
    std::vector<std::string> vRutas( 83 );
    vRutas[0] = "data/img/jugar/disponible/a.png"; vRutas[1] = "data/img/jugar/disponible/b.png"; vRutas[2] =  "data/img/jugar/disponible/c.png"; vRutas[3] = "data/img/jugar/disponible/d.png"; vRutas[4] = "data/img/jugar/disponible/e.png";
    vRutas[5] = "data/img/jugar/disponible/f.png"; vRutas[6] = "data/img/jugar/disponible/g.png"; vRutas[7] = "data/img/jugar/disponible/h.png"; vRutas[8] = "data/img/jugar/disponible/i.png"; vRutas[9] = "data/img/jugar/disponible/j.png";
    vRutas[10] = "data/img/jugar/disponible/k.png"; vRutas[11] = "data/img/jugar/disponible/l.png"; vRutas[12] = "data/img/jugar/disponible/m.png"; vRutas[13] = "data/img/jugar/disponible/n.png"; vRutas[14] = "data/img/jugar/disponible/nn.png";
    vRutas[15] = "data/img/jugar/disponible/o.png"; vRutas[16] = "data/img/jugar/disponible/p.png"; vRutas[17] = "data/img/jugar/disponible/q.png"; vRutas[18] = "data/img/jugar/disponible/r.png"; vRutas[19] = "data/img/jugar/disponible/s.png";
    vRutas[20] = "data/img/jugar/disponible/t.png"; vRutas[21] = "data/img/jugar/disponible/u.png"; vRutas[22] = "data/img/jugar/disponible/v.png"; vRutas[23] = "data/img/jugar/disponible/w.png"; vRutas[24] = "data/img/jugar/disponible/x.png";
    vRutas[25] = "data/img/jugar/disponible/y.png"; vRutas[26] = "data/img/jugar/disponible/z.png"; vRutas[27] = "data/img/jugar/bloqueado/a.png"; vRutas[28] = "data/img/jugar/bloqueado/b.png"; vRutas[29] = "data/img/jugar/bloqueado/c.png";
    vRutas[30] = "data/img/jugar/bloqueado/d.png"; vRutas[31] = "data/img/jugar/bloqueado/e.png"; vRutas[32] = "data/img/jugar/bloqueado/f.png"; vRutas[33] = "data/img/jugar/bloqueado/g.png"; vRutas[34] = "data/img/jugar/bloqueado/h.png";
    vRutas[35] = "data/img/jugar/bloqueado/i.png"; vRutas[36] = "data/img/jugar/bloqueado/j.png"; vRutas[37] = "data/img/jugar/bloqueado/k.png"; vRutas[38] = "data/img/jugar/bloqueado/l.png"; vRutas[39] = "data/img/jugar/bloqueado/m.png";
    vRutas[40] = "data/img/jugar/bloqueado/n.png"; vRutas[41] = "data/img/jugar/bloqueado/nn.png"; vRutas[42] = "data/img/jugar/bloqueado/o.png"; vRutas[43] = "data/img/jugar/bloqueado/p.png"; vRutas[44] = "data/img/jugar/bloqueado/q.png";
    vRutas[45] = "data/img/jugar/bloqueado/r.png"; vRutas[46] = "data/img/jugar/bloqueado/s.png"; vRutas[47] = "data/img/jugar/bloqueado/t.png"; vRutas[48] = "data/img/jugar/bloqueado/u.png"; vRutas[49] = "data/img/jugar/bloqueado/v.png";
    vRutas[50] = "data/img/jugar/bloqueado/w.png"; vRutas[51] = "data/img/jugar/bloqueado/x.png"; vRutas[52] = "data/img/jugar/bloqueado/y.png"; vRutas[53] = "data/img/jugar/bloqueado/z.png"; vRutas[54] = "data/img/jugar/resaltado/a.png";
    vRutas[55] = "data/img/jugar/resaltado/b.png"; vRutas[56] = "data/img/jugar/resaltado/c.png"; vRutas[57] = "data/img/jugar/resaltado/d.png"; vRutas[58] = "data/img/jugar/resaltado/e.png"; vRutas[59] = "data/img/jugar/resaltado/f.png";
    vRutas[60] = "data/img/jugar/resaltado/g.png"; vRutas[61] = "data/img/jugar/resaltado/h.png"; vRutas[62] = "data/img/jugar/resaltado/i.png"; vRutas[63] = "data/img/jugar/resaltado/j.png"; vRutas[64] = "data/img/jugar/resaltado/k.png";
    vRutas[65] = "data/img/jugar/resaltado/l.png"; vRutas[66] = "data/img/jugar/resaltado/m.png"; vRutas[67] = "data/img/jugar/resaltado/n.png"; vRutas[68] = "data/img/jugar/resaltado/nn.png"; vRutas[69] = "data/img/jugar/resaltado/o.png";
    vRutas[70] = "data/img/jugar/resaltado/p.png"; vRutas[71] = "data/img/jugar/resaltado/q.png"; vRutas[72] = "data/img/jugar/resaltado/r.png"; vRutas[73] = "data/img/jugar/resaltado/s.png"; vRutas[74] = "data/img/jugar/resaltado/t.png";
    vRutas[75] = "data/img/jugar/resaltado/u.png"; vRutas[76] = "data/img/jugar/resaltado/v.png"; vRutas[77] = "data/img/jugar/resaltado/w.png"; vRutas[78] = "data/img/jugar/resaltado/x.png"; vRutas[79] = "data/img/jugar/resaltado/y.png";
    vRutas[80] = "data/img/jugar/resaltado/z.png"; vRutas[81] = "data/img/jugar/boton1.png"; vRutas[82] = "data/img/jugar/boton2.png";
    Juego.CargarImagenes( m_vSup, vRutas );
}

void CBotones::Renderizar( SDL_Surface* pDestSurface )
{
    /* MOSTRAR LAS LETRAS EN PANTALLA */
    m_rDestLetras.x = 12;
    m_rDestLetras.y = 356;

    for( int i = 0; i < 27; i++ )
    {
        if( i != 0 && i != 4 && i != 8 && i != 15 && i != 21 ) // CONSONANTES
        {
            // En modo "comprar vocal"
            if( Principal.Estado() == 1 )
            {
                SDL_BlitSurface( m_vSup[i+27], NULL , pDestSurface, &m_rDestLetras );
            }
            // En el resto de modos
            else
            {
                // Si la consonante no estaba comprada
                if( !Panel.ComprobarLetra( m_vCode[i] ) )
                {
                    if( m_iBotonResaltado-1 == i )
                        SDL_BlitSurface( m_vSup[i+54], NULL , pDestSurface, &m_rDestLetras );
                    else
                        SDL_BlitSurface( m_vSup[i], NULL , pDestSurface, &m_rDestLetras );
                }
                // Si la consonante estaba comprada
                else
                    SDL_BlitSurface( m_vSup[i+27], NULL , pDestSurface, &m_rDestLetras );
            }
        }
        else // VOCALES
        {
            // En modo "comprar vocal", "resolver" o "resuelto"
            if( Principal.Estado() == 1 || Principal.Estado() == 2 || Principal.Estado() == 3 )
            {
                // Si la vocal no está comprada
                if( !Panel.ComprobarLetra( m_vCode[i] ) )
                {
                    if( m_iBotonResaltado-1 == i )
                        SDL_BlitSurface( m_vSup[i+54], NULL , pDestSurface, &m_rDestLetras );
                    else
                        SDL_BlitSurface( m_vSup[i], NULL , pDestSurface, &m_rDestLetras );
                }
                // Si la vocal ya había sido comprada
                else
                    SDL_BlitSurface( m_vSup[i+27], NULL , pDestSurface, &m_rDestLetras );
            }
            // En modo normal
            else
            {
                SDL_BlitSurface( m_vSup[i+27], NULL , pDestSurface, &m_rDestLetras );
            }
        }
        // ESTABLECE LAS POSICIONES
        m_rDestLetras.x += 56;
        if( i == 8 || i == 17 )
        {
            m_rDestLetras.y += 42;
            m_rDestLetras.x = 12;
        }
    }

    /* MOSTRAR LOS BOTONES EN PANTALLA */
    if( Principal.Salida() )
    {
        // Después de haber hecho click en "Menú principal"
        BlitButton( pDestSurface, 2 );
        FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_SI" ), 301, BOT_YTEXTO, 0 );
        BlitButton( pDestSurface, 3 );
        FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_NO" ), 498, BOT_YTEXTO, 0 );
    }
    else if( Principal.Estado() == 3 )
    {
        // Si el panel está resuelto: jugar otra vez o menú principal
        BlitButton( pDestSurface, 3 );
        FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_JUGAR" ), 498, BOT_YTEXTO, 0 );
        BlitButton( pDestSurface, 4 );
        FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_SALIR" ), 695, BOT_YTEXTO, 0 );
    }
    else if( Principal.Estado() == 2 )
    {
        // En modo resolver: reiniciar o menú principal
        BlitButton( pDestSurface, 3 );
        FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_REINICIAR" ), 498, BOT_YTEXTO, 0 );
        BlitButton( pDestSurface, 4 );
        FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_SALIR" ), 695, BOT_YTEXTO, 0 );
    }
    else if( Principal.Estado() == 1 )
    {
        // En modo "comprar vocal": cancelar o menú principal
        BlitButton( pDestSurface, 3 );
        FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_CANCELAR" ), 498, BOT_YTEXTO, 0 );
        BlitButton( pDestSurface, 4 );
        FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_SALIR" ), 695, BOT_YTEXTO, 0 );
    }
    else
    {
        // En modo normal: tirar, comprar vocal o resolver
        if( Panel.ComprobarLetra('A') && Panel.ComprobarLetra('E') && Panel.ComprobarLetra('I') && Panel.ComprobarLetra('O') && Panel.ComprobarLetra('U') )
        {
            // Si todas las vocales están compradas
            BlitButton( pDestSurface, 1 );
            FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_TIRAR" ), 104, BOT_YTEXTO, 0 );
            BlitButton( pDestSurface, 3 );
            FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_RESOLVER" ), 498, BOT_YTEXTO, 0 );
            BlitButton( pDestSurface, 4 );
            FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_SALIR" ), 695, BOT_YTEXTO, 0 );
        }
        else
        {
            // Si hay vocales sin comprar
            BlitButton( pDestSurface, 1 );
            FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_TIRAR" ), 104, BOT_YTEXTO, 0 );
            BlitButton( pDestSurface, 2 );
            FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_COMPRAR" ), 301, BOT_YTEXTO, 0 );
            BlitButton( pDestSurface, 3 );
            FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_RESOLVER" ), 498, BOT_YTEXTO, 0 );
            BlitButton( pDestSurface, 4 );
            FCalibri.EscribirCentradoRelativo( pDestSurface, Traduccion.String( "PLAY_SALIR" ), 695, BOT_YTEXTO, 0 );
        }
    }

}

void CBotones::BlitButton( SDL_Surface* pDestSurface, const int& iBoton )
{
    if( iBoton == 1 )
        m_rDestBotones.x = 18;
    else if( iBoton == 2 )
        m_rDestBotones.x = 215;
    else if( iBoton == 3 )
        m_rDestBotones.x = 412;
    else if( iBoton == 4 )
        m_rDestBotones.x = 609;

    if( m_iBotonResaltado == iBoton+27 )
        SDL_BlitSurface( m_vSup[82], NULL, pDestSurface, &m_rDestBotones );
    else
        SDL_BlitSurface( m_vSup[81], NULL, pDestSurface, &m_rDestBotones );
}

void CBotones::MouseMovido( const int& iX, const int& iY )
{
    if( iY >= 356 && iY < 398 ) // 1ª línea
    {
        if( iX >= 12 && iX < 68 )
            m_iBotonResaltado = 1;
        else if( iX >= 68 && iX < 124 )
            m_iBotonResaltado = 2;
        else if( iX >= 124 && iX < 180 )
            m_iBotonResaltado = 3;
        else if( iX >= 180 && iX < 236 )
            m_iBotonResaltado = 4;
        else if( iX >= 236 && iX < 292 )
            m_iBotonResaltado = 5;
        else if( iX >= 292 && iX < 348 )
            m_iBotonResaltado = 6;
        else if( iX >= 348 && iX < 404 )
            m_iBotonResaltado = 7;
        else if( iX >= 404 && iX < 460 )
            m_iBotonResaltado = 8;
        else if( iX >= 460 && iX < 516 )
            m_iBotonResaltado = 9;
        else
            m_iBotonResaltado = 0;
    }
    else if( iY >= 398 && iY < 440 ) // 2ª línea
    {
        if( iX >= 12 && iX < 68 )
            m_iBotonResaltado = 10;
        else if( iX >= 68 && iX < 124 )
            m_iBotonResaltado = 11;
        else if( iX >= 124 && iX < 180 )
            m_iBotonResaltado = 12;
        else if( iX >= 180 && iX < 236 )
            m_iBotonResaltado = 13;
        else if( iX >= 236 && iX < 292 )
            m_iBotonResaltado = 14;
        else if( iX >= 292 && iX < 348 )
            m_iBotonResaltado = 15;
        else if( iX >= 348 && iX < 404 )
            m_iBotonResaltado = 16;
        else if( iX >= 404 && iX < 460 )
            m_iBotonResaltado = 17;
        else if( iX >= 460 && iX < 516 )
            m_iBotonResaltado = 18;
        else
            m_iBotonResaltado = 0;
    }
    else if( iY >= 440 && iY < 482 ) // 3ª línea
    {
        if( iX >= 12 && iX < 68 )
            m_iBotonResaltado = 19;
        else if( iX >= 68 && iX < 124 )
            m_iBotonResaltado = 20;
        else if( iX >= 124 && iX < 180 )
            m_iBotonResaltado = 21;
        else if( iX >= 180 && iX < 236 )
            m_iBotonResaltado = 22;
        else if( iX >= 236 && iX < 292 )
            m_iBotonResaltado = 23;
        else if( iX >= 292 && iX < 348 )
            m_iBotonResaltado = 24;
        else if( iX >= 348 && iX < 404 )
            m_iBotonResaltado = 25;
        else if( iX >= 404 && iX < 460 )
            m_iBotonResaltado = 26;
        else if( iX >= 460 && iX < 516 )
            m_iBotonResaltado = 27;
        else
             m_iBotonResaltado = 0;
    }
    else if( iY >= 488 && iY < 522 )
    {
        if( iX >= 18 && iX < 188 )
            m_iBotonResaltado = 28;
        else if( iX >= 215 && iX < 385 )
            m_iBotonResaltado = 29;
        else if( iX >= 412 && iX < 582 )
            m_iBotonResaltado = 30;
        else if( iX >= 609 && iX < 779 )
            m_iBotonResaltado = 31;
        else
            m_iBotonResaltado = 0;
    }
    else
    {
        m_iBotonResaltado = 0;
    }
}

int CBotones::GetResaltado()
{
    return m_iBotonResaltado;
}

void CBotones::Limpiar()
{
    for( int i = 0; i < 83; i++ )
        SDL_FreeSurface( m_vSup[i] );
}
