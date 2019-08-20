cmake_minimum_required(VERSION 2.8.9)
project (learnCplusplus)
set(TARGET_PROGRAME_NAME learnCplusplus)
add_executable(${PROJECT_NAME} learnCplusplus.cpp)
#target_compile_options(learCplusplus PRIVATE  "-std=c++11")
set(GLOBAL_CXXFLAGS
        ${GLOBAL_CXXFLAGS}
        -std=c++11
)
#target_compile_options(learCplusplus PRIVATE  "-std=c++11 -Wgnu-alignof-expression")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
      set(GLOBAL_CXXFLAGS
        ${GLOBAL_CXXFLAGS}
        -Wgnu-alignof-expression -Wno-gnu-anonymous-struct -Wno-gnu-designator
        -Wno-gnu-zero-variadic-macro-arguments -Wno-gnu-statement-expression
        -Wgnu-conditional-omitted-operand
      )
endif()
target_compile_options(${PROJECT_NAME} PUBLIC ${GLOBAL_CXXFLAGS})
