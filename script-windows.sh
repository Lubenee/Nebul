cd src
g++ -c *.cpp -I"D:\SFML-2.5.1\include"
g++ *.o -o a -L"D:\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
./a.exe