include(CMakeParseArguments)

# -----------------------------------------------------------------------------
function(_source_group GROUP_ROOT)
  set(_sources "")
  foreach(file IN LISTS ARGN)
    get_filename_component(path ${file} ABSOLUTE)
    list(APPEND _sources "${path}")
  endforeach()
  #message(STATUS "Using GROUP_ROOT ${GROUP_ROOT}")
  source_group(TREE "${GROUP_ROOT}" FILES ${_sources})
endfunction()

# -----------------------------------------------------------------------------
function(_copy_runtime TARGET)
  if(NOT ${PROJECT_NAME}_RUNTIME_PREFIX STREQUAL "")
    # Copy headers to install
    #if(NOT PUBLIC_HEADERS STREQUAL "")
      #file(MAKE_DIRECTORY ${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/${project_name})
      #add_custom_command(
      #      TARGET ${TARGET} POST_BUILD
      #      COMMAND ${CMAKE_COMMAND} -E copy
      #        ${PUBLIC_HEADERS}
      #        ${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/${project_name})
    #endif()
    get_target_property(_type ${TARGET} TYPE)
    if(_type STREQUAL "STATIC_LIBRARY")
      file(MAKE_DIRECTORY ${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_LIBDIR})
      add_custom_command(
        TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
          $<TARGET_FILE:${TARGET}>
          ${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_LIBDIR})
    elseif(_type STREQUAL "SHARED_LIBRARY" OR _type STREQUAL "MODULE_LIBRARY")
      if(WIN32 AND _type STREQUAL "SHARED_LIBRARY")
        file(MAKE_DIRECTORY ${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_BINDIR})
        add_custom_command(
          TARGET ${TARGET} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:${TARGET}>
            ${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_BINDIR})
      else()
        file(MAKE_DIRECTORY ${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_LIBDIR})
        add_custom_command(
          TARGET ${TARGET} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_LINKER_FILE:${TARGET}>
            ${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_LIBDIR})
      endif()
    elseif(_type STREQUAL "EXECUTABLE")
      file(MAKE_DIRECTORY ${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_BINDIR})
      add_custom_command(
        TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
          $<TARGET_FILE:${TARGET}>
          ${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_BINDIR})
    endif()
  endif()
endfunction()

# -----------------------------------------------------------------------------
function(_add_library NAME)
  set(_options VERBOSE LIB_INSTALL_ONLY)
  set(_oneval_arguments
    TYPE
    GROUP_ROOT
    )
  set(_multival_arguments
    SOURCES
    PRIVATE_HEADERS
    PUBLIC_HEADERS
    PRIVATE_LINK_LIBRARIES
    PUBLIC_LINK_LIBRARIES
    )
  cmake_parse_arguments(
    "" # prefix (empty)
    "${_options}"
    "${_oneval_arguments}"
    "${_multival_arguments}"
    ${ARGN}
    )

  # Display arguments if being VERBOSE
  if(_VERBOSE)
    foreach(opt IN LISTS _options _oneval_arguments _multival_arguments)
      message(STATUS "_add_library(${NAME}): ${opt} -> '${_${opt}}'")
    endforeach()
  endif()
  
  if(NOT _PUBLIC_HEADERS)
    set(_PUBLIC_HEADERS "")
  endif()

  # Build library
  add_library(${NAME} ${_TYPE}
    ${_SOURCES} ${_PUBLIC_HEADERS} ${_PRIVATE_HEADERS}
    )
  generate_export_header(${NAME})

  # Set interface include directories
  target_include_directories(${NAME}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
      $<INSTALL_INTERFACE:include>
      $<INSTALL_INTERFACE:include/${project_name}>
    PRIVATE
      ${_PRIVATE_HEADERS}
  )

  # Link to dependencies
  target_link_libraries(${NAME}
    PRIVATE ${_PRIVATE_LINK_LIBRARIES}
    PUBLIC ${_PUBLIC_LINK_LIBRARIES}
  )

  if(NOT _LIB_INSTALL_ONLY)
    # Install headers
    foreach(header ${_PUBLIC_HEADERS})
      get_filename_component(dest ${header} DIRECTORY)
      install(FILES ${header}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${project_name}/${dest}
        COMPONENT Development
        )
    endforeach()
  endif()

  # Install library
  install(TARGETS ${NAME} EXPORT ${PROJECT_NAME}Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT RuntimeLibraries
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT RuntimeLibraries
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
    )

  # Also copy files to install as part of the buid
  _copy_runtime(${NAME})

  # Add sources to IDE source group
  set_target_properties(${NAME} PROPERTIES FOLDER ${PROJECT_NAME})
  if(NOT _GROUP_ROOT)
    set(_GROUP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
  endif()
  _source_group(${_GROUP_ROOT} ${_SOURCES} ${_PUBLIC_HEADERS} ${_PRIVATE_HEADERS})
endfunction()

# -----------------------------------------------------------------------------
function(_add_executable NAME)
  set(_multival_arguments
    SOURCES
    HEADERS
    LINK_LIBRARIES
    )
  cmake_parse_arguments(
    "" # prefix (empty)
    "" # options (none)
    "" # single-value arguments (none)
    "${_multival_arguments}"
    ${ARGN}
    )

  add_executable(${NAME} ${_SOURCES} ${_HEADERS})
  _copy_runtime(${NAME})

  target_include_directories(${NAME}
    PRIVATE ${${PROJECT_NAME}_INCLUDE_FOLDERS}
    )

  set_target_properties(${NAME} PROPERTIES
    FOLDER ${PROJECT_NAME}
    )

  # Link to dependencies
  target_link_libraries(${NAME}
    PRIVATE ${_LINK_LIBRARIES}
    )

  # Install executable
  install(TARGETS ${NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Utilities
    )

  # Add sources to IDE source group
  _source_group(${CMAKE_CURRENT_SOURCE_DIR} ${ARGN})

  # Configure running executable out of MSVC
  if(MSVC AND NOT ${PROJECT_NAME}_RUNTIME_PREFIX STREQUAL "")
    set_property(TARGET ${NAME}
      PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
      "${${PROJECT_NAME}_RUNTIME_PREFIX}/${CMAKE_INSTALL_BINDIR}"
      )
  endif()
endfunction()
