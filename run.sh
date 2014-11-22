rm debug/debug
g++ sources/*.cpp main.cpp -Iheaders -o debug/debug
./debug/debug debug/entry.txt