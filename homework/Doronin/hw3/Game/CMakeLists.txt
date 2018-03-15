cmake_minimum_required(VERSION 3.9)
project(Game)

set(CMAKE_CXX_STANDARD 11)

add_executable(Game main.cpp units/Unit.h units/Peasant.h units/Knight.h units/Archer.h weapons/Fist.h weapons/Bow.h weapons/Showel.h weapons/Sword.h Armor/Shirt.h Armor/Lats.h Armor/Hauber.h units/Pig.h)