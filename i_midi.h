// Copyright © 1998, Bruce A. Lewis
// This code may not be re-used in a commercial product
// of any kind without express written consent from
// the author, Bruce A. Lewis.
//
#ifndef MIDIDEF
   #define MIDIDEF 1

typedef enum { midi_nofile, midi_stop, midi_play, midi_pause } midi_state;

typedef struct
   {
    DWORD    MidiPosition;
    DWORD    MidiDevice;
    DWORD    MidiStatus;
    MCIERROR MidiError;
    char     szMidiFile[128];
   }MIDI_Data_t;

BOOL  MidiPlay(HWND hWnd, MIDI_Data_t *mdd);
BOOL  MidiReplay(HWND hWnd, MIDI_Data_t *mdd);
BOOL  MidiPause(HWND hWnd, MIDI_Data_t *mdd);
BOOL  MidiResume(HWND hWnd, MIDI_Data_t *mdd);
void  MidiStop(MIDI_Data_t *mdd);

#endif
