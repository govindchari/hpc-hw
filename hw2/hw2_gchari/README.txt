g++ -o librefBLAS.so -fpic -shared refBLAS.cpp
g++ -o test test.cpp librefBLAS.so -Wl,-rpath=$(pwd)