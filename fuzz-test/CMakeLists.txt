cmake_minimum_required (VERSION 2.8.11)
project(binson-c-light-fuzz)
enable_language(C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(Sanitizers_DIR)
find_package(Sanitizers)

include_directories(../)
add_executable(fuzz_binson main_entry.cc fuzz_binson.c ../binson_parser.c)
add_sanitizers(fuzz_binson)

add_executable(fuzz_defined main_entry.cc fuzz_defined.c ../binson_parser.c)
add_sanitizers(fuzz_defined)

add_executable(fuzz_to_string main_entry.cc fuzz_to_string.c ../binson_parser.c)
add_sanitizers(fuzz_to_string)

add_executable(fuzz_parser_verify main_entry.cc fuzz_parser_verify.c ../binson_parser.c)
add_sanitizers(fuzz_parser_verify)


add_executable(fuzz_goinoutobj main_entry.cc fuzz_goinoutobj.c ../binson_parser.c)
add_sanitizers(fuzz_goinoutobj)


add_executable(fuzz_goinoutarr main_entry.cc fuzz_goinoutarr.c ../binson_parser.c)
add_sanitizers(fuzz_goinoutarr)

add_executable(fuzz_verify_array main_entry.cc fuzz_verify_array.c ../binson_parser.c)
add_sanitizers(fuzz_verify_array)

add_executable(fuzz_class main_entry.cc fuzz_class.cpp ../binson_parser.c ../binson.cpp ../binson_writer.c)
add_sanitizers(fuzz_class)
