cmake_minimum_required(VERSION 4.3)

project(cses CXX)

enable_testing()

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
            COMMAND ${SOLVER} < ${INPUT} > ${OUTPUT}
            COMMAND ${CHECKER} ${INPUT} ${OUTPUT} ${ANSWER} 2> ${RESULT}
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
