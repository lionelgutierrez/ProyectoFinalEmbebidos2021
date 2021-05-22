//=====[#include guards - begin]===============================================

#ifndef _SENSOR_SUMEDAD_SUELO_H_
#define _SENSOR_SUMEDAD_SUELO_H_

//=====[Libraries]=============================================================

//=====[Declaration of public defines]=======================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void inicioSensorHumedadSuelo();
void actualizarSensorHumedadSuelo();
float sensorSueloValor();
float sensorSueloUmral();
void sensorSueloAjusteValor(float umbralNuevo);

//=====[#include guards - end]=================================================

#endif // _SENSOR_SUMEDAD_SUELO_H_