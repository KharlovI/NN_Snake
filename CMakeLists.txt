cmake_minimum_required(VERSION 3.23)
project(AISnake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

include_directories(Snake)

##file(COPY Snake/firstLayer.txt DESTINATION ${CMAKE_BINARY_DIR})
##file(COPY Snake/secondLayer.txt DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_BINARY_DIR}/firstLayer.txt DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Snake)
file(COPY ${CMAKE_BINARY_DIR}/secondLayer.txt DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Snake)
file(COPY Snake/NotCourierSans.otf DESTINATION ${CMAKE_BINARY_DIR})
file(COPY Snake/Apple_Texture.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY Snake/Snake_Texture.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY Snake/Background_Texture.png DESTINATION ${CMAKE_BINARY_DIR})

add_executable(AISnake
        Snake/Apple.cpp
        Snake/Apple.h
        Snake/Genotype.cpp
        Snake/Genotype.h
        Snake/main.cpp
        Snake/Matrix.h
        Snake/Snake.cpp
        Snake/Snake.h
        Snake/Utilities.cpp
        Snake/Utilities.h
        Snake/Button.cpp
        Snake/Button.h
        Snake/firstLayer.txt
        Snake/secondLayer.txt)

set(SFML_DIR "S:\\Programs\\CLion 2022.2.3\\SFML\\lib\\cmake\\SFML")

target_link_libraries(AISnake sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED graphics network audio window system)
