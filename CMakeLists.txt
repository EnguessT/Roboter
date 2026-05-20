cmake_minimum_required(VERSION 3.20)

project(Roboter 
    VERSION 1.0.0
    LANGUAGES CXX
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


set(OSBits 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBits 64)
endif()

# output structure
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBits}/${CMAKE_BUILD_TYPE})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBits}/${CMAKE_BUILD_TYPE}/libs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBits}/${CMAKE_BUILD_TYPE})


# build options
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
elseif(MSVC)
    add_compile_options(/W4 /permissive- /EHsc)
endif()

#-------------------------------------------
include(FetchContent)

#--------- SFML --------------------------------
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
)
FetchContent_MakeAvailable(SFML)

#-------- TGUI -----------------------------
set(BUILD_SHARED_LIBS OFF)      
set(TGUI_BACKEND SFML_GRAPHICS) 

FetchContent_Declare(
  TGUI
  GIT_REPOSITORY https://github.com/texus/TGUI
  GIT_TAG v1.12.1  
)
FetchContent_MakeAvailable(TGUI)

# sources files
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Include headers
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

#link libraries
target_link_libraries(${PROJECT_NAME} 
            PRIVATE 
            TGUI::TGUI
            SFML::Graphics
            SFML::Window
            SFML::System
            SFML::Audio  
            SFML::Network 
            -pthread    
            
)
