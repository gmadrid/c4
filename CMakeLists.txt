project(c4)
cmake_minimum_required(VERSION 3.11)
set(CMAKE_BUILD_TYPE Debug)

include(cmake/DownloadProject.cmake)

###
### gtest
###
# download_project(PROJ                googletest
# 		 GIT_REPOSITORY      https://github.com/google/googletest.git
# 		 GIT_TAG             master
# 		 UPDATE_DISCONNECTED 1)
# add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})		

###
### abseil
###
set(BUILD_TESTING "OFF")
download_project(PROJ                abseil
		 GIT_REPOSITORY      https://github.com/abseil/abseil-cpp.git
		 GIT_TAG             master
		 UPDATE_DISCONNECTED 1)
add_subdirectory(${abseil_SOURCE_DIR} ${abseil_BINARY_DIR})

###
### json
###
# set(JSON_BuildTests OFF)
# download_project(PROJ                json
#                  GIT_REPOSITORY      https://github.com/nlohmann/json.git
# 		 GIT_TAG             master
# 		 UPDATE_DISCONNECTED 1)
# add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})		 

###
### Library
###
add_library(c4_lib
	src/lib/board.cc
	src/lib/game.cc
	src/lib/minimax.cc
	src/lib/player.cc
	src/lib/win_finder.cc
)
target_link_libraries(c4_lib
  PUBLIC
    absl_strings
#    nlohmann_json
)
target_compile_features(c4_lib
  PUBLIC
    cxx_auto_type
    cxx_constexpr
    cxx_defaulted_functions
    cxx_deleted_functions
    cxx_nullptr
    cxx_override
    cxx_range_for
    cxx_rvalue_references
)

###
### Homebrew libs
###
#find_path(TCLAP_PATH tclap)

###
### Executable
###
add_executable(c4 src/main/main.cc)
target_include_directories(c4
  SYSTEM
  PRIVATE
#    ${TCLAP_PATH}
)
target_link_libraries(c4
  PRIVATE
    c4_lib)

###
### unittests
###
enable_testing()
#add_executable(unit_tests
#  src/test/leitner_box_test.cc
  # src/test/mnemonica_test.cc
  # src/test/question_test.cc
  # src/test/schedule_test.cc
#  )

# target_link_libraries(unit_tests
#   PRIVATE
#     c4_lib
# #    gtest
# #    gtest_main
#     )
# add_test(NAME    c4_test
# 	 COMMAND unit_tests)
