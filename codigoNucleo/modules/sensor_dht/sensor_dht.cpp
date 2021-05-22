//=====[Libraries]=============================================================
#include "DHT.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "sensor_dht.h"

//=====[Declaration of private defines]======================================

#define SENSOR_DHT_PROM_VALORES    10

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DHT sensor(D8,DHT11); 

//=====[Declaration and initialization of private global variables]============
float valorDHTHumedad = 0.0;
float valorDHTTemperatura = 0.0;
float valorDHTHumedadArray[SENSOR_DHT_PROM_VALORES];
float valorDHTTemperaturadArray[SENSOR_DHT_PROM_VALORES];

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void inicioSensorDHT()
{
    int i;
    
    for( i=0; i<SENSOR_DHT_PROM_VALORES ; i++ ) {
        valorDHTHumedadArray[i] = 0;
        valorDHTTemperaturadArray[i] = 0;
    }
}

void actualizarSensorDHT()
{

    static int sensorIndice = 0;
    float sensorDHTHumedadLecturaSuma = 0.0; 
    float sensorDHTTempLecturaSuma = 0.0; 
    float sensorDHTHumedadPromedio = 0.0;
    float sensorDHTTempPromedio = 0.0;
	int error;
    int i = 0;

 	error = sensor.readData();
    if (error == 0) {
    	valorDHTHumedadArray[sensorIndice] = sensor.ReadHumidity();
    	valorDHTTemperaturadArray[sensorIndice] = sensor.ReadTemperature(CELCIUS);
		sensorIndice++;
    	if ( sensorIndice >= SENSOR_DHT_PROM_VALORES) {
        	sensorIndice = 0;
    	}
	
	//Calculo humedad promedio
    sensorDHTHumedadLecturaSuma = 0.0;
    for (i = 0; i < SENSOR_DHT_PROM_VALORES; i++) {
        sensorDHTHumedadLecturaSuma = sensorDHTHumedadLecturaSuma + valorDHTHumedadArray[i];
    }
    sensorDHTHumedadPromedio = sensorDHTHumedadLecturaSuma / SENSOR_DHT_PROM_VALORES;
	valorDHTHumedad = sensorDHTHumedadPromedio;	

	//Calculo temperatura promedio
    sensorDHTTempLecturaSuma = 0.0;
    for (i = 0; i < SENSOR_DHT_PROM_VALORES; i++) {
        sensorDHTTempLecturaSuma = sensorDHTTempLecturaSuma + valorDHTTemperaturadArray[i];
    }
    sensorDHTTempPromedio = sensorDHTTempLecturaSuma / SENSOR_DHT_PROM_VALORES;
	valorDHTTemperatura = sensorDHTTempPromedio;	

   } 
	
}

float sensorDHTHumedad()
{
	return valorDHTHumedad;
}
float sensorDHTTemperatura()
{
	return valorDHTTemperatura;
}

//=====[Implementations of private functions]==================================

