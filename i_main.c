
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log:$
//
// DESCRIPTION:
//	Main program, simply calls D_DoomMain high level loop.
//
//-----------------------------------------------------------------------------

static const char
rcsid[] = "$Id: i_main.c,v 1.4 1997/02/03 22:45:10 b1 Exp $";

/////////////////////////////////////////////////////////////////////////////////////
// Windows Includes...
/////////////////////////////////////////////////////////////////////////////////////
#define INCL_PM
#define INCL_GPI
#define INCL_DOS
#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES
#define INCL_DOSMODULEMGR
#define INCL_WINERRORS
#define INCL_GRE_COLORTABLE
#define INCL_GRE_DEVMISC3
#include "windows.h"
#define  _MEERROR_H_
#include <mmioos2.h>                    /* It is from MMPM toolkit           */
#include <dive.h>
#include <fourcc.h>

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>

#include "i_joystick.h"

#include "doomdef.h"
#include "doomstat.h"
#include "d_event.h"
#include "d_main.h"
#include "m_argv.h"
#include "g_game.h"
#include "i_system.h"
#include "m_music.h"
#include "i_cd.h"
#include "i_midi.h"
#include "dxerr.h"

#include "d_console.h"

#include "v_video.h"


extern int    always_run;
extern int    mvert;
extern int    keylink;

extern int    joyb1;
extern int    joyb2;
extern int    joyb3;
extern int    joyb4;
extern int    mouseb1;
extern int    mouseb2;
extern int    mouseb3;

static HDIVE             hDive;
static SETUP_BLITTER     SetupBlitter;
static ULONG             ulImage;
static BOOL              fVrnDisabled;
static ULONG             ulColors;
static DIVE_CAPS         DiveCaps = {0};
static FOURCC            fccFormats[100] = {0};
static RGB2              rgbPalette[256];

int MY_SCREENWIDTH = 320;
int MY_SCREENHEIGHT = 200;

void RenderScene(void);

BOOL SetupDIVE(void);
void ShutdownDIVE(void);

// this structure holds a RGB triple in three unsigned bytes
typedef struct RGB_color_typ
   {
    unsigned char red;      // red   component of color 0-63
    unsigned char green;    // green component of color 0-63
    unsigned char blue;     // blue  component of color 0-63
   }xRGB_color, *xRGB_color_ptr;

// this structure holds an entire color palette
typedef struct xRGB_palette_typ
   {
    int start_reg;          // index of the starting register that is save
    int end_reg;            // index of the ending registe that is saved
    xRGB_color colors[256];  // the storage area for the palette
   }xRGB_palette, *xRGB_palette_ptr;

xRGB_palette xpal;

/////////////////////////////////////////////////////////////////////////////////////
// Application Defines and Data
/////////////////////////////////////////////////////////////////////////////////////

#define MUSIC_NONE      0
#define MUSIC_CDAUDIO   1
#define MUSIC_MIDI      2

/////////////////////////////////////////////////////////////////////////////////////
// Game states -- these are the modes in which the outer game loop can be
/////////////////////////////////////////////////////////////////////////////////////
#define GAME_START  0
#define GAME_SPLASH 1
#define GAME_MENU   2
#define GAME_PLAY   3
#define GAME_EXIT   4
#define GAME_QUIT   5
#define GAME_LIMBO  6
#define GAME_PAUSE  7

int     GameMode = GAME_START;

extern byte *screens[5];

extern int usemouse;
extern int usejoystick;
int joystickenabled;

short     si_Kbd[256];

char      szMsgText[256];

extern    CD_Data_t   CDData;
extern    MIDI_Data_t MidiData;

char        szMidiFile[] = "doomsong.mid";

int         MusicType = MUSIC_MIDI;

void  WriteDebug(char *);

char *YesNo[] = { "No", "Yes" };

void  D_DoomMain(void);
void *W_CacheLumpName(char *, int);
void  I_SetPalette(byte *);
void  MY_DoomSetup(void);
void  MY_DoomLoop(void);

