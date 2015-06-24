// Copyright © 1998, Bruce A. Lewis
// This code may not be re-used in a commercial product
// of any kind without express written consent from
// the author, Bruce A. Lewis.
//
// Global define needed for calling these functions
#include "windows.h"

#include <stdio.h>

#include "i_midi.h"
#include "io.h"

// Local define needed only for error message capture and display
#define     MCIMSGLEN  128
char        MidiMsg[MCIMSGLEN+1];

BOOL MidiPlay(HWND hWnd, MIDI_Data_t *mdd)
   {
    char szCommandString[128];
    ULONG ulRC;

    if (access(mdd->szMidiFile, 4) != 0)
       {
        mdd->MidiStatus = midi_nofile;
        return(FALSE);
       }

    sprintf( szCommandString, "open %s alias doomsong wait", mdd->szMidiFile );
    ulRC = mciSendString( szCommandString, 0, 0, 0, 'M' );

    if (ulRC)
       {
        mciGetErrorString(ulRC, MidiMsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, MidiMsg, "MIDI Open", 0, MB_ICONHAND | MB_OK);
        mdd->MidiError = ulRC;
        return(FALSE);
       }

    strcpy( szCommandString, "play doomsong" );
    ulRC = mciSendString( szCommandString, 0, 0, hWnd, 'M' );
    if (ulRC)
       {
        mciGetErrorString(ulRC, MidiMsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, MidiMsg, "MIDI Play", 0, MB_ICONHAND | MB_OK);
        strcpy( szCommandString, "close doomsong wait" );
        mciSendString( szCommandString, 0, 0, 0, 'M' );
        mdd->MidiError = ulRC;
        return(FALSE);
       }

    mdd->MidiStatus = midi_play;
    return(TRUE);
   }

BOOL MidiReplay(HWND hWnd, MIDI_Data_t *mdd)
   {
    char szCommandString[128];
    ULONG ulRC;

    strcpy( szCommandString, "play doomsong" );
    ulRC = mciSendString( szCommandString, 0, 0, hWnd, 'M' );
    if (ulRC)
       {
        mciGetErrorString(ulRC, MidiMsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, MidiMsg, "MIDI Replay", 0, MB_ICONHAND | MB_OK);
        strcpy( szCommandString, "close doomsong wait" );
        mciSendString( szCommandString, 0, 0, 0, 'M' );
        mdd->MidiError = ulRC;
        return(FALSE);
       }

    return(TRUE);
   }

BOOL MidiPause(HWND hWnd, MIDI_Data_t *mdd)
   {
    char szCommandString[128];
    ULONG ulRC;

    strcpy( szCommandString, "pause doomsong" );
    ulRC = mciSendString( szCommandString, 0, 0, hWnd, 'M' );
    if (ulRC)
       {
        mciGetErrorString(ulRC, MidiMsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, MidiMsg, "MIDI Resume", 0, MB_ICONHAND | MB_OK);
        strcpy( szCommandString, "close doomsong wait" );
        mciSendString( szCommandString, 0, 0, 0, 'M' );
        mdd->MidiError = ulRC;
        return(FALSE);
       }
    mdd->MidiStatus = midi_pause;
    return(TRUE);
   }

BOOL MidiResume(HWND hWnd, MIDI_Data_t *mdd)
   {
    char szCommandString[128];
    ULONG ulRC;

    strcpy( szCommandString, "resume doomsong" );
    ulRC = mciSendString( szCommandString, 0, 0, hWnd, 'M' );
    if (ulRC)
       {
        mciGetErrorString(ulRC, MidiMsg, MCIMSGLEN);
        WinMessageBox(HWND_DESKTOP, hWnd, MidiMsg, "MIDI Pause", 0, MB_ICONHAND | MB_OK);
        strcpy( szCommandString, "close doomsong wait" );
        mciSendString( szCommandString, 0, 0, 0, 'M' );
        mdd->MidiError = ulRC;
        return(FALSE);
       }
    mdd->MidiStatus = midi_play;
    return(TRUE);
   }

void MidiStop(MIDI_Data_t *mdd)
   {
    char szCommandString[128];
    ULONG ulRC;

    strcpy( szCommandString, "stop doomsong wait" );
    mciSendString( szCommandString, 0, 0, 0, 'M' );
    strcpy( szCommandString, "close doomsong wait" );
    mciSendString( szCommandString, 0, 0, 0, 'M' );
    mdd->MidiStatus = midi_stop;
   }

