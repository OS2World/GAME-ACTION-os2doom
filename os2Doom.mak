.SUFFIXES:
.SUFFIXES: .obj .c .h 

#CFLAGS          =      -Gd- -Se -Re -Ss -Ms -Gm+ -Gt+ -Ti
CFLAGS          =      -Gd- -Se -Re -Ss -Ms -Gm+ -Gt+ 
CC              =      icc $(CFLAGS)

.c.obj :
        $(CC) -c -Fo"$(@B).obj" $(@B).c

ALL:  OS2Doom.exe 

LINK32_OBJS= \
	am_map.obj \
	d_console.obj \
	d_items.obj \
	d_main.obj \
	d_net.obj \
	doomdef.obj \
	doomstat.obj \
	dstrings.obj \
	dxerr.obj \
	f_finale.obj \
	f_wipe.obj \
	g_game.obj \
	hu_lib.obj \
	hu_stuff.obj \
	i_cd.obj \
	i_joystick.obj \
	i_main.obj \
	i_midi.obj \
	i_net.obj \
	i_sound.obj \
	i_system.obj \
	i_video.obj \
	info.obj \
	m_argv.obj \
	m_bbox.obj \
	m_cheat.obj \
	m_fixed.obj \
	m_menu.obj \
	m_misc.obj \
	m_music.obj \
	m_random.obj \
#	m_swap.obj \
	p_ceilng.obj \
	p_doors.obj \
	p_enemy.obj \
	p_floor.obj \
	p_inter.obj \
	p_lights.obj \
	p_map.obj \
	p_maputl.obj \
	p_mobj.obj \
	p_plats.obj \
	p_pspr.obj \
	p_saveg.obj \
	p_setup.obj \
	p_sight.obj \
	p_spec.obj \
	p_switch.obj \
	p_telept.obj \
	p_tick.obj \
	p_user.obj \
	qmus2mid.obj \
	r_bsp.obj \
	r_data.obj \
	r_draw.obj \
	r_main.obj \
	r_plane.obj \
	r_segs.obj \
	r_sky.obj \
	r_things.obj \
	s_sound.obj \
	sounds.obj \
	st_lib.obj \
	st_stuff.obj \
	tables.obj \
	v_video.obj \
	w_wad.obj \
	wi_stuff.obj \
	z_zone.obj

OS2Doom.exe: $(LINK32_OBJS) os2doom.def
#    ilink /debug /free /out:os2doom.exe $(LINK32_OBJS) MMPM2.LIB SO32DLL.LIB TCP32DLL.LIB PMWSOCK.LIB os2doom.def
    ilink /free /out:os2doom.exe $(LINK32_OBJS) MMPM2.LIB SO32DLL.LIB TCP32DLL.LIB PMWSOCK.LIB os2doom.def



SOURCE=.\d_console.c
DEP_CPP_D_CON=\
	 d_englsh.h \
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 g_game.h \
	 hu_stuff.h \
	 i_system.h \
	 info.h \
	 m_cheat.h \
	 m_fixed.h \
	 m_music.h \
	 p_inter.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_defs.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 z_zone.h \
	

d_console.obj: $(SOURCE) $(DEP_CPP_D_CON)


SOURCE=.\d_items.c
DEP_CPP_D_ITE=\
	 d_items.h \
	 d_think.h \
	 doomdef.h \
	 info.h \
	

d_items.obj: $(SOURCE) $(DEP_CPP_D_ITE)



SOURCE=.\d_main.c
DEP_CPP_D_MAI=\
	 am_map.h \
	 d_console.h \
	 d_englsh.h \
	 d_event.h \
	 d_french.h \
	 d_items.h \
	 d_main.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dstrings.h \
	 f_finale.h \
	 f_wipe.h \
	 g_game.h \
	 hu_stuff.h \
	 i_sound.h \
	 i_system.h \
	 i_video.h \
	 info.h \
	 m_argv.h \
	 m_fixed.h \
	 m_menu.h \
	 m_misc.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_setup.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 st_stuff.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 wi_stuff.h \
	 z_zone.h \
	
