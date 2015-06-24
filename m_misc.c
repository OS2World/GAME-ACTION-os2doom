// Emacs style mode select   -*- C++ -*- 
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
//
// $Log:$
//
// DESCRIPTION:
//	Main loop menu stuff.
//	Default Config File.
//	PCX Screenshots.
//
//-----------------------------------------------------------------------------

static const char
rcsid[] = "$Id: m_misc.c,v 1.6 1997/02/03 22:45:10 b1 Exp $";

#define INCL_PM
#include "windows.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <io.h>
//#include <unistd.h>
#include <direct.h>

#include <ctype.h>


#include "doomdef.h"

#include "z_zone.h"

//#include "m_swap.h"
#include "m_argv.h"

#include "w_wad.h"

#include "i_system.h"
#include "i_video.h"
#include "v_video.h"

#include "hu_stuff.h"

// State.
#include "doomstat.h"

// Data.
#include "dstrings.h"

#include "m_misc.h"

//
// M_DrawText
// Returns the final X coordinate
// HU_Init must have been called to init the font
//
extern patch_t*		hu_font[HU_FONTSIZE];


int
M_DrawText
( int		x,
  int		y,
  boolean	direct,
  char*		string )
{
    int 	c;
    int		w;

    while (*string)
    {
	c = toupper(*string) - HU_FONTSTART;
	string++;
	if (c < 0 || c> HU_FONTSIZE)
	{
	    x += 4;
	    continue;
	}
		
	w = hu_font[c]->width;
	if (x+w > SCREENWIDTH)
	    break;
	if (direct)
	    V_DrawPatchDirect(x, y, 0, hu_font[c]);
	else
	    V_DrawPatch(x, y, 0, hu_font[c]);
	x+=w;
    }

    return x;
}



//
// M_GetFileSize
//
#ifndef O_BINARY
#define O_BINARY 0
#endif

int M_GetFileSize( char const*	name )
   {
    int		handle;
    int		count;
	
    handle = open ( name, O_RDWR | O_BINARY);

    if (handle == -1)
        return 0;

    count = lseek(handle, 0, SEEK_END);
    close (handle);
	
    return count;
   }

//
// M_WriteFile
//
boolean
M_WriteFile
( char const*	name,
  void*		source,
  int		length )
{
    int		handle;
    int		count;
	
    handle = open ( name, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666);

    if (handle == -1)
	return false;

    count = write (handle, source, length);
    close (handle);
	
    if (count < length)
	return false;
		
    return true;
}

//
// M_AppendFile
//
boolean M_AppendFile(char const *name, void *source, int length )
   {
    int		handle;
    int		count;
	
    handle = open( name, O_RDWR | O_BINARY);

    if (handle == -1)
        return false;

    lseek(handle, 0L, SEEK_END);

    count = write (handle, source, length);
    close (handle);
	
    if (count < length)
        return false;
		
    return true;
   }


//
// M_ReadFile
//
int
M_ReadFile
( char const*	name,
  byte**	buffer )
{
    int	handle, count, length;
    struct stat	fileinfo;
    byte		*buf;
	
    handle = open (name, O_RDONLY | O_BINARY, 0666);
    if (handle == -1)
	I_Error ("Couldn't read file %s", name);
    if (fstat (handle,&fileinfo) == -1)
	I_Error ("Couldn't read file %s", name);
    length = fileinfo.st_size;
    buf = Z_Malloc (length, PU_STATIC, NULL);
    count = read (handle, buf, length);
    close (handle);
	
    if (count < length)
	I_Error ("Couldn't read file %s", name);
		
    *buffer = buf;
    return length;
}


//
// DEFAULTS
//
int		usemouse;
int		usejoystick;

extern int	key_right;
extern int	key_left;
extern int	key_up;
extern int	key_down;

extern int	key_strafeleft;
extern int	key_straferight;

