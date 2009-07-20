CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(mga)

#SET(CMAKE_BUILD_TYPE DEBUG)
#SET(CMAKE_BUILD_TYPE Profile)
SET(CMAKE_BUILD_TYPE RELEASE)

SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREAD OFF)

SET(BOOST_INCLUDEDIR /opt/include/boost-1_36)
INCLUDE(FindBoost)
FIND_PACKAGE(Boost 1.36.0 )

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

INCLUDE_DIRECTORIES(${mga_SOURCE_DIR})

macro(GA_LIBRARY name path)
  AUX_SOURCE_DIRECTORY(. LIB_SRC)
  ADD_LIBRARY(${name} SHARED ${LIB_SRC})
  TARGET_LINK_LIBRARIES(${name} ${ARGN})
endmacro(GA_LIBRARY)

macro(GA_ADD_SUBPROJECTS)
  file(GLOB paths 
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*/CMakeLists.txt")
  MESSAGE(STATUS "Subprojects:")
  foreach(cur_path ${paths})
    get_filename_component(lib_dir ${cur_path} PATH)
    MESSAGE(STATUS "+ "  ${lib_dir})
    add_subdirectory(${lib_dir})
  endforeach(cur_path paths)
endmacro(GA_ADD_SUBPROJECTS)

macro(GA_EXECUTABLE name src)
  MESSAGE(STATUS " + " ${name})
  add_executable(${name} ${src})
  TARGET_LINK_LIBRARIES(${name} ${ARGN})
endmacro(GA_EXECUTABLE)


ga_add_subprojects()

ga_executable(ga_test test.cpp ga utils)

ga_executable(cmeans_test cmeans_test.cpp utils)

ga_executable(concret concret.cpp ga utils cdata)

ga_executable(tree_test tree_test.cpp tree)

ga_executable(fuzzy_test fuzzy_test.cpp fuzzy)

ga_executable(gp gp.cpp ga tree)

ga_executable(mixture mixture.cpp ga tree)

ga_executable(sugeno0 sugeno0.cpp cdata fuzzy)

ga_executable(fgp fgp.cpp ga tree fuzzy)
ga_executable(fgp2 fgp2.cpp ga tree fuzzy)

ga_executable(gp_fly gp_fly.cpp ga tree)

ga_executable(afro_gp afro_gp.cpp ga tree)
