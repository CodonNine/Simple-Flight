
include_directories(${PROJECT_SOURCE_DIR}/Core/Inc ${PROJECT_SOURCE_DIR}/BSP)
file(GLOB SRC ${PROJECT_SOURCE_DIR}/BSP/*.c)

add_library(BSP ${SRC})