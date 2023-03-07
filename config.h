/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 6;        /* horizontal padding for statusbar */
static const int vertpadbar         = 7;        /* vertical padding for statusbar */
static const int colorfultag        = 1;        /* 0 means use SchemeSel for selected non vacant tag */
#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */

static const char *fonts[] = {
    "Ubuntu:weight=medium:size=10:antialias=true:hinting=true",
    "JetBrainsMono Nerd Font Mono:size=19:antialias=true:autohint=true"
};

// Constants
#define TERMINAL "st"
#define TERMCLASS "st-256color"
#define BROWSER "firefox"
#define EMACS "emacsclient -c -a 'emacs' "

// scratchpads
typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spfm", "-g", "144x34", "-e", "lfrun", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
const char *spcmd4[] = {TERMINAL, "-n", "spcalc", "-f", "Ubuntu:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keepassxc",   spcmd3},
  {"spcalc",      spcmd4},
};


/*
 * SELECT YOUR COLOR SCHEME
 * Available themes are:
 * 1. dracula.h
 * 2. gruvchad.h
 * 3. nord.h
 * 4.catppuccin.h
 */

#include "themes/catppuccin.h"
static const char *colors[][3]      = {
    /*                     fg       bg      border */
    [SchemeNorm]       = { gray3,   black,  gray2 },
    [SchemeSel]        = { gray4,   blue,   blue  },
    [SchemeTitle]      = { white,   black,  black }, // active window title
    [TabSel]           = { blue,    gray2,  black },
    [TabNorm]          = { gray3,   black,  black },
    [SchemeTag]        = { gray3,   black,  black },
    [SchemeTag1]       = { blue,    black,  black },
    [SchemeTag2]       = { red,     black,  black },
    [SchemeTag3]       = { orange,  black,  black },
    [SchemeTag4]       = { green,   black,  black },
    [SchemeTag5]       = { pink,    black,  black },
    [SchemeTag6]       = { yellow,  black,  black },
    [SchemeTag7]       = { purple,  black,  black },
    [SchemeTag8]       = { cyan,    black,  black },
    [SchemeTag9]       = { Magenta, black,  black },
    [SchemeLayout]     = { green,   black,  black },
    [SchemeBtnPrev]    = { green,   black,  black },
    [SchemeBtnNext]    = { yellow,  black,  black },
    [SchemeBtnClose]   = { red,     black,  black },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", ""  };

static const int tagschemes[] = {
    SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5, SchemeTag6, SchemeTag7, SchemeTag8, SchemeTag9
};

// underlinetags
static const unsigned int ulinepad      = 5;    /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke   = 2;    /* thickness / height of the underline */
static const unsigned int ulinevoffset  = 0;    /* how far above the bottom of the bar the line should appear */
static const int ulineall               = 0;    /* 1 to show underline on all tags, 0 for just the active ones */


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class               instance      title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",              NULL,         NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",           NULL,         NULL,           1 << 8,    0,          0,          -1,        -1 },
  { "TelegramDesktop",   NULL,         NULL,           0,         1,          0,          -1,        -1 },
	{ TERMCLASS,           NULL,         NULL,           0,         0,          1,           0,        -1 },
	{ NULL,                NULL,         "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
  { NULL,                "spterm",     NULL,         SPTAG(0),    1,          0,           0,        -1 },
	{ NULL,                "spfm",       NULL,         SPTAG(1),    1,          0,           0,        -1 },
  { NULL,                "keepassxc",  NULL,         SPTAG(2),    1,          0,           0,        -1 },
  { NULL,                "spcalc",     NULL,         SPTAG(3),    1,          0,           0,        -1 },
  { NULL,                "yad",        NULL,         0,           1,          0,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "[M]",      monocle },
    { "[@]",      spiral },
  	{ "[\\]",     dwindle },
  	{ "H[]",      deck },
  	{ "TTT",      bstack },
  	{ "===",      bstackhoriz },
  	{ "HHH",      grid },
  	{ "###",      nrowgrid },
  	{ "---",      horizgrid },
  	{ ":::",      gaplessgrid },
  	{ "|M|",      centeredmaster },
  	{ ">M>",      centeredfloatingmaster },
  	{ "><>",      NULL },    /* no layout function means floating behavior */
  	{ NULL,       NULL },	
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)												\
	&((Keychord){1, {{MODKEY, KEY}},								view,           {.ui = 1 << TAG} }), \
		&((Keychord){1, {{MODKEY|ControlMask, KEY}},					toggleview,     {.ui = 1 << TAG} }), \
		&((Keychord){1, {{MODKEY|ShiftMask, KEY}},						tag,            {.ui = 1 << TAG} }), \
		&((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},			toggletag,      {.ui = 1 << TAG} }),

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dm-run", NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *browser[]  = { BROWSER, NULL };

