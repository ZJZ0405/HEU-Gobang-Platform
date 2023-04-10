cmake_minimum_required(VERSION 3.26)

project(CSMind)

aux_source_directory(src SRC)
aux_source_directory(src/AI AI_SRC)
aux_source_directory(src/ConsoleGUI CONSOLEGUI_SRC)

include_directories(${SRC}
${AI_SRC}
${CONSOLEGUI_SRC})

add_executable(main
${SRC}
${AI_SRC}
${CONSOLEGUI_SRC})