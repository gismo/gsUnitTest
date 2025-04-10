
if(CMAKE_VERSION VERSION_LESS "3.19")
  cmake_minimum_required(VERSION 2.8.12)
else()
  cmake_minimum_required(VERSION 3.1...3.10)
endif()

if(POLICY CMP0048)# CMake 3.0
  cmake_policy(SET CMP0011 NEW)
  cmake_policy(SET CMP0042 NEW)
  cmake_policy(SET CMP0048 NEW)
endif()

if(POLICY CMP0054)# CMake 3.1
  cmake_policy(SET CMP0054 NEW)
endif()

if(POLICY CMP0063)# CMake 3.3
  cmake_policy(SET CMP0063 NEW)
endif()

project(UnitTest++)

option(UTPP_USE_PLUS_SIGN "Set this to OFF is you with to use '-cpp' instead of '++' in lib/include paths" ON)

# get the main sources
file(GLOB headers_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB sources_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# get the gismo related sources
file(GLOB gsheaders_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} gs/*.h)
file(GLOB gssources_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} gs/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# get platform specific sources
if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    #add_definitions(-DUNITTEST_WIN32_DLL)
    set(platformDir_ Win32)
else()
    set(platformDir_ Posix)
endif(WIN32)

file(GLOB platformHeaders_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${platformDir_}/*.h)
file(GLOB platformSources_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${platformDir_}/*.cpp)
#source_group(${platformDir_} FILES ${platformHeaders_} ${platformSources_})

# create the lib
#add_library(UnitTestPP SHARED ${headers_} ${sources_} ${gsheaders_} ${gssources_} ${platformHeaders_} ${platformSources_})
add_library(UnitTestPP STATIC ${headers_} ${sources_} ${gsheaders_} ${gssources_} ${platformHeaders_} ${platformSources_})

# add install targets
if(${UTPP_USE_PLUS_SIGN})
	set (UTPP_INSTALL_DESTINATION "include/UnitTest++")
else()
	set (UTPP_INSTALL_DESTINATION "include/UnitTestPP")
endif()

install(TARGETS UnitTestPP DESTINATION lib)
install(FILES ${headers_} DESTINATION ${UTPP_INSTALL_DESTINATION})
install(FILES ${gsheaders_} DESTINATION ${UTPP_INSTALL_DESTINATION}/gs)
install(FILES ${platformHeaders_} DESTINATION ${UTPP_INSTALL_DESTINATION}/${platformDir_})

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
