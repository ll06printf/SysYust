add_executable(AST_Builder AST_BuilderTest.cpp)
target_link_libraries(AST_Builder
    PRIVATE AST
)

list(LENGTH sy_source_list sy_length)
if (${EnableASTBuildTest} AND NOT ${sy_length} EQUAL 0)
    list(LENGTH sy_source_list sy_length)
    MATH(EXPR sy_length "${sy_length}-1")
    foreach(index RANGE ${sy_length})
        list(GET sy_test_name_list ${index} current_name)
        list(GET sy_source_list ${index} current_path)
#        message(${current_name}:${current_path})
        add_test(NAME AST_Build_${current_name}
            COMMAND SysYCompiler -o - --AST ${current_path}
        )
    endforeach ()
endif()