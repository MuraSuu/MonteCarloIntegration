cmake_minimum_required(VERSION 3.31)
project(Integration CXX)

find_package(GSL REQUIRED)

add_executable(Integration
    src/MonteCarloIntegration.cc
)

target_include_directories(Integration PRIVATE src)
target_link_libraries(Integration GSL::gsl)
