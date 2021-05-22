//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "sistema_riego.h"
#include "user_interface.h"
#include "sensor_humedad_suelo.h"
#include "sensor_dht.h"
#include "fecha_y_hora.h"
#include "matrix_keypad.h"
#include "display.h"
#include "electrovalvula.h"

//=====[Declaration of private defines]======================================

#define DISPLAY_REFRESH_TIME_REPORT_MS 1000
#define NUMERO_KEYS_UMBRAL  3
//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static int displayRefreshTimeMs = DISPLAY_REFRESH_TIME_REPORT_MS;
char digitosUmbral[NUMERO_KEYS_UMBRAL];
int indiceUmbral = 0;
bool leerCodigo = false; //se pone en true al leer * que comienza el cambio de codigo
//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceMatrixKeypadUpdate();

static void iniciarDisplayUI();
static void actualizarDisplayUI();
static void inicioInterfazUsuarioDisplay();
static void actualizarDisplay();

//=====[Implementations of public functions]===================================

void inciarUI()
{
    matrixKeypadInit( SYSTEM_TIME_INCREMENT_MS );
    iniciarDisplayUI();
}

void actualizarUI()
{
    userInterfaceMatrixKeypadUpdate();
    actualizarDisplayUI();
}


//=====[Implementations of private functions]==================================

static void userInterfaceMatrixKeypadUpdate()
{
    char keyReleased = matrixKeypadUpdate();
    if( keyReleased != '\0' ) 
    {
        if( keyReleased == '#' && leerCodigo ) 
        {
            // Si tengo 3 o menos caracteres armo el nevo umbral
            if (indiceUmbral<NUMERO_KEYS_UMBRAL) 
            {
                //Convierto digitosUmbral a entero
                //si numero esta entre 0 y 100 actualizo el umbral
                int valor;
                int ok = sscanf(digitosUmbral, "%d", &valor); 
                if (ok >0)
                {
                    if (valor >=0 && valor<=100)
                    {
                        float umbralNuevo = (float)valor;             
                        sensorSueloAjusteValor(umbralNuevo);
                    }
                    
                }
                
            }  
            indiceUmbral = 0; 
            leerCodigo = false;  
        }
        else if (keyReleased == '*' )
        {
            indiceUmbral = 0; 
            strcpy(digitosUmbral, "00");
            leerCodigo = true;
        }
        else if (keyReleased != '#' && leerCodigo)
        {
            if (indiceUmbral < NUMERO_KEYS_UMBRAL)
            {
                digitosUmbral[indiceUmbral] = keyReleased;
                indiceUmbral++;
            }
        }
    }
}

static void inicioInterfazUsuarioDisplay()
{
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Temperatura:" );

    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Humedad:" );
    
    displayCharPositionWrite ( 0,2 );
    displayStringWrite( "Humedad suelo:" );
    
    displayCharPositionWrite ( 0,3 );
    displayStringWrite( "Umbral:" );    

    displayCharPositionWrite ( 12,3 );
    displayStringWrite( "Valv:" );      
    
}

static void actualizarDisplay()
{
    char stringTemperatura[2];

    sprintf(stringTemperatura, "%.0f", sensorDHTTemperatura());
    displayCharPositionWrite ( 12,0 );
    displayStringWrite( stringTemperatura );
    displayCharPositionWrite ( 14,0 );
    displayStringWrite( "'C" );

    char stringHumedad[3];  

    sprintf(stringHumedad, "%.0f", sensorDHTHumedad());
    displayCharPositionWrite ( 8,1 );
    displayStringWrite( stringHumedad );
    displayCharPositionWrite ( 11,1 );
    displayStringWrite( "%" );
    
    char stringHumedadSuelo[3];
    sprintf(stringHumedadSuelo, "%.0f", sensorSueloValor());
    displayCharPositionWrite ( 15,2 );
    displayStringWrite( stringHumedadSuelo );
    displayCharPositionWrite ( 18,2 );
    displayStringWrite( "%" );    
    
    char stringUmbralSuelo[3];
    sprintf(stringUmbralSuelo, "%.0f", sensorSueloUmral());
    displayCharPositionWrite ( 7,3 );
    displayStringWrite( stringUmbralSuelo );
    displayCharPositionWrite ( 10,3 );
    displayStringWrite( "%" );    
    
    displayCharPositionWrite ( 17,3 );
    if (electrovalvulaEstado() == PARADA)
    {
        displayStringWrite( "OFF" );        
    }
    else
    {
        displayStringWrite( "ON" ); 
    }
    
}



static void iniciarDisplayUI()
{
    displayInit( DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER );
    inicioInterfazUsuarioDisplay();
}

static void actualizarDisplayUI()
{
    static int accumulatedDisplayTime = 0;
    
    if( accumulatedDisplayTime >=
        displayRefreshTimeMs ) {

        accumulatedDisplayTime = 0;
        actualizarDisplay();
        
   } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    }
}


