/////////////////////////////////////////////////////////////////////////////////////
// DirectX Includes...
/////////////////////////////////////////////////////////////////////////////////////
#include "windows.h"
#include <stdio.h>

void WriteDebug(char *);

void DS_Error( ULONG hresult, char *msg )
   {
    char msgtext[128];
    char errmsg[128];

    sprintf(errmsg,"Error Code: %04X", hresult);
    strcpy(errmsg, msgtext);
    sprintf(msgtext, "DSERR: %s\n", errmsg);
    WriteDebug( msgtext );
    sprintf(msgtext, "%s FAILED\n", msg);
    WriteDebug( msgtext );
   }

void DD_Error( ULONG hresult, char *msg )
   {
    static char msgtext[128];
    static char errmsg[128];

    sprintf(errmsg, "Error Code : %04X", hresult);
    sprintf(msgtext, "DDERR: %s\n", errmsg);
    WriteDebug( msgtext );
    sprintf(msgtext, "%s FAILED\n", msg);
    WriteDebug( msgtext );
   }

void DI_Error( ULONG hresult, char *msg)
   {
    char msgtext[512];
    char errmsg[512];

    sprintf(errmsg, "Error Code : %04X", hresult);
    sprintf(msgtext, "DIERR: %s\n", errmsg);
    WriteDebug( msgtext );
    sprintf(msgtext, "%s FAILED\n", msg);
    WriteDebug( msgtext );
   }


