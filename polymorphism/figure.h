#ifndef FIGURE_TYPE
#define FIGURE_TYPE

// --
// define abstract figure
typedef void * figure_data_t;

typedef double (* figure_area_t) (figure_data_t);
typedef double (* figure_perimeter_t) (figure_data_t);
typedef char*  (* figure_to_string_t) (figure_data_t);

struct figure {
    figure_data_t data;
    figure_area_t area;
    figure_perimeter_t perimeter;
    figure_to_string_t to_string;
};
typedef struct figure figure_t;
// end of abstract figure
//--

void figure_free(figure_t * figure) {
    free(figure->data);
    free(figure);
}

#endif