//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "sistema_riego.h"
#include "sensor_humedad_suelo.h"
#include "sensor_dht.h"
#include "ethernet_Conn.h"
#include "electrovalvula.h"
#include "timer.h"
#include "user_interface.h"
#include "pc_serial_com.h"

//extern 
//EventQueue colaEventos;
bool procesarEvento = false;
//=====[Declaration of private defines]======================================

//=====[Declaration of private data types]=====================================
// Event queue para leer los sensores cuando avise el ticker timer
int contDHT =0;
int maxDHT =6;
//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================
int contador = 0;
int conSuelo = 0;

void inicioSistemaRiego()
{
    inciarUI(); // inicializa interfaz de usaurio
    inicioConexionSerial(); // Inicializo interfaz serial
    inicioSensorDHT(); // Inicializo sensor DHT
    inicioSensorHumedadSuelo(); //Inicializo  sensor humedad suelo
    inicioEthernet(); // Comienza la comunicacion ethernet
    inicioElectrovalvula(); //Inicializo electrovalvula

    inicioTimer(); //Inicio ticker para lectura de valores de sensores

}


void rutinaActualizaSensores()
{
   actualizarSensorHumedadSuelo(); //Actualizo el valor sensado de humedad de suelo
    
    contDHT++;
    if (contDHT == maxDHT)
    {  
       actualizarSensorDHT(); //Actualizo los valores de temp y humedad
       contDHT = 0;
    }
    procesarEvento = false;
    
}

void actualizarSistemaRiego()
{
    actualizarUI();
    actualizarComunicacionSerial();
    actualizarElectrovalvula();
    actualizarDatosSensoresPC();
    if (procesarEvento)
    {
        rutinaActualizaSensores();
    }
    
    delay(SYSTEM_TIME_INCREMENT_MS);
   
}

void agregarEventoTimer()
{
    procesarEvento = true;
}


//=====[Implementations of private functions]==================================
