-- 增
  insert into student values (1, 'sock');
  insert into student(name) values ('sock');
-- 删
  delete from student where name = 'sock'
  delete from student;
-- 改
  update student set id = 15 where name = 'sock';
  update student set id = 15, name = 'laoma' where id = 1;

-- delete from table 与 truncate table 的区别
  -- 功能: delete 是逐行删除数据, truncate 是截断数据, 清空所有记录回到建表时的原始状态
          -- 比如说delete不能清空自增序列, 但是truncate可以
  -- 效率: delete 返回删除的行数, truncate返回0, truncate直接截断, 效率更高
