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

#include "Lenguaje.h"

void CLenguaje::Load( const std::string& szLang )
{
    // Almacena el ID del idioma cargado
    m_szIdioma = szLang;
    // Carga el archivo de traducción e inserta las cadenas en el map
    std::string Ruta = "./data/lang/" + szLang + "_interface.txt";
    std::fstream File( Ruta.c_str(), std::fstream::in );
    if( File.is_open() ) {
        int Count = 0;
        while( !File.eof() && Count < LANG_ENTRADAS ) {
            getline( File, m_szIDs[Count] );
            getline( File, m_szTraducciones[Count] );
            File.ignore( 2, '\n' );
            m_dEntradas[m_szIDs[Count]] = m_szTraducciones[Count];
            Count++;
        }

        if( Count != LANG_ENTRADAS )
            Juego.Error( "El archivo de idioma \"" + szLang + "_interface.txt\" no es correcto." );

        File.close();
    } else {
        Juego.Error( "No se pudo abrir el archivo de idioma \"" + Ruta + "\"." );
    }
}

std::string CLenguaje::String( const std::string& ID )
{
    // Devuelve la traduccion correspondiente al identificador
    if( m_dEntradas.count( ID ) == 0 )
    {
        Juego.Error( "El archivo de idioma no posee el contenido necesario." );
        return "";
    }
    else
    {
        return m_dEntradas[ID];
    }
}

std::string CLenguaje::GetLang()
{
    return m_szIdioma;
}
