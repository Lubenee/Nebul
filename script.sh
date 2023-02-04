#! /bin/sh
cd src
g++ -c *.cpp
g++ *.o -o rpg -lsfml-graphics -lsfml-window -lsfml-system -include pch.h
./rpg