NODEP_CPP_D_MAI=\
	 multires.h \
	

d_main.obj: $(SOURCE) $(DEP_CPP_D_MAI)



SOURCE=.\d_net.c
DEP_CPP_D_NET=\
	 d_console.h \
	 d_event.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 g_game.h \
	 i_net.h \
	 i_system.h \
	 i_video.h \
	 m_menu.h \
	

d_net.obj: $(SOURCE) $(DEP_CPP_D_NET) 



SOURCE=.\doomdef.c
DEP_CPP_DOOMD=\
	 doomdef.h \
	

doomdef.obj: $(SOURCE) $(DEP_CPP_DOOMD) 


SOURCE=.\doomstat.c
DEP_CPP_DOOMS=\
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 info.h \
	 m_fixed.h \
	 p_mobj.h \
	 p_pspr.h \
	 tables.h \
	

doomstat.obj: $(SOURCE) $(DEP_CPP_DOOMS) 


SOURCE=.\dstrings.c
DEP_CPP_DSTRI=\
	 d_englsh.h \
	 d_french.h \
	 dstrings.h \
	

dstrings.obj: $(SOURCE) $(DEP_CPP_DSTRI) 



SOURCE=.\dxerr.c
	

dxerr.obj: $(SOURCE) 


SOURCE=.\f_finale.c

DEP_CPP_F_FIN=\
	 d_englsh.h \
	 d_event.h \
	 d_french.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dstrings.h \
	 hu_stuff.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
#	 m_swap.h \
	 p_mobj.h \
	 r_data.h \
	 r_defs.h \
	 r_state.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 z_zone.h \
	

f_finale.obj: $(SOURCE) $(DEP_CPP_F_FIN) 


SOURCE=.\f_wipe.c
DEP_CPP_F_WIP=\
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 f_wipe.h \
	 i_video.h \
	 info.h \
	 m_fixed.h \
	 m_random.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_data.h \
	 r_defs.h \
	 r_state.h \
	 tables.h \
	 v_video.h \
	 z_zone.h \
	

f_wipe.obj: $(SOURCE) $(DEP_CPP_F_WIP) 



SOURCE=.\g_game.c
DEP_CPP_G_GAM=\
	 am_map.h \
	 d_englsh.h \
	 d_event.h \
	 d_french.h \
	 d_items.h \
	 d_main.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dstrings.h \
	 f_finale.h \
	 g_game.h \
	 hu_stuff.h \
	 i_system.h \
	 info.h \
	 m_argv.h \
	 m_fixed.h \
	 m_menu.h \
	 m_misc.h \
	 m_random.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_saveg.h \
	 p_setup.h \
	 p_spec.h \
	 p_tick.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_sky.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 st_stuff.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 wi_stuff.h \
	 z_zone.h \
	
NODEP_CPP_G_GAM=\
	 multires.h \
	

g_game.obj: $(SOURCE) $(DEP_CPP_G_GAM) 



SOURCE=.\hu_lib.c
DEP_CPP_HU_LI=\
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 hu_lib.h \
	 info.h \
	 m_fixed.h \
#	 m_swap.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	 v_video.h \
	
NODEP_CPP_HU_LI=\
	 multires.h \
	

hu_lib.obj: $(SOURCE) $(DEP_CPP_HU_LI) 



SOURCE=.\hu_stuff.c
DEP_CPP_HU_ST=\
	 d_console.h \
	 d_englsh.h \
	 d_event.h \
	 d_french.h \
	 d_think.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dstrings.h \
	 hu_lib.h \
	 hu_stuff.h \
	 m_fixed.h \
#	 m_swap.h \
	 r_defs.h \
	 s_sound.h \
	 sounds.h \
	 w_wad.h \
	 z_zone.h \
	

