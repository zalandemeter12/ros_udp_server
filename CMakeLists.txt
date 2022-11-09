cmake_minimum_required(VERSION 2.8.3)
project(udp_comm)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package() 

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(udpLib src/udp.cpp)
target_link_libraries(udpLib ${catkin_LIBRARIES})

add_executable(udp_comm src/udp_comm.cpp)
target_link_libraries(udp_comm ${catkin_LIBRARIES} udpLib)
