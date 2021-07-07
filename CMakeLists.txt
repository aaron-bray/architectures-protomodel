cmake_minimum_required(VERSION 3.12)

project(ProtoModel VERSION 0.0.1 LANGUAGES C CXX)

#------------------------------------------------------------------------------
# Superbuild
#------------------------------------------------------------------------------
option(${PROJECT_NAME}_SUPERBUILD
  "Build ourself and our dependencies as subprojects"
  ON
  )

if(${PROJECT_NAME}_SUPERBUILD)

  include(cmake/superbuild.cmake)

  if(${PROJECT_NAME}_DEPENDENCIES)
    # Transfer to CMake/external/CMakeLists.txt which will drive building our
    # dependencies, and ourself, as external projects, and then halt further
    # evaluation; the external project for ourself will reinvoke this same
    # CMakeLists.txt with SUPERBUILD=OFF
    add_subdirectory(cmake/External)
    return()
  else()
    message(STATUS "No dependencies are enabled, skipping superbuild")
  endif()
endif()

#------------------------------------------------------------------------------
# Regular build
#------------------------------------------------------------------------------

# Include various utility modules
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(GNUInstallDirs)

# Include project configuration and dependencies
include(cmake/config.cmake)
include(cmake/dependencies.cmake)
include(cmake/utilities.cmake)

add_subdirectory(src)


#-----------------------------------------------------------------------------
# This variable controls the prefix used to generate the following files:
#  ${PROJECT_NAME}ConfigVersion.cmake
#  ${PROJECT_NAME}Config.cmake
#  ${PROJECT_NAME}Targets.cmake
# and it also used to initialize ${PROJECT_NAME}_INSTALL_CONFIG_DIR value.
set(export_config_name ${PROJECT_NAME})
set(${PROJECT_NAME}_INSTALL_CONFIG_DIR "lib/cmake/${${PROJECT_NAME}_INSTALL_FOLDER}")
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/${${PROJECT_NAME}_INSTALL_CONFIG_DIR})
#------------------------------------------------------------------------------
# Configure ${PROJECT_NAME}ConfigVersion.cmake common to build and install tree
include(CMakePackageConfigHelpers)
set(config_version_file ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake)
write_basic_package_version_file(
  ${config_version_file}
  VERSION "${${PROJECT_NAME}_VERSION}"
  COMPATIBILITY ExactVersion
  )
#------------------------------------------------------------------------------
# Export '${PROJECT_NAME}Targets.cmake' for a build tree
export(
  EXPORT ${PROJECT_NAME}Targets
  NAMESPACE ProtoModel::
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
  )

# Configure '${PROJECT_NAME}Config.cmake' for a build tree
set(build_config ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake)
configure_package_config_file(
  cmake/${PROJECT_NAME}ConfigBuild.cmake.in
  ${build_config}
  INSTALL_DESTINATION "${PROJECT_BINARY_DIR}"
  )

#------------------------------------------------------------------------------
# Export '${PROJECT_NAME}Targets.cmake' for an install tree
install(
  EXPORT ${PROJECT_NAME}Targets
  NAMESPACE ProtoModel::
  FILE ${PROJECT_NAME}Targets.cmake
  DESTINATION ${${PROJECT_NAME}_INSTALL_CONFIG_DIR}
  )

set(install_config ${PROJECT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}Config.cmake)
configure_package_config_file(
  cmake/${PROJECT_NAME}ConfigInstall.cmake.in
  ${install_config}
  INSTALL_DESTINATION ${${PROJECT_NAME}_INSTALL_CONFIG_DIR}
  )

# Install config files
install(
  FILES ${config_version_file} ${install_config}
  DESTINATION "${${PROJECT_NAME}_INSTALL_CONFIG_DIR}"
  )
