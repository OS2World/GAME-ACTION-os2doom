// i_cd.c
// Copyright © 1998, Bruce A. Lewis
// This code may not be re-used in a commercial product
// of any kind without express written consent from
// the author, Bruce A. Lewis.
//
// Global define needed for calling these functions
#include <stdio.h>

#include "windows.h"
#include "i_cd.h"

// Local define needed only for error message capture and display
#define     MCIMSGLEN  256
char        CDmsg[MCIMSGLEN+32];

BOOL CDOpen(HWND hWnd, CD_Data_t *cdd)
   {
    cdd->CDError = mciSendString( "open cdaudio01 alias cdmusic shareable wait", 0, 0, 0, 'C' );

    if (cdd->CDError)
       {
        mciGetErrorString(cdd->CDError, CDmsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, CDmsg, "Open CD", 0, MB_ICONHAND | MB_OK);
        return(FALSE);
       }

    return(TRUE);
   }

BOOL CDCheck(HWND hWnd, CD_Data_t *cdd)
   {
    char szReturn[128];

    if ( cdd->CDError )
       return FALSE;

    cdd->CDError = mciSendString( "status cdmusic media present wait", szReturn, 128, 0, 'C' );

    if (cdd->CDError)
       {
        mciGetErrorString(cdd->CDError, CDmsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, CDmsg, "Check CD", 0, MB_ICONHAND | MB_OK);
        return(FALSE);
       }

    cdd->CDMedia = (strcmp(szReturn,"TRUE") == 0);
    return(TRUE);
   }

BOOL CDMediaIdentity(HWND hWnd, CD_Data_t *cdd, char *szIdent)
   {
    char szReturn[128];

    if ( cdd->CDError )
       return FALSE;

    cdd->CDError = mciSendString( "info cdmusic product wait", szReturn, 128, 0, 'C' );

    if (cdd->CDError)
       {
        mciGetErrorString(cdd->CDError, CDmsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, CDmsg, "Product CD", 0, MB_ICONHAND | MB_OK);
        return(FALSE);
       }

    strcpy( szIdent, szReturn );
    return(TRUE);
   }


BOOL CDTrackCount(HWND hWnd, CD_Data_t *cdd)
   {
    char szReturn[128];

    if ( cdd->CDError )
       return FALSE;

    cdd->CDTrackCount = 0;
    cdd->CDError = mciSendString( "status cdmusic number of tracks wait", szReturn, 128, 0, 'C' );

    if (cdd->CDError)
       {
        mciGetErrorString(cdd->CDError, CDmsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, CDmsg, "Track Count CD", 0, MB_ICONHAND | MB_OK);
        return(FALSE);
       }

    cdd->CDTrackCount = atoi(szReturn);
    return(TRUE);
   }

BOOL CDTrackType(HWND hWnd, CD_Data_t *cdd)
   {
    char szCommand[128];
    char szReturn[128];

    if ( cdd->CDError )
       return FALSE;

    sprintf( szCommand, "status cdmusic type track %d wait", cdd->CDTrack+1 );

    cdd->CDError = mciSendString( szCommand, szReturn, 128, 0, 'C' );

    if (cdd->CDError)
       {
        mciGetErrorString(cdd->CDError, CDmsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, CDmsg, "Track Type CD", 0, MB_ICONHAND | MB_OK);
        return(FALSE);
       }

    if ( strcmp(szReturn,"audio") == 0)
        cdd->CDTrackList[cdd->CDTrack] = MCI_CD_TRACK_AUDIO;
    else
        cdd->CDTrackList[cdd->CDTrack] = MCI_CD_TRACK_DATA;
    return(TRUE);
   }

BOOL CDTrackPlay(HWND hWnd, CD_Data_t *cdd)
   {
    char szCommand[128];
    char szReturn[128];
    ULONG ulTo;
    ULONG ulFrom;

    if ( cdd->CDError )
       return FALSE;

    cdd->CDError = mciSendString( "set cdmusic time format tmsf wait", 0, 0, 0, 'C' );

    ulTo = 0;
    ulFrom = 0;
    TMSF_TRACK(ulFrom) = cdd->CDTrack+1;
    TMSF_TRACK(ulTo) = cdd->CDTrack+2;

    if (cdd->CDTrack == (cdd->CDTrackCount-1))
       {
        sprintf( szCommand, "play cdmusic from %ld notify", ulFrom );
        cdd->CDError = mciSendString( szCommand, szReturn, 128, hWnd, 'C' );
       }
    else
       {
        sprintf( szCommand, "play cdmusic from %ld to %ld notify", ulFrom, ulTo );
        cdd->CDError = mciSendString( szCommand, szReturn, 128, hWnd, 'C' );
       }

    if (cdd->CDError)
       {
        mciGetErrorString(cdd->CDError, CDmsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, CDmsg, "Track Play CD", 0, MB_ICONHAND | MB_OK);
        return(FALSE);
       }
    cdd->CDStatus = cd_play;
    return(TRUE);
   }

BOOL CDPause(HWND hWnd, CD_Data_t *cdd)
   {
    if ( cdd->CDError )
       return FALSE;

    cdd->CDError = mciSendString( "pause cdmusic notify", 0, 0, hWnd, 'C' );

    if (cdd->CDError)
       {
        mciGetErrorString(cdd->CDError, CDmsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, CDmsg, "Pause CD", 0, MB_ICONHAND | MB_OK);
        return(FALSE);
       }
    cdd->CDStatus = cd_pause;
    return(TRUE);
   }

BOOL CDResume(HWND hWnd, CD_Data_t *cdd)
   {
    if ( cdd->CDError )
       return FALSE;

    cdd->CDError = mciSendString( "resume cdmusic notify", 0, 0, hWnd, 'C' );

    if (cdd->CDError)
       {
        mciGetErrorString(cdd->CDError, CDmsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, CDmsg, "Resume CD", 0, MB_ICONHAND | MB_OK);
        return(FALSE);
       }
    cdd->CDStatus = cd_play;
    return(TRUE);
   }

void CDStop(CD_Data_t *cdd)
   {
    if ( cdd->CDError )
       return;

    mciSendString("stop cdmusic", 0, 0, 0, 'C');
    cdd->CDStatus = cd_stop;
   }

void CDClose(CD_Data_t *cdd)
   {
    if ( cdd->CDError )
       return;

    mciSendString("close cdmusic", 0, 0, 0, 'C');
   }

