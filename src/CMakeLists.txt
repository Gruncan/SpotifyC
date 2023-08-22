


add_library(${PROJECT_TARGET_LIB} STATIC "http_request.c")
target_include_directories(${PROJECT_TARGET_LIB} PUBLIC "include/" "${CMAKE_BINARY_DIR}/configured_files/include")
