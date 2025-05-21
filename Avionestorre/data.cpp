#include "data.h"

AvionCommand avionCommands[5] = {
  AVION1,AVION2,AVION3,AVION4,AVION5};

AvionCommand randomCommand()
{
    return avionCommands[random(0, 5)];
}