/////////////////////////////////////////////////////////////////////////////////////
// Windows Defines and Data
/////////////////////////////////////////////////////////////////////////////////////
MRESULT EXPENTRY WndProc( HWND hwnd, ULONG iMsg, MPARAM wParam, MPARAM lParam );

char      szAppName[] = "OS2Doom";
char      szDbgName[] = "OS2Doom.dbg";
char      szCfgName[] = "OS2Doom.cfg";

HWND      hFrame;
HWND      hClient;

#ifdef LINUXDOOM
int
main
( int		argc,
  char**	argv ) 
{ 
    myargc = argc; 
    myargv = argv; 
 
    D_DoomMain (); 

    return 0;
} 
#endif

void CheckJoystickEvent(void)
{
    JOYSTICK_STATUS             diJoyState;
    static JOYSTICK_STATUS      diHoldJoy;
    ULONG          hresult;
    static  event_t  event;
    static  event_t  mbevent;
    static  event_t  jbevent;

    if (joystickenabled == TRUE /* && usejoystick == TRUE */)
       {
        hresult = JoystickValues(&diJoyState);

        if (hresult)
           {
            if (diJoyState.Joy1X != diHoldJoy.Joy1X || diJoyState.Joy1Y != diHoldJoy.Joy1Y ||
                diJoyState.Joy1A != diHoldJoy.Joy1A || diJoyState.Joy1B != diHoldJoy.Joy1B ||
                diJoyState.Joy2A != diHoldJoy.Joy2A || diJoyState.Joy2B != diHoldJoy.Joy2B)
               {
                event.type = ev_joystick;
                event.data1 = 0;

                if (joyb1 == 0)
                    event.data1 |= diJoyState.Joy1A;
                else if (diHoldJoy.Joy1A != diJoyState.Joy1A)
                   {
                    jbevent.type = (diJoyState.Joy1A) ? ev_keydown : ev_keyup;
                    jbevent.data1 = joyb1;
                    D_PostEvent(&jbevent);
                   }

                if (joyb2 == 0)
                    event.data1 |= diJoyState.Joy1B << 1;
                else if (diHoldJoy.Joy1B != diJoyState.Joy1B)
                   {
                    jbevent.type = (diJoyState.Joy1B) ? ev_keydown : ev_keyup;
                    jbevent.data1 = joyb2;
                    D_PostEvent(&jbevent);
                   }

                if (joyb3 == 0)
                    event.data1 |= diJoyState.Joy2A << 2;
                else if (diHoldJoy.Joy2A != diJoyState.Joy2A)
                   {
                    jbevent.type = (diJoyState.Joy2A) ? ev_keydown : ev_keyup;
                    jbevent.data1 = joyb3;
                    D_PostEvent(&jbevent);
                   }

                if (joyb4 == 0)
                    event.data1 |= diJoyState.Joy2B << 3;
                else if (diHoldJoy.Joy2B != diJoyState.Joy2B)
                   {
                    jbevent.type = (diJoyState.Joy2B) ? ev_keydown : ev_keyup;
                    jbevent.data1 = joyb4;
                    D_PostEvent(&jbevent);
                   }

                if (diJoyState.Joy1X != diHoldJoy.Joy1X || diJoyState.Joy1Y != diHoldJoy.Joy1Y )
                   {
                    event.data2 = diJoyState.Joy1X * 1000;
                    event.data3 = diJoyState.Joy1Y * 1000;
                    D_PostEvent(&event);
                   }

                diHoldJoy = diJoyState;
               }
           }
       }
}

void _Optlink GameLoopThread(PVOID pvoid)
   {
    DosSetPriority(PRTYS_THREAD, PRTYC_IDLETIME, 0, 0);

    while (GameMode != GAME_QUIT)
       {
       CheckJoystickEvent();
       MY_DoomLoop();
       }

//    extern HWND hClient;
//    extern int GameMode;
//    extern int     demotype;
//    extern boolean demorecording;

    WriteDebug("Exiting OS2Doom...\n");

    D_QuitNetGame ();
    I_ShutdownSound();
    I_ShutdownMusic();
    M_SaveDefaults();
    I_ShutdownGraphics();

    if (demorecording)
       {
        if (demotype == DEMO_I)
           G_EndDemo();
        else
           G_EndDemo_II();
       }

    WinPostMsg( hClient, WM_CLOSE, 0, 0 );

    _endthread();
   }

