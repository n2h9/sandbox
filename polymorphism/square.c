#include <stdlib.h>
#include <stdio.h>
#include "./figure.h"

// --
// define square related functions and data containing structure
struct figure_data_square {
    double a;
};
typedef struct figure_data_square figure_data_square_t;

double figure_square_area(figure_data_t d) {
    figure_data_square_t * data = (figure_data_square_t *) d;
    return data->a * data->a; 
}

double figure_square_perimeter(figure_data_t d) {
    figure_data_square_t * data = (figure_data_square_t *) d;
    return 4 * data->a; 
}

char * figure_square_to_string(figure_data_t d) {
    figure_data_square_t * data = (figure_data_square_t *) d;

    char * templ = "Square with the side a = %f";
    char *buf;
    size_t sz;
    sz = snprintf(NULL, 0, templ, data->a);
    buf = (char *) malloc(sz + 1); 
    snprintf(buf, sz+1, templ, data->a);

    return buf;
}

figure_t * figure_square_new(double a) {
    figure_t* f_square = (figure_t *) malloc(sizeof(figure_t));
    f_square->data = (figure_data_square_t*) malloc(sizeof(figure_data_square_t));
    ((figure_data_square_t*) f_square->data)->a = a;
    f_square->area = figure_square_area;
    f_square->perimeter = figure_square_perimeter;
    f_square->to_string = figure_square_to_string;

    return f_square;
}
// end of square
// --