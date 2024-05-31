cmake_minimum_required(VERSION 3.7)
project(bsd-finger)

set(BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(SBIN_DIR "${CMAKE_INSTALL_PREFIX}/sbin")
set(MAN_DIR "${CMAKE_INSTALL_PREFIX}/share/man")

add_subdirectory(finger)
add_subdirectory(fingerd)