void main(int argc, char *argv[])
   {
    HAB hab;
    HMQ hmq;
    ULONG flCreate;
    PPIB  ppib;
    PTIB  ptib;
    QMSG        msg;
    FILE       *fn;
    HWND        hwnd;
    int         i, k;
    int         p;

    DosGetInfoBlocks(&ptib,&ppib);
    ppib->pib_ultype = 3;

    hab = WinInitialize( 0 );
    hmq = WinCreateMsgQueue( hab, 0 );

    fn = fopen(szDbgName, "w");
    fclose(fn);

    WinRegisterClass( hab, szAppName, WndProc, CS_SIZEREDRAW, 0 );

    CDData.CDStatus = cd_empty;
    CDData.CDMedia = FALSE;
    CDData.CDPosition = 0;
    CDData.CDCode[0] = '\0';

    sprintf(szMsgText, "OS2Doom Version %2d.%02d\n", CONSVERS/100, CONSVERS%100);
    WriteDebug(szMsgText);

    flCreate = FCF_TITLEBAR   | 
//               FCF_SYSMENU    | 
//               FCF_MINBUTTON  | 
//               FCF_MAXBUTTON  | 
//               FCF_SIZEBORDER | 
               FCF_TASKLIST;

    hFrame = WinCreateStdWindow(
                        HWND_DESKTOP,
                        0,
                        &flCreate,
                        szAppName,
                        szMsgText,
                        WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                        0,
                        0x666,
                        &hClient
                        );

    myargc = argc;
    myargv = argv;

    p = M_CheckParm("-width");

    SCREENWIDTH = 320;
    SCREENHEIGHT = 200;

    if (p && p < myargc-1)
        MY_SCREENWIDTH = atoi(myargv[p+1]);

    if ( MY_SCREENWIDTH < 320 )
        MY_SCREENWIDTH = 320;

    p = M_CheckParm("-height");

    if (p && p < myargc-1)
        MY_SCREENHEIGHT = atoi(myargv[p+1]);

    if ( SCREENHEIGHT < 200 )
        MY_SCREENHEIGHT = 200;

    sprintf(szMsgText, "Resolution: %d x %d\n",MY_SCREENWIDTH,MY_SCREENHEIGHT);
    WriteDebug(szMsgText);

    WinSetWindowPos( hFrame, 
                     HWND_TOP, 
                     0,0,MY_SCREENWIDTH,MY_SCREENHEIGHT, 
                     SWP_SIZE | SWP_ACTIVATE | SWP_SHOW );

    SetupDIVE();

    D_DoomMain();
    MY_DoomSetup();
    GameMode = GAME_PLAY;
//    singletics = true;

    WinShowCursor( hClient, FALSE );

    _beginthread( GameLoopThread, 0, 16000, 0 );

    while( WinGetMsg( hab, &msg, 0L, 0, 0 ) )
        WinDispatchMsg( hab, &msg );

    GameMode = GAME_QUIT;

    DosSleep(100);

    WinShowCursor( hClient, TRUE );

    ShutdownDIVE();

    for (i = 4; i >= 0; i--)
        free(screens[i]);

    WinDestroyWindow( hFrame );

    WinDestroyMsgQueue( hmq );

    WinTerminate( hab );

    exit(0);
   }

