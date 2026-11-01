#include "draw_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "matrix.h"
#include "parser.h"
#include "gmath.h"

void add_point( struct matrix * points, double x, double y, double z) {
    if (points->lastcol >= points->cols) {
        grow_matrix(points, (points->cols)*2);
    }
    points->m[0][points->lastcol] = x;
    points->m[1][points->lastcol] = y;
    points->m[2][points->lastcol] = z;
    points->m[3][points->lastcol] = 1;
    points->lastcol++;
}
void add_edge( struct matrix * points, 
	   double x0, double y0, double z0, 
	   double x1, double y1, double z1) {
           add_point(points, x0, y0, z0);
           add_point(points, x1, y1, z1);
}
void add_triangle( struct matrix * points, 
   double x0, double y0, double z0, 
   double x1, double y1, double z1, 
   double x2, double y2, double z2) {
       add_point(points, x0, y0, z0);
       add_point(points, x1, y1, z1);
       add_point(points, x2, y2, z2);
}

void draw_lines( struct matrix * points, screen scr, color colr) {
    for (int c = 0; c+1 < points->lastcol; c+=2) {
        if ((int) points->m[0][c] >=0 && (int) points->m[1][c] >= 0 && (int) points->m[0][c+1] >= 0 &&(int) points->m[1][c+1]>= 0) {
            draw_line((int) points->m[0][c],(int) points->m[1][c], (int) points->m[0][c+1],(int)         points->m[1][c+1],scr,colr);
        }
    }
}
void draw_polygons( struct matrix * points, screen scr, color colr) {
    for (int c = 0; c+2 < points->lastcol; c+=3) {
        double * norm = calculate_normal(points, c);
        if (norm[2] > 0) {//normal or something?
            if ((int) points->m[0][c] >=0 && (int) points->m[1][c] >= 0 && (int) points->m[0][c+1] >= 0 &&(int) points->m[1][c+1]>= 0) {
                draw_line((int) points->m[0][c],(int) points->m[1][c], (int) points->m[0][c+1],(int)points->m[1][c+1],scr,colr);
            }
            if ((int) points->m[0][c+1] >=0 && (int) points->m[1][c+1] >= 0 && (int) points->m[0][c+2] >= 0 &&(int) points->m[1][c+2]>= 0) {
                draw_line((int) points->m[0][c+1],(int) points->m[1][c+1], (int) points->m[0][c+2],(int)points->m[1][c+2],scr,colr);
            }
            if ((int) points->m[0][c] >=0 && (int) points->m[1][c] >= 0 && (int) points->m[0][c+2] >= 0 &&(int) points->m[1][c+2]>= 0) {
                draw_line((int) points->m[0][c],(int) points->m[1][c], (int) points->m[0][c+2],(int)points->m[1][c+2],scr,colr);
            }
        }
        free(norm);
    }
}

void add_triangle_indices(struct matrix *polygons,
                          struct matrix *vertices,
                          int a, int b, int c) {
    add_triangle(polygons,
        vertices->m[0][a], vertices->m[1][a], vertices->m[2][a],
        vertices->m[0][b], vertices->m[1][b], vertices->m[2][b],
        vertices->m[0][c], vertices->m[1][c], vertices->m[2][c]
    );
}
///=====================================================================

void pline(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    fgets(line, 255, f); line[strcspn(line, "\n")] = '\0';
    sscanf(line, "%lf %lf %lf %lf %lf %lf",
       &coors[0],
       &coors[1],
       &coors[2],
       &coors[3],
       &coors[4],
       &coors[5]);
    add_edge(edges, coors[0], coors[1], coors[2], coors[3], coors[4], coors[5]);
}

void pident(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    ident(transform);
}

void pscale(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    fgets(line, 255, f); line[strcspn(line, "\n")] = '\0';
    sscanf(line, "%lf %lf %lf",
       &coors[0],
       &coors[1],
       &coors[2]
    );
    ident(second);
    second->m[0][0] = coors[0];
    second->m[1][1] = coors[1];
    second->m[2][2] = coors[2];
    matrix_mult(second, transform);
}

