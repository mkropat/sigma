#include <cairo-xlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "sigmalib.h"

static void draw(cairo_t *cr) {
  cairo_select_font_face(cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 48.0);
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_move_to(cr, 10.0, 50.0);
  cairo_show_text(cr, "Hello, world!");
}

sigma_context_t *sigma_init() {
  sigma_context_t *context = malloc(sizeof(sigma_context_t));
  context->cr = NULL;
  context->display = NULL;
  context->surface = NULL;
  context->window = 0;

  context->display = XOpenDisplay(NULL);
  if (context->display == NULL) {
    free(context);
    return NULL;
  }

  int screen = DefaultScreen(context->display);

  context->window = XCreateSimpleWindow(
    context->display,
    RootWindow(context->display, screen),
    10, 10,
    800, 600,
    1,
    BlackPixel(context->display, screen),
    WhitePixel(context->display, screen)
  );

  // Process Window Close Event through event handler so XNextEvent does Not fail
  Atom delWindow = XInternAtom(context->display, "WM_DELETE_WINDOW", 0);
  XSetWMProtocols(context->display , context->window, &delWindow, 1);

  XSelectInput(context->display, context->window, ExposureMask | KeyPressMask);

  /* map (show) the window */
  XMapWindow(context->display, context->window);

  cairo_surface_t *surface = cairo_xlib_surface_create(
    context->display,
    context->window,
    DefaultVisual(context->display, screen),
    800,
    600
  );
  context->cr = cairo_create(surface);

  return context;
}

void sigma_loop(sigma_context_t *context) {
  while (1) {
    XEvent e;
    XNextEvent(context->display, &e);

    if (e.type == KeyPress || e.type == ClientMessage)
      break;

    if (e.type == Expose) {
      draw(context->cr);
    }
  }
}

void sigma_cleanup(sigma_context_t *context) {
  if (context->cr != NULL) {
    cairo_destroy(context->cr);
  }
  if (context->surface != NULL) {
    cairo_surface_destroy(context->surface);
  }

  if (context->window != 0) {
    XDestroyWindow(context->display, context->window);
  }
  if (context->display != NULL) {
    XCloseDisplay(context->display);
  }

  free(context);
}

//int main() {
//  sigma_context_t *context = sigma_init();
//  sigma_loop(context);
//  sigma_cleanup(context);
//
//  return 0;
//}
