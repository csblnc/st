cmake_minimum_required(VERSION 3.23)
project(satTest)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES test/main.cpp test/jsonHelper.cpp pipe/parentExe.cpp pipe/pipe.h pipe/pipe.cpp pipe/Luncher.cpp simple/main.cpp utils/main.cpp test/initSolve.cpp test/initSolve.h)
add_executable(hello ${SOURCES})

add_executable(project
        test/main.cpp
        test/dpll.cpp
        test/jsonHelper.cpp
        test/initSolve.cpp
        test/check.cpp
        test/walksat.cpp
        )

add_executable(pipe_test
        pipe/Luncher.cpp
        pipe/pipe.cpp
        )

add_executable(input_test
        simple/main.cpp
        )

add_executable(fork_test
        utils/main.cpp
        )

#E:\LAB\IS\cd\jsoncpp\include\json
#target_include_directories(postProcess_Clion PUBLIC D:/Project/myproject/postProcess_Clion/jsoncpp/include/json)
#target_link_libraries(postProcess_Clion PUBLIC D:/Software/cpplib/jsoncpp-master/jsoncpp-master/build_vsMingW/lib/libjsoncpp.a)
#
#add_executable(test test/main.cpp genExample/genExam.cpp genExample/genExam.h genExample/lcExam.cpp genExample/lcExam.h)