void pmove(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    fgets(line, 255, f); line[strcspn(line, "\n")] = '\0';
    sscanf(line, "%lf %lf %lf",
       &coors[0],
       &coors[1],
       &coors[2]
    );
    ident(second);
    second->m[0][3] = coors[0];
    second->m[1][3] = coors[1];
    second->m[2][3] = coors[2];
    matrix_mult(second, transform);
}

void protate(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {    
    fgets(line, 255, f); line[strcspn(line, "\n")] = '\0';
    char dim;
    sscanf(line, "%c %lf",
       &dim,
       &coors[1]
    );
    ident(second);
    if (dim == 'z') {
        second->m[0][0] = cos(coors[1]*3.14159265/180);
        second->m[0][1] = -1*sin(coors[1]*3.14159265/180);
        second->m[1][0] = sin(coors[1]*3.14159265/180);
        second->m[1][1] = cos(coors[1]*3.14159265/180);
        matrix_mult(second, transform);
    }
    if (dim == 'x') {
        second->m[1][1] = cos(coors[1]*3.14159265/180);
        second->m[1][2] = -1*sin(coors[1]*3.14159265/180);
        second->m[2][1] = sin(coors[1]*3.14159265/180);
        second->m[2][2] = cos(coors[1]*3.14159265/180);
        matrix_mult(second, transform);
    }
    if (dim == 'y') {
        second->m[2][2] = cos(coors[1]*3.14159265/180);
        second->m[2][0] = -1*sin(coors[1]*3.14159265/180);
        second->m[0][2] = sin(coors[1]*3.14159265/180);
        second->m[0][0] = cos(coors[1]*3.14159265/180);
        matrix_mult(second, transform);
    }
}

void papply(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    matrix_mult(transform, edges);
    matrix_mult(transform, polygons);
}

void pdisplay(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    clear_screen_custom(s, b);
    draw_lines(edges, s, c);
    draw_polygons(polygons, s, c);
    save_ppm(s, "temp.ppm");
    sdl_display("temp.ppm");  
}

void psave(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    fgets(line, 255, f);
    for (int i = 0; i < 255; i++) {
        if (line[i] == '\n') {line[i] = 0;}
    }
    draw_lines( edges, s, c);
    save_extension(s, line);
    save_ppm(s, "img.ppm");
    sdl_display( line );
}

void pcircle(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    for (int i = 0; i < 256; i++) {line[i] = 0;}
    fgets(line, 255, f); 
    line[strcspn(line, "\n")] = '\0';
    sscanf(line, "%lf %lf %lf %lf",
       &coors[0],
       &coors[1],
       &coors[2],
       &coors[3]
    );
    int segments = 100;
    for (int i = 1; i <= segments; i++) {
        add_edge(edges, 
        coors[0] + coors[3] * cos(i * 2 * 3.14159265 / segments),
        coors[1] + coors[3] * sin(i * 2 * 3.14159265 / segments),
        coors[2],
        
        coors[0] + coors[3] * cos((i-1) * 2 * 3.14159265 / segments),
        coors[1] + coors[3] * sin((i-1) * 2 * 3.14159265 / segments),
        coors[2]
    );
        
    }
}

void phermite(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    fgets(line, 255, f); 
    line[strcspn(line, "\n")] = '\0';
    sscanf(line, "%lf %lf %lf %lf %lf %lf %lf %lf",
       &coors[0],
       &coors[1],
       &coors[2],
       &coors[3],
       &coors[4],
       &coors[5],
       &coors[6],
       &coors[7]
    );
    int segments = 100;
    curvex->m[0][0] = coors[0];
    curvex->m[1][0] = coors[2];
    curvex->m[2][0] = coors[4];
    curvex->m[3][0] = coors[6];
    
    curvey->m[0][0] = coors[1];
    curvey->m[1][0] = coors[3];
    curvey->m[2][0] = coors[5];
    curvey->m[3][0] = coors[7];
    
    matrix_mult(hermite, curvex);
    matrix_mult(hermite, curvey);
    for (int i = 1; i <= segments; i++) {
        double t = (double) i / segments;
        double t2 = ((double) i - 1) / segments;
        add_edge(edges, 
        curvex->m[0][0] * t * t * t +
        curvex->m[1][0] * t * t +
        curvex->m[2][0] * t +
        curvex->m[3][0],
         
        curvey->m[0][0] * t * t * t +
        curvey->m[1][0] * t * t +
        curvey->m[2][0] * t +
        curvey->m[3][0],
        
        0,
        
        curvex->m[0][0] * t2 * t2 * t2 +
        curvex->m[1][0] * t2 * t2 +
        curvex->m[2][0] * t2 +
        curvex->m[3][0],
         
        curvey->m[0][0] * t2 * t2 * t2 +
        curvey->m[1][0] * t2 * t2 +
        curvey->m[2][0] * t2 +
        curvey->m[3][0],
        
        0
        );
    }
}

void pbezier(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    fgets(line, 255, f); 
    line[strcspn(line, "\n")] = '\0';
    sscanf(line, "%lf %lf %lf %lf %lf %lf %lf %lf",
       &coors[0],
       &coors[1],
       &coors[2],
       &coors[3],
       &coors[4],
       &coors[5],
       &coors[6],
       &coors[7]
    );
    int segments = 100;
    curvex->m[0][0] = coors[0];
    curvex->m[1][0] = coors[2];
    curvex->m[2][0] = coors[4];
    curvex->m[3][0] = coors[6];
    
    curvey->m[0][0] = coors[1];
    curvey->m[1][0] = coors[3];
    curvey->m[2][0] = coors[5];
    curvey->m[3][0] = coors[7];
    
    matrix_mult(bezier, curvex);
    matrix_mult(bezier, curvey);
    for (int i = 1; i <= segments; i++) {
        double t = (double) i / segments;
        double t2 = ((double) i - 1) / segments;
        add_edge(edges, 
        curvex->m[0][0] * t * t * t +
        curvex->m[1][0] * t * t +
        curvex->m[2][0] * t +
        curvex->m[3][0],
         
        curvey->m[0][0] * t * t * t +
        curvey->m[1][0] * t * t +
        curvey->m[2][0] * t +
        curvey->m[3][0],
        
        0,
        
        curvex->m[0][0] * t2 * t2 * t2 +
        curvex->m[1][0] * t2 * t2 +
        curvex->m[2][0] * t2 +
        curvex->m[3][0],
         
        curvey->m[0][0] * t2 * t2 * t2 +
        curvey->m[1][0] * t2 * t2 +
        curvey->m[2][0] * t2 +
        curvey->m[3][0],
        
        0
        );
    }
}

void psphere(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    
    fgets(line, 255, f); 
    line[strcspn(line, "\n")] = '\0';
    sscanf(line, "%lf %lf %lf %lf",
       &coors[0],
       &coors[1],
       &coors[2],
       &coors[3]
    );
    int semisegments = 10;
    int semis = 10;
    struct matrix * sphere = new_matrix(4,semis*semisegments);
    for (int i = 0; i < semis; i++) {
        for (int k = 0; k < semisegments; k++) {
            double theta = k * 3.14159265 / (semisegments-1);
            double alpha = i * 2 * 3.14159265 / semis;
            double r = coors[3];
            add_point(sphere, 
            coors[0] + r * cos(theta),
            coors[1] + r * sin(theta) * cos(alpha),
            coors[2] + r * sin(theta) * sin(alpha)
            );
        }
    }
    for (int i = 0; i < semis; i++) {
    int next_i = (i + 1) % semis;

        for (int k = 0; k < semisegments - 1; k++) {
            int p   = i * semisegments + k;
            int p1  = p + 1;
            int pn  = next_i * semisegments + k;
            int pn1 = pn + 1;
    
            if (k < semisegments - 2)
                add_triangle_indices(polygons, sphere, p, p1, pn1);
    
            if (k > 0)
                add_triangle_indices(polygons, sphere, p, pn1, pn);
        }
    }
    free_matrix(sphere);
}


void pbox(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    fgets(line, 255, f); 
    line[strcspn(line, "\n")] = '\0';
    sscanf(line, "%lf %lf %lf %lf %lf %lf",
       &coors[0],
       &coors[1],
       &coors[2],
       &coors[3],           
       &coors[4],
       &coors[5]
    );
    double x = coors[0];
    double y = coors[1];
    double z = coors[2];
    double x2 = coors[3]+x;
    double y2 = y-coors[4];
    double z2 = z-coors[5];

    add_triangle(polygons, x,  y,  z,  x,  y2, z,  x2, y2, z);
    add_triangle(polygons, x,  y,  z,  x2, y2, z,  x2, y,  z);

    add_triangle(polygons, x,  y,  z2, x2, y,  z2, x2, y2, z2);
    add_triangle(polygons, x,  y,  z2, x2, y2, z2, x,  y2, z2);

    add_triangle(polygons, x, y,  z,  x, y,  z2, x, y2, z2);
    add_triangle(polygons, x, y,  z,  x, y2, z2, x, y2, z);

    add_triangle(polygons, x2, y,  z,  x2, y2, z,  x2, y2, z2);
    add_triangle(polygons, x2, y,  z,  x2, y2, z2, x2, y,  z2);

    add_triangle(polygons, x,  y, z,  x2, y, z,  x2, y, z2);
    add_triangle(polygons, x,  y, z,  x2, y, z2, x,  y, z2);

    add_triangle(polygons, x,  y2, z,  x,  y2, z2, x2, y2, z2);
    add_triangle(polygons, x, y2, z, x2, y2, z2, x2, y2, z);
}

void ptorus(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    fgets(line, 255, f); 
    line[strcspn(line, "\n")] = '\0';
    sscanf(line, "%lf %lf %lf %lf %lf",
       &coors[0],
       &coors[1],
       &coors[2],
       &coors[3],           
       &coors[4]
    );
    double x = coors[0];
    double y = coors[1];
    double z = coors[2];
    double r = coors[3];
    double R = coors[4];
    
    int segments = 10;
    int loops = 10;
    struct matrix * torus = new_matrix(4,loops*segments);
    for (int i = 0; i < loops; i++) {
        for (int k = 0; k < segments; k++) {
            double theta = k * 2 * 3.14159265 / segments;
            double alpha = i * 2 * 3.14159265 / loops;
            double r = coors[3];
            add_point(torus, 
            coors[0] + cos(alpha)* (r*cos(theta)+R),
            coors[1] + r * sin(theta),
            coors[2] + -1*sin(alpha)* (r*cos(theta)+R)
            );
        }
    }
    for (int i = 0; i < loops; i++) {
        for (int k = 0; k < segments; k++) {
            int next_i = (i + 1) % loops;
            int next_k = (k + 1) % segments;
    
            int p   = i * segments + k;
            int p1  = i * segments + next_k;
            int pn  = next_i * segments + k;
            int pn1 = next_i * segments + next_k;
    
            add_triangle_indices(polygons, torus, p, pn1, p1);
            add_triangle_indices(polygons, torus, p, pn, pn1);
        }
    }
    free_matrix(torus);
}

void pclear(FILE* f, 
            struct matrix* transform, 
            struct matrix* edges, struct matrix* polygons,
            struct matrix* second,
            struct matrix* curvex,
            struct matrix* curvey,
            struct matrix* hermite,
            struct matrix* bezier,
            color c, color b, screen s, 
            double* coors, char* line) {
    //clear edges
    edges->lastcol = 0;
    polygons->lastcol = 0;
}