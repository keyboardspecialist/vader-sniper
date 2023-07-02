cmake_minimum_required( VERSION 3.14.0 )

project(VaderSniper)

#FTXUI
include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v4.1.1
)

set(FTXUI_BUILD_EXAMPLES OFF)
set(FTXUI_ENABLE_INSTALL OFF)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_Declare(cpp-httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    GIT_TAG v0.12.6
    )

FetchContent_GetProperties(cpp-httplib)
if(NOT cpp-httplib_POPULATED)
    FetchContent_Populate(cpp-httplib)
    add_subdirectory(${cpp-httplib_SOURCE_DIR} ${cpp-httplib_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


FetchContent_MakeAvailable(cpp-httplib)
FetchContent_MakeAvailable(ftxui)

#

add_executable  (   vader-sniper
                    vsnipe.cc 
                )

set_property(TARGET vader-sniper PROPERTY CXX_STANDARD 17)

target_link_libraries(  vader-sniper
                        
                        PRIVATE

                        ftxui::screen
                        ftxui::dom
                        ftxui::component
                    )

target_include_directories( vader-sniper
                            
                            PRIVATE
                            ${ftxui_SOURCE_DIR}/include
                            ${cpp-httplib_SOURCE_DIR}
                        )