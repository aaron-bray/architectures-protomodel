
_add_library(CommonDataModel
  PUBLIC_HEADERS
    CommonDataModel.h
    algorithms/Algorithm.h
    objects/Object1.h
    objects/Object2.h
    io/CommonDataModelSerialization.h
    io/SerializationUtils.h
  SOURCES
    algorithms/Algorithm.cpp
    objects/Object1.cpp
    objects/Object2.cpp
    io/CommonDataModelSerialization.cpp
    io/SerializationUtils.cpp
  PRIVATE_HEADERS
    ${CMAKE_BINARY_DIR}/src/bind
  PRIVATE_LINK_LIBRARIES
    ProtobufBindings
    protobuf::libprotobuf
)

