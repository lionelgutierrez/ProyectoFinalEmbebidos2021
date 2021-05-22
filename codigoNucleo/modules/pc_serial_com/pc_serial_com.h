//=====[#include guards - begin]===============================================

#ifndef _PC_SERIAL_COM_H_
#define _PC_SERIAL_COM_H_

//=====[Libraries]=============================================================

//=====[Declaration of public defines]=======================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void inicioConexionSerial();
char comunicacionSerialLeerCaracter();
void comunicacionSerialEscribir( const char* str );
void actualizarComunicacionSerial();
void mostrarHumedadSuelo();
void mostraHumedadTempAmbiente();
void mostrarUmbralHumedad();
//=====[#include guards - end]=================================================

#endif // _PC_SERIAL_COM_H_