hu_stuff.obj: $(SOURCE) $(DEP_CPP_HU_ST) 



SOURCE=.\i_cd.c
DEP_CPP_I_CD_=\
	 i_cd.h \
	

i_cd.obj: $(SOURCE) $(DEP_CPP_I_CD_) 



SOURCE=.\i_joystick.c
DEP_CPP_I_JOYSTICK_=\
	 i_joystick.h \
	

i_joystick.obj: $(SOURCE) $(DEP_CPP_I_JOYSTICK_) 



SOURCE=.\i_midi.c
DEP_CPP_I_MID=\
	 i_midi.h \
	

i_midi.obj: $(SOURCE) $(DEP_CPP_I_MID) 



SOURCE=.\i_net.c
DEP_CPP_I_NET=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_net.h \
	 i_system.h \
	 info.h \
	 m_argv.h \
	 m_fixed.h \
	 p_mobj.h \
	 p_pspr.h \
	 tables.h \
	

i_net.obj: $(SOURCE) $(DEP_CPP_I_NET) 



SOURCE=.\i_sound.c
DEP_CPP_I_SOU=\
	 d_event.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_sound.h \
	 i_system.h \
	 m_argv.h \
	 m_misc.h \
	 sounds.h \
	 w_wad.h \
	 z_zone.h \
	

i_sound.obj: $(SOURCE) $(DEP_CPP_I_SOU) 



SOURCE=.\i_system.c
DEP_CPP_I_SYS=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 g_game.h \
	 i_sound.h \
	 i_system.h \
	 i_video.h \
	 m_misc.h \
	 sounds.h \
	

i_system.obj: $(SOURCE) $(DEP_CPP_I_SYS) 



SOURCE=.\i_video.c
DEP_CPP_I_VID=\
	 d_event.h \
	 d_items.h \
	 d_main.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_argv.h \
	 m_fixed.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_data.h \
	 r_defs.h \
	 r_state.h \
	 tables.h \
	 v_video.h \
	

i_video.obj: $(SOURCE) $(DEP_CPP_I_VID) 



SOURCE=.\info.c
DEP_CPP_INFO_=\
	 d_think.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 info.h \
	 m_fixed.h \
	 p_mobj.h \
	 sounds.h \
	 tables.h \
	

info.obj: $(SOURCE) $(DEP_CPP_INFO_) 



SOURCE=.\m_argv.c

m_argv.obj: $(SOURCE) 



SOURCE=.\m_bbox.c
DEP_CPP_M_BBO=\
	 m_bbox.h \
	 m_fixed.h \
	

m_bbox.obj: $(SOURCE) $(DEP_CPP_M_BBO) 



SOURCE=.\m_cheat.c
DEP_CPP_M_CHE=\
	 m_cheat.h \
	

m_cheat.obj: $(SOURCE) $(DEP_CPP_M_CHE) 



SOURCE=.\m_fixed.c
DEP_CPP_M_FIX=\
	 d_event.h \
	 d_ticcmd.h \
	 doomtype.h \
	 i_system.h \
	 m_fixed.h \
	

m_fixed.obj: $(SOURCE) $(DEP_CPP_M_FIX) 



SOURCE=.\m_menu.c
DEP_CPP_M_MEN=\
	 d_console.h \
	 d_englsh.h \
	 d_event.h \
	 d_french.h \
	 d_items.h \
	 d_main.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dstrings.h \
	 g_game.h \
	 hu_stuff.h \
	 i_system.h \
	 i_video.h \
	 info.h \
	 m_argv.h \
	 m_fixed.h \
	 m_menu.h \
#	 m_swap.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_M_MEN=\
	 multires.h \
	

m_menu.obj: $(SOURCE) $(DEP_CPP_M_MEN) 



