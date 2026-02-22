cmake_minimum_required(VERSION 3.31)
project(Integration CXX)

find_package(exprtk REQUIRED)

add_executable(Integration
    src/MonteCarloIntegration.cc
)

target_include_directories(Integration PRIVATE src)
target_link_libraries(Integration exprtk::exprtk)
