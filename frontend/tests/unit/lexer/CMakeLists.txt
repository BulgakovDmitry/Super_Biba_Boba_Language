find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

set(SRC_LIST
    src/lexer.cpp
    ${FLEX_Lexer_OUTPUTS}
)

add_executable(lexer ${SRC_LIST})

target_link_libraries(lexer
    PRIVATE 
        frontend::headers
        GTest::gtest
        GTest::gtest_main
        Threads::Threads
        ${FLEX_LIBRARIES}
)

gtest_discover_tests(lexer
    PROPERTIES LABELS "unit"
)  