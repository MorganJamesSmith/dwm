/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	/*{ "Gimp",     NULL,       NULL,       0,            1,           -1 },*/
	/*{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },*/
	{ "I DON'T LIKE RULES",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]         = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]          = { "emacsclient", "-create-frame", "-e", "(if (get-buffer \"vterm\") (switch-to-buffer \"vterm\") (vterm))", NULL };
static const char *calc[]             = { "st", "-e", "R", "--no-save", NULL };
static const char *editor[]           = { "emacsclient", "-create-frame", "-a=", NULL };
static const char *web[]              = { "tabbed", "-c", "-r", "2", "surf", "-e", "''", NULL };
static const char *lock[]             = { "slock", NULL };
static const char *volumedown[]       = { "lmc", "down", "5", NULL };
static const char *volumeup[]         = { "lmc", "up", "5", NULL };
static const char *volumemutetoggle[] = { "lmc", "mute", NULL };
static const char *volumemute[]       = { "lmc", "truemute", NULL };
static const char *songnext[]         = { "lmc", "next", NULL };
static const char *songprev[]         = { "lmc", "prev", NULL };
static const char *songtoggle[]       = { "lmc", "toggle", NULL };
static const char *songscrubf[]       = { "lmc", "f", "5", NULL };
static const char *songscrubb[]       = { "lmc", "b", "5", NULL };
static const char *songstatus[]       = { "notify", "songstatus", NULL };
static const char *backlightup[]      = { "xbacklight", "-steps", "1", "-time", "0", "-inc", "10", NULL };
static const char *backlightdown[]    = { "xbacklight", "-steps", "1", "-time", "0", "-dec", "10", NULL };
static const char *displayselect[]    = { "displayselect", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,    XF86XK_AudioLowerVolume,      spawn,          {.v = volumedown } },
	{ 0,         XF86XK_AudioLowerVolume,      spawn,          {.v = volumedown } },
	{ MODKEY,    XF86XK_AudioRaiseVolume,      spawn,          {.v = volumeup } },
	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          {.v = volumeup } },
	{ MODKEY,     XF86XK_MonBrightnessUp,      spawn,          {.v = backlightup } },
	{ 0,          XF86XK_MonBrightnessUp,      spawn,          {.v = backlightup } },
	{ MODKEY,   XF86XK_MonBrightnessDown,      spawn,          {.v = backlightdown } },
	{ 0,        XF86XK_MonBrightnessDown,      spawn,          {.v = backlightdown } },
	{ MODKEY,           XF86XK_AudioMute,      spawn,          {.v = volumemutetoggle } },
	{ 0,                XF86XK_AudioMute,      spawn,          {.v = volumemutetoggle } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_w,      spawn,          {.v = web } },
	{ MODKEY,                       XK_e,      spawn,          {.v = editor } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_a,      spawn,          {.v = calc } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_p,      spawn,          {.v = songtoggle } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = volumemutetoggle } },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_x,      spawn,          {.v = lock } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_F1,     spawn,          {.v = volumemute } },
	{ MODKEY,                       XK_F5,     spawn,          {.v = backlightdown } },
	{ MODKEY,                       XK_F6,     spawn,          {.v = backlightup } },
	{ MODKEY,                       XK_F7,     spawn,          {.v = displayselect } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                     XK_question, spawn,          {.v = songstatus } },
	{ MODKEY,                       XK_Up,     spawn,          {.v = volumeup } },
	{ MODKEY,                       XK_Down,   spawn,          {.v = volumedown } },
	{ MODKEY,                       XK_Right,  spawn,          {.v = songnext } },
	{ MODKEY|ShiftMask,             XK_Right,  spawn,          {.v = songscrubf } },
	{ MODKEY,                       XK_Left,   spawn,          {.v = songprev } },
	{ MODKEY|ShiftMask,             XK_Left,   spawn,          {.v = songscrubb } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

