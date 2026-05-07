cmake_minimum_required(VERSION 3.8)
project(ShapeViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add SDL3
add_subdirectory(externals/SDL3-3.2.22)

# Sources
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${MY_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/includes/"
)

# Link SDL3
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

if(WIN32)
    # Definim calea unde se află DLL-ul (folosim slash-uri normale, CMake le traduce)
    set(SDL3_DLL_PATH "${CMAKE_CURRENT_BINARY_DIR}/externals/SDL3-3.2.22/Debug/SDL3.dll")

    # Adăugăm comanda de copiere automată după build
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_DLL_PATH}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Se copiază SDL3.dll lângă executabil pentru Windows..."
    )
endif()