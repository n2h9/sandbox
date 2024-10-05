## Project structure 

https://www.youtube.com/watch?v=UH6F6ypdYbw 21:43

## Formatting with clang-format in VS code

https://dev.to/dhanu0510/how-to-configure-c-code-formatting-in-visual-studio-code-4d5m

## googletest
https://google.github.io/googletest/quickstart-cmake.html 

## debug
To debug need to build debug version of application.

check https://stackoverflow.com/questions/49583381/how-to-debug-a-cmake-make-project-in-vscode 

```sh
mkdir Debug
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```