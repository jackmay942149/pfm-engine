clang main.c ^
-lgdi32 -luser32 -lopengl32  ^
-I ./src/base -I ./src/core -I ./src/opengl ^
-obuild/main.exe -g -std=c23
"build/main.exe"
