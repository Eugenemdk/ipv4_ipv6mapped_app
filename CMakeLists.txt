cmake_minimum_required(VERSION 3.0.0)
project(IPV4_MAPPEDIPV6 VERSION 0.1.0)

include(CTest)
enable_testing()



file( GLOB APP_SOURCES server_client_lib/*.cxx )

add_executable(IPV4_MAPPEDIPV6 main.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
