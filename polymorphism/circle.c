#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "./figure.h"

// --
// define circle related functions and data containing structure
struct figure_data_circle {
    double r;
};
typedef struct figure_data_circle figure_data_circle_t;

double figure_circle_area(figure_data_t d) {
    figure_data_circle_t * data = (figure_data_circle_t *) d;
    return data->r * data->r * M_PI; 
}

double figure_circle_perimeter(figure_data_t d) {
    figure_data_circle_t * data = (figure_data_circle_t *) d;
    return 2 * data->r * M_PI; 
}

char * figure_circle_to_string(figure_data_t d) {
    figure_data_circle_t * data = (figure_data_circle_t *) d;

    char * templ = "Circle with the r = %f";
    char *buf;
    size_t sz;
    sz = snprintf(NULL, 0, templ, data->r);
    buf = (char *) malloc(sz + 1);
    snprintf(buf, sz+1, templ, data->r);

    return buf;
}

figure_t * figure_circle_new(double r) {
    figure_t* f_circle = (figure_t *) malloc(sizeof(figure_t));
    f_circle->data = (figure_data_circle_t*) malloc(sizeof(figure_data_circle_t));
    ((figure_data_circle_t*) f_circle->data)->r = r;
    f_circle->area = figure_circle_area;
    f_circle->perimeter = figure_circle_perimeter;
    f_circle->to_string = figure_circle_to_string;

    return f_circle;
}

// end of circle
// --