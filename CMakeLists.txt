cmake_minimum_required(VERSION 3.15.0)
project(cieutils LANGUAGES CXX VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

# Declare all CMake settings
set(${PROJECT_NAME_UPPER}_BUILD_SHARED_LIBRARY ON CACHE BOOL "build shared libraries instead of static ones")
set(${PROJECT_NAME_UPPER}_BUILD_PYTHON_MODULE ON CACHE BOOL "build python bindings for ${PROJECT_NAME}")
set(${PROJECT_NAME_UPPER}_BUILD_TESTS OFF CACHE BOOL "build testrunner for ${PROJECT_NAME}")
set(${PROJECT_NAME_UPPER}_ENABLE_MPI OFF CACHE BOOL "Build with MPI support")
set(${PROJECT_NAME_UPPER}_ENABLE_PROFILING OFF CACHE BOOL "Enable profiling macros.")
set(${PROJECT_NAME_UPPER}_ENABLE_OUT_OF_RANGE_CHECKS OFF CACHE BOOL "Enable macros for checking out-of-range errors.")
set(${PROJECT_NAME_UPPER}_ENABLE_DIVISION_BY_ZERO_CHECKS OFF CACHE BOOL "Enable macros for checking division by zero errors.")
set(${PROJECT_NAME_UPPER}_ENABLE_ADDRESS_SANITIZER OFF CACHE BOOL "Compile with address sanitizer.")
set(${PROJECT_NAME_UPPER}_ENABLE_THREAD_SANITIZER OFF CACHE BOOL "Compile with thread sanitizer.")
set(${PROJECT_NAME_UPPER}_ENABLE_UB_SANITIZER OFF CACHE BOOL "Compile with undefined behaviour sanitizer.")

# Static paths
if(UNIX)
    set(${PROJECT_NAME_UPPER}_INSTALL_DATA_DIR "${CMAKE_INSTALL_PREFIX}/cie/data" CACHE STRING "")
    set(${PROJECT_NAME_UPPER}_OUTPUT_DIR "$ENV{HOME}/.local/share/cie/output" CACHE STRING "")
elseif(APPLE)
    set(${PROJECT_NAME_UPPER}_INSTALL_DATA_DIR "${CMAKE_INSTALL_PREFIX}/cie/data" CACHE STRING "")
    set(${PROJECT_NAME_UPPER}_OUTPUT_DIR "$ENV{HOME}/.local/share/cie/output" CACHE STRING "")
elseif(WIN32)
    message(FATAL_ERROR "Unsupported OS")
else()
    message(FATAL_ERROR "Unsupported OS")
endif()

# Language server
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dynamic linking
set(CMAKE_INSTALL_RPATH "$ORIGIN")

# Collect dependencies
find_package(nlohmann_json REQUIRED)

# Get the current commit hash
find_package(Git)
if (${Git_FOUND})
    execute_process(COMMAND
                    "${GIT_EXECUTABLE}" rev-parse --abbrev-ref HEAD
                    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                    OUTPUT_VARIABLE ${PROJECT_NAME_UPPER}_BRANCH_NAME
                    OUTPUT_STRIP_TRAILING_WHITESPACE)

    execute_process(COMMAND
                    "${GIT_EXECUTABLE}" rev-parse HEAD
                    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                    OUTPUT_VARIABLE ${PROJECT_NAME_UPPER}_COMMIT_HASH
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
    set(${PROJECT_NAME_UPPER}_BRANCH_NAME "unavailable")
    set(${PROJECT_NAME_UPPER}_COMMIT_HASH "unavailable")
endif()

# Generate sources from source templates
file(GLOB source_templates "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp.in")
foreach(source_template ${source_templates})
    # Configure and output to intermediate file (read-write permissions)
    get_filename_component(source_template_name "${source_template}" NAME_WE)
    configure_file("${source_template}" "${CMAKE_CURRENT_SOURCE_DIR}/src/${source_template_name}.cpp")

    # Withdraw write permission from the generated file
    file(CHMOD
         "${CMAKE_CURRENT_SOURCE_DIR}/src/${source_template_name}.cpp"
         FILE_PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
endforeach()

# Compile definitions
if(${PROJECT_NAME_UPPER}_ENABLE_PROFILING)
    add_compile_definitions(CIE_ENABLE_PROFILING=1)
endif()

if(${PROJECT_NAME_UPPER}_ENABLE_OUT_OF_RANGE_CHECKS)
    add_compile_definitions(CIE_ENABLE_OUT_OF_RANGE_CHECKS=1)
endif()

if(${PROJECT_NAME_UPPER}_ENABLE_DIVISION_BY_ZERO_CHECKS)
    add_compile_definitions(CIE_ENABLE_DIVISION_BY_ZERO_CHECKS=1)
endif()

if(${PROJECT_NAME_UPPER}_ENABLE_ADDRESS_SANITIZER)
    add_compile_options("-fsanitize=address")
    add_link_options("-fsanitize=address")
endif()

if(${PROJECT_NAME_UPPER}_ENABLE_THREAD_SANITIZER)
    add_compile_options("-fsanitize=thread")
    add_link_options("-fsanitize=thread")
endif()

if(${PROJECT_NAME_UPPER}_ENABLE_UB_SANITIZER)
    add_compile_options("-fsanitize=undefined")
    add_link_options("-fsanitize=undefined")
endif()

# Build main library
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/packages/*/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
if (${${PROJECT_NAME_UPPER}_BUILD_SHARED_LIBRARY} OR ${${PROJECT_NAME_UPPER}_BUILD_PYTHON_MODULE})
    add_library(${PROJECT_NAME} SHARED ${sources})
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)
else()
    add_library(${PROJECT_NAME} STATIC ${sources})
endif()

target_include_directories(${PROJECT_NAME}
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>")
target_include_directories(${PROJECT_NAME}
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/inc>")
target_include_directories(${PROJECT_NAME}
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/tessil/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/external/tessil/include>")

set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets LIBRARY DESTINATION "cie/lib")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/packages" DESTINATION "cie/include" FILES_MATCHING PATTERN "*.hpp")

# MPI support
if (${PROJECT_NAME_UPPER}_ENABLE_MPI)
    find_package(MPI REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE "${MPI_INCLUDE_PATH}")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME_UPPER}_COMPILE_MPI")
    target_link_libraries(${PROJECT_NAME} PUBLIC MPI::MPICXX)
endif()

# Build test executable
if (${PROJECT_NAME_UPPER}_BUILD_TESTS)
    file(GLOB_RECURSE test_sources "${CMAKE_CURRENT_SOURCE_DIR}/packages/*/test/*.cpp")
    list(INSERT test_sources 0 "${CMAKE_CURRENT_SOURCE_DIR}/test/${PROJECT_NAME}_testrunner.cpp")

    add_executable(${PROJECT_NAME}_testrunner ${test_sources})
    target_link_libraries(${PROJECT_NAME}_testrunner PRIVATE ${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME}_testrunner PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

# Build python module
if (${PROJECT_NAME_UPPER}_BUILD_PYTHON_MODULE)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)
    find_package(pybind11 REQUIRED)

    file(GLOB_RECURSE python_module_sources "${CMAKE_CURRENT_SOURCE_DIR}/python/bindings/*.cpp")
    pybind11_add_module(${PROJECT_NAME}_python_bindings MODULE ${python_module_sources})
    target_link_libraries(${PROJECT_NAME}_python_bindings PRIVATE ${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME}_python_bindings PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

    # Each subdirectory in modules is assumed to be a python module
    # and is installed as-is
    file(GLOB children "${CMAKE_CURRENT_SOURCE_DIR}/python/modules/*")
    foreach(child ${children})
        if (IS_DIRECTORY "${child}")
            get_filename_component(module_name "${child}" NAME)
            install(DIRECTORY "${child}" DESTINATION "cie")
        endif()
    endforeach()

    # Install bindings
    install(TARGETS ${PROJECT_NAME}_python_bindings EXPORT ${PROJECT_NAME}Targets LIBRARY DESTINATION "cie/lib")

    # Main CiE module __init__
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/python/modules/__init__.py" DESTINATION "cie")
endif()

# Export
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(TARGETS ${PROJECT_NAME} NAMESPACE cie:: FILE ${PROJECT_NAME}Targets.cmake)
export(PACKAGE ${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}Targets FILE ${PROJECT_NAME}Targets.cmake DESTINATION "cie/lib")
install(EXPORT ${PROJECT_NAME}Targets FILE ${PROJECT_NAME}Targets.cmake DESTINATION "cie/lib/cmake/${PROJECT_NAME}")

# Package
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VENDOR "")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/license")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/readme")

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES
    /.git
    /build
    *.gitignore)
include(CPack)

include(CMakePackageConfigHelpers)
configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "cie/lib/cmake/${PROJECT_NAME}")