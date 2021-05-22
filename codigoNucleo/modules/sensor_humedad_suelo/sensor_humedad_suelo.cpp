//=====[Libraries]=============================================================

#include "mbed.h"
#include "sensor_humedad_suelo.h"
#include "sistema_riego.h"

//=====[Declaration of private defines]======================================

#define SENSOR_SUELO_PROM_VALORES    10

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn sensorSuelo(A3);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

float valorSensorSuelo = 0.0;
float valorSensorSueloArray[SENSOR_SUELO_PROM_VALORES];
float umbralSensor = 30.0; //Umbral para activar electrovalvula. Valor inicial
//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

float sensorSueloUmral()
{
	return umbralSensor;
}
void sensorSueloAjusteValor(float umbralNuevo)
{
	umbralSensor = 	umbralNuevo;
}

void inicioSensorHumedadSuelo()
{
    int i;
    
    for( i=0; i<SENSOR_SUELO_PROM_VALORES ; i++ ) {
        valorSensorSueloArray[i] = 0;
    }
}

void actualizarSensorHumedadSuelo()
{
        static int sensorSueloIndice = 0;
    float sensorSueloLecturaSuma = 0.0; 
    float sensorSueloPromedio = 0.0;
	float valorSensadoPorcen = 0.0;
	//seco = 57000
    //100% agua = 37000
    //Formula % humedad =((57000-sensorValor)/20000)*100

    int i = 0;

	valorSensadoPorcen = ((57000.0-sensorSuelo.read_u16())/20000.0)*100;
    if (valorSensadoPorcen >= 100.0) 
    {
       valorSensadoPorcen= 100.0;
    }	
    if (valorSensadoPorcen < 0.0) 
    {
       valorSensadoPorcen= 0.0;
    }	    
    
    valorSensorSueloArray[sensorSueloIndice] = valorSensadoPorcen;
	sensorSueloIndice++;
    if ( sensorSueloIndice >= SENSOR_SUELO_PROM_VALORES) {
        sensorSueloIndice = 0;
    }
	
    sensorSueloLecturaSuma = 0.0;
    for (i = 0; i < SENSOR_SUELO_PROM_VALORES; i++) {
        sensorSueloLecturaSuma = sensorSueloLecturaSuma + valorSensorSueloArray[i];
    }
    sensorSueloPromedio = sensorSueloLecturaSuma / SENSOR_SUELO_PROM_VALORES;
	valorSensorSuelo = sensorSueloPromedio;
	
}


float sensorSueloValor()
{
    return valorSensorSuelo;
}



//=====[Implementations of private functions]==================================

