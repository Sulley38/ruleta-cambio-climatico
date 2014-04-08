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

#include "ObjPanel.h"

// Carácteres válidos para el panel
const std::string CPanel::m_szValidos = "0ABCDEFGHIJKLMN\xD1OPQRSTUVWXYZabcdefghijklmn\xF1opqrstuvwxyz\xE1\xE9\xED\xF3\xFA\xC1\xC9\xCD\xD3\xDA\xBF?\xA1!\xAD, ";

void CPanel::Cargar()
{
    // Inicializa las variables
    m_iPanelActual = 0;
    m_rDest.w = 0;
    m_rDest.h = 0;
    m_rOrig.w = 47;
    m_rOrig.h = 58;
    m_rDestMarco.x = 19;
    m_rDestMarco.y = 13;
    m_rDestMarco.w = 762;
    m_rDestMarco.h = 301;

    // Carga el mapa de caracteres
    m_vSup.resize(2);
    std::vector<std::string> vRutas(2);
    vRutas[0] = "data/font/casillaspanel.png";
    vRutas[1] = "data/img/jugar/marcopanel.png";
    Juego.CargarImagenes( m_vSup, vRutas );
}

void CPanel::CargarPaneles()
{
    // Selecciona y abre el archivo de los paneles
    std::string szRuta = "./data/lang/" + Traduccion.GetLang() + "_paneles.txt";
    std::fstream fArchivo( szRuta.c_str(), std::fstream::in );
    if( fArchivo.is_open() )
    {
        // Separa las pistas de los paneles y los guarda
        SInt iPaneles = 0;
        std::string szLinea;
        while( getline( fArchivo, szLinea ) && szLinea != "" )
        {
            m_vPaneles.push_back( szLinea.substr( 0, szLinea.find( ';' ) ) );
            szLinea = szLinea.substr( szLinea.find( ';' )+1 );
            m_vPistas.push_back( szLinea );
            if( szLinea.size() > 76 )
                Juego.Advertencia( "La pista \"" + szLinea + "\" es mayor de 76 caracteres." );
            iPaneles++;
        }

        // Cierra el archivo
        fArchivo.close();

        // Reserva la memoria para ciertas variables
        m_vPanelesJugados.resize( iPaneles );

        // Forma el panel centrado
        for( int i = 0; i < iPaneles; i++ )
        {
            std::string szPanel = m_vPaneles[i];
            SInt iLineas = 1;
            size_t iPos = szPanel.find( '/', 0 );

            // Comprueba cuántas líneas tiene el panel
            while( iPos != std::string::npos  ) {
                iPos = szPanel.find( '/', iPos+1 );
                iLineas++;
            }

            if( iLineas > 5 ) {
                Juego.Error( "El panel \"" + m_vPaneles[i] + "\" supera el n\xFAmero m\xE1ximo de l\xEDneas." );
            } else {
                // Establece los paneles en orden y centrados
                std::string szMontado;
                if( iLineas == 1 ) {
                    szMontado.append( 30, '0' );
                    szMontado += ComponerLinea( szPanel, i, "primera", 16 );
                    szMontado.append( 30, '0' );
                }
                else if( iLineas == 2 ) {
                    // Líneas 1 y 2
                    szMontado.append( 30, '0' );
                    szMontado += ComponerLinea( szPanel, i, "primera", 16 );
                    szMontado += ComponerLinea( szPanel, i, "segunda", 16 );
                    szMontado.append( 14, '0' );
                }
                else if( iLineas == 3 ) {
                    // Línea 1
                    szMontado.append( 14, '0' );
                    szMontado += ComponerLinea( szPanel, i, "primera", 16 );
                    szMontado += ComponerLinea( szPanel, i, "segunda", 16 );
                    szMontado += ComponerLinea( szPanel, i, "tercera", 16 );
                    szMontado.append( 14, '0' );
                }
                else if( iLineas == 4 ) {
                    szMontado.append( 14, '0' );
                    szMontado += ComponerLinea( szPanel, i, "primera", 16 );
                    szMontado += ComponerLinea( szPanel, i, "segunda", 16 );
                    szMontado += ComponerLinea( szPanel, i, "tercera", 16 );
                    szMontado += ComponerLinea( szPanel, i, "cuarta", 14 );
                }
                else if( iLineas == 5 ) {
                    szMontado += ComponerLinea( szPanel, i, "primera", 14 );
                    szMontado += ComponerLinea( szPanel, i, "segunda", 16 );
                    szMontado += ComponerLinea( szPanel, i, "tercera", 16 );
                    szMontado += ComponerLinea( szPanel, i, "cuarta", 16 );
                    szMontado += ComponerLinea( szPanel, i, "quinta", 14 );
                }

                if( szMontado.size() == PAN_CASILLAS )
                {
                    // Si todo va bien, convierte las minúsculas en mayúsculas
                    for( int j = 0; j < PAN_CASILLAS; j++ )
                    {
                        if( m_szValidos.find( szMontado[j] ) == std::string::npos ) {
                            Juego.Error( "El panel \"" + m_vPaneles[i] + "\" contiene un car" + '\xE1' + "cter irreconocible: " + szMontado[j] );
                        } else {
                            if( szMontado[j] == '\xE1' ) szMontado[j] = '\xC1';
                            else if( szMontado[j] == '\xE9' ) szMontado[j] = '\xC9';
                            else if( szMontado[j] == '\xED' ) szMontado[j] = '\xCD';
                            else if( szMontado[j] == '\xF3' ) szMontado[j] = '\xD3';
                            else if( szMontado[j] == '\xFA' ) szMontado[j] = '\xDA';
                            else if( szMontado[j] == '\xF1' ) szMontado[j] = '\xD1';
                            else if( szMontado[j] == ' ' ) szMontado[j] = '0';
                            else szMontado[j] = toupper( szMontado[j] );
                        }
                    }
                    // Asigna el panel definitivo
                    m_vPaneles[i] = szMontado;
                }
                else
                {
                    // Si algo no va bien y no lo sabíamos
                    Juego.Error( "El panel \"" + m_vPaneles[i] + "\" no encaja en las casillas del panel." );
                }
            }
        }
    }
    else
    {
        Juego.Error( "No se pudo abrir el archivo \"" + szRuta + "\"." );
    }
}

