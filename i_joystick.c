#define INCL_DOSFILEMGR         // include needed for DosOpen call
#define INCL_DOSDEVICES         // include needed for DosDevIOCtl call
#define INCL_DOSDEVIOCTL        // include needed for DosDevIOCtl call
#include <os2.h>

#include <memory.h>

#include "i_joystick.h"


HFILE hJoystick;     // game port file handle

int JoystickOn(void)
{
   ULONG action;    // return value from DosOpen

   return DosOpen(GAMEPDDNAME, &hJoystick, &action, 0, FILE_READONLY, FILE_OPEN, OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL);
}

void JoystickOff(void)
{
   if (hJoystick)
     {
      DosClose(hJoystick);
      hJoystick = 0;
     }
}

int JoystickValues(JOYSTICK_STATUS * stick)
{
   GAME_STATUS_STRUCT gameStatus;
   ULONG dataLen = sizeof(GAME_STATUS_STRUCT);
   APIRET rc = 0;

   if (!hJoystick)
      return 0;

   rc = DosDevIOCtl(hJoystick, IOCTL_CAT_USER, GAME_GET_STATUS_SAMPWAIT, NULL, 0, NULL, &gameStatus, dataLen, &dataLen);

   if (rc)
      return 0;

   memset( stick, 0, sizeof(JOYSTICK_STATUS) );

   stick->Joy1X = (gameStatus.curdata.A.x > 400) ? 1 : ( (gameStatus.curdata.A.x < 200) ? -1 : 0 ) ;
   stick->Joy1Y = (gameStatus.curdata.A.y > 400) ? 1 : ( (gameStatus.curdata.A.y < 200) ? -1 : 0 ) ;
   stick->Joy2X = (gameStatus.curdata.B.x > 400) ? 1 : ( (gameStatus.curdata.B.x < 200) ? -1 : 0 ) ;
   stick->Joy2Y = (gameStatus.curdata.B.y > 400) ? 1 : ( (gameStatus.curdata.B.y < 200) ? -1 : 0 ) ;

   stick->Joy1A = !(gameStatus.curdata.butMask & 0x10);
   stick->Joy1B = !(gameStatus.curdata.butMask & 0x20);
   stick->Joy2A = !(gameStatus.curdata.butMask & 0x40);
   stick->Joy2B = !(gameStatus.curdata.butMask & 0x80);

   return TRUE;
}
