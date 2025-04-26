add_executable(${projectName} main.cpp)
set(CADMIUM_DIR $ENV{CADMIUM})
target_include_directories(${projectName} PUBLIC
    "."
    "include"
    ${CADMIUM_DIR}
    "${CADMIUM_DIR}/../json/include"
)
target_compile_options(${projectName} PUBLIC  -ggdb -O0 -std=gnu++2b)
