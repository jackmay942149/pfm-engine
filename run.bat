clang main.c ^
-lgdi32 -luser32 -lopengl32  ^
-I ./src/base -I ./src/core -I ./src/opengl -I ./src/libraries ^
-obuild/main.exe -g -std=c23
"build/main.exe"