SOURCE=.\m_misc.c
DEP_CPP_M_MIS=\
	 d_englsh.h \
	 d_event.h \
	 d_french.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dstrings.h \
	 hu_stuff.h \
	 i_system.h \
	 i_video.h \
	 info.h \
	 m_argv.h \
	 m_fixed.h \
	 m_misc.h \
#	 m_swap.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_data.h \
	 r_defs.h \
	 r_state.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 z_zone.h \
	

m_misc.obj: $(SOURCE) $(DEP_CPP_M_MIS) 



SOURCE=.\m_music.c
DEP_CPP_M_MUS=\
	 i_cd.h \
	 i_midi.h \
	

m_music.obj: $(SOURCE) $(DEP_CPP_M_MUS) 



SOURCE=.\m_random.c

m_random.obj: $(SOURCE) 



#SOURCE=.\m_swap.c
#DEP_CPP_M_SWA=\
#	 m_swap.h \
#	
#
#m_swap.obj: $(SOURCE) $(DEP_CPP_M_SWA) 



SOURCE=.\p_ceilng.c
DEP_CPP_P_CEI=\
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 info.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	 z_zone.h \
	

p_ceilng.obj: $(SOURCE) $(DEP_CPP_P_CEI) 



SOURCE=.\p_doors.c
DEP_CPP_P_DOO=\
	 d_englsh.h \
	 d_french.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dstrings.h \
	 info.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	 z_zone.h \
	

p_doors.obj: $(SOURCE) $(DEP_CPP_P_DOO) 



SOURCE=.\p_enemy.c
DEP_CPP_P_ENE=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 g_game.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 m_random.h \
	 p_local.h \
	 p_mobj.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	
NODEP_CPP_P_ENE=\
	 multires.h \
	

p_enemy.obj: $(SOURCE) $(DEP_CPP_P_ENE) 



SOURCE=.\p_floor.c
DEP_CPP_P_FLO=\
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 info.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	 z_zone.h \
	

p_floor.obj: $(SOURCE) $(DEP_CPP_P_FLO) 



SOURCE=.\p_inter.c
DEP_CPP_P_INT=\
	 am_map.h \
	 d_englsh.h \
	 d_event.h \
	 d_french.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dstrings.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 m_random.h \
	 p_inter.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	

p_inter.obj: $(SOURCE) $(DEP_CPP_P_INT) 



SOURCE=.\p_lights.c
DEP_CPP_P_LIG=\
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 info.h \
	 m_fixed.h \
	 m_random.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	 z_zone.h \
	

p_lights.obj: $(SOURCE) $(DEP_CPP_P_LIG) 



SOURCE=.\p_map.c
DEP_CPP_P_MAP=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_bbox.h \
	 m_fixed.h \
	 m_random.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	

p_map.obj: $(SOURCE) $(DEP_CPP_P_MAP) 



SOURCE=.\p_maputl.c
DEP_CPP_P_MAPU=\
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 info.h \
	 m_bbox.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	

p_maputl.obj: $(SOURCE) $(DEP_CPP_P_MAPU) 



SOURCE=.\p_mobj.c

DEP_CPP_P_MOB=\
	 d_event.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 hu_stuff.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 m_random.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 st_stuff.h \
	 tables.h \
	 z_zone.h \
	
NODEP_CPP_P_MOB=\
	 multires.h \
	

p_mobj.obj: $(SOURCE) $(DEP_CPP_P_MOB) 



SOURCE=.\p_plats.c
DEP_CPP_P_PLA=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 m_random.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	 z_zone.h \
	

p_plats.obj: $(SOURCE) $(DEP_CPP_P_PLA) 



SOURCE=.\p_pspr.c
DEP_CPP_P_PSP=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 info.h \
	 m_fixed.h \
	 m_random.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	
NODEP_CPP_P_PSP=\
	 multires.h \
	

p_pspr.obj: $(SOURCE) $(DEP_CPP_P_PSP) 



