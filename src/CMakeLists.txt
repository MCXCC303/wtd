cmake_minimum_required(VERSION 3.28)
project(wtd)

set(CMAKE_C_STANDARD 11)

add_executable(wtd
        main.c
        builtin.c
        builtin.h
        config.c
        help.c
        init_wtd.c
        parse_command.c
        rename.c        
        remove_wtd.c
        td.c
        type.c
        version.c
)
