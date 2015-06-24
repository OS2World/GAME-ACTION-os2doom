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
// DESCRIPTION:
//  Internally used data structures for virtually everything,
//   key definitions, lots of other stuff.
//
//-----------------------------------------------------------------------------

#ifndef __DOOMDEF__
#define __DOOMDEF__

#include <stdio.h>
#include <string.h>

//
// Global parameters/defines.
//
// DOOM version
enum { DOOM_VERSION =  109 };


// Game mode handling - identify IWAD version
//  to handle IWAD dependend animations etc.
typedef enum
{
  shareware,	// DOOM 1 shareware, E1, M9
  registered,	// DOOM 1 registered, E3, M27
  commercial,	// DOOM 2 retail, E1 M34
  // DOOM 2 german edition not handled
  retail,	// DOOM 1 retail, E4, M36
  addon_tnt,    // DOOM 2 TNT
  addon_plut,   // DOOM 2 Plutonia
  indetermined	// Well, no IWAD found.
  
} GameMode_t;


// Mission packs - might be useful for TC stuff?
typedef enum
{
  doom,		// DOOM 1
  doom2,	// DOOM 2
  pack_tnt,	// TNT mission pack
  pack_plut,	// Plutonia pack
  none

} GameMission_t;


// Identify language to use, software localization.
typedef enum
{
  english,
  french,
  german,
  unknown

} Language_t;


// If rangecheck is undefined,
// most parameter validation debugging code will not be compiled
#define RANGECHECK

// Do or do not use external soundserver.
// The sndserver binary to be run separately
//  has been introduced by Dave Taylor.
// The integrated sound support is experimental,
//  and unfinished. Default is synchronous.
// Experimental asynchronous timer based is
//  handled by SNDINTR. 
#define SNDSERV  1
//#define SNDINTR  1


// This one switches between MIT SHM (no proper mouse)
// and XFree86 DGA (mickey sampling). The original
// linuxdoom used SHM, which is default.
//#define X11_DGA		1


//
// For resize of screen, at start of game.
// It will not work dynamically, see visplanes.
//
#define	BASE_WIDTH		320

// It is educational but futile to change this
//  scaling e.g. to 2. Drawing of status bar,
//  menues etc. is tied to the scale implied
//  by the graphics.
#define	SCREEN_MUL		1
#define	INV_ASPECT_RATIO	0.625 // 0.75, ideally

// Defines suck. C sucks.
// C++ might sucks for OOP, but it sure is a better C.
// So there.
//#define SCREENWIDTH  640
extern int SCREENWIDTH;
//SCREEN_MUL*BASE_WIDTH //320
//#define SCREENHEIGHT 480
extern int SCREENHEIGHT;
//(int)(SCREEN_MUL*BASE_WIDTH*INV_ASPECT_RATIO) //200


// The maximum number of players, multiplayer/networking.
#define MAXPLAYERS		4

// State updates, number of tics / second.
#define TICRATE		35

// The current state of the game: whether we are
// playing, gazing at the intermission screen,
// the game final animation, or a demo. 
typedef enum
{
    GS_LEVEL,
    GS_INTERMISSION,
    GS_FINALE,
    GS_DEMOSCREEN
} gamestate_t;

//
// Difficulty/skill settings/filters.
//

// Skill flags.
#define	MTF_EASY		1
#define	MTF_NORMAL		2
#define	MTF_HARD		4

// Deaf monsters/do not react to sound.
#define	MTF_AMBUSH		8

typedef enum
{
    sk_baby,
    sk_easy,
    sk_medium,
    sk_hard,
    sk_nightmare
} skill_t;




//
// Key cards.
//
typedef enum
{
    it_bluecard,
    it_yellowcard,
    it_redcard,
    it_blueskull,
    it_yellowskull,
    it_redskull,
    
    NUMCARDS
    
} card_t;



// The defined weapons,
//  including a marker indicating
//  user has not changed weapon.
typedef enum
{
    wp_fist,
    wp_pistol,
    wp_shotgun,
    wp_chaingun,
    wp_missile,
    wp_plasma,
    wp_bfg,
    wp_chainsaw,
    wp_supershotgun,

    NUMWEAPONS,
    
    // No pending weapon change.
    wp_nochange

} weapontype_t;


// Ammunition types defined.
typedef enum
{
    am_clip,	// Pistol / chaingun ammo.
    am_shell,	// Shotgun / double barreled shotgun.
    am_cell,	// Plasma rifle, BFG.
    am_misl,	// Missile launcher.
    NUMAMMO,
    am_noammo	// Unlimited for chainsaw / fist.	

} ammotype_t;


// Power up artifacts.
typedef enum
{
    pw_invulnerability,
    pw_strength,
    pw_invisibility,
    pw_ironfeet,
    pw_allmap,
    pw_infrared,
    NUMPOWERS
    
} powertype_t;



//
// Power up durations,
//  how many seconds till expiration,
//  assuming TICRATE is 35 ticks/second.
//
typedef enum
{
    INVULNTICS	= (30*TICRATE),
    INVISTICS	= (60*TICRATE),
    INFRATICS	= (120*TICRATE),
    IRONTICS	= (60*TICRATE)
    
} powerduration_t;




//
// DOOM keyboard definition.
// This is the stuff configured by Setup.Exe.
// Most key data are simple ascii (uppercased).
//

#define KEY_PAUSE	0xff