MRESULT EXPENTRY WndProc( HWND hwnd, ULONG iMsg, MPARAM mp1, MPARAM mp2 )
   {
    static event_t     event;
    static RECTL      rcls[50];

    HPS     hps;
    SWP     swp;
    RECTL   rcl;
    HRGN    hrgn;
    RGNRECT rgnCtl;
    POINTL  pointl;

    switch(iMsg)
       {
      case WM_VRNDISABLED:
          fVrnDisabled = TRUE;
          DiveSetupBlitter ( hDive, 0 );
          break;

      case WM_VRNENABLED:
          hps  = WinGetPS ( hwnd );
          hrgn = GpiCreateRegion ( hps, 0L, NULL );

          WinQueryVisibleRegion ( hwnd, hrgn );

          rgnCtl.ircStart     = 1;
          rgnCtl.crc          = 50;
          rgnCtl.ulDirection  = 1;

          // Get the all ORed rectangles

          GpiQueryRegionRects ( hps, hrgn, NULL, &rgnCtl, rcls);

          GpiDestroyRegion( hps, hrgn );

          WinReleasePS( hps );

          // Now find the window position and size, relative to parent.

          WinQueryWindowPos ( hwnd, &swp );

          // Convert the point to offset from desktop lower left.

          pointl.x = swp.x;
          pointl.y = swp.y;

          WinMapWindowPoints ( hFrame, HWND_DESKTOP, &pointl, 1 );

          // Tell DIVE about the new settings.

          SetupBlitter.ulStructLen       = sizeof( SETUP_BLITTER );
          SetupBlitter.fccSrcColorFormat = FOURCC_LUT8;
          SetupBlitter.ulSrcWidth        = MY_SCREENWIDTH;
          SetupBlitter.ulSrcHeight       = MY_SCREENHEIGHT;
          SetupBlitter.ulSrcPosX         = 0;
          SetupBlitter.ulSrcPosY         = 0;
          SetupBlitter.fInvert           = TRUE;
          SetupBlitter.ulDitherType      = 1;

          SetupBlitter.fccDstColorFormat = FOURCC_SCRN;
          SetupBlitter.ulDstWidth        = swp.cx;
          SetupBlitter.ulDstHeight       = swp.cy;
          SetupBlitter.lDstPosX          = 0;
          SetupBlitter.lDstPosY          = 0;
          SetupBlitter.lScreenPosX       = pointl.x;
          SetupBlitter.lScreenPosY       = pointl.y;

          SetupBlitter.ulNumDstRects     = rgnCtl.crcReturned;
          SetupBlitter.pVisDstRects      = rcls;

          DiveSetupBlitter ( hDive, &SetupBlitter );
          fVrnDisabled = FALSE;
          break;

      case WM_REALIZEPALETTE:
          // This tells DIVE that the physical palette may have changed.
          DiveSetDestinationPalette ( hDive, 0, 0, 0 );
          break;

        case MM_MCINOTIFY:
             switch ( SHORT2FROMMP(mp1) )
                {
                case 'C':
                   if (SHORT1FROMMP(mp1) == MCI_NOTIFY_SUCCESSFUL)
                      CDTrackPlay(hwnd, &CDData);
                   break;
                case 'M':
                   if (SHORT1FROMMP(mp1) == MCI_NOTIFY_SUCCESSFUL)
                      MidiReplay(hwnd, &MidiData);
                   break;
                case 'W':
                   // I_StopSound(0);
                   break;
                }
             break;

       case WM_CHAR:
            if ( !( CHARMSG(&iMsg)->fs & KC_VIRTUALKEY ) ||
                 ( SHORT2FROMMP(mp1) != VK_SHIFT && SHORT2FROMMP(mp1) != VK_CTRL ) ||
                 ( keylink == TRUE && (CHARMSG(&iMsg)->fs & KC_KEYUP ) ) )
               {
                event.type = ( CHARMSG(&iMsg)->fs & KC_KEYUP ) ? ev_keyup : ev_keydown;
                event.data1 = CHAR4FROMMP(mp1);
                D_PostEvent(&event);
               }
            return 0;

       case WM_ACTIVATE:
            GameMode = mp1 ? GAME_PLAY : GAME_PAUSE;
            break;

       case WM_PAINT:
            hps = WinBeginPaint(hwnd,0,&rcl);
            RenderScene();
            WinEndPaint(hps);
            return 0;

       case WM_CLOSE:
            WinPostMsg( hwnd, WM_QUIT, 0, 0 );
            return 0;
       }

    return WinDefWindowProc(hwnd, iMsg, mp1, mp2);
   }