SOURCE=.\p_saveg.c
DEP_CPP_P_SAV=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	 z_zone.h \
	

p_saveg.obj: $(SOURCE) $(DEP_CPP_P_SAV) 



SOURCE=.\p_setup.c
DEP_CPP_P_SET=\
	 d_event.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 g_game.h \
	 i_system.h \
	 info.h \
	 m_bbox.h \
	 m_fixed.h \
#	 m_swap.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 tables.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_P_SET=\
	 multires.h \
	

p_setup.obj: $(SOURCE) $(DEP_CPP_P_SET) 



SOURCE=.\p_sight.c
DEP_CPP_P_SIG=\
	 d_event.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	

p_sight.obj: $(SOURCE) $(DEP_CPP_P_SIG) 



SOURCE=.\p_spec.c
DEP_CPP_P_SPE=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 g_game.h \
	 i_system.h \
	 info.h \
	 m_argv.h \
	 m_fixed.h \
	 m_random.h \
	 p_local.h \
	 p_mobj.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_P_SPE=\
	 multires.h \
	

p_spec.obj: $(SOURCE) $(DEP_CPP_P_SPE) 



SOURCE=.\p_switch.c
DEP_CPP_P_SWI=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 g_game.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	
NODEP_CPP_P_SWI=\
	 multires.h \
	

p_switch.obj: $(SOURCE) $(DEP_CPP_P_SWI) 



SOURCE=.\p_telept.c
DEP_CPP_P_TEL=\
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 info.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	

p_telept.obj: $(SOURCE) $(DEP_CPP_P_TEL) 



SOURCE=.\p_tick.c
DEP_CPP_P_TIC=\
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 info.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	 z_zone.h \
	

p_tick.obj: $(SOURCE) $(DEP_CPP_P_TIC) 



SOURCE=.\p_user.c
DEP_CPP_P_USE=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 info.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	
NODEP_CPP_P_USE=\
	 multires.h \
	

p_user.obj: $(SOURCE) $(DEP_CPP_P_USE) 



SOURCE=.\r_bsp.c
DEP_CPP_R_BSP=\
	 d_event.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_bbox.h \
	 m_fixed.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_data.h \
	 r_defs.h \
	 r_main.h \
	 r_plane.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	

r_bsp.obj: $(SOURCE) $(DEP_CPP_R_BSP) 



SOURCE=.\r_data.c
DEP_CPP_R_DAT=\
	 d_event.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
#	 m_swap.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_sky.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_R_DAT=\
	 multires.h \
	

r_data.obj: $(SOURCE) $(DEP_CPP_R_DAT) 



SOURCE=.\r_main.c
DEP_CPP_R_MAI=\
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 info.h \
	 m_bbox.h \
	 m_fixed.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_sky.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	
NODEP_CPP_R_MAI=\
	 multires.h \
	

r_main.obj: $(SOURCE) $(DEP_CPP_R_MAI) 



SOURCE=.\r_plane.c
DEP_CPP_R_PLA=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_sky.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_R_PLA=\
	 multires.h \
	

r_plane.obj: $(SOURCE) $(DEP_CPP_R_PLA) 



SOURCE=.\r_segs.c
DEP_CPP_R_SEG=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_draw.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_sky.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	

r_segs.obj: $(SOURCE) $(DEP_CPP_R_SEG) 



SOURCE=.\r_sky.c
DEP_CPP_R_SKY=\
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 info.h \
	 m_fixed.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_data.h \
	 r_defs.h \
	 r_sky.h \
	 r_state.h \
	 tables.h \
	

r_sky.obj: $(SOURCE) $(DEP_CPP_R_SKY) 



SOURCE=.\r_things.c
DEP_CPP_R_THI=\
	 d_event.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
#	 m_swap.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_R_THI=\
	 multires.h \
	

r_things.obj: $(SOURCE) $(DEP_CPP_R_THI) 



