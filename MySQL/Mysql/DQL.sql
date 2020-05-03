-- 基本查询
-- from 表->where筛选->group分组->having筛选->select选出->order排序->limit分页
  -- where 按行筛选, group by 按字段对行分组
  -- order by 默认升序asc, 倒序是desc
    select * from student order by math asc, chinese desc; -- 先按math升序, 在按Chinese降序
  -- limit 可以筛选也可以分页
    select * from student limit 0, 3; -- limit 起始位置,显示条数


-- 去重
  select distinct * from student;
-- 运算符
  -- 比较运算符
  select * from student where id > 10; -- > < >= <=
  select * from student where id <> 10; -- = != <>
  select * from student where id between 5 and 10; 
  select * from student where id in (3, 5, 7);
  select * from student where name like '刘%'; -- like / not like
  select * from student where name like '刘_';
  select * from student where name is null; -- is null/is not null
  -- 逻辑运算符
  select * from student where id > 10 and id < 20;
  select * from student where id > 10 or name = '刘%';
  select * from student where not(id < 10); -- 不常用
-- 聚合函数, having 可以通过聚合函数进行二次筛选
  -- count() max() min() avg() sum()
  select Email from Person group by Email having count(*) > 1;