std::string CPanel::ComponerLinea( std::string& szData, const SInt& i, const std::string& szOrden, const SInt& iMax )
{
    std::string szRes = "";
    size_t iCasillas, iLongitud = szData.find( '/' );
    if( iLongitud == std::string::npos )
        iLongitud = szData.size();
    // Si el tamaño es correcto, rellena de ceros a la izquierda y a la derecha para que quede centrado
    if( iLongitud <= iMax ) {
        iCasillas = floor( iMax - iLongitud )/2;
        szRes.append( iCasillas, '0' );
        szRes.append( szData.substr( 0, iLongitud ) );
        szRes.append( iMax - iLongitud - iCasillas, '0' );
    } else {
        if( szOrden == "quinta" )
            Juego.Error( "La quinta l\xEDnea del panel \"" + m_vPaneles[i] + "\" es mayor de 14 caracteres. Considera reconstruir el panel completo." );
        else if( iMax == 14 )
            Juego.Error( "La " + szOrden + " l\xEDnea del panel \"" + m_vPaneles[i] + "\" es mayor de 14 caracteres. Considera dividirla con \"/\"." );
        else
            Juego.Error( "La " + szOrden + " l\xEDnea del panel \"" + m_vPaneles[i] + "\" es mayor de 16 caracteres. Considera dividirla con \"/\"." );
    }
    // Si no es la última línea, borra lo que ya se ha centrado
    if( iLongitud != szData.size() )
        szData.erase( 0, iLongitud+1 );
    return szRes;
}

void CPanel::NuevoPanel()
{
    // Resetea las letras compradas
    m_dCompradas.clear();

    // Comprueba que no todos los paneles hayan sido jugados.
    SInt Count = 0, iPaneles = m_vPanelesJugados.size();
    while( Count < iPaneles && m_vPanelesJugados[Count] ) Count++;
    if( Count == iPaneles )
    {
        // Vuelve a empezar con los paneles (poco probable que pase dada la cantidad de paneles)
        Count = 0;
        while( Count < iPaneles ) {
            m_vPanelesJugados[Count] = false;
            Count++;
        }
    }

    // Escoge un panel aleatoriamente.
    int Random = Juego.GetRandom() % iPaneles;
    // Comprueba que aún no se haya jugado y lo establece como actual.
    while( m_vPanelesJugados[Random] == true )
        Random = Juego.GetRandom() % iPaneles;
    m_vPanelesJugados[Random] = true;
    // Establece el número de panel y de pista para toda la clase.
    m_iPanelActual = Random;
}

