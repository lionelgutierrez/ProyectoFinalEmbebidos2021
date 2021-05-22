//=====[#include guards - begin]===============================================
#include "mbed.h"
#ifndef _SISTEMA_RIEGO_H_
#define _SISTEMA_RIEGO_H_

//=====[Libraries]=============================================================

//=====[Declaration of public defines]=======================================

#define SYSTEM_TIME_INCREMENT_MS   10

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void inicioSistemaRiego();
void actualizarSistemaRiego();
void agregarEventoTimer();
//=====[#include guards - end]=================================================

#endif // _SISTEMA_RIEGO_H_