SOURCE=.\s_sound.c
DEP_CPP_S_SOU=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_sound.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 m_random.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_S_SOU=\
	 multires.h \
	

s_sound.obj: $(SOURCE) $(DEP_CPP_S_SOU) 



SOURCE=.\sounds.c
DEP_CPP_SOUND=\
	 doomtype.h \
	 sounds.h \
	

sounds.obj: $(SOURCE) $(DEP_CPP_SOUND) 



SOURCE=.\st_lib.c
DEP_CPP_ST_LI=\
	 d_event.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
#	 m_swap.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 st_lib.h \
	 st_stuff.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_ST_LI=\
	 multires.h \
	

st_lib.obj: $(SOURCE) $(DEP_CPP_ST_LI) 



SOURCE=.\st_stuff.c
DEP_CPP_ST_ST=\
	 am_map.h \
	 d_englsh.h \
	 d_event.h \
	 d_french.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dstrings.h \
	 g_game.h \
	 i_system.h \
	 i_video.h \
	 info.h \
	 m_cheat.h \
	 m_fixed.h \
	 m_random.h \
	 p_inter.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 st_lib.h \
	 st_stuff.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_ST_ST=\
	 multires.h \
	

st_stuff.obj: $(SOURCE) $(DEP_CPP_ST_ST) 



SOURCE=.\tables.c
DEP_CPP_TABLE=\
	 m_fixed.h \
	 tables.h \
	

tables.obj: $(SOURCE) $(DEP_CPP_TABLE) 



SOURCE=.\w_wad.c
DEP_CPP_W_WAD=\
	 d_event.h \
	 d_ticcmd.h \
	 doomtype.h \
	 i_system.h \
#	 m_swap.h \
	 w_wad.h \
	 z_zone.h \
	

w_wad.obj: $(SOURCE) $(DEP_CPP_W_WAD) 



SOURCE=.\wi_stuff.c
DEP_CPP_WI_ST=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 g_game.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 m_random.h \
#	 m_swap.h \
	 p_mobj.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 s_sound.h \
	 sounds.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 wi_stuff.h \
	 z_zone.h \
	
NODEP_CPP_WI_ST=\
	 multires.h \
	

wi_stuff.obj: $(SOURCE) $(DEP_CPP_WI_ST) 



SOURCE=.\WINDOOM.c
DEP_CPP_WINDO=\
	 d_console.h \
	 d_event.h \
	 d_items.h \
	 d_main.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dxerr.h \
	 g_game.h \
	 i_cd.h \
	 i_midi.h \
	 i_system.h \
	 info.h \
	 m_argv.h \
	 m_fixed.h \
	 m_music.h \
	 p_mobj.h \
	 p_pspr.h \
	 tables.h \
	

WINDOOM.obj: $(SOURCE) $(DEP_CPP_WINDO) 



SOURCE=.\am_map.c
DEP_CPP_AM_MA=\
	 am_map.h \
	 d_englsh.h \
	 d_event.h \
	 d_french.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 dstrings.h \
	 i_system.h \
	 info.h \
	 m_cheat.h \
	 m_fixed.h \
	 p_local.h \
	 p_mobj.h \
	 p_pspr.h \
	 p_spec.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 st_stuff.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_AM_MA=\
	 multires.h \
	

am_map.obj: $(SOURCE) $(DEP_CPP_AM_MA) 



SOURCE=.\z_zone.c
DEP_CPP_Z_ZON=\
	 d_event.h \
	 d_ticcmd.h \
	 doomdef.h \
	 doomtype.h \
	 i_system.h \
	 z_zone.h \
	

z_zone.obj: $(SOURCE) $(DEP_CPP_Z_ZON) 



SOURCE=.\qmus2mid.c
DEP_CPP_QMUS2=\
	 qmus2mid.h \
	

qmus2mid.obj: $(SOURCE) $(DEP_CPP_QMUS2) 



