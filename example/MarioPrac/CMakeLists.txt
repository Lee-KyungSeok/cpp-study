cmake_minimum_required(VERSION 3.12)
project(MarioPrac)

set(CMAKE_CXX_STANDARD 14)

add_executable(MarioPrac Core.cpp Core.h MapManager.cpp MapManager.h Running.cpp Stage.cpp Stage.h value.h FileStream.cpp FileStream.h Player.cpp Player.h ObjectManager.cpp ObjectManager.h)