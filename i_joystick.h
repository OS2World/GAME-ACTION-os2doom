#include "joyos2.h"

typedef struct
{
   int Joy1X;
   int Joy1Y;
   int Joy1A;
   int Joy1B;
   int Joy2X;
   int Joy2Y;
   int Joy2A;
   int Joy2B;
} JOYSTICK_STATUS;

int JoystickOn(void);
int JoystickValues(JOYSTICK_STATUS * stick);
void JoystickOff(void);

