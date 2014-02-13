#include "Main.h"
#include "ObjBotones.h"
#include "ObjContador.h"
#include "ObjPanel.h"
#include "ObjRuleta.h"
#include "ScrIdioma.h"
#include "ScrInicio.h"
#include "ScrJugar.h"
#include "ScrRecuento.h"

// Definiciones de las clases externas
CApp Juego;
CFuente FBerlin, FCalibri, FEras, FFranklin, FShowcard, FTrebuchet;
CLenguaje Traduccion;
CIdioma Idioma;
CInicio Inicio;
CJugar Principal;
CRecuento Recuento;
CBotones Botones;
CContador Contador;
CPanel Panel;
CRuleta Ruleta;

int main( int argc, char* argv[] )
{
    Juego.Cargar();
    Juego.Comenzar();
    return Juego.GetExitCode();
}

CApp::CApp() : m_iTicksNecesarios ( 1000 / MAX_FPS )
{
    m_iXPos         = 0;
    m_iYPos         = 0;
	m_iWidth		= 800;
	m_iHeight		= 600;

    SDL_VERSION( &m_wmWindow.version );
    m_bPausa	    = false;
    m_bTerminar = false;
    m_iPantallaActual = 0;

    m_iFPSActual        = 0;
    m_iTicksActual      = 0;
    m_iTicksPerdidos    = 0;

    m_iTicksInicial     = 0;
    m_iTicksFinal       = 0;
    m_iTicksEmpleados   = 0;

    m_iExitCode = 0;
}

CApp::~CApp()
{
}

/** ----------- PROCEDIMIENTOS DE INICIALIZACIÓN ----------- **/

void CApp::Cargar()
{
    // Iniciar subsistemas de SDL
	if ( SDL_Init( SUBSYSTEMS ) < 0 )
		Juego.Error( "Error al iniciar SDL: " + std::string(SDL_GetError()) );

	if ( IMG_Init( IMG_INIT_PNG ) != IMG_INIT_PNG )
	    Juego.Error( "Error al iniciar el sistema SDL_image: " + std::string(IMG_GetError()) );

    if( Mix_Init( 0 ) != 0 )
        Juego.Error( "Error al iniciar el sistema SDL_mixer: " + std::string(Mix_GetError()) );

    // Intentar crear una ventana centrada del tamaño establecido y con icono.
    SetIcon();
	SetScreen( m_iWidth, m_iHeight );
	SetPosition( m_iXPos, m_iYPos );

	// Actualizar título de la ventana
	SetTitle( "Cargando..." );

	// Establece la semilla de los números pseudo-aleatorios
	srand( time(0) + getpid() );

	// Carga los recursos necesarios para el juego
	CargarRecursos();
}

/** Establece el tamaño de la ventana y obtiene sus propiedades
	@param iWidth Ancho de la ventana
	@param iHeight Alto de la ventana
**/
void CApp::SetScreen( const int& iWidth, const int& iHeight )
{
    // Determine the center of the screen
    const SDL_VideoInfo* vInfo = SDL_GetVideoInfo();
    if( vInfo )
    {
        m_iXPos = ( vInfo->current_w / 2 ) - ( m_iWidth / 2 );
        m_iYPos = ( vInfo->current_h / 2 ) - ( m_iHeight / 2 );
    }
    else
    {
        Juego.Error( "Error al obtener la resoluci\xF3n de pantalla." );
    }

    // Create the screen
	m_iWidth  = iWidth;
	m_iHeight = iHeight;
#ifdef _DEBUG
    m_pScreen = SDL_SetVideoMode( iWidth, iHeight, 0, SDL_DOUBLEBUF | SDL_HWSURFACE );
#else
	m_pScreen = SDL_SetVideoMode( iWidth, iHeight, 0, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN );
#endif

    // If we fail, return error.
	if ( m_pScreen == NULL )
		Juego.Error( "Error al establecer el modo de pantalla: " + std::string(SDL_GetError()) );

    // Get the screen properties
    if( SDL_GetWMInfo( &m_wmWindow ) <= 0 )
        Juego.Error( "Error al obtener las propiedades de la ventana: " + std::string(SDL_GetError()) );
}

