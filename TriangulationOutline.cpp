#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>
#include <iostream>
#include <cmath>
#include <utility>

#define N 120
#define WIDTH N
#define HEIGHT N

using Pair = std::pair<int, int>;

Pair Point(int x, int y) {
    return std::make_pair(x, y);
}

void showText(cairo_t *cr) {
  cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 

  cairo_select_font_face(cr, "TimesNewRoman", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 5);
  cairo_move_to(cr, 35, 8);
  cairo_set_source_rgb(cr, 255, 0, 0);
  cairo_show_text(cr, "Delaunay Triangulation"); 
}

void drawPoint(cairo_t *cr, Pair point) {
    cairo_arc(cr, point.first, point.second, 0.5, 0, 2*M_PI);
    cairo_set_source_rgb(cr, 0, 0, 0); 
    cairo_fill(cr);
}

void drawLine(cairo_t *cr, Pair p1, Pair p2) {
    cairo_set_line_width(cr, 0.3);
    cairo_move_to(cr, p1.first, p1.second);
    cairo_line_to(cr, p2.first, p2.second);
    cairo_close_path(cr);
    cairo_set_source_rgba(cr, 0, 0, 0, 0.8);
    cairo_stroke(cr);
}

int main() {
    cairo_surface_t *surface;
    cairo_t *cr;

    surface = cairo_pdf_surface_create("DelaunayTriangulation.pdf", WIDTH, HEIGHT + 5);
    cr = cairo_create(surface);
    showText(cr);
    int x1, y1, x2, y2;
    while (std::cin >> x1 >> y1 >> x2 >> y2) {
        drawLine(cr, Point(x1, y1), Point(x2, y2));
        drawPoint(cr, Point(x1, y1));
        drawPoint(cr, Point(x2, y2));
    }
    cairo_surface_destroy(surface);
    cairo_destroy(cr);
    return 0;
}
