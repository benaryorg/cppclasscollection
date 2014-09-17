cmake_minimum_required (VERSION 2.4)

project (LIBCPPBENARYORG)

file(GLOB_RECURSE files ${LIBCPPBENARYORG_SOURCE_DIR}/*.cpp) 

add_library ( cppbenaryorg SHARED ${files} ) 

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_definitions(-D__WIN32__)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries ( cppbenaryorg pthread )
	add_definitions(-D__linux__)
endif()

INSTALL(TARGETS cppbenaryorg
	RUNTIME DESTINATION /usr/bin
	LIBRARY DESTINATION /usr/lib
	ARCHIVE DESTINATION /usr/lib
)
