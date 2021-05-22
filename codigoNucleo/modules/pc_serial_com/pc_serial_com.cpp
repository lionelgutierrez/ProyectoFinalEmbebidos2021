//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "pc_serial_com.h"
#include "sensor_humedad_suelo.h"
#include "sensor_dht.h"
#include "fecha_y_hora.h"
#include "electrovalvula.h"

#include "ethernet_Conn.h"
//=====[Declaration of private defines]======================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

Serial uartUsb(USBTX, USBRX);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static void actualizarComandosSerial( char caracterRecibido );
void mostrarHumedadSuelo();
void mostraHumedadTempAmbiente();
void mostrarUmbralHumedad(); 
static void setearUmbralHumedad();
static void mostrarEstadoElectrovalvula();
static void setearFechaHora();
static void mostrarFechaHora();
static void comandosDisponibles();
//static void prenderElectrovalvula();
//static void apagarElectrovalvula();
//=====[Implementations of public functions]===================================

void inicioConexionSerial()
{
    comandosDisponibles();
}

char comunicacionSerialLeerCaracter()
{
    char caracterRecibido = '\0';
    if( uartUsb.readable() ) {
        caracterRecibido = uartUsb.getc();
    }
    return caracterRecibido;
}

void comunicacionSerialEscribir( const char* str )
{
    uartUsb.printf( "%s", str );
}

void actualizarComunicacionSerial()
{

    char caracterRecibido = comunicacionSerialLeerCaracter();
    if( caracterRecibido != '\0' ) {
        actualizarComandosSerial( caracterRecibido );
    }    
}

//=====[Implementations of private functions]==================================

static void actualizarComandosSerial( char caracterRecibido )
{
    switch (caracterRecibido) {
        case '1': mostrarHumedadSuelo(); break;
        case '2': mostraHumedadTempAmbiente(); break;
        case '3': mostrarUmbralHumedad(); break;
        case '4': setearUmbralHumedad(); break;
        case '5': mostrarEstadoElectrovalvula(); break;
        case 's': case 'S': setearFechaHora(); break;
        case 't': case 'T': mostrarFechaHora(); break;
        default: comandosDisponibles(); break;
    } 
}

static void comandosDisponibles()
{
    uartUsb.printf( "Comandos disponibles:\r\n" );
    uartUsb.printf( "Presione '1' para obetner la humedad de suelo\r\n" );
    uartUsb.printf( "Presione '2' para obtener tempratura y humedad ambiente\r\n" );
    uartUsb.printf( "Presione '3' para obtener el umbral de humedad de suelo\r\n" );
    uartUsb.printf( "Presione '4' para definir nuevo umbral de humedad de suelo\r\n" );
    uartUsb.printf( "Presione '5' para ver si la electrovalvula esta abierta o cerrada\r\n" );
    uartUsb.printf( "Presione 's' o 'S' para setear fecha y hora\r\n" );
    uartUsb.printf( "Presione 't' o 'T' para obtener fecha y hora\r\n" );
    uartUsb.printf( "\r\n" );
}

void mostrarHumedadSuelo()
{
    uartUsb.printf( "Humedad del suelo: %.2f %%\r\n", sensorSueloValor());
}
void mostraHumedadTempAmbiente()
{
    uartUsb.printf( "Temperatura ambiente: %.2f °C\r\n", sensorDHTTemperatura());
    uartUsb.printf( "Humedad ambiente: %.2f %%\r\n", sensorDHTHumedad());
}

void mostrarUmbralHumedad()
{
    uartUsb.printf( "Humbral de humedad para activacion electrovalvula: %.2f %%\r\n", sensorSueloUmral());
}

static void setearUmbralHumedad()
{
int valor;

    uartUsb.printf("\r\nTipear el nuevo umbral de humedad de suelo (1-100) y presiones enter: ");
    uartUsb.scanf("%d", &valor);
        
    if (valor > 0  && valor <= 100) 
    {
        float umbralNuevo = (float) valor;
        sensorSueloAjusteValor(umbralNuevo);
        uartUsb.printf("\r\nCambio de umbral de humedad de suelo correcto\r\n");
    }
    else
    {
        uartUsb.printf("\r\nError en el ingreso de nuevo umbral de humedad de suelo. El mismo debe estar entre 1 y 100. Operacion cancelada ");
    }
}

static void setearFechaHora()
{
    int anio   = 0;
    int mes  = 0;
    int dia    = 0;
    int hora   = 0;
    int minuto = 0;
    int segundo = 0;
    
    uartUsb.printf("\r\nTipear el año actual en formato AAAA y presiones enter: ");
    uartUsb.scanf("%d", &anio);
    uartUsb.printf("%d\r\n", anio);

    uartUsb.printf("Tipear el mes actual (1-12) y presiones enter: ");
    uartUsb.scanf("%d", &mes);
    uartUsb.printf("%d\r\n", mes);

    uartUsb.printf("Tipear el dia actual (1-31) y presiones enter: ");
    uartUsb.scanf("%d", &dia);
    uartUsb.printf("%d\r\n", dia);

    uartUsb.printf("Tipear la hora actual (0-23) y presiones enter: ");    
    uartUsb.scanf("%d", &hora);
    uartUsb.printf("%d\r\n",hora);

    uartUsb.printf("Tipear los minutos actuales (0-59) y presiones enter: ");
    uartUsb.scanf("%d", &minuto);
    uartUsb.printf("%d\r\n", minuto);

    uartUsb.printf("Tipear los segundos actuales (0-59) y presiones enter: ");
    uartUsb.scanf("%d", &segundo);
    uartUsb.printf("%d\r\n", segundo);
    
    uartUsb.printf("Se actualizó la fecha y hora\r\n");

    while ( uartUsb.readable() ) {
        uartUsb.getc();
    }

    actualizarFechaHora( anio, mes, dia, hora, minuto, segundo );
}

static void mostrarFechaHora()
{
    uartUsb.printf("Fecha y hora = %s", leerFechaHora());
}

static void mostrarEstadoElectrovalvula()
{
    switch ( electrovalvulaEstado() ) {
        case PARADA: uartUsb.printf( "La electrovalvula esta apagada\r\n"); break;
        case ENCENDIDA: uartUsb.printf( "La electrovalvula esta encendida\r\n"); break;
    }
}
