// Copyright © 1998, Bruce A. Lewis
// This code may not be re-used in a commercial product
// of any kind without express written consent from
// the author, Bruce A. Lewis.
//
#ifndef CDDEF
   #define CDDEF 1

// Global define needed for calling these functions

typedef enum { cd_stop, cd_play, cd_pause, cd_empty } cdstate;

typedef struct
   {
    BOOL     CDMedia;
    char     CDCode[18];
    DWORD    CDPosition;
    DWORD    CDDevice;
    DWORD    CDTrack;
    DWORD    CDTrackCount;
    DWORD    CDStatus;
    DWORD    CDTrackList[32];
    MCIERROR CDError;
   }CD_Data_t;

BOOL  CDOpen(HWND hWnd, CD_Data_t *cdd);
BOOL  CDCheck(HWND hWnd, CD_Data_t *cdd);
BOOL  CDMediaIdentity(HWND hWnd, CD_Data_t *cdd, char *szIdent);
BOOL  CDTrackCount(HWND hWnd, CD_Data_t *cdd);
BOOL  CDTrackType(HWND hWnd, CD_Data_t *cdd);
BOOL  CDTrackPlay(HWND hWnd, CD_Data_t *cdd);
BOOL  CDPause(HWND hWnd, CD_Data_t *cdd);
BOOL  CDResume(HWND hWnd, CD_Data_t *cdd);
void  CDStop(CD_Data_t *cdd);
void  CDClose(CD_Data_t *cdd);

#endif

