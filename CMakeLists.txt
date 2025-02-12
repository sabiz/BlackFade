cmake_minimum_required(VERSION 3.3)

project(BlackFade C)
add_executable(BlackFade WIN32 src/main.c src/blackfade.c res/black_fade.rc)
set_property(TARGET BlackFade PROPERTY C_STANDARD 23)
