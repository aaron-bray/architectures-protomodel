# Always rebuild the bindings 
# TODO add a touch file
set(BINDINGS ${CMAKE_CURRENT_SOURCE_DIR})
set(BINDINGS_OUT ${CMAKE_BINARY_DIR}/src/bind)
message(STATUS "Proto files are in : ${BINDINGS}")
include(GenerateBindings.cmake)
add_custom_target(ProtobufCompiler ALL
                  COMMAND ${CMAKE_COMMAND} -DProtobuf_PROTOC_EXECUTABLE:FILEPATH=${Protobuf_PROTOC_EXECUTABLE}
                                           -DBINDINGS:PATH=${BINDINGS}
                                           -DBINDINGS_OUT:PATH="${BINDINGS_OUT}"
                                           -P ${CMAKE_CURRENT_SOURCE_DIR}/GenerateBindings.cmake)
set_target_properties (ProtobufCompiler PROPERTIES FOLDER ${PROJECT_NAME})
# Protocol Library
_add_library(ProtobufBindings
  PRIVATE_HEADERS
    "CommonDataModel.pb.h"
  SOURCES
    "CommonDataModel.pb.cc"
  PRIVATE_LINK_LIBRARIES
    protobuf::libprotobuf
  LIB_INSTALL_ONLY
)
add_dependencies(ProtobufBindings ProtobufCompiler)
