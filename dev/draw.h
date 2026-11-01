
    
  
#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include "matrix.h"
#include "ml6.h"

void add_point( struct matrix * points, double x, double y, double z);
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1);
void add_triangle(struct matrix *points,
                  double x0, double y0, double z0,
                  double x1, double y1, double z1,
                  double x2, double y2, double z2);
void add_triangle_indices(struct matrix *polygons, struct matrix *vertices,
                          int a, int b, int c);
void draw_polygons(struct matrix *points, screen s, color c);
void draw_lines( struct matrix * points, screen s, color c);
void draw_line(int x0, int y0, int x1, int y1, screen s, color c);

void pline(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void pident(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void pscale(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void pmove(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void protate(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void papply(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void pdisplay(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void psave(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void pcircle(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void phermite(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void pbezier(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void psphere(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void pbox(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);

void ptorus(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);
            
void pclear(FILE* f, struct matrix* transform, struct matrix* edges, struct matrix* polygons, struct matrix* second,
            struct matrix* curvex, struct matrix* curvey, struct matrix* hermite, struct matrix* bezier,
            color c, color b, screen s, double* coors, char* line);
#endif

