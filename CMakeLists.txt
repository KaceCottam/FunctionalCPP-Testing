cmake_minimum_required(VERSION 3.8)

project(FunctionalCPP)

set(FPLUS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/fplus/include)
add_subdirectory(lib/fmt)

set(KC_BIN "${CMAKE_SOURCE_DIR}/bin")

# All new projects will link with fplus.
# Usage: new_project(NAME <name> [LIBRARY_TYPE] [OUTPUT_DIR] [VERSION]
#                    [SOURCES] <sources...>
#                    [INCLUDE_DIRS] <include directories...>
#                    [REQUIRES] <required libraries...>)
function(new_project)
  set(SingleArgs NAME LIBRARY_TYPE OUTPUT_DIR VERSION)
  set(MultiArgs SOURCES INCLUDE_DIRS REQUIRES)
  cmake_parse_arguments(PR None "${SingleArgs}" "${MultiArgs}" "${ARGV}")

  string(TOUPPER ${PR_NAME} PR_NAME_UPPER)
  option("BUILD_${PR_NAME_UPPER}" OFF})
  if(${BUILD_${PR_NAME_UPPER}})
    project(${PR_NAME})

    if(PR_SOURCES)
      if(PR_LIBRARY_TYPE)
        add_library(${PR_NAME} ${PR_LIBRARY_TYPE} ${PR_SOURCES})
      else()
      add_executable(${PR_NAME} ${PR_SOURCES})
      endif()
    endif()
    if(PR_INCLUDE_DIRS)
      target_link_libraries(${PR_NAME} PRIVATE ${PR_INCLUDES})
    endif()
    if(PR_REQUIRES)
      target_link_libraries(${PR_NAME} PRIVATE ${PR_INCLUDES})
    endif()
    target_include_directories(${PR_NAME} PRIVATE ${FPLUS_INCLUDE_DIR})
    target_link_libraries(${PR_NAME} fmt-header-only)
    if(PR_OUTPUT_DIR)
      set_target_properties(${PR_NAME}
                            PROPERTIES
                            CXX_STANDARD 17
                            RUNTIME_OUTPUT_DIRECTORY ${PR_OUTPUT_DIR}
                            LIBRARY_OUTPUT_DIRECTORY ${PR_OUTPUT_DIR}
                            ARCHIVE_OUTPUT_DIRECTORY ${PR_OUTPUT_DIR})
    else()
      set_target_properties(${PR_NAME}
                            PROPERTIES
                            CXX_STANDARD 17
                            RUNTIME_OUTPUT_DIRECTORY ${KC_BIN}
                            LIBRARY_OUTPUT_DIRECTORY ${KC_BIN}
                            ARCHIVE_OUTPUT_DIRECTORY ${KC_BIN})
    endif()
  else()
    message("Compile cmake with the option `-DBUILD_${PR_NAME_UPPER}=ON` to build ${PR_NAME}.")
  endif()
endfunction()

new_project(NAME FirstProject
            SOURCES "projects/FirstProject/FirstProject.cpp")

new_project(NAME ErrorHandling
            SOURCES "projects/ErrorHandling/ErrorHandling.cpp")