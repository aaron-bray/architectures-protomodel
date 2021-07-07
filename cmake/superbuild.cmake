include(${CMAKE_CURRENT_LIST_DIR}/config.cmake)

function(define_dependency NAME)
  option(USE_SYSTEM_${NAME}
    "Exclude ${NAME} from superbuild and use an external version."
    OFF
    )
  list(APPEND ${PROJECT_NAME}_DEPENDENCIES ${NAME})
  set(${PROJECT_NAME}_DEPENDENCIES
    "${${PROJECT_NAME}_DEPENDENCIES}" PARENT_SCOPE
    )
endfunction()

# Add our external dependencies
define_dependency(protobuf)
