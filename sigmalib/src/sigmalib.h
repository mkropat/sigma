#ifndef _SIGMALIB_H
#define _SIGMALIB_H

#include <cairo.h>
#include <X11/Xlib.h>

typedef struct {
  cairo_surface_t *surface;
  cairo_t *cr;
  Display *display;
  Window window;
} sigma_context_t;

sigma_context_t *sigma_init();
void sigma_loop(sigma_context_t *);
void sigma_cleanup(sigma_context_t *);

#endif
