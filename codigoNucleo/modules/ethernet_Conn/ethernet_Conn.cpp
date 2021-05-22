//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "ethernet_Conn.h"
#include "EthernetInterface.h"
#include "electrovalvula.h"
#include "sistema_riego.h"

//=====[Declaration of private defines]======================================
#define IP        "192.168.1.200"
#define IP_SERVER "192.168.1.130"
#define NETMASK   "255.255.255.0"
#define GATEWAY   "192.168.1.1"
#define DATOS_PC_TIEMPO_REFRESCO_MS  600000 //10 minutos
// Network interface
EthernetInterface eth;
TCPSocket socket;
UDPSocket udpsocket;

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============


//=====[Declaration and initialization of private global variables]============
static int tiempoRefrescoDatosPC = DATOS_PC_TIEMPO_REFRESCO_MS;
//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void inicioEthernet()
{
eth.set_network(IP, NETMASK, GATEWAY);
// Brings up the network interface
eth.connect();
const char *ip = eth.get_ip_address();
const char *mac = eth.get_mac_address();
//printf("Direccion IP: %s\n", ip ? ip : "Sin IP");
//printf("MAC address: %s\n", mac ? mac : "Sin MAC");
	
}

//=====[Implementations of private functions]==================================

void enviarPCValorElectrovalvula(electrovalvulaEstado_t  Estado)
{
	TCPSocket socket;
    socket.open(&eth);
    
    SocketAddress a;
    eth.gethostbyname(IP_SERVER, &a);
    a.set_port(4000);
    socket.connect(a);
    
    // Envio GET con accion
    char sbuffer[] = "GET /accion?accion=   HTTP/1.1\r\nHost: 192.168.1.130\r\n\r\n";
    if (Estado == ENCENDIDA)
    {
    	strcpy(sbuffer, "GET /accion?accion=ON HTTP/1.1\r\nHost: 192.168.1.130\r\n\r\n");
    }
    if (Estado == PARADA)
    {
    	strcpy(sbuffer, "GET /accion?accion=OFF HTTP/1.1\r\nHost: 192.168.1.130\r\n\r\n");
    }    
    
    int scount = socket.send(sbuffer, sizeof sbuffer);
    
    char rbuffer[100];
    int rcount = socket.recv(rbuffer, sizeof rbuffer);

    // Cierro la conexion
    socket.close();
    
}

void enviarDatosSensoresPC()
{
	char stringTemperatura[2];
	char stringHumedad[3];  

	TCPSocket socket;
    socket.open(&eth);
    
    SocketAddress a;
    eth.gethostbyname(IP_SERVER, &a);
    a.set_port(4000);
    socket.connect(a);
    
    // Envio GET con accion
 	char sbuffer[100];
    sprintf(stringTemperatura, "%.0f", sensorDHTTemperatura());
    sprintf(stringHumedad, "%.0f", sensorDHTHumedad());
    sprintf(sbuffer,"%s%s%s%s%s",  "GET /sensores?temp=",stringTemperatura,"&hum=",stringHumedad ," HTTP/1.1\r\nHost: 192.168.1.130\r\n\r\n");
	   
    int scount = socket.send(sbuffer, sizeof sbuffer);
    
    char rbuffer[100];
    int rcount = socket.recv(rbuffer, sizeof rbuffer);
    
    // Cierro la conexion
    socket.close();
	
	
}

void actualizarDatosSensoresPC()
{
	static int tiempoAcumulado = 0;
    
    if( tiempoAcumulado >=
        tiempoRefrescoDatosPC ) {

        tiempoAcumulado = 0;
        enviarDatosSensoresPC();
        
   } else {
        tiempoAcumulado =
            tiempoAcumulado + SYSTEM_TIME_INCREMENT_MS;        
    }  
}