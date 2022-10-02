cmake_minimum_required(VERSION 3.17)
project(Context)

include_directories(../../Source)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC wlfw)