/** Sitúa la ventana en una posición determinada
	@param iX Coordenada X de la posición
	@param iY Coordenada Y de la posición
**/
void CApp::SetPosition( const int& iX, const int& iY )
{
#ifdef __WIN32__
    SetWindowPos( m_wmWindow.window, HWND_TOP, iX, iY, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW );
#elif __LINUX__
    if( m_wmWindow.subsystem == SDL_SYSWM_X11 )
    {
        XLockDisplay( m_wmWindow.info.x11.display );
        XMoveWindow( m_wmWindow.info.x11.display, m_wmWindow.info.x11.wmwindow, iX, iY );
        XUnlockDisplay( m_wmWindow.info.x11.display );
    }
#endif
}

/** Carga las imágenes, fuentes y demás recursos necesarios para el transcurso del juego
**/
void CApp::CargarRecursos()
{
    // Cargar los recursos necesarios
    Idioma.Cargar();
    Inicio.Cargar();
    Principal.Cargar();
    Recuento.Cargar();
    // Analiza las fuentes
    FBerlin.Escanear( "data/font/berlinsans24.png", 1, 214, 31, 74, SDL_ALPHA_OPAQUE );
    FCalibri.Escanear( "data/font/calibri24.png", 1, 70, 40, 70, SDL_ALPHA_OPAQUE );
    FEras.Escanear( "data/font/erasdemi28.png", 1, 0, 0, 0, SDL_ALPHA_OPAQUE );
    FFranklin.Escanear( "data/font/franklin22.png", 1, 0, 0, 0, SDL_ALPHA_OPAQUE );
    FShowcard.Escanear( "data/font/showcardg48.png", 1, 0, 0, 0, SDL_ALPHA_OPAQUE );
    FTrebuchet.Escanear( "data/font/trebuchet24.png", 1, 0, 0, 0, SDL_ALPHA_OPAQUE );
}

/** Procedimiento auxiliar para cargar imágenes en sus respectivas superficies
    @param Superficie Vector con punteros a las superficies
    @param Ruta Vector con las rutas a las imágenes
**/
void CApp::CargarImagenes( std::vector<SDL_Surface*>& Superficie, std::vector<std::string> Ruta )
{
    int iCantidad = Superficie.size();
    SDL_Surface* Temp;
    for( int i = 0; i < iCantidad; ++i ) {
        Temp = IMG_Load( Ruta[i].c_str() );
        if( Temp == NULL ) {
            Error( IMG_GetError() );
        } else {
            Superficie[i] = SDL_DisplayFormatAlpha( Temp );
            SDL_FreeSurface( Temp );
        }
    }
}

/** ----------- PROCEDIMIENTOS DE TOMA DE DECISIÓN Y RENDERIZADO ----------- **/

/** Bucle principal del juego **/
void CApp::Comenzar()
{
    SetTitle( "La ruleta del cambio climático" );
	// Bucle hasta señal de salida
	while( !m_bTerminar )
	{
        m_iTicksInicial = SDL_GetTicks();

		// Controlar la entrada por ratón y teclado
		LeerEntrada();

		if( m_bPausa ) {
			// Poner en pausa en caso de estar minimizado
        #ifdef __WIN32__
			WaitMessage();
        #elif __LINUX__
            while( !XPending( m_wmWindow.info.x11.display ) )
            {
                SDL_Delay( 200 );
            }
        #endif
			m_iTicksPerdidos = SDL_GetTicks() - m_iTicksInicial;
		} else {
			// Renderizar
			Renderizar();
		}

        m_iTicksFinal = SDL_GetTicks();

        // Control del framerate
        ControlFPS();
	}

	Terminar();
}

