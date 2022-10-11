# Description

figure.h -> provides a figure struct with 
- abstract data container (void *)
- function pointers to functions to calculate area, perimeter, create string about struct

square.c ->
circle.c ->
 - create an example of figure structure with particular to square and circle functions

 main.c ->
 - creates an array of figures
 - iteares over array, prints description, calculated square and perimeter

 # Build


```sh
gcc main.c -Wall -Og -O1 -fsanitize=address -lm
```