SOURCE=.\r_draw.c
DEP_CPP_R_DRA=\
	 d_event.h \
	 d_items.h \
	 d_net.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomstat.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_fixed.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	 v_video.h \
	 w_wad.h \
	 z_zone.h \
	
NODEP_CPP_R_DRA=\
	 multires.h \
	

r_draw.obj: $(SOURCE) $(DEP_CPP_R_DRA) 



SOURCE=.\v_video.c
DEP_CPP_V_VID=\
	 d_event.h \
	 d_items.h \
	 d_player.h \
	 d_think.h \
	 d_ticcmd.h \
	 doomdata.h \
	 doomdef.h \
	 doomtype.h \
	 i_system.h \
	 info.h \
	 m_bbox.h \
	 m_fixed.h \
#	 m_swap.h \
	 p_mobj.h \
	 p_pspr.h \
	 r_bsp.h \
	 r_data.h \
	 r_defs.h \
	 r_local.h \
	 r_main.h \
	 r_plane.h \
	 r_segs.h \
	 r_state.h \
	 r_things.h \
	 tables.h \
	 v_video.h \
	
NODEP_CPP_V_VID=\
	 multires.h \
	

v_video.obj: $(SOURCE) $(DEP_CPP_V_VID) 


CLEAN: 
	-@erase  am_map.obj 
	-@erase  d_console.obj 
	-@erase  d_items.obj 
	-@erase  d_main.obj 
	-@erase  d_net.obj 
	-@erase  doomdef.obj 
	-@erase  doomstat.obj 
	-@erase  dstrings.obj 
	-@erase  dxerr.obj 
	-@erase  f_finale.obj 
	-@erase  f_wipe.obj 
	-@erase  g_game.obj 
	-@erase  hu_lib.obj 
	-@erase  hu_stuff.obj 
	-@erase  i_cd.obj 
	-@erase  i_main.obj 
	-@erase  i_midi.obj 
	-@erase  i_net.obj 
	-@erase  i_sound.obj 
	-@erase  i_system.obj 
	-@erase  i_video.obj 
	-@erase  info.obj 
	-@erase  m_argv.obj 
	-@erase  m_bbox.obj 
	-@erase  m_cheat.obj 
	-@erase  m_fixed.obj 
	-@erase  m_menu.obj 
	-@erase  m_misc.obj 
	-@erase  m_music.obj 
	-@erase  m_random.obj 
#	-@erase  m_swap.obj 
	-@erase  p_ceilng.obj 
	-@erase  p_doors.obj 
	-@erase  p_enemy.obj 
	-@erase  p_floor.obj 
	-@erase  p_inter.obj 
	-@erase  p_lights.obj 
	-@erase  p_map.obj 
	-@erase  p_maputl.obj 
	-@erase  p_mobj.obj 
	-@erase  p_plats.obj 
	-@erase  p_pspr.obj 
	-@erase  p_saveg.obj 
	-@erase  p_setup.obj 
	-@erase  p_sight.obj 
	-@erase  p_spec.obj 
	-@erase  p_switch.obj 
	-@erase  p_telept.obj 
	-@erase  p_tick.obj 
	-@erase  p_user.obj 
	-@erase  qmus2mid.obj 
	-@erase  r_bsp.obj 
	-@erase  r_data.obj 
	-@erase  r_draw.obj 
	-@erase  r_main.obj 
	-@erase  r_plane.obj 
	-@erase  r_segs.obj 
	-@erase  r_sky.obj 
	-@erase  r_things.obj 
	-@erase  s_sound.obj 
	-@erase  sounds.obj 
	-@erase  st_lib.obj 
	-@erase  st_stuff.obj 
	-@erase  tables.obj 
	-@erase  v_video.obj 
	-@erase  w_wad.obj 
	-@erase  wi_stuff.obj 
	-@erase  WINDOOM.obj 
	-@erase  z_zone.obj 
	-@erase  OS2Doom.exe 

