#ifndef DATA_H
#define DATA_H

#include <Arduino.h>

enum AvionCommand
{
    AVION1,    
    AVION2,  
    AVION3, 
    AVION4,
    AVION5
};

// Devuelve un comando avion aleatorio
AvionCommand randomCommand();

#endif