/** Gestiona la entrada por ratón y teclado
	@remark Se ejecuta una vez por frame
**/
void CApp::LeerEntrada()
{
	// Espera eventos y selecciona los que nos interesan
	SDL_Event evento;
	while ( SDL_PollEvent( &evento ) )
	{
		switch ( evento.type )
		{
        case SDL_QUIT:
			SetQuitFlag();
			break;
		case SDL_KEYDOWN:
			Teclas( evento.key.keysym.sym );
			break;
		case SDL_MOUSEMOTION:
			MovimientoRaton( evento.motion.x, evento.motion.y );
			break;
		case SDL_MOUSEBUTTONDOWN:
			PulsacionRaton( evento.button.button, evento.motion.x, evento.motion.y );
			break;
		case SDL_ACTIVEEVENT:
			if ( evento.active.state & SDL_APPACTIVE ) {
				if ( evento.active.gain )
					VentanaActiva();
				else
					VentanaInactiva();
			}
			break;
		}
	}
}

/** Gestiona la pulsación de teclas
    @param iTecla Código de la tecla pulsada
**/
void CApp::Teclas( const int& iTecla )
{
    // Handle key pressed
    if( m_iPantallaActual == 0 )
        Idioma.TeclaPulsada( iTecla );
    else if( m_iPantallaActual == 1 )
        Inicio.TeclaPulsada( iTecla );
    else if( m_iPantallaActual == 2 )
        Principal.TeclaPulsada( iTecla );
    else if( m_iPantallaActual == 3 )
        Recuento.TeclaPulsada( iTecla );
}

/** Gestiona el movimiento de raton, pero no la pulsacion
    @param iX Posición absoluta en el eje X
    @param iY Posición absoluta en el eje Y
**/
void CApp::MovimientoRaton( const int& iX, const int& iY )
{
	if( m_iPantallaActual == 0 )
        Idioma.MouseMovido( iX, iY );
    else if( m_iPantallaActual == 1 )
        Inicio.MouseMovido( iX, iY );
    else if( m_iPantallaActual == 2 )
        Principal.MouseMovido( iX, iY );
    else if( m_iPantallaActual == 3 )
        Recuento.MouseMovido( iX, iY );
}

/** Gestiona la pulsación de raton
    @param iBoton Botón pulsado
    @param iX Posición absoluta en el eje X
    @param iY Posición absoluta en el eje Y
**/
void CApp::PulsacionRaton( const int& iBoton, const int& iX, const int& iY )
{
	if( iBoton == 1 ) {
        if( m_iPantallaActual == 0 )
            Idioma.MousePulsado( iX, iY );
        else if( m_iPantallaActual == 1 )
            Inicio.MousePulsado( iX, iY );
        else if( m_iPantallaActual == 2 )
            Principal.MousePulsado( iX, iY );
        else if( m_iPantallaActual == 3 )
            Recuento.MousePulsado( iX, iY );
	}
}

/** Pausa el juego **/
void CApp::VentanaInactiva()
{
    m_bPausa = true;
    if( m_iPantallaActual == 2 )
        Contador.Pausar(true);
}

/** Reanuda el juego **/
void CApp::VentanaActiva()
{
    m_bPausa = false;
    if( m_iPantallaActual == 2 )
        Contador.Pausar(false);
}

/** Gestiona el renderizado en pantalla **/
void CApp::Renderizar()
{
    // Bloquea la superficie SDL si es necesario
	if ( SDL_MUSTLOCK( m_pScreen ) )
		if ( SDL_LockSurface( m_pScreen ) < 0 )
			return;

	if( m_iPantallaActual == 0 )
        Idioma.Renderizar( m_pScreen );
    else if( m_iPantallaActual == 1 )
        Inicio.Renderizar( m_pScreen );
    else if( m_iPantallaActual == 2 )
        Principal.Renderizar( m_pScreen );
    else if( m_iPantallaActual == 3 )
        Recuento.Renderizar( m_pScreen );

	// Desbloquea la superficie SDL si es necesario
	if ( SDL_MUSTLOCK( m_pScreen ) )
		SDL_UnlockSurface( m_pScreen );

	// Actualizar la pantalla: mostrar el nuevo frame
	SDL_Flip( m_pScreen );
}

/** ----------- PROCEDIMIENTOS AUXILIARES ----------- **/

/** Establece el icono de la ventana
    @remark Tiene que ejecutarse antes que SDL_SetVideoMode
**/
void CApp::SetIcon()
{
    SDL_Surface* pIcon;
    Uint32 ColorKey;

    pIcon = SDL_LoadBMP( "data/img/wicon.bmp" );
    if( pIcon == NULL ){
        Juego.Advertencia( SDL_GetError() );
    } else {
        ColorKey = SDL_MapRGB( pIcon->format, 255, 255, 255 );
        SDL_SetColorKey( pIcon, SDL_SRCCOLORKEY, ColorKey );
        SDL_WM_SetIcon( pIcon, 0 );
        SDL_FreeSurface( pIcon );
    }
}

/** Actualiza el título de la ventana
	@remark Admite caracteres codificados en UTF-8
**/
void CApp::SetTitle( const std::string& Titulo )
{
	SDL_WM_SetCaption( Titulo.c_str(), 0 );
}

/** Establece la pantalla de juego que se tiene que mostrar
    @param iScreen -> 0 = IDIOMA; 1 = INICIO; 2 = JUEGO; 3 = RECUENTO;
**/
void CApp::SetCurrentScreen( const int& iScreen )
{
    m_iPantallaActual = iScreen;
}

/** Termina el bucle principal
    @remark Una vez llamado, no hay vuelta de hoja
**/
void CApp::SetQuitFlag()
{
    m_bTerminar = true;
}

/** Devuelve un número pseudo-aleatorio
    @remark Se debe hacer módulo con el valor devuelto para limitar el número
**/
int CApp::GetRandom()
{
    return rand();
}

/** Convierte una variable númerica en una cadena de texto imprimible en pantalla
    @param i El número a convertir
**/
std::string CApp::IntToString( const int& i )
{
    std::ostringstream OSS;
    OSS << i;
    return OSS.str();
}

/** Calcula los FPS y mantiene el límite
    @remark El límite se establece con la definición MAX_FPS
**/
void CApp::ControlFPS()
{
    // Aumenta en 1 por cada pasada
    m_iFPSActual++;

    m_iTicksEmpleados = m_iTicksFinal - m_iTicksInicial - m_iTicksPerdidos;

    // Establece el retraso necesario para limitar los FPS
    if( m_iTicksEmpleados < m_iTicksNecesarios )
    {
        SDL_Delay( m_iTicksNecesarios - m_iTicksEmpleados );
    }

    // Muestra los FPS actuales en la barra de título y vuelve a empezar a contar
    m_iTicksActual += SDL_GetTicks() - m_iTicksInicial - m_iTicksPerdidos;
    if( m_iTicksActual >= 1000 )
    {
#ifdef _DEBUG
        SetTitle( "La ruleta del cambio climático " + std::string(APP_VERSION_STR) + " - " + IntToString(m_iFPSActual) + " FPS" );
#endif
        m_iTicksActual = 0;
        m_iFPSActual = 0;
    }
    m_iTicksPerdidos = 0;
}

/** ----------- PROCEDIMIENTOS DE MANEJO DE ERRORES ----------- **/
void CApp::Advertencia( const std::string& Mensaje )
{
    std::cout << "Warning: " << Mensaje << std::endl;
}

void CApp::Error( const std::string& Mensaje )
{
    m_bTerminar = true;
    m_iExitCode = 1;
    std::cout << "Error: " << Mensaje << std::endl;
}

/** Devuelve el código con el que está previsto que termine la ejecución
    @return False (0) si todo va bien
**/
int CApp::GetExitCode()
{
    return m_iExitCode;
}

/** ----------- PROCEDIMIENTOS DE LIMPIEZA Y LIBERAR MEMORIA ----------- **/

void CApp::Terminar()
{
	// Liberar la memoria
	Idioma.Limpiar();
	Inicio.Limpiar();
    Principal.Limpiar();
    Recuento.Limpiar();
    if( m_pScreen != NULL )
        SDL_FreeSurface( m_pScreen );
    // Elimina las fuentes
    FBerlin.Terminar();
    FCalibri.Terminar();
    FEras.Terminar();
    FFranklin.Terminar();
    FShowcard.Terminar();
    FTrebuchet.Terminar();
    // Termina los módulos de SDL
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
