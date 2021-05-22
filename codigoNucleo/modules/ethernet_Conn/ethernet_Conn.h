//=====[#include guards - begin]===============================================

#ifndef _ETHERNET_CONN_H_
#define _ETHERNET_CONN_H_
#include "electrovalvula.h"
#include "sensor_dht.h"

//=====[Libraries]=============================================================

//=====[Declaration of public defines]=======================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void inicioEthernet();
void enviarPCValorElectrovalvula(electrovalvulaEstado_t  Estado);
void actualizarDatosSensoresPC();

//=====[#include guards - end]=================================================

#endif // _ETHERNET_CONN_H_