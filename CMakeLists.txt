cmake_minimum_required(VERSION 3.16)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_executable(test cmpt_error.h course.h course.cpp database.h final_project.cpp matching.h menu.h str_manip_utils.h)