void CPanel::Renderizar( SDL_Surface* pDestSurface )
{
    m_rDest.x = 71;
    m_rDest.y = 18;

    for( int i = 0; i < PAN_CASILLAS; i++ )
    {
        m_rOrig.x = 329;
        m_rOrig.y = 232;

        switch( m_vPaneles[m_iPanelActual][i] )
        {
        // EN BLANCO
        case '0':
            m_rOrig.x = 329;
            m_rOrig.y = 174;
          break;

        // CONSONANTES
        case 'B':
            if( m_dCompradas['B'] ) {
                m_rOrig.x = 47;
                m_rOrig.y = 0;
            }
          break;

        case 'C':
            if( m_dCompradas['C'] ) {
                m_rOrig.x = 94;
                m_rOrig.y = 0;
            }
          break;

        case 'D':
            if( m_dCompradas['D'] ) {
                m_rOrig.x = 141;
                m_rOrig.y = 0;
            }
          break;

        case 'F':
            if( m_dCompradas['F'] ) {
                m_rOrig.x = 235;
                m_rOrig.y = 0;
            }
          break;

        case 'G':
            if( m_dCompradas['G'] ) {
                m_rOrig.x = 282;
                m_rOrig.y = 0;
            }
          break;

        case 'H':
            if( m_dCompradas['H'] ) {
                m_rOrig.x = 329;
                m_rOrig.y = 0;
            }
          break;

        case 'J':
            if( m_dCompradas['J'] ) {
                m_rOrig.x = 47;
                m_rOrig.y = 58;
            }
          break;

        case 'K':
            if( m_dCompradas['K'] ) {
                m_rOrig.x = 94;
                m_rOrig.y = 58;
            }
          break;

        case 'L':
            if( m_dCompradas['L'] ) {
                m_rOrig.x = 141;
                m_rOrig.y = 58;
            }
          break;

        case 'M':
            if( m_dCompradas['M'] ) {
                m_rOrig.x = 188;
                m_rOrig.y = 58;
            }
          break;

        case 'N':
            if( m_dCompradas['N'] ) {
                m_rOrig.x = 235;
                m_rOrig.y = 58;
            }
          break;

        case '\xD1':
            if( m_dCompradas['\xD1'] ) {
                m_rOrig.x = 282;
                m_rOrig.y = 58;
            }
          break;

        case 'P':
            if( m_dCompradas['P'] ) {
                m_rOrig.x = 0;
                m_rOrig.y = 116;
            }
          break;

        case 'Q':
            if( m_dCompradas['Q'] ) {
                m_rOrig.x = 47;
                m_rOrig.y = 116;
            }
          break;

        case 'R':
            if( m_dCompradas['R'] ) {
                m_rOrig.x = 94;
                m_rOrig.y = 116;
            }
          break;

        case 'S':
            if( m_dCompradas['S'] ) {
                m_rOrig.x = 141;
                m_rOrig.y = 116;
            }
          break;

        case 'T':
            if( m_dCompradas['T'] ) {
                m_rOrig.x = 188;
                m_rOrig.y = 116;
            }
          break;

        case 'V':
            if( m_dCompradas['V'] ) {
                m_rOrig.x = 282;
                m_rOrig.y = 116;
            }
          break;

        case 'W':
            if( m_dCompradas['W'] ) {
                m_rOrig.x = 328;
                m_rOrig.y = 116;
            }
          break;

        case 'X':
            if( m_dCompradas['X'] ) {
                m_rOrig.x = 0;
                m_rOrig.y = 174;
            }
          break;

        case 'Y':
            if( m_dCompradas['Y'] ) {
                m_rOrig.x = 47;
                m_rOrig.y = 174;
            }
          break;

        case 'Z':
            if( m_dCompradas['Z'] ) {
                m_rOrig.x = 94;
                m_rOrig.y = 174;
            }
          break;

        // VOCALES
        case 'A':
            if( m_dCompradas['A'] ) {
                m_rOrig.x = 0;
                m_rOrig.y = 0;
            }
          break;
        case '\xC1':
            if( m_dCompradas['A'] ) {
                m_rOrig.x = 0;
                m_rOrig.y = 232;
            }
          break;

        case 'E':
            if( m_dCompradas['E'] ) {
                m_rOrig.x = 188;
                m_rOrig.y = 0;
            }
          break;
        case '\xC9':
            if( m_dCompradas['E'] ) {
                m_rOrig.x = 47;
                m_rOrig.y = 232;
            }
          break;

        case 'I':
            if( m_dCompradas['I'] ) {
                m_rOrig.x = 0;
                m_rOrig.y = 58;
            }
          break;
        case '\xCD':
            if( m_dCompradas['I'] ) {
                m_rOrig.x = 94;
                m_rOrig.y = 232;
            }
          break;

        case 'O':
            if( m_dCompradas['O'] ) {
                m_rOrig.x = 329;
                m_rOrig.y = 58;
            }
          break;
        case '\xD3':
            if( m_dCompradas['O'] ) {
                m_rOrig.x = 141;
                m_rOrig.y = 232;
            }
          break;

        case 'U':
            if( m_dCompradas['U'] ) {
                m_rOrig.x = 234;
                m_rOrig.y = 116;
            }
          break;
        case '\xDA':
            if( m_dCompradas['U'] ) {
                m_rOrig.x = 188;
                m_rOrig.y = 232;
            }
          break;

        // OTROS CARACTERES
        case '\xBF':
            m_rOrig.x = 141;
            m_rOrig.y = 174;
          break;
        case '?':
            m_rOrig.x = 188;
            m_rOrig.y = 174;
          break;
        case '\xA1':
            m_rOrig.x = 235;
            m_rOrig.y = 174;
          break;
        case '!':
            m_rOrig.x = 282;
            m_rOrig.y = 174;
          break;
        case ',':
            m_rOrig.x = 235;
            m_rOrig.y = 232;
          break;
        case '\xAD':
            m_rOrig.x = 282;
            m_rOrig.y = 232;
          break;

        // CARACTER DESCONOCIDO
        default:
            m_rOrig.x = 188;
            m_rOrig.y = 174;
          break;
        }

        SDL_BlitSurface( m_vSup[0], &m_rOrig, pDestSurface, &m_rDest );
        m_rDest.x += 47;
        if( i == 13 || i == 29 || i == 45 )
        {
            m_rDest.x = 24;
            m_rDest.y += 58;
        }
        else if( i == 61 )
        {
            m_rDest.x = 71;
            m_rDest.y += 58;
        }

    }

    // Dibuja el marco del panel
    SDL_BlitSurface( m_vSup[1], NULL, pDestSurface, &m_rDestMarco );
    // Muestra la pista
    FFranklin.EscribirCentrado( pDestSurface, m_vPistas[m_iPanelActual], 318, 0 );
}

