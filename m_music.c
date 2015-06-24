// Copyright © 1998, Bruce A. Lewis
// This code may not be re-used in a commercial product
// of any kind without express written consent from
// the author, Bruce A. Lewis.
//
/////////////////////////////////////////////////////////////////////////////////////
// Windows Includes...
/////////////////////////////////////////////////////////////////////////////////////
#include "windows.h"

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>

#include "i_cd.h"      // My own cdaudio "library"
#include "i_midi.h"    // My own midi "library"

extern HWND hClient;
char MsgText[256];

void WriteDebug(char *);

CD_Data_t   CDData;
MIDI_Data_t MidiData;

void GetCDInfo(HWND hWnd)
   {
    int  i;
    char cdName[32];

    if (CDData.CDDevice == 0)
       {
        CDOpen(hWnd, &CDData);
        sprintf(MsgText, "CDDevice ID = %X\n", CDData.CDDevice);
        WriteDebug(MsgText);
       }
    CDCheck(hWnd, &CDData);
    if (CDData.CDMedia == FALSE)
       {
        WriteDebug("CD Player is empty...\n");
        CDData.CDTrack = 0;
        CDData.CDTrackCount = 0;
        for (i = 0; i < 32; i++)
           CDData.CDTrackList[i] = 0;
        CDData.CDStatus = cd_empty;
       }
    else
       {
        WriteDebug("CD Player has a CD in it...\n");
        CDMediaIdentity(hWnd, &CDData, cdName);
        cdName[16] = '\0';
        sprintf(MsgText, "CD Hex ID = %s\n", cdName);
        WriteDebug(MsgText);
        if (strcmp(CDData.CDCode, cdName) != 0)
           {
            strcpy(CDData.CDCode, cdName);
            CDData.CDStatus = cd_stop;
            CDTrackCount(hWnd, &CDData);
            sprintf(MsgText, "Number of Tracks = %d\n", CDData.CDTrackCount);
            WriteDebug(MsgText);
            for (CDData.CDTrack = 0; CDData.CDTrack < CDData.CDTrackCount; CDData.CDTrack++)
               {
                CDTrackType(hWnd, &CDData);
                if (CDData.CDTrackList[CDData.CDTrack] == MCI_CD_TRACK_AUDIO)
                   sprintf(MsgText, "Track %d : Audio\n", CDData.CDTrack, CDData.CDTrackList[CDData.CDTrack]);
                else
                   sprintf(MsgText, "Track %d : Data\n", CDData.CDTrack, CDData.CDTrackList[CDData.CDTrack]);
                WriteDebug(MsgText);
               }
            if (CDData.CDTrackList[0] == MCI_CD_TRACK_AUDIO)
               CDData.CDTrack = 0;
            else
               CDData.CDTrack = 1;
            if (CDData.CDTrack == CDData.CDTrackCount)
               {
                CDData.CDTrackCount = 0;
                CDData.CDTrack = 0;
                CDData.CDStatus = cd_empty;
               }
           }
       }
   }

void PlayCDMusic()
   {
    if ((CDData.CDStatus != cd_play) && (CDData.CDStatus != cd_pause))
       {
        if (CDData.CDStatus == cd_empty)
           GetCDInfo(hClient);
        else
           {
            CDCheck(hClient, &CDData);
            if (CDData.CDMedia == FALSE)
                GetCDInfo(hClient);
           }
        if (CDData.CDStatus != cd_empty)
           {
            if (MidiData.MidiStatus != midi_stop)
               {
                MidiStop(&MidiData);
                CDTrackPlay(hClient, &CDData);
                CDData.CDStatus = cd_play;
               }
           }
       }
   }

void PlayCDTrack(int track)
   {
    if ((MidiData.MidiStatus != midi_play) && (MidiData.MidiStatus != midi_pause))
       {
        if ((track < 0) || (track > CDData.CDTrackCount))
           return;
        if (CDData.CDTrackList[track] == MCI_CD_TRACK_AUDIO)
           {
            CDData.CDTrack = track;
            CDTrackPlay(hClient, &CDData);
           }
       }
   }

