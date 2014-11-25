rm bin/debug
g++ -g src/**/*.cpp main.cpp -Ilib -o bin/debug -lallegro -lallegro_image -lallegro_main -lallegro_ttf -lallegro_font -std=c++11 -lallegro_primitives
./bin/debug bin/entry.txt
# sudo gdb ./debug/debug