# 定义变量, 表示当前文件夹下的所有的源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_SRC_LIST)
aux_source_directory(./model MODEL_SRC_LIST)
aux_source_directory(./redis REDIS_SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_COMMON_LIST)
set(SRC_MAIN ${PROJECT_SOURCE_DIR}/test/server.cpp)

# 生成可执行文件
add_executable(chatServer ${SRC_LIST} ${DB_SRC_LIST} ${MODEL_SRC_LIST} ${REDIS_SRC_LIST} ${SRC_COMMON_LIST} ${SRC_MAIN})

# 配置链接库
target_link_libraries(chatServer muduo_net muduo_base mysqlclient hiredis pthread)