extern int	key_fire;
extern int	key_use;
extern int	key_strafe;
extern int	key_speed;

extern int  key_mvert;

extern int  always_run;
extern int  swap_stereo;
extern int  mvert;
extern int  keylink;

extern int	mousebfire;
extern int	mousebstrafe;
extern int	mousebforward;

extern int	mouseb1;
extern int	mouseb2;
extern int	mouseb3;

extern int	joybfire;
extern int	joybstrafe;
extern int	joybuse;
extern int	joybspeed;

extern int  joyb1;
extern int  joyb2;
extern int  joyb3;
extern int  joyb4;

extern int	viewwidth;
extern int	viewheight;

extern int	mouseSensitivity;
extern int	showMessages;

extern int	detailLevel;

extern int	screenblocks;

extern int	showMessages;

// machine-independent sound params
extern	int	numChannels;


// UNIX hack, to be removed.
#ifdef SNDSERV
extern char*	sndserver_filename;
extern int	mb_used;
#endif

#ifdef LINUX
char*		mousetype;
char*		mousedev;
#endif

extern char*	chat_macros[];



typedef struct
{
    char*	name;
    int*	location;
    int		defaultvalue;
    int		scantranslate;		// PC scan code hack
    int		untranslated;		// lousy hack
} default_t;

default_t	defaults[] =
{
    {"mouse_sensitivity",&mouseSensitivity, 5},
    {"sfx_volume",&snd_SfxVolume, 8},
    {"music_volume",&snd_MusicVolume, 8},
    {"show_messages",&showMessages, 1},
    

#ifdef NORMALUNIX
    {"key_right",&key_right, KEY_RIGHTARROW},
    {"key_left",&key_left, KEY_LEFTARROW},
    {"key_up",&key_up, KEY_UPARROW},
    {"key_down",&key_down, KEY_DOWNARROW},
    {"key_strafeleft",&key_strafeleft, ','},
    {"key_straferight",&key_straferight, '.'},

    {"key_fire",&key_fire, KEY_RCTRL},
    {"key_use",&key_use, ' '},
    {"key_strafe",&key_strafe, KEY_RALT},
    {"key_speed",&key_speed, KEY_RSHIFT},

// UNIX hack, to be removed. 
#ifdef SNDSERV
    {"sndserver", (int *) &sndserver_filename, (int) "sndserver"},
    {"mb_used", &mb_used, 2},
#endif
    
#endif

#ifdef LINUX
    {"mousedev", (int*)&mousedev, (int)"/dev/ttyS0"},
    {"mousetype", (int*)&mousetype, (int)"microsoft"},
#endif

    {"use_mouse",&usemouse, 1},
    {"mouseb_fire",&mousebfire,0},
    {"mouseb_strafe",&mousebstrafe,1},
    {"mouseb_forward",&mousebforward,2},

    {"use_joystick",&usejoystick, 0},
    {"joyb_fire",&joybfire,0},
    {"joyb_strafe",&joybstrafe,1},
    {"joyb_use",&joybuse,3},
    {"joyb_speed",&joybspeed,2},

    {"screenblocks",&screenblocks, 9},
    {"detaillevel",&detailLevel, 0},

    {"snd_channels",&numChannels, 3},



    {"usegamma",&usegamma, 0},

    {"chatmacro0", (int *) &chat_macros[0], (int) HUSTR_CHATMACRO0 },
    {"chatmacro1", (int *) &chat_macros[1], (int) HUSTR_CHATMACRO1 },
    {"chatmacro2", (int *) &chat_macros[2], (int) HUSTR_CHATMACRO2 },
    {"chatmacro3", (int *) &chat_macros[3], (int) HUSTR_CHATMACRO3 },
    {"chatmacro4", (int *) &chat_macros[4], (int) HUSTR_CHATMACRO4 },
    {"chatmacro5", (int *) &chat_macros[5], (int) HUSTR_CHATMACRO5 },
    {"chatmacro6", (int *) &chat_macros[6], (int) HUSTR_CHATMACRO6 },
    {"chatmacro7", (int *) &chat_macros[7], (int) HUSTR_CHATMACRO7 },
    {"chatmacro8", (int *) &chat_macros[8], (int) HUSTR_CHATMACRO8 },
    {"chatmacro9", (int *) &chat_macros[9], (int) HUSTR_CHATMACRO9 }

};

int	numdefaults;
char*	defaultfile;

char szValue[32];
HINI hini;

void OpenINI(void)
   {
    char DoomDir[128];

    getcwd(DoomDir, 128);
    strcat(DoomDir, "\\Doom.INI");
    hini = PrfOpenProfile( 0, DoomDir );
   }


//
// M_SaveDefaults
//
void M_SaveDefaults (void)
   {
/*
    int		i;
    int		v;
    FILE*	f;
*/
	
    OpenINI();
    sprintf(szValue, "%d", mouseSensitivity);
    PrfWriteProfileString(hini, "DEFAULTS", "mouse_sensitivity", szValue);
    sprintf(szValue, "%d", snd_SfxVolume);
    PrfWriteProfileString(hini, "DEFAULTS", "sfx_volume", szValue);
    sprintf(szValue, "%d", snd_MusicVolume);
    PrfWriteProfileString(hini, "DEFAULTS", "music_volume", szValue);
    sprintf(szValue, "%d", showMessages);
    PrfWriteProfileString(hini, "DEFAULTS", "show_messages", szValue);

    sprintf(szValue, "%d", key_right);
    PrfWriteProfileString(hini, "DEFAULTS", "key_right", szValue);
    sprintf(szValue, "%d", key_left);
    PrfWriteProfileString(hini, "DEFAULTS", "key_left", szValue);
    sprintf(szValue, "%d", key_up);
    PrfWriteProfileString(hini, "DEFAULTS", "key_up", szValue);
    sprintf(szValue, "%d", key_down);
    PrfWriteProfileString(hini, "DEFAULTS", "key_down", szValue);

    sprintf(szValue, "%d", key_mvert);
    PrfWriteProfileString(hini, "DEFAULTS", "key_mvert", szValue);

    sprintf(szValue, "%d", key_strafeleft);
    PrfWriteProfileString(hini, "DEFAULTS", "key_strafeleft", szValue);
    sprintf(szValue, "%d", key_straferight);
    PrfWriteProfileString(hini, "DEFAULTS", "key_straferight", szValue);

    sprintf(szValue, "%d", key_fire);
    PrfWriteProfileString(hini, "DEFAULTS", "key_fire", szValue);
    sprintf(szValue, "%d", key_use);
    PrfWriteProfileString(hini, "DEFAULTS", "key_use", szValue);
    sprintf(szValue, "%d", key_strafe);
    PrfWriteProfileString(hini, "DEFAULTS", "key_strafe", szValue);
    sprintf(szValue, "%d", key_speed);
    PrfWriteProfileString(hini, "DEFAULTS", "key_speed", szValue);

    sprintf(szValue, "%d", always_run);
    PrfWriteProfileString(hini, "DEFAULTS", "always_run", szValue);
    sprintf(szValue, "%d", swap_stereo);
    PrfWriteProfileString(hini, "DEFAULTS", "swap_stereo", szValue);
    sprintf(szValue, "%d", mvert);
    PrfWriteProfileString(hini, "DEFAULTS", "mvert", szValue);
    sprintf(szValue, "%d", keylink);
    PrfWriteProfileString(hini, "DEFAULTS", "keylink", szValue);


    sprintf(szValue, "%d", usemouse);
    PrfWriteProfileString(hini, "DEFAULTS", "use_mouse", szValue);
    sprintf(szValue, "%d", mousebfire);
    PrfWriteProfileString(hini, "DEFAULTS", "mouseb_fire", szValue);
    sprintf(szValue, "%d", mousebstrafe);
    PrfWriteProfileString(hini, "DEFAULTS", "mouseb_strafe", szValue);
    sprintf(szValue, "%d", mousebforward);
    PrfWriteProfileString(hini, "DEFAULTS", "mouseb_forward", szValue);

    sprintf(szValue, "%d", mouseb1);
    PrfWriteProfileString(hini, "DEFAULTS", "mouseb1", szValue);
    sprintf(szValue, "%d", mouseb2);
    PrfWriteProfileString(hini, "DEFAULTS", "mouseb2", szValue);
    sprintf(szValue, "%d", mouseb3);
    PrfWriteProfileString(hini, "DEFAULTS", "mouseb3", szValue);

    sprintf(szValue, "%d", usejoystick);
    PrfWriteProfileString(hini, "DEFAULTS", "use_joystick", szValue);
    sprintf(szValue, "%d", joybfire);
    PrfWriteProfileString(hini, "DEFAULTS", "joyb_fire", szValue);
    sprintf(szValue, "%d", joybstrafe);
    PrfWriteProfileString(hini, "DEFAULTS", "joyb_strafe", szValue);
    sprintf(szValue, "%d", joybuse);
    PrfWriteProfileString(hini, "DEFAULTS", "joyb_use", szValue);
    sprintf(szValue, "%d", joybspeed);
    PrfWriteProfileString(hini, "DEFAULTS", "joyb_speed", szValue);

    sprintf(szValue, "%d", joyb1);
    PrfWriteProfileString(hini, "DEFAULTS", "joyb1", szValue);
    sprintf(szValue, "%d", joyb2);
    PrfWriteProfileString(hini, "DEFAULTS", "joyb2", szValue);
    sprintf(szValue, "%d", joyb3);
    PrfWriteProfileString(hini, "DEFAULTS", "joyb3", szValue);
    sprintf(szValue, "%d", joyb4);
    PrfWriteProfileString(hini, "DEFAULTS", "joyb4", szValue);

    sprintf(szValue, "%d", screenblocks);
    PrfWriteProfileString(hini, "DEFAULTS", "screenblocks", szValue);
    sprintf(szValue, "%d", detailLevel);
    PrfWriteProfileString(hini, "DEFAULTS", "detaillevel", szValue);

    sprintf(szValue, "%d", usegamma);
    PrfWriteProfileString(hini, "DEFAULTS", "usegamma", szValue);

    sprintf(szValue, "%d", numChannels);
    PrfWriteProfileString(hini, "DEFAULTS", "snd_channels", szValue);
/*
    f = fopen (defaultfile, "w");
    if (!f)
	return; // can't write the file, but don't complain
		
    for (i=0 ; i<numdefaults ; i++)
    {
	if (defaults[i].defaultvalue > -0xfff
	    && defaults[i].defaultvalue < 0xfff)
	{
	    v = *defaults[i].location;
	    fprintf (f,"%s\t\t%i\n",defaults[i].name,v);
	} else {
	    fprintf (f,"%s\t\t\"%s\"\n",defaults[i].name,
		     * (char **) (defaults[i].location));
	}
    }
	
    fclose (f);
*/
   }


