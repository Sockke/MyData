-- 数据库 -- 

-- sql语言类型 -- 
  -- DDL 
    create
    alter
  -- DML
    insert
    delete
    update
  -- DQL
    select (from where)
  -- DCL
    grant
    revoke
    rollback
    commit

-- 字符集和校验规则 -- 
  -- 查看默认字符集
  show variables like 'character_set_database';
  show charset; -- 查看数据库支持的所有字符集

    -- ascii gbk unicode utf8
    ascii -- 每个字符占1个字节
    gbk -- 每个字符占2个字节
    uft8 -- 每个字符占3个字节

  -- 查看默认校验规则
  show variables like 'collation_database';
  show collation; -- 查看数据库支持的所有校验规则

    -- 校验规则 --
    create database test collate 'utf8_general_ci' -- 默认字符集, 数据不区分大小写
    create database test collate 'utf8_bin' -- 数据区分大小写

  
-- 数据库的导出与导入 --
  -- 导出
    # mysqldump -u root -p shop goods > shop_goods.sql
  -- 导入
    > source ./shop_goods.sql;
