#ifndef COMMON_H_
#define COMMON_H_

#define APP_VERSION 1,1,0,0
#define APP_VERSION_STR "1.1"
#define MAX_FPS 50
#define SUBSYSTEMS (SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_NOPARACHUTE)

#define BOT_YTEXTO 492
#define JUG_VOCAL 100
#define LANG_ENTRADAS 37
#define MAX_LETRAS 128
#define MAX_STRING 64
#define PAN_CASILLAS 76
#define RUL_GAJOS 22
#define RUL_SONIDOS 6
#define RUL_VUELTAS 65
#define RUL_DINERO 10000
#define RUL_PLAYERS 3

#ifdef __cplusplus
    #include <cctype>
    #include <cmath>
    #include <ctime>
    #include <iostream>
    #include <map>
    #include <fstream>
    #include <sstream>
    #include <string>
    #include <vector>
#endif
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_syswm.h>
#include <unistd.h>
#ifdef __WIN32__
    #include <windows.h>
#elif __LINUX__
    #include <X11/Xlib.h>
#endif

#if defined(_MSC_VER) && !defined(__WIN32__)
    #define __WIN32__
#endif

typedef unsigned short int SInt;

#include "Fuente.h"
#include "Lenguaje.h"
#include "Main.h"

#endif // COMMON_H_
