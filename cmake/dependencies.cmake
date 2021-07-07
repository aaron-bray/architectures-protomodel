# Tell protobuf-config.cmake to try to be compatible with FindProtobuf.cmake;
# this makes it easier for us to work with either one
set(protobuf_MODULE_COMPATIBLE ON CACHE BOOL "CMake built-in FindProtobuf.cmake module compatible" FORCE)
mark_as_advanced(protobuf_MODULE_COMPATIBLE)

# Try to use the config written by protobuf
find_package(protobuf QUIET CONFIG NO_DEFAULT_PATH)
if(protobuf_DIR AND protobuf_FOUND)
  # Success; set flag so we will reexport protobuf for our users
  set(${PROJECT_NAME}_USING_PROTOBUF_DIR ON)
elseif(NOT protobuf_FOUND)
  # Nope; fall back on FindProtobuf.cmake
  find_package(Protobuf REQUIRED)
endif()

