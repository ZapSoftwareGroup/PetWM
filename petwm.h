#include <X11/Xlib.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

/* The X display pointer */
static Display* dpy;

static int (*xerrorxlib)(Display*, XErrorEvent*);

/* Error handlers */
static int handlestartxerror(Display *dpy, XErrorEvent *ee);
static int handlexerror(Display *dpy, XErrorEvent *ee);

static int running = 1;

void handlexevent(XEvent* e);

void run();

void die(const char*, ...);

void check_for_other_wm();
