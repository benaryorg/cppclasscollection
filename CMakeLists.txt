cmake_minimum_required(VERSION 2.4)

project(LIBCPPBENARYORG)

file(GLOB headers ${LIBCPPBENARYORG_SOURCE_DIR}/*.h)
file(GLOB files ${LIBCPPBENARYORG_SOURCE_DIR}/*.cpp)

add_library(cppbenaryorg SHARED ${files})

if(MSVC)
	add_definitions(-D__WIN32__)
elseif(UNIX)
	target_link_libraries(cppbenaryorg pthread)
	add_definitions(-D__linux__)
endif()

INSTALL(TARGETS cppbenaryorg
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

INSTALL(FILES ${headers} DESTINATION include/cppbenaryorg)