//
// M_LoadDefaults
//
extern byte	scantokey[128];

void WriteDebug(char *);
char MsgText[256];

void M_LoadDefaults (void)
{
/*
    int		i;
    int		len;
    FILE*	f;
    char	def[80];
    char	strparm[100];
    char*	newstring;
    int		parm;
    boolean	isstring;
*/    

    OpenINI();

    mouseSensitivity = PrfQueryProfileInt(hini, "DEFAULTS", "mouse_sensitivity", 5);
    snd_SfxVolume = PrfQueryProfileInt(hini, "DEFAULTS", "sfx_volume", 15);
    snd_MusicVolume = PrfQueryProfileInt(hini, "DEFAULTS", "music_volume", 8);
    showMessages = PrfQueryProfileInt(hini, "DEFAULTS", "show_messages", 1);

    key_right = PrfQueryProfileInt(hini, "DEFAULTS", "key_right", KEY_RIGHTARROW);
    key_left = PrfQueryProfileInt(hini, "DEFAULTS", "key_left", KEY_LEFTARROW);
    key_up = PrfQueryProfileInt(hini, "DEFAULTS", "key_up", KEY_UPARROW);
    key_down = PrfQueryProfileInt(hini, "DEFAULTS", "key_down", KEY_DOWNARROW);

    key_strafeleft = PrfQueryProfileInt(hini, "DEFAULTS", "key_strafeleft", KEY_COMMA);
    key_straferight = PrfQueryProfileInt(hini, "DEFAULTS", "key_straferight", KEY_PERIOD);

    key_fire = PrfQueryProfileInt(hini, "DEFAULTS", "key_fire", KEY_RCTRL);
    key_use = PrfQueryProfileInt(hini, "DEFAULTS", "key_use", KEY_SPACE);
    key_strafe = PrfQueryProfileInt(hini, "DEFAULTS", "key_strafe", KEY_RALT);
    key_speed = PrfQueryProfileInt(hini, "DEFAULTS", "key_speed", KEY_RSHIFT);

    key_mvert = PrfQueryProfileInt(hini, "DEFAULTS", "key_mvert", KEY_SLASH);

    always_run = PrfQueryProfileInt(hini, "DEFAULTS", "always_run", FALSE);
    swap_stereo = PrfQueryProfileInt(hini, "DEFAULTS", "swap_stereo", FALSE);
    mvert = PrfQueryProfileInt(hini, "DEFAULTS", "mvert", TRUE);
    keylink = PrfQueryProfileInt(hini, "DEFAULTS", "keylink", TRUE);

    usemouse = PrfQueryProfileInt(hini, "DEFAULTS", "use_mouse", TRUE);
    mousebfire = PrfQueryProfileInt(hini, "DEFAULTS", "mouseb_fire", 0);
    mousebstrafe = PrfQueryProfileInt(hini, "DEFAULTS", "mouseb_strafe", 1);
    mousebforward = PrfQueryProfileInt(hini, "DEFAULTS", "mouseb_forward", 2);

    mouseb1 = PrfQueryProfileInt(hini, "DEFAULTS", "mouseb1", key_fire);
    mouseb2 = PrfQueryProfileInt(hini, "DEFAULTS", "mouseb2", key_strafe);
    mouseb3 = PrfQueryProfileInt(hini, "DEFAULTS", "mouseb3", key_up);

    usejoystick = PrfQueryProfileInt(hini, "DEFAULTS", "use_joystick", FALSE);
    joybfire = PrfQueryProfileInt(hini, "DEFAULTS", "joyb_fire", 0);
    joybstrafe = PrfQueryProfileInt(hini, "DEFAULTS", "joyb_strafe", 1);
    joybuse = PrfQueryProfileInt(hini, "DEFAULTS", "joyb_use", 3);
    joybspeed = PrfQueryProfileInt(hini, "DEFAULTS", "joyb_speed", 2);

    joyb1 = PrfQueryProfileInt(hini, "DEFAULTS", "joyb1", key_fire);
    joyb2 = PrfQueryProfileInt(hini, "DEFAULTS", "joyb2", key_strafe);
    joyb3 = PrfQueryProfileInt(hini, "DEFAULTS", "joyb3", key_use);
    joyb4 = PrfQueryProfileInt(hini, "DEFAULTS", "joyb4", key_speed);

    screenblocks = PrfQueryProfileInt(hini, "DEFAULTS", "screenblocks", 10);
    detailLevel = PrfQueryProfileInt(hini, "DEFAULTS", "detaillevel", 0);

    usegamma = PrfQueryProfileInt(hini, "DEFAULTS", "usegamma", 0);

    numChannels = PrfQueryProfileInt(hini, "DEFAULTS", "snd_channels", 256);
   }
