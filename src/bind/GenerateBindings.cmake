
if( Protobuf_PROTOC_EXECUTABLE )
  # C++ Bindings
  set(_RUN_PROTOC OFF)
  
  # Enumerate all files to compile
  set(_FILES "${BINDINGS}/CommonDataModel.proto")
  
  file(MAKE_DIRECTORY "${BINDINGS_OUT}")
  if(EXISTS ${BINDINGS_OUT}/schema_last_built)
    foreach(f ${_FILES})
      message(STATUS "Checking ${f} is newer than ${BINDINGS}/schema_last_built")
      if(${f} IS_NEWER_THAN ${BINDINGS_OUT}/schema_last_built)
        message(STATUS "${f} has changed since the last build")
        set(_RUN_PROTOC ON)
      endif()
    endforeach()
  else()
    set(_RUN_PROTOC ON)
  endif()

  if(NOT _RUN_PROTOC)
    message(STATUS "Not generating bindings, nothing has changed since last build")
    return()
  endif()
  message(STATUS "Generating C++ Schema Bindings Using : ${Protobuf_PROTOC_EXECUTABLE}")
  foreach(f ${_FILES})
    execute_process(COMMAND ${Protobuf_PROTOC_EXECUTABLE} --proto_path=${BINDINGS}
                                                          --cpp_out=${BINDINGS_OUT}
                                                          ${f})
  endforeach()
else()#
  message(WARNING "Could not find the protoc executable, will not generate C++ bindings")
endif()

file(TOUCH ${BINDINGS_OUT}/schema_last_built)
message(STATUS "Touch file ${BINDINGS_OUT}/schema_last_built")
