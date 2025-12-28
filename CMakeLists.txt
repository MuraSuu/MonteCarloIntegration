cmake_minimum_required(VERSION 3.31)
project(Simulations)

add_executable(MonteCarlo
    src/main.cc
    src/MonteCarloIntegration.cc
)

add_executable(RandomWalk
    src/RandomWalk.cc
    src/main2.cc
)

target_include_directories(MonteCarlo PRIVATE src)
target_include_directories(RandomWalk PRIVATE src)
