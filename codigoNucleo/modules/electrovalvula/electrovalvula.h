//=====[#include guards - begin]===============================================

#ifndef _ELECTROVALVULA_H_
#define _ELECTROVALVULA_H_

//=====[Libraries]=============================================================

//=====[Declaration of public defines]=======================================

//=====[Declaration of public data types]======================================

typedef enum {
    PARADA,
    ENCENDIDA
} electrovalvulaEstado_t;

//=====[Declarations (prototypes) of public functions]=========================

void inicioElectrovalvula();
void electrovalvulaSetearEstado( electrovalvulaEstado_t Estado );
electrovalvulaEstado_t electrovalvulaEstado();
void actualizarElectrovalvula();

//=====[#include guards - end]=================================================

#endif // _ELECTROVALVULA_H_
