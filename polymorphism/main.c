#include <stdlib.h>
#include <stdio.h>
#include "./figure.h"
#include "./square.c"
#include "./circle.c"

void figure_print(figure_t * figure);

int main () {
    // array of figures
    int figures_size = 16;
    figure_t** figures = (figure_t **) malloc(sizeof(figure_t*) * figures_size);
    for (int i = 0; i < figures_size; i++) {
        figures[i] = NULL;
    }
    figures[0] = figure_square_new(12.0);
    figures[1] = figure_circle_new(1.0);
    // end of array of figures

    // print the calculation about each figure
    for (figure_t** f = figures; (*f) != NULL; f++) {
        figure_print(*f);
    }
    // --


    // free figures
    for (figure_t** f = figures; (*f) != NULL; f++) {
        figure_free(*f);
    }
    free(figures);
    // --

    return 0;
}

void figure_print(figure_t * figure) {
    printf("Figure:\n");
    char * desc = figure->to_string(figure->data);
    printf("  %s\n", desc);
    free(desc);
    printf("  area = %f\n", figure->area(figure->data));
    printf("  perimeter = %f\n", figure->perimeter(figure->data));
    printf("\n");
}