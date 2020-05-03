# 配置需要编译的源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_COMMON_LIST)


# 配置生成的可执行文件
add_executable(chatClient ${SRC_LIST} ${SRC_COMMON_LIST})

# 配置链接库
target_link_libraries(chatClient pthread)