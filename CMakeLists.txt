cmake_minimum_required(VERSION 3.31)

project(cses CXX)

add_executable(checker checker/checker.cpp)

set(OPTIMIZE_FLAGS -O3 -mcpu=native -relocation-model=pic)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS lib/*.mlir)

foreach(SOURCE ${SOURCES})
    add_custom_command(
        OUTPUT ${SOURCE}.ll
        COMMAND mlir-opt ${SOURCE} -o ${SOURCE}.fmt # for debug use only
        COMMAND mlir-opt ${SOURCE} -convert-scf-to-cf -convert-to-llvm -o ${SOURCE}.ir
        COMMAND mlir-translate ${SOURCE}.ir -mlir-to-llvmir -o ${SOURCE}.ll
        COMMAND opt ${SOURCE}.ll ${OPTIMIZE_FLAGS} -S -o ${SOURCE}.opt # for debug use only
        COMMAND llc ${SOURCE}.ll ${OPTIMIZE_FLAGS} # for debug use only
        DEPENDS ${SOURCE}
    )
    list(APPEND LIB_LLVM_FILES ${SOURCE}.ll)
endforeach()

file(GLOB_RECURSE TEST_ZIPS CONFIGURE_DEPENDS src/*/tests.zip)

foreach(TEST_ZIP ${TEST_ZIPS})
    get_filename_component(PROBLEM_DIR ${TEST_ZIP} DIRECTORY)
    get_filename_component(PROBLEM_NAME ${PROBLEM_DIR} NAME_WE)
    file(GLOB INPUTS CONFIGURE_DEPENDS ${PROBLEM_DIR}/tests/*.in)
    file(GLOB SOURCES CONFIGURE_DEPENDS ${PROBLEM_DIR}/*.mlir)

    ###### mktests ######
    add_custom_command(
        OUTPUT ${PROBLEM_DIR}/tests
        COMMAND rm -rf ${PROBLEM_DIR}/tests
        COMMAND unzip ${TEST_ZIP} -d ${PROBLEM_DIR}/tests
        DEPENDS ${TEST_ZIP}
    )
    add_custom_target(mktests-${PROBLEM_NAME}
        DEPENDS ${PROBLEM_DIR}/tests
    )
    list(APPEND MKTESTS_TARGETS mktests-${PROBLEM_NAME})

    ###### rmtests ######
    add_custom_target(rmtests-${PROBLEM_NAME}
        COMMAND rm -rf ${PROBLEM_DIR}/tests
    )
    list(APPEND RMTESTS_TARGETS rmtests-${PROBLEM_NAME})

    foreach(SOURCE ${SOURCES})
        get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)

        ###### compile ######
        add_custom_command(
            OUTPUT ${SOURCE}.cpp
            COMMAND mlir-opt ${SOURCE} -o ${SOURCE}.fmt # for debug use only
            COMMAND mlir-opt ${SOURCE} -convert-scf-to-cf -convert-to-llvm -o ${SOURCE}.ir
            COMMAND mlir-translate ${SOURCE}.ir -mlir-to-llvmir -o ${SOURCE}.ll
            COMMAND opt ${SOURCE}.ll ${OPTIMIZE_FLAGS} -S -o ${SOURCE}.opt # for debug use only
            COMMAND llc ${SOURCE}.ll ${OPTIMIZE_FLAGS} # for debug use only
            COMMAND llvm-link ${SOURCE}.ll ${LIB_LLVM_FILES}
            | opt -passes='internalize,default<O3>' -internalize-public-api-list=main
            | llc ${OPTIMIZE_FLAGS} -o ${SOURCE}.asm
            COMMAND ${CMAKE_SOURCE_DIR}/asm2cpp.py ${SOURCE}.asm ${SOURCE}.cpp
            DEPENDS ${SOURCE} ${LIB_LLVM_FILES}
        )
        set(TARGET_NAME ${PROBLEM_NAME}-${SOURCE_NAME})
        add_executable(${TARGET_NAME} ${SOURCE}.cpp)

        ###### judge ######
        set(JUDGE_RESULTS "")
        foreach(INPUT ${INPUTS})
            get_filename_component(TEST_DIR ${INPUT} DIRECTORY)
            get_filename_component(TEST_NAME ${INPUT} NAME_WE)
            set(ANSWER ${TEST_DIR}/${TEST_NAME}.out)
            set(OUTPUT ${TEST_DIR}/${TEST_NAME}.${SOURCE_NAME}.out)
            set(RESULT ${TEST_DIR}/${TEST_NAME}.${SOURCE_NAME}.res)
            list(APPEND JUDGE_RESULTS ${RESULT})
            add_custom_command(
                OUTPUT ${RESULT}
                COMMAND ${CMAKE_BINARY_DIR}/${TARGET_NAME} < ${INPUT} > ${OUTPUT}
                COMMAND checker ${INPUT} ${OUTPUT} ${ANSWER} 2> ${RESULT}
                COMMAND rm ${OUTPUT}
                DEPENDS checker ${INPUT} ${ANSWER} ${TARGET_NAME}
            )
            add_custom_target(judge-${TARGET_NAME}-${TEST_NAME}
                DEPENDS ${RESULT}
            )
        endforeach()
        add_custom_target(judge-${TARGET_NAME} DEPENDS ${JUDGE_RESULTS})
        list(APPEND JUDGE_TARGETS judge-${TARGET_NAME})
    endforeach()
endforeach()

file(GLOB_RECURSE CACHES CONFIGURE_DEPENDS *.mlir.*)

add_custom_target(judge DEPENDS ${JUDGE_TARGETS})
add_custom_target(cleanup COMMAND rm -rf ${CACHES})
add_custom_target(mktests DEPENDS ${MKTESTS_TARGETS})
add_custom_target(rmtests DEPENDS ${RMTESTS_TARGETS})
