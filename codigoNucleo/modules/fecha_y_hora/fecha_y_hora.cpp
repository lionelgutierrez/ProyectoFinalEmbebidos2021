//=====[Libraries]=============================================================

#include "mbed.h"

#include "fecha_y_hora.h"

//=====[Declaration of private defines]======================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

char* leerFechaHora()
{
    time_t epochSeconds;
    epochSeconds = time(NULL);
    return ctime(&epochSeconds);    
}

void actualizarFechaHora( int anio, int mes, int dia, 
                       int hora, int minuto, int segundo )
{
    struct tm rtcTime;

    rtcTime.tm_year = anio - 1900;
    rtcTime.tm_mon  = mes - 1;
    rtcTime.tm_mday = dia;
    rtcTime.tm_hour = hora;
    rtcTime.tm_min  = minuto;
    rtcTime.tm_sec  = segundo;

    rtcTime.tm_isdst = -1;

    set_time( mktime( &rtcTime ) );
}

//=====[Implementations of private functions]==================================