bool CPanel::ComprobarResuelto()
{
    // Comprueba, una a una, si todas las letras del panel están compradas
    char Aux;
    for( int i = 0; i < PAN_CASILLAS; i++ ) {
        if( m_vPaneles[m_iPanelActual][i] == '\xC1' ) Aux = 'A';
        else if( m_vPaneles[m_iPanelActual][i] == '\xC9' ) Aux = 'E';
        else if( m_vPaneles[m_iPanelActual][i] == '\xCD' ) Aux = 'I';
        else if( m_vPaneles[m_iPanelActual][i] == '\xD3' ) Aux = 'O';
        else if( m_vPaneles[m_iPanelActual][i] == '\xDA' ) Aux = 'U';
        else Aux = m_vPaneles[m_iPanelActual][i];
        if( Aux != '0' && Aux != '\xBF' && Aux != '?' && Aux != '\xA1' && Aux != '!' && Aux != ',' && Aux != '\xAD' && m_dCompradas[Aux] == false )
            return false;
    }
    return true;
}

bool CPanel::ComprobarLetra( const char& ID )
{
    return m_dCompradas[ID];
}

void CPanel::MarcarLetra( const char& ID )
{
    m_dCompradas[ID] = true;
}

void CPanel::MarcarTodo()
{
    for( std::map<char,bool>::iterator it = m_dCompradas.begin(); it != m_dCompradas.end(); it++ )
        it->second = true;
}

int CPanel::BuscarLetra( const char& ID )
{
    // Busca el número de veces que está una letra en el panel
    SInt iCuenta = 0;
    char Aux = ID;
    // En el caso de las vocales, también contar las tildadas
    if( ID == 'A' ) Aux = '\xC1';
    else if( ID == 'E' ) Aux = '\xC9';
    else if( ID == 'I' ) Aux = '\xCD';
    else if( ID == 'O' ) Aux = '\xD3';
    else if( ID == 'U' ) Aux = '\xDA';
    for( int i = 0; i < PAN_CASILLAS; i++ )
        if( m_vPaneles[m_iPanelActual][i] == ID || m_vPaneles[m_iPanelActual][i] == Aux )
            iCuenta++;

    return iCuenta;
}

void CPanel::Limpiar()
{
    SDL_FreeSurface( m_vSup[0] );
    SDL_FreeSurface( m_vSup[1] );
}
