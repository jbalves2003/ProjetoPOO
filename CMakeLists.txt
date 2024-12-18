cmake_minimum_required(VERSION 3.28)
project(ProjetoPoo)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProjetoPoo main.cpp
        Buffer.cpp
        Buffer.h
        Map.cpp
        Map.h
        CommandHandler.cpp
        CommandHandler.h
        Caravana.cpp
        Caravana.h
        ComercioCaravana.cpp
        ComercioCaravana.h
        MilitarCaravana.cpp
        MilitarCaravana.h
        SecretaCaravana.cpp
        SecretaCaravana.h)