void PlayMidiFile(char *song)
   {
    strcpy(MidiData.szMidiFile, song);
    MidiPlay(hClient, &MidiData);
   }

void PlayMidiMusic()
   {
    if ((CDData.CDStatus != cd_stop) && (CDData.CDStatus != cd_empty))
       {
        CDStop(&CDData);
        CDData.CDStatus = cd_stop;
       }
    if ((MidiData.MidiStatus != midi_play) && (MidiData.MidiStatus != midi_pause))
       {
        MidiPlay(hClient, &MidiData);
       }
   }


void PauseResumeMusic()
   {
    switch(MidiData.MidiStatus)
       {
        case midi_play:
             MidiPause(hClient, &MidiData);
             break;
        case midi_pause:
             MidiResume(hClient, &MidiData);
             break;
       }
    if ((CDData.CDStatus == cd_play) || (CDData.CDStatus == cd_pause))
       {
        if (CDData.CDStatus == cd_empty)
           {
            GetCDInfo(hClient);
           }
        else
           {
            CDCheck(hClient, &CDData);
            if (CDData.CDMedia == FALSE)
               {
                GetCDInfo(hClient);
                CDData.CDTrack = CDData.CDTrackCount;
               }
           }
       }
    switch(CDData.CDStatus)
       {
        case cd_play:
             CDPause(hClient, &CDData);
             CDData.CDStatus = cd_pause;
             break;
        case cd_pause:
             CDResume(hClient, &CDData);
             CDData.CDStatus = cd_play;
             break;
       }
   }

void PlayNextSong()
   {
    if ((MidiData.MidiStatus != midi_play) && (MidiData.MidiStatus != midi_pause))
       {
        if (CDData.CDStatus == cd_empty)
           {
            GetCDInfo(hClient);
           }
        else
           {
            CDCheck(hClient, &CDData);
            if (CDData.CDMedia == FALSE)
               {
                GetCDInfo(hClient);
                CDData.CDTrack = CDData.CDTrackCount;
               }
           }
        if (CDData.CDTrackCount != 0)
           {
            if (CDData.CDStatus != cd_stop)
                CDStop(&CDData);
            CDData.CDTrack++;
            if (CDData.CDTrack >= CDData.CDTrackCount)
                CDData.CDTrack = 0;
            while(CDData.CDTrackList[CDData.CDTrack] != MCI_CD_TRACK_AUDIO)
               {
                CDData.CDTrack++;
                if (CDData.CDTrack >= CDData.CDTrackCount)
                    CDData.CDTrack = 0;
               }
            CDTrackPlay(hClient, &CDData);
            CDData.CDStatus = cd_play;
           }
       }
   }

void PlayPrevSong()
   {
    if ((MidiData.MidiStatus != midi_play) && (MidiData.MidiStatus != midi_pause))
       {
        if (CDData.CDStatus == cd_empty)
           {
            GetCDInfo(hClient);
           }
        else
           {
            CDCheck(hClient, &CDData);
            if (CDData.CDMedia == FALSE)
               {
                GetCDInfo(hClient);
                CDData.CDTrack = CDData.CDTrackCount;
               }
           }
        if (CDData.CDTrackCount != 0)
           {
            if (CDData.CDStatus != cd_stop)
                CDStop(&CDData);
            CDData.CDTrack--;
            if (CDData.CDTrack <= 0)
                CDData.CDTrack = CDData.CDTrackCount;
            while(CDData.CDTrackList[CDData.CDTrack] != MCI_CD_TRACK_AUDIO)
               {
                CDData.CDTrack--;
                if (CDData.CDTrack < 0 )
                    CDData.CDTrack = CDData.CDTrackCount;
               }
            CDTrackPlay(hClient, &CDData);
            CDData.CDStatus = cd_play;
           }
       }
   }

void StopMusic()
   {
    if ((CDData.CDStatus != cd_stop) && (CDData.CDStatus != cd_empty))
       {
        CDStop(&CDData);
        CDClose(&CDData);
       }
    if (MidiData.MidiStatus != midi_stop)
       {
        MidiStop(&MidiData);
       }
   }

