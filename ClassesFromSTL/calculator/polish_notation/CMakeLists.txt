set(TOKENIZE_SRC ${CMAKE_SOURCE_DIR}/ClassesFromSTL/calculator/tokenize/tokenize.cpp)
file(GLOB POLISH_NOTATION_SRC ./*.cpp)

add_executable(polish_notation_public_test ${POLISH_NOTATION_SRC} ${TOKENIZE_SRC} polish_notation_public_test.cpp)
