//=====[Libraries]=============================================================

#include "mbed.h"
#include "timer.h"
#include "sistema_riego.h"

//=====[Declaration of private defines]======================================

#define TIMER_ACTUALIZACION    1.0
Ticker miTimer;

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void inicioTimer()
{ 
    miTimer.attach(&agregarEventoTimer, TIMER_ACTUALIZACION);
    
}

//=====[Implementations of private functions]==================================