/*
snd_musicdevice		3
snd_sfxdevice		3
snd_sbport		544
snd_sbirq		5
snd_sbdma		1
snd_mport		816

chatmacro0		"no macro"
chatmacro1		"no macro"
chatmacro2		"no macro"
chatmacro3		"no macro"
chatmacro4		"no macro"
chatmacro5		"no macro"
chatmacro6		"no macro"
chatmacro7		"no macro"
chatmacro8		"no macro"
chatmacro9		"no macro"
*/

//
// SCREEN SHOTS
//


typedef struct
{
    char		manufacturer;
    char		version;
    char		encoding;
    char		bits_per_pixel;

    unsigned short	xmin;
    unsigned short	ymin;
    unsigned short	xmax;
    unsigned short	ymax;
    
    unsigned short	hres;
    unsigned short	vres;

    unsigned char	palette[48];
    
    char		reserved;
    char		color_planes;
    unsigned short	bytes_per_line;
    unsigned short	palette_type;
    
    char		filler[58];
    unsigned char	data;		// unbounded
} pcx_t;


//
// WritePCXfile
//
void
WritePCXfile
( char*		filename,
  byte*		data,
  int		width,
  int		height,
  byte*		palette )
{
    int		i;
    int		length;
    pcx_t*	pcx;
    byte*	pack;
	
    pcx = Z_Malloc (width*height*2+1000, PU_STATIC, NULL);

    pcx->manufacturer = 0x0a;		// PCX id
    pcx->version = 5;			// 256 color
    pcx->encoding = 1;			// uncompressed
    pcx->bits_per_pixel = 8;		// 256 color
    pcx->xmin = 0;
    pcx->ymin = 0;
    pcx->xmax = width-1;
    pcx->ymax = height-1;
    pcx->hres = width;
    pcx->vres = height;
    memset (pcx->palette,0,sizeof(pcx->palette));
    pcx->color_planes = 1;		// chunky image
    pcx->bytes_per_line = width;
    pcx->palette_type = 2;	// not a grey scale
    memset (pcx->filler,0,sizeof(pcx->filler));


    // pack the image
    pack = &pcx->data;
	
    for (i=0 ; i<width*height ; i++)
    {
	if ( (*data & 0xc0) != 0xc0)
	    *pack++ = *data++;
	else
	{
	    *pack++ = 0xc1;
	    *pack++ = *data++;
	}
    }
    
    // write the palette
    *pack++ = 0x0c;	// palette ID byte
    for (i=0 ; i<768 ; i++)
	*pack++ = gammatable[usegamma][*palette++];
    
    // write output file
    length = pack - (byte *)pcx;
    M_WriteFile (filename, pcx, length);

    Z_Free (pcx);
}


//
// M_ScreenShot
//
void M_ScreenShot (void)
{
    int		i;
    byte*	linear;
    char	lbmname[12];
    
    // munge planar buffer to linear
    linear = screens[2];
    I_ReadScreen (linear);
    
    // find a file name to save it to
    strcpy(lbmname,"DOOM00.pcx");
		
    for (i=0 ; i<=99 ; i++)
    {
	lbmname[4] = i/10 + '0';
	lbmname[5] = i%10 + '0';
	if (access(lbmname,0) == -1)
	    break;	// file doesn't exist
    }
    if (i==100)
	I_Error ("M_ScreenShot: Couldn't create a PCX");
    
    // save the pcx file
    WritePCXfile (lbmname, linear,
		  SCREENWIDTH, SCREENHEIGHT,
		  W_CacheLumpName ("PLAYPAL",PU_CACHE));
	
    players[consoleplayer].message = "screen shot";
}


