cmake_minimum_required(VERSION 4.3)

project(cses CXX)

enable_testing()

find_package(Python3 COMPONENTS Interpreter REQUIRED)
set(JUDGE_GUARD ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/toy_guard.py --memory-mb 512 --time-seconds 300)

add_compile_options(-Wall -Wextra -std=c++23)

add_executable(checker checker/checker.cpp)

file(GLOB SOLVER_SRCS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/problems/*/main.cpp)

foreach(SOLVER_SRC ${SOLVER_SRCS})
    get_filename_component(SOLVER_DIR ${SOLVER_SRC} DIRECTORY)
    get_filename_component(PROBLEM_ID ${SOLVER_DIR} NAME)

    # mktest
    set(TEST_ZIP ${SOLVER_DIR}/tests.zip)
    set(TEST_DIR ${CMAKE_BINARY_DIR}/${PROBLEM_ID})
    if(NOT EXISTS ${TEST_ZIP})
        continue()
    endif()
    add_custom_command(
        OUTPUT ${TEST_DIR}/.stamp
        COMMAND unzip -q ${TEST_ZIP} -d ${TEST_DIR}
        COMMAND touch ${TEST_DIR}/.stamp
        DEPENDS ${TEST_ZIP}
    )
    add_custom_target(mktest-${PROBLEM_ID} DEPENDS ${TEST_DIR}/.stamp)
    list(APPEND MKTEST_TARGETS mktest-${PROBLEM_ID})

    # rmtest
    if(NOT EXISTS ${TEST_DIR})
        continue()
    endif()
    add_custom_target(rmtest-${PROBLEM_ID} COMMAND rm -rf ${TEST_DIR})
    list(APPEND RMTEST_TARGETS rmtest-${PROBLEM_ID})

    # solver
    set(SOLVER ${PROBLEM_ID}-solver)
    add_executable(${SOLVER} ${SOLVER_SRC})
    set(SOLVER_DEBUG ${PROBLEM_ID}-solver-debug)
    add_executable(${SOLVER_DEBUG} ${SOLVER_SRC})
    target_compile_options(${SOLVER_DEBUG} PRIVATE -O0 -g) 

    # checker
    set(CHECKER checker)
    set(CHECKER_SRC ${SOLVER_DIR}/checker.cpp)
    if(EXISTS ${CHECKER_SRC})
        set(CHECKER ${PROBLEM_ID}-checker)
        add_executable(${CHECKER} ${CHECKER_SRC})
        target_include_directories(${CHECKER} PRIVATE ${CMAKE_SOURCE_DIR}/checker)
    endif()

    # judge
    file(GLOB INPUTS CONFIGURE_DEPENDS ${TEST_DIR}/*.in)
    set(RESULTS)
    foreach(INPUT ${INPUTS})
        get_filename_component(T ${INPUT} NAME_WE)
        set(ANSWER ${TEST_DIR}/${T}.out)
        set(OUTPUT ${TEST_DIR}/${T}.tmp)
        set(RESULT ${TEST_DIR}/${T}.res)
        list(APPEND RESULTS ${RESULT})
        add_test(
            NAME ${PROBLEM_ID}-${T}
            COMMAND ${SOLVER_DEBUG} < ${INPUT}
        )
        add_custom_command(
            OUTPUT ${RESULT}
            COMMAND ${JUDGE_GUARD} -- ${SOLVER} < ${INPUT} > ${OUTPUT}
            COMMAND ${JUDGE_GUARD} -- ${CHECKER} ${INPUT} ${OUTPUT} ${ANSWER} 2> ${RESULT}
            DEPENDS ${CHECKER} ${INPUT} ${SOLVER} ${ANSWER}
            COMMENT "judge ${RESULT}"
        )
        add_custom_target(judge-${PROBLEM_ID}-${T} DEPENDS ${RESULT})
    endforeach()
    add_custom_target(judge-${PROBLEM_ID} DEPENDS ${RESULTS})
    list(APPEND JUDGE_TARGETS judge-${PROBLEM_ID})
endforeach()

add_custom_target(judge DEPENDS ${JUDGE_TARGETS})
add_custom_target(mktest DEPENDS ${MKTEST_TARGETS})
add_custom_target(rmtest DEPENDS ${RMTEST_TARGETS})

# ---------------------------------------------------------------------------
# Toy language solutions (main.toy)
# ---------------------------------------------------------------------------
set(TOY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/toy_lang)
set(TOY_BUILD_DIR ${CMAKE_SOURCE_DIR}/toy_lang/build)
set(TOY_OPT ${TOY_BUILD_DIR}/bin/toy-opt)
set(TOYC ${TOY_SOURCE_DIR}/compiler/toyc.py)
include(ExternalProject)
ExternalProject_Add(toy_lang
    SOURCE_DIR ${TOY_SOURCE_DIR}
    BINARY_DIR ${TOY_BUILD_DIR}
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DMLIR_DIR=/usr/lib64/cmake/mlir
        -DLLVM_DIR=/usr/lib64/cmake/llvm
    INSTALL_COMMAND ""
    BUILD_ALWAYS OFF
)

file(GLOB TOY_SOLVER_SRCS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/problems/*/main.toy)
foreach(TOY_SRC ${TOY_SOLVER_SRCS})
    get_filename_component(TOY_SOLVER_DIR ${TOY_SRC} DIRECTORY)
    get_filename_component(TOY_PROBLEM_ID ${TOY_SOLVER_DIR} NAME)
    if(NOT EXISTS ${TOY_SOLVER_DIR}/tests.zip)
        continue()
    endif()

    # checker override when the problem ships a custom checker
    set(TOY_CHECKER checker)
    if(EXISTS ${TOY_SOLVER_DIR}/checker.cpp)
        if(NOT TARGET ${TOY_PROBLEM_ID}-checker)
            add_executable(${TOY_PROBLEM_ID}-checker ${TOY_SOLVER_DIR}/checker.cpp)
            target_include_directories(${TOY_PROBLEM_ID}-checker PRIVATE ${CMAKE_SOURCE_DIR}/checker)
        endif()
        set(TOY_CHECKER ${TOY_PROBLEM_ID}-checker)
    endif()

    set(TOY_SOLVER ${CMAKE_BINARY_DIR}/${TOY_PROBLEM_ID}/${TOY_PROBLEM_ID}-toy-solver)
    add_custom_command(
        OUTPUT ${TOY_SOLVER}
        COMMAND timeout 900 ${Python3_EXECUTABLE} ${TOYC} ${TOY_SRC} --toy-opt ${TOY_OPT} -o ${TOY_SOLVER}
        DEPENDS ${TOY_SRC} toy_lang
        COMMENT "toyc ${TOY_PROBLEM_ID}"
    )
    add_custom_target(toy-build-${TOY_PROBLEM_ID} DEPENDS ${TOY_SOLVER})
    list(APPEND TOY_BUILD_TARGETS toy-build-${TOY_PROBLEM_ID})

    file(GLOB TOY_INPUTS CONFIGURE_DEPENDS ${CMAKE_BINARY_DIR}/${TOY_PROBLEM_ID}/*.in)
    set(TOY_RESULTS)
    set(TOY_INTERACTIVE FALSE)
    if(TOY_PROBLEM_ID GREATER_EQUAL 270 AND TOY_PROBLEM_ID LESS_EQUAL 275)
        set(TOY_INTERACTIVE TRUE)
    endif()
    foreach(INPUT ${TOY_INPUTS})
        get_filename_component(T ${INPUT} NAME_WE)
        set(TOY_ANSWER ${CMAKE_BINARY_DIR}/${TOY_PROBLEM_ID}/${T}.out)
        set(TOY_OUTPUT ${CMAKE_BINARY_DIR}/${TOY_PROBLEM_ID}/${T}.toy.out)
        set(TOY_RESULT ${CMAKE_BINARY_DIR}/${TOY_PROBLEM_ID}/${T}.toy.res)
        list(APPEND TOY_RESULTS ${TOY_RESULT})
        if(TOY_INTERACTIVE)
            add_custom_command(
                OUTPUT ${TOY_RESULT}
                COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/interact.py ${TOY_PROBLEM_ID} ${TOY_SOLVER} ${INPUT} > ${TOY_RESULT}
                DEPENDS ${INPUT} ${TOY_SOLVER}
            )
        else()
            add_custom_command(
                OUTPUT ${TOY_RESULT}
                COMMAND ${JUDGE_GUARD} -- ${TOY_SOLVER} < ${INPUT} > ${TOY_OUTPUT}
                COMMAND ${JUDGE_GUARD} -- ${TOY_CHECKER} ${INPUT} ${TOY_OUTPUT} ${TOY_ANSWER} 2> ${TOY_RESULT}
                COMMAND rm -f ${TOY_OUTPUT}
                DEPENDS ${TOY_CHECKER} ${INPUT} ${TOY_ANSWER} ${TOY_SOLVER}
            )
        endif()
        add_custom_target(toy-judge-${TOY_PROBLEM_ID}-${T} DEPENDS ${TOY_RESULT})
    endforeach()
    if(TOY_INTERACTIVE)
        set(TOY_TEST_DIR ${CMAKE_BINARY_DIR}/${TOY_PROBLEM_ID})
        add_custom_command(
            OUTPUT ${TOY_TEST_DIR}/.stamp
            COMMAND unzip -q ${TOY_SOLVER_DIR}/tests.zip -d ${TOY_TEST_DIR}
            COMMAND touch ${TOY_TEST_DIR}/.stamp
            DEPENDS ${TOY_SOLVER_DIR}/tests.zip
        )
        add_custom_target(mktest-toy-${TOY_PROBLEM_ID} DEPENDS ${TOY_TEST_DIR}/.stamp)
        add_custom_target(toy-judge-${TOY_PROBLEM_ID} DEPENDS ${TOY_RESULTS} mktest-toy-${TOY_PROBLEM_ID})
    else()
        add_custom_target(toy-judge-${TOY_PROBLEM_ID} DEPENDS ${TOY_RESULTS} mktest-${TOY_PROBLEM_ID})
    endif()
    list(APPEND TOY_JUDGE_TARGETS toy-judge-${TOY_PROBLEM_ID})
endforeach()

add_custom_target(toy-build DEPENDS ${TOY_BUILD_TARGETS})
add_custom_target(toy-judge DEPENDS ${TOY_JUDGE_TARGETS})
