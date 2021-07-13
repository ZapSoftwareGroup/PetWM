#include "petwm.h"

static int handlestartxerror(Display* dpy, XErrorEvent* ee)
{
	die("Another window manager is already running!");
	return 0;
}

static int handlexerror(Display *dpy, XErrorEvent *ee)
{
	die("Error: %d", ee->error_code);
	return 0;
}

void die(const char *format, ...)
{
    va_list vargs;
    va_start(vargs, format);
    vfprintf(stderr, format, vargs);
    fprintf(stderr, "\n");
    va_end(vargs);
    exit(1);
}

void check_for_other_wm()
{
	xerrorxlib = XSetErrorHandler(handlestartxerror);
	/* Asking for substructure redirection causes
	 * an error if another wm is already running */
	XSelectInput(dpy, DefaultRootWindow(dpy),
			SubstructureRedirectMask | SubstructureNotifyMask);
	/* Forcefully send the request to the xserver */
	XSync(dpy, False);
	/* Set the error handler to the default handler */
	XSetErrorHandler(handlexerror);
	XSync(dpy, False);
}

void handlexevent(XEvent* e)
{
	switch(e->type)
	{
		case CreateNotify:
			break;
		case DestroyNotify:
			break;
		default:
			printf("Unhandled event: %d\n", e->type);
	}
}

void run()
{
	/* This contains the main event loop */
	XEvent e;
	while(running && !XNextEvent(dpy, &e))
	{
		handlexevent(&e);
	}
}

int main(int argc, char** argv)
{
	/* Handle eventual cli parameters here */
	dpy = XOpenDisplay(NULL);
	if(!dpy)
	{
		printf("Cannot open display!\n");
		exit(1);
	}
	check_for_other_wm();

	run();

	XCloseDisplay(dpy);
	return EXIT_SUCCESS;
}