void WriteDebug(char *Message)
   {
    FILE *fn;

    fn = fopen(szDbgName, "a+");
    fprintf(fn, "%s", Message);
    fclose(fn);
   }

/////////////////////////////////////////////////////////////////////////////////////
// DIVE
/////////////////////////////////////////////////////////////////////////////////////

BOOL SetupDIVE()
   {
    ULONG hresult;

    GetCDInfo(hClient);

    PlayMidiFile(szMidiFile);

    hresult = JoystickOn();
    if (hresult)
       {
       joystickenabled = FALSE;
       DI_Error( hresult, "Joystick");
       }
    else
       {
       joystickenabled = TRUE;
       }

   fVrnDisabled = TRUE;

   // Get the screen capabilities, and if the system support only 16 colors
   // the sample should be terminated.
   DiveCaps.pFormatData = fccFormats;
   DiveCaps.ulFormatLength = 120;
   DiveCaps.ulStructLen = sizeof(DIVE_CAPS);

   if ( DiveQueryCaps ( &DiveCaps, DIVE_BUFFER_SCREEN ) ||
        DiveCaps.ulDepth < 8 ||
        DiveOpen( &hDive, FALSE, 0 ) )
     {
     WinMessageBox( HWND_DESKTOP, HWND_DESKTOP,
              "This program cannot run on this system.",
              0, 0, MB_OK | MB_INFORMATION );
     return FALSE;
     }

    DiveAllocImageBuffer( hDive, &ulImage, FOURCC_LUT8, SCREENWIDTH, SCREENHEIGHT, 0, 0 ) ;

    WinSetVisibleRegionNotify( hClient, TRUE );

    WinPostMsg( hFrame, WM_VRNENABLED, 0, 0 );

    return TRUE;
   }

void RenderScene()
   {
   INT    i, j;
   PBYTE  pbBuffer, pbScreen;
   ULONG  ulScanLineBytes, ulScanLines;

   if ( !ulImage || fVrnDisabled || GameMode != GAME_PLAY )
      return;

   pbScreen = screens[0];

   DiveSetSourcePalette ( hDive, 0, 256, &rgbPalette[0].bBlue );

   DiveBeginImageBufferAccess( hDive, ulImage, &pbBuffer, &ulScanLineBytes, &ulScanLines );

   for ( i = 0 ; i < SCREENHEIGHT ; i++ )
      memcpy( pbBuffer + i * SCREENWIDTH, pbScreen + ( SCREENHEIGHT - i - 1 ) * SCREENWIDTH, SCREENWIDTH );

   DiveEndImageBufferAccess ( hDive, ulImage );

   DiveBlitImage( hDive, ulImage, DIVE_BUFFER_SCREEN );
   }


void ShutdownDIVE()
   {
   WinSetVisibleRegionNotify( hClient, FALSE );

   DiveFreeImageBuffer( hDive, ulImage );
   DiveClose( hDive );

   if ( joystickenabled )
     {
      JoystickOff();
     }

   StopMusic();
   }

//
// Palette stuff.
//
//
// I_SetPalette
//
void I_SetPalette(byte* palette)
   {
      static int iFirst = 1;

    int i;

    for (i = 0; i < 256; i++)
       {
        rgbPalette[i].bRed   = gammatable[usegamma][*palette++];
        rgbPalette[i].bGreen = gammatable[usegamma][*palette++];
        rgbPalette[i].bBlue  = gammatable[usegamma][*palette++];
        rgbPalette[i].fcOptions = 0;
       }
       if (iFirst) {
          FILE *f;
          f = fopen("palette.lmp","wb");
          fwrite(palette,3,256,f);
          fclose(f);
          iFirst = 0;
       } /* endif */
   }

