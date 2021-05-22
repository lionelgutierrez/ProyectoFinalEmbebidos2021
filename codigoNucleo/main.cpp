//=====[Libraries]=============================================================

#include "sistema_riego.h"

//=====Punto de entrada del sistema. Todo se gestinoa desde la libreria sistema_riego========

int main()
{
    inicioSistemaRiego();
    while (true) {
        actualizarSistemaRiego();
    }
}