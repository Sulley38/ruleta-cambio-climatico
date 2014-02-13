/*
    El archivo que contiene los textos de la interfaz debe llamarse LC_interface.txt
    El archivo que contiene los paneles traducidos debe llamarse LC_paneles.txt
    LC son las dos letras que identifican los diferentes idiomas:
        en -> English    es -> Castellano    eu -> Euskara

    El formato del archivo de interfaz es:

        TEXTO_IDENTIFICADOR
        Traducción
        (línea en blanco)

*/

#ifndef LENGUAJE_H_
#define LENGUAJE_H_

#include "Common.h"

extern class CLenguaje
{
private:
    /** Idioma que se ha cargado **/
    std::string m_szIdioma;

    /** Contenedor de los identificadores y las entradas traducidas **/
    std::string m_szIDs[LANG_ENTRADAS];
    std::string m_szTraducciones[LANG_ENTRADAS];

    /** Relación entre los IDs y las traducciones **/
    std::map<std::string,std::string> m_dEntradas;

public:
    /** Carga las entradas del idioma seleccionado **/
    void Load( const std::string& szLang );

    /** Devuelve la entrada traducida **/
    std::string String( const std::string& ID );

    /** Devuelve el ID del idioma que se ha cargado **/
    std::string GetLang();
} Traduccion;

#endif // LENGUAJE_H_
