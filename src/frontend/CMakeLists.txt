# 处理Antlr4 生成

# 建立变量
set(Antlr4_SysY_Class
        SysYBaseListener
        SysYBaseVisitor
        SysYLexer
        SysYListener
        SysYParser
        SysYVisitor
)

set(SYSY_HEADER)
set(SYSY_SOURCE)

foreach (CurrentClass ${Antlr4_SysY_Class})
    list(APPEND SYSY_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/generated/${CurrentClass}.h)
    list(APPEND SYSY_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/generated/${CurrentClass}.cpp)
endforeach ()

# 生成语法文件的cpp目标
add_custom_command(OUTPUT ${SYSY_HEADER} ${SYSY_SOURCE}
    COMMAND antlr4 -o ${CMAKE_CURRENT_SOURCE_DIR}/generated -visitor ${CMAKE_CURRENT_SOURCE_DIR}/SysY.g4
    COMMAND cp ${SYSY_HEADER} ${SYSYUST_PUBLIC_HEADER_DIR}/antlr4_target
)
add_custom_target(Antlr4_SysY_Generate DEPENDS ${SYSY_HEADER} ${SYSY_SOURCE})

# 添加接口目标和自省
add_library(Antlr4_SysY STATIC ${SYSY_SOURCE} ${SYSY_HEADER})
add_dependencies(Antlr4_SysY Antlr4_SysY_Generate)

target_include_directories(Antlr4_SysY
        PUBLIC ${SYSYUST_PUBLIC_HEADER_DIR}/antlr4_target
        ${CMAKE_SOURCE_DIR}/lib/antlr4-cpp-runtime/runtime/src
)
target_link_libraries(Antlr4_SysY PUBLIC antlr4_runtime-build_static)