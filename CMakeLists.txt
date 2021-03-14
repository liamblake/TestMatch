cmake_minimum_required(VERSION 3.0)
project(testmatch_backend)

#SET(BOOST_ROOT "D:/liaml/Documents/Repos/TestMatch/TestMatch-Backend/boost")
#SET (BOOST_INCLUDEDIR "D:/liaml/Documents/Repos/TestMatch/TestMatch-Backend/boost")
#set(Boost_LIBRARY_DIR "D:/liaml/Documents/Repos/TestMatch/TestMatch-Backend/boost/stage/lib")

###############################################################################
## file globbing ##############################################################
###############################################################################

set(sources src/Cards.cpp src/FileIO.cpp src/Player.cpp src/Simulation.cpp)
file(GLOB_RECURSE includes include/*.cpp)
file(GLOB sources_unittests src/test/unit/*.cpp)

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_executable(testmatch_backend ${sources} ${data})

# this lets me include files relative to the root src dir with a <> pair
target_include_directories(testmatch_backend PUBLIC include)

###############################################################################
## dependencies ###############################################################
###############################################################################

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF) 
#set(BOOST_ROOT boost)
find_package(Boost 1.36.0 COMPONENTS unit_test_framework serialization REQUIRED)

include_directories (testmatch_backend ${Boost_INCLUDE_DIR})
target_link_libraries(testmatch_backend PUBLIC
  ${Boost_LIBRARIES}
)

###############################################################################
## testing ####################################################################
###############################################################################

# this is for our testing framework
# we don't add REQUIRED because it's just for testing
add_executable(unit_tests ${sources_unittest} ${sources})

# we add this define to prevent collision with the main
# this might be better solved by not adding the source with the main to the
# testing target
target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

target_link_libraries(unit_tests PUBLIC
  ${Boost_LIBRARIES}
)