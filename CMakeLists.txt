cmake_minimum_required(VERSION 3.26)

project(CSMind)

aux_source_directory(src/AI AI_SRC)
aux_source_directory(src/ConsoleGUI CONSOLEGUI_SRC)
# find_package(glog REQUIRED)

# 分测试环境
if(APPLE) # MacOS
    include_directories(${SRC}
    ${AI_SRC})

    add_executable(main
    src/console-main.c
    ${AI_SRC})    
elseif(WIN64) # Windows
    include_directories(${SRC}
    ${AI_SRC}
    ${CONSOLEGUI_SRC})

    add_executable(main
    src/GUI-main.c
    ${AI_SRC}
    ${CONSOLEGUI_SRC}) 
endif()



