cmake_minimum_required (VERSION 2.4)

project (LIBCPPBENARYORG)

file(GLOB_RECURSE files ${LIBCPPBENARYORG_SOURCE_DIR}/*.cpp) 
add_library ( cppbenaryorg SHARED ${files} ) 

INSTALL(TARGETS cppbenaryorg
	RUNTIME DESTINATION /usr/bin
	LIBRARY DESTINATION /usr/lib
	ARCHIVE DESTINATION /usr/lib
)