#define KEY_CAPITAL 0x3a

//#define KEY_CONSOLE '`'
#define KEY_SCRNSHOT (0xB7)

#define KEY_F1            0x3B
#define KEY_F2            0x3C
#define KEY_F3            0x3D
#define KEY_F4            0x3E
#define KEY_F5            0x3F
#define KEY_F6            0x40
#define KEY_F7            0x41
#define KEY_F8            0x42
#define KEY_F9            0x43
#define KEY_F10           0x44
#define KEY_F11           0x57
#define KEY_F12           0x58

#define KEY_A               0x1E
#define KEY_B               0x30
#define KEY_C               0x2E
#define KEY_D               0x20
#define KEY_E               0x12
#define KEY_F               0x21
#define KEY_G               0x22
#define KEY_I               0x17
#define KEY_H               0x23
#define KEY_J               0x24
#define KEY_K               0x25
#define KEY_L               0x26
#define KEY_M               0x32
#define KEY_N               0x31
#define KEY_O               0x18
#define KEY_P               0x19
#define KEY_Q               0x10
#define KEY_R               0x13
#define KEY_S               0x1F
#define KEY_T               0x14
#define KEY_U               0x16
#define KEY_V               0x2F
#define KEY_W               0x11
#define KEY_X               0x2D
#define KEY_Y               0x15
#define KEY_Z               0x2C

#define KEY_1               0x02
#define KEY_2               0x03
#define KEY_3               0x04
#define KEY_4               0x05
#define KEY_5               0x06
#define KEY_6               0x07
#define KEY_7               0x08
#define KEY_8               0x09
#define KEY_9               0x0A
#define KEY_0               0x0B

#define KEY_MINUS           0x0C    // - on main keyboard
#define KEY_EQUALS          0x0D

#define KEY_BACKSPACE       0x0E    // backspace
#define KEY_ESCAPE	      0x01
#define KEY_ENTER	      0x1C
#define KEY_CONSOLE       0x29

#define KEY_RIGHTARROW	  0x64
#define KEY_LEFTARROW	  0x63
#define KEY_UPARROW	  0x61
#define KEY_DOWNARROW	  0x66

#define KEY_SPACE           0x39
#define KEY_TAB		    0x0F
#define KEY_LSHIFT          0x2A
#define KEY_RSHIFT          0x36
#define KEY_LCTRL           0x1D
#define KEY_RCTRL           0x5B
#define KEY_LALT	    0x38
#define KEY_RALT            0x5E    // right Alt

#define KEY_COMMA           0x33
#define KEY_PERIOD          0x34    // . on main keyboard
#define KEY_SLASH           0x35    // / on main keyboard
// new keys not part of DOOM...

#define KEY_LBRACKET        0x1A
#define KEY_RBRACKET        0x1B
#define KEY_SEMICOLON       0x27
#define KEY_APOSTROPHE      0x28
#define KEY_DIVIDE          0x5C    // / on numeric keypad
#define KEY_MULTIPLY        0x37    // * on numeric keypad
#define KEY_NUMLOCK         0x45
#define KEY_SCROLL          0x46    // Scroll Lock
#define KEY_NUMPAD7         0x47
#define KEY_NUMPAD8         0x48
#define KEY_NUMPAD9         0x49
#define KEY_SUBTRACT        0x4A    // - on numeric keypad
#define KEY_NUMPAD4         0x4B
#define KEY_NUMPAD5         0x4C
#define KEY_NUMPAD6         0x4D
#define KEY_ADD             0x4E    // + on numeric keypad
#define KEY_NUMPAD1         0x4F
#define KEY_NUMPAD2         0x50
#define KEY_NUMPAD3         0x51
#define KEY_NUMPAD0         0x52
#define KEY_DECIMAL         0x53    // . on numeric keypad

#define KEY_HOME            0x47    // Home on arrow keypad
#define KEY_UP              0x48    // UpArrow on arrow keypad
#define KEY_PRIOR           0x49    // PgUp on arrow keypad
#define KEY_LEFT            0x4B    // LeftArrow on arrow keypad
#define KEY_RIGHT           0x4D    // RightArrow on arrow keypad
#define KEY_END             0x4F    // End on arrow keypad
#define KEY_DOWN            0x50    // DownArrow on arrow keypad
#define KEY_NEXT            0x51    // PgDn on arrow keypad
#define KEY_INSERT          0x52    // Insert on arrow keypad
#define KEY_DELETE          0x53    // Delete on arrow keypad

extern unsigned char scan2char[256];


// DOOM basic types (boolean),
//  and max/min values.
//#include "doomtype.h"

// Fixed point.
//#include "m_fixed.h"

// Endianess handling.
//#include "m_swap.h"


// Binary Angles, sine/cosine/atan lookups.
//#include "tables.h"

// Event type.
//#include "d_event.h"

// Game function, skills.
//#include "g_game.h"

// All external data is defined here.
//#include "doomdata.h"

// All important printed strings.
// Language selection (message strings).
//#include "dstrings.h"

// Player is a special actor.
//struct player_s;


//#include "d_items.h"
//#include "d_player.h"
//#include "p_mobj.h"
//#include "d_net.h"

// PLAY
//#include "p_tick.h"




// Header, generated by sound utility.
// The utility was written by Dave Taylor.
//#include "sounds.h"




#endif          // __DOOMDEF__
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
