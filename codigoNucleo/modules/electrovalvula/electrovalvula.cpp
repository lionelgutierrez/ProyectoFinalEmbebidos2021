//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "electrovalvula.h"
#include "sensor_humedad_suelo.h"
#include "ethernet_Conn.h"
#include "sistema_riego.h"


//=====[Declaration of private defines]======================================

#define MOTOR_UPDATE_TIME 9
#define ELECTROVALVULA_TIEMPO_REFRESCO_MS 5000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalInOut releElectrovalvula(PF_1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

electrovalvulaEstado_t  estadoElectrovalvula;

//=====[Declaration and initialization of private global variables]============
static int tiempoRefrescoElectrovalvula = ELECTROVALVULA_TIEMPO_REFRESCO_MS;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void inicioElectrovalvula()
{
    releElectrovalvula.mode(OpenDrain);
    releElectrovalvula.input();
    estadoElectrovalvula = PARADA;
}

electrovalvulaEstado_t  electrovalvulaEstado()
{
    return estadoElectrovalvula;
}

void electrovalvulaSetearEstado( electrovalvulaEstado_t  Estado  )
{
    estadoElectrovalvula = Estado;
    if (estadoElectrovalvula == PARADA) 
    {
        releElectrovalvula.input();
    }

    if (estadoElectrovalvula == ENCENDIDA) 
    {
        releElectrovalvula.output();
        releElectrovalvula = LOW;
    }
}

void accionarElectrovalvula()
{
    float valorHumedadSuelo = sensorSueloValor();
    float umbralHumedad = sensorSueloUmral();
    
    // Si humedad > umbral debo prender la electrovalvula (si no esta ya prendida)
    if (valorHumedadSuelo>umbralHumedad)
    {
        if (electrovalvulaEstado() == PARADA)
        {
            electrovalvulaSetearEstado(ENCENDIDA);
            enviarPCValorElectrovalvula(ENCENDIDA);
        }
    }
    
    // Si humedad <= umbral debo apagar la electrovalvula (si esta prendida)
    if (valorHumedadSuelo<=umbralHumedad)
    {
        if (electrovalvulaEstado() == ENCENDIDA)
        {
            electrovalvulaSetearEstado(PARADA);
            enviarPCValorElectrovalvula(PARADA);
        }
    }
    
}

void actualizarElectrovalvula()
{
    static int tiempoAcumulado = 0;
    
    if( tiempoAcumulado >=
        tiempoRefrescoElectrovalvula ) {

        tiempoAcumulado = 0;
        accionarElectrovalvula();
        
   } else {
        tiempoAcumulado =
            tiempoAcumulado + SYSTEM_TIME_INCREMENT_MS;        
    }    
}
//=====[Implementations of private functions]==================================
