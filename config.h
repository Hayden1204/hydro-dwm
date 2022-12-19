/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 15, .gappx = 15};
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no standard bar */
static const int topbar             = 1;        /* 0 means standard bar at bottom */
static const int extrabar           = 1;        /* 0 means no extra bar */
static const char statussep         = ';';      /* separator between statuses */
static const char *fonts[]          = { "JetBrains Mono:size=13" };
static const char dmenufont[]       = "JetBrains Mono:size=13";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#5294e2";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *const autostart[] = {
	"pipewire", NULL,
	"pipewire-pulse", NULL,
	"wireplumber", NULL,
	"redshift", NULL,
	"picom", "--no-fading-openclose", NULL,
	"nitrogen", "--restore", NULL,
	"slstatus", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",             NULL,     NULL,           0,         0,          0,           0,        -1 },
	{ "LibreWolf",        NULL,     NULL,           0,         0,          0,          -1,        -1 },
	{ "st-256color",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,               NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ "Gnome-screenshot", NULL,     NULL,           0,         1,          0,           1,        -1 },
	{ "Pavucontrol",      NULL,     NULL,           0,         1,          0,           1,        -1 },
	{ "Bitwarden",        NULL,     NULL,           0,         1,          0,           1,        -1 },
	{ "Usbimager",        NULL,     NULL,           0,         1,          0,           1,        -1 },
	{ "PollyMC",          NULL,     NULL,           0,         1,          0,           1,        -1 },
	{ "antimicrox",       NULL,     NULL,           0,         1,          0,           1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.475; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;     /* number of clients in master area */
static const int resizehints = 1;     /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;  /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *appearancecmd[] = { "lxappearance", NULL };
static const char *screenshotcmd[] = { "gnome-screenshot", "-i", NULL };
static const char *audioctrlcmd[]  = { "pavucontrol", NULL };
static const char *browsercmd[]    = { "librewolf", NULL };
static const char *filemancmd[]    = { "pcmanfm", NULL };
static const char *passmancmd[]    = { "bitwarden-desktop", NULL };
static const char *virtmancmd[]    = { "virt-manager", NULL };
static const char *youtubecmd[]    = { "freetube", NULL };
static const char *editorcmd[]     = { "st", "-e", "nvim", NULL };
static const char *matrixcmd[]     = { "element-desktop", NULL };
static const char *signalcmd[]     = { "signal-desktop", NULL };
static const char *imagercmd[]     = { "usbimager", NULL };

static const Key keys[] = {
	/* modifier                     key           function        argument */
	{ MODKEY|ShiftMask,             XK_Return,    spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,    spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_w,         spawn,          {.v = appearancecmd } },
	{ MODKEY|ShiftMask,             XK_k,         spawn,          {.v = screenshotcmd } },
	{ MODKEY|ShiftMask,             XK_a,         spawn,          {.v = audioctrlcmd } },
	{ MODKEY|ShiftMask,             XK_u,         spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_d,         spawn,          {.v = filemancmd } },
	{ MODKEY|ShiftMask,             XK_p,         spawn,          {.v = passmancmd } },
	{ MODKEY|ShiftMask,             XK_v,         spawn,          {.v = virtmancmd } },
	{ MODKEY|ShiftMask,             XK_y,         spawn,          {.v = youtubecmd } },
	{ MODKEY|ShiftMask,             XK_e,         spawn,          {.v = editorcmd } },
	{ MODKEY|ShiftMask,             XK_m,         spawn,          {.v = matrixcmd } },
	{ MODKEY|ShiftMask,             XK_s,         spawn,          {.v = signalcmd } },
	{ MODKEY|ShiftMask,             XK_i,         spawn,          {.v = imagercmd } },
	{ MODKEY,                       XK_b,         togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_b,         toggleextrabar, {0} },
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_BackSpace, zoom,           {0} },
	{ MODKEY,                       XK_Tab,       view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,         killclient,     {0} },
	{ MODKEY,                       XK_t,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,     setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,     togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,         togglefullscr,  {0} },
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,         tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,    tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,     setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,     setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,     setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,     setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                         0)
	TAGKEYS(                        XK_2,                         1)
	TAGKEYS(                        XK_3,                         2)
	TAGKEYS(                        XK_4,                         3)
	TAGKEYS(                        XK_5,                         4)
	TAGKEYS(                        XK_6,                         5)
	TAGKEYS(                        XK_7,                         6)
	TAGKEYS(                        XK_8,                         7)
	TAGKEYS(                        XK_9,                         8)
	{ MODKEY|ShiftMask,             XK_q,         quit,           {0} },
	{ MODKEY|ShiftMask,             XK_x,         quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarLeftStatus,   0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarMiddle,       0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarRightStatus,  0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