#include <X11/XF86keysym.h>
static Keychord *keychords[] = {
    /* modifier                 key         function          argument */
    &((Keychord){1, {{MODKEY|ShiftMask, XK_Return}},          spawn,         {.v = dmenucmd } }),
    &((Keychord){1, {{MODKEY, XK_Return}},                    spawn,         {.v = termcmd }}),
    &((Keychord){1, {{MODKEY, XK_w}},                         killclient,    {0} }),

    // vanitygaps
    &((Keychord){1, {{MODKEY|ControlMask, XK_h}},             incrgaps,       {.i = +1 } }),
    &((Keychord){1, {{MODKEY|ControlMask, XK_l}},             incrgaps,       {.i = -1 } }),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_h}},               incrogaps,      {.i = +1 } }),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_l}},               incrogaps,      {.i = -1 } }),
    &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, XK_h}},   incrigaps,      {.i = +1 } }),
    &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, XK_l}},   incrigaps,      {.i = -1 } }),
    &((Keychord){1, {{MODKEY|Mod1Mask, XK_0}},                togglegaps,     {0} }),
    &((Keychord){1, {{MODKEY|Mod1Mask|ShiftMask, XK_0}},      defaultgaps,    {0} }),
    &((Keychord){1, {{MODKEY|ShiftMask,   XK_y}},             incrihgaps,     {.i = +1 } }),
    &((Keychord){1, {{MODKEY|ShiftMask,   XK_o}},             incrihgaps,     {.i = -1 } }),
    &((Keychord){1, {{MODKEY|ControlMask, XK_y}},             incrivgaps,     {.i = +1 } }),
    &((Keychord){1, {{MODKEY|ControlMask, XK_o}},             incrivgaps,     {.i = -1 } }),
    &((Keychord){1, {{MODKEY|Mod1Mask,  XK_y}},               incrohgaps,     {.i = +1 } }),
    &((Keychord){1, {{MODKEY|Mod1Mask,  XK_o}},               incrohgaps,     {.i = -1 } }),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_y}},               incrovgaps,     {.i = +1 } }),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_o}},               incrovgaps,     {.i = -1 } }),
    // tag view
    &((Keychord){1, {{MODKEY, XK_Tab}},             view,           {0} }),
    &((Keychord){1, {{MODKEY, XK_0}},               view,           {.ui = ~0 } }),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_0}},     tag,            {.ui = ~0 } }),

    // Switch between windows
    &((Keychord){1, {{MODKEY, XK_j}},      focusstack,     {.i = +1 } }),
    &((Keychord){1, {{MODKEY, XK_k}},      focusstack,     {.i = -1 } }),

    // Toggle bar
    &((Keychord){1, {{MODKEY|ShiftMask, XK_b}},      togglebar,      {0} }),

    // Move windows in current stack
    &((Keychord){1, {{MODKEY|ShiftMask, XK_j}},      rotatestack,    {.i = +1 } }),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_k}},      rotatestack,    {.i = -1 } }),

    // Change window sizes
    &((Keychord){1, {{MODKEY, XK_s}},      incnmaster,     {.i = -1 } }),
    &((Keychord){1, {{MODKEY, XK_h}},      setmfact,       {.f = -0.05} }),
    &((Keychord){1, {{MODKEY, XK_l}},      setmfact,       {.f = +0.05} }),
    &((Keychord){1, {{MODKEY, XK_i}},      incnmaster,     {.i = +1 } }),

    // Layout manipulation 	
    &((Keychord){1, {{MODKEY|ControlMask, XK_comma}},  cyclelayout,  {.i = -1 } }),
    &((Keychord){1, {{MODKEY|ControlMask, XK_period}}, cyclelayout,  {.i = +1 } }),
    &((Keychord){1, {{MODKEY, XK_t}},                  setlayout,    {.v = &layouts[0]} }),
    &((Keychord){1, {{MODKEY, XK_m}},                  setlayout,    {.v = &layouts[1]} }),
    &((Keychord){1, {{MODKEY, XK_n}},                  setlayout,    {.v = &layouts[2]} }),
    &((Keychord){1, {{MODKEY, XK_g}},                  setlayout,    {.v = &layouts[7]} }),
    &((Keychord){1, {{MODKEY, XK_f}},                  setlayout,    {.v = &layouts[13]}}),
    &((Keychord){1, {{MODKEY, XK_space}},              setlayout,    {0} }),
    &((Keychord){1, {{MODKEY|ControlMask, XK_Return}}, zoom,         {0} }),

    // scratchpads
    &((Keychord){1, {{MODKEY, XK_y}},               togglescratch,  {.ui = 0 } }),
    &((Keychord){1, {{MODKEY, XK_u}},               togglescratch,  {.ui = 1 } }),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_t}},     togglescratch,  {.ui = 2 } }),
    &((Keychord){1, {{MODKEY, XK_Escape}},          togglescratch,  {.ui = 3 } }),
    // &((Keychord){1, {{MODKEY, XK_z}},               togglescratch,  {.ui = 4 } }),

    // Switching between monitors 
    &((Keychord){1, {{MODKEY, XK_comma}},            focusmon,      {.i = -1 } }),
    &((Keychord){1, {{MODKEY, XK_period}},           focusmon,      {.i = +1 } }),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_comma}},  tagmon,        {.i = -1 } }),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_period}}, tagmon,        {.i = +1 } }),

    // Tags
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
    &((Keychord){1, {{MODKEY|ShiftMask, XK_q}},      quit,      {0} }),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_r}},      quit,      {1} }),

    // Apps
    &((Keychord){1, {{MODKEY, XK_b}},                spawn,     {.v = browser }}),
    &((Keychord){1, {{MODKEY, XK_a}},                 spawn,     SHCMD("pcmanfm")}),
    &((Keychord){1, {{MODKEY, XK_r}},                spawn,     SHCMD("redshift -O 2400") }),
    &((Keychord){1, {{MODKEY|Mod1Mask, XK_r}},       spawn,     SHCMD("redshift -x") }),
    &((Keychord){1, {{MODKEY|Mod1Mask, XK_h}},       spawn,     SHCMD(TERMINAL " -e htop")}),

    // Dunst
    &((Keychord){2, {{MODKEY, XK_d}, {0, XK_q}},     spawn,     SHCMD("dunstctl close-all")}),
    &((Keychord){2, {{MODKEY, XK_d}, {0, XK_h}},     spawn,     SHCMD("dunstctl history-pop")}),
    &((Keychord){2, {{MODKEY, XK_d}, {0, XK_w}},     spawn,     SHCMD("dunstctl close")}),

    // Emacs
    &((Keychord){2, {{MODKEY, XK_e}, {0, XK_e}},     spawn,     SHCMD( EMACS "--eval '(dashboard-refresh-buffer)'")}),
    &((Keychord){2, {{MODKEY, XK_e}, {0, XK_b}},     spawn,     SHCMD( EMACS "--eval '(ibuffer)'") }),
    &((Keychord){2, {{MODKEY, XK_e}, {0, XK_d}},     spawn,     SHCMD( EMACS "--eval '(dired nil)'") }),
    &((Keychord){2, {{MODKEY, XK_e}, {0, XK_i}},     spawn,     SHCMD( EMACS "--eval '(erc)'") }),
    &((Keychord){2, {{MODKEY, XK_e}, {0, XK_n}},     spawn,     SHCMD( EMACS "--eval '(elfeed)'") }),
    &((Keychord){2, {{MODKEY, XK_e}, {0, XK_s}},     spawn,     SHCMD( EMACS "--eval '(eshell)'") }),
    &((Keychord){2, {{MODKEY, XK_e}, {0, XK_v}},     spawn,     SHCMD( EMACS "--eval '(+vterm/here nil)'") }),

    // Volume
    &((Keychord){1,{{0, XF86XK_AudioLowerVolume}},   spawn,     SHCMD("volume down")}),
    &((Keychord){1,{{0, XF86XK_AudioRaiseVolume}},   spawn,     SHCMD("volume up")}),
    &((Keychord){1,{{0, XF86XK_AudioMute}},          spawn,     SHCMD("volume mute")}),

    // dmscripts
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_p}},     spawn,     SHCMD("passmenu -p \"Pass: \"")}),
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_m}},     spawn,     SHCMD("dm-monitors")}),
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_d}},     spawn,     SHCMD("dm-documents")}),
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_q}},     spawn,     SHCMD("dm-logout")}),
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_k}},     spawn,     SHCMD("dm-kill")}),
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_e}},     spawn,     SHCMD("dm-confedit")}),
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_w}},     spawn,     SHCMD("dm-wifi")}),
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_o}},     spawn,     SHCMD("dm-openvpn")}),
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_b}},     spawn,     SHCMD("dm-setbg")}),
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_g}},     spawn,     SHCMD("dm-emojis")}),
    &((Keychord){1, {{0,XK_Print}},                  spawn,     SHCMD("dm-maim")}),

    // My scripts
    &((Keychord){1, {{MODKEY,XK_F2}},                spawn,     SHCMD("xwallpapers")}),
    &((Keychord){1, {{MODKEY,XK_c}},                 spawn,     SHCMD("changexmap")}),
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

