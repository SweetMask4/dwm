/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const int horizpadbar        = 6;        /* horizontal padding for statusbar */
static const int vertpadbar         = 7;        /* vertical padding for statusbar */
#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */

static const char *fonts[] = {"Iosevka:weight=regular:size=10:antialias=true:hinting=true" ,
                              "JetBrainsMono Nerd Font Mono:size=19:antialias=true:autohint=true",
                             };
// scratchpads
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x34", "-e", "lf", NULL };
// const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	// {"keepassxc",   spcmd3},
};

// Theme
#include "themes/catppuccin.h"
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { gray, black, black },
	[SchemeSel]  = { gray, black,  black  }
	// [SchemeLayout]  = { green, black,  black  },
	// [SchemeTitle]  = { white, black,  black  },
};

/* tagging */
static const char *tags[] = { "", "","", "", "", "", "", "", "", ""  };

static const char *tagsel[][2] = {
	{ pink, black },
	{ mauve, black },
	{ red, black },
	{ maroon, black },
	{ peach, black },
    { yellow, black },
    { red, black },
    { pink, black },
    { peach, black },
    { mauve,black },
};

// underlinetags
static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",	  NULL,			NULL,		0,				1,			 -1 },
	{ "Firefox",  NULL,			NULL,		1 << 8,			0,			 -1 },
	{ NULL,		  "spterm",		NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spfm",		NULL,		SPTAG(1),		1,			 -1 },
	// { NULL,		  "keepassxc",	NULL,		SPTAG(2),		0,			 -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "horizgrid.c"
#include "fibonacci.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
    { "---",      gaplessgrid },
 	{ "[\\]",     dwindle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "###",      horizgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu-run", NULL };
static const char *termcmd[]  = { "st", NULL };
// static const char *upvol[] = { "volume up", NULL };
// static const char *downvol[] = { "volume down", NULL};
// static const char *mutevol[] = { "volume mute", NULL};

// constants
#define EMACS "emacsclient -c -a 'emacs'"

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */

    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_w,      killclient,     {0} },
	
	// vanitygaps
    { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	
    // tag view
	{ MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	
    // Switch between windows
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

    // Toggle bar
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },

    // Move windows in current stack
    { MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },

    // Change window sizes
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },

    // Layout manipulation 	
    { MODKEY|ControlMask,		    XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, /* float */ 
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, /* monocle */
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} }, /* grid */    
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[4]} }, /* fibonacci */
	{ MODKEY|ShiftMask,             XK_v,      setlayout,      {.v = &layouts[5]} }, /* fibonacci */
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[6]} }, /* bottomstack */
	{ MODKEY|ShiftMask,             XK_o,      setlayout,      {.v = &layouts[7]} }, /* bottomstack */
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[8]} }, /* bottomstack */
    { MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[9]} }, /* bottomstack */
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ControlMask,           XK_Return, zoom,           {0} },

    // scratchpads
    { MODKEY,            			XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            			XK_x,	   togglescratch,  {.ui = 2 } },

    // Switching between monitors 
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    
    // Workspaces
    TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	
    // Restart or quit dwm 
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask, XK_r,       quit,                      {1} }, 

    // Apps
    { MODKEY,                       XK_b, spawn, SHCMD("firefox") },
    { MODKEY,                       XK_a, spawn, SHCMD("pcmanfm") },
    { MODKEY,                       XK_p, spawn, SHCMD("passmenu -p \"Pass: \"")},
    { MODKEY,                       XK_r, spawn, SHCMD("redshift -O 2400") },
    { MODKEY|ShiftMask,             XK_r, spawn, SHCMD("redshift -x") },

    // Emacs
    { MODKEY,                       XK_e, spawn, SHCMD(EMACS "--eval '(dashboard-refresh-buffer)'" ) },

    // Volume
    {0, XF86XK_AudioLowerVolume,    spawn, SHCMD("volume down")},
    {0, XF86XK_AudioRaiseVolume,    spawn, SHCMD("volume up")},
    {0, XF86XK_AudioMute,           spawn, SHCMD("volume mute")},

    // My scripts
    { MODKEY,                       XK_F2,     spawn,          SHCMD("xwallpapers") }, 
    { MODKEY,                       XK_x,      spawn,          SHCMD("dm-monitors")},
    { MODKEY,                       XK_z,      spawn,          SHCMD("changexmap")},
    { MODKEY,                       XK_d,      spawn,          SHCMD("dm-documents")},
    { MODKEY,                       XK_q,      spawn,          SHCMD("dm-logout")},
    { MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("dm-kill")},
    { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("dm-confedit")},
    { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("dm-wifi")},
    { MODKEY|ControlMask|ShiftMask, XK_b,      spawn,          SHCMD("dm-setbg")},
    { MODKEY|ControlMask|ShiftMask, XK_a,      spawn,          SHCMD("dm-emojis")},
    { 0,                            XK_Print,  spawn,          SHCMD("dm-maim")},
 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

