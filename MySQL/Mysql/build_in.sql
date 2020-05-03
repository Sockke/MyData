-- 内置函数

-- 字符串函数
  select charset('sock'); -- 查看字符集
  select instr('sock is a good man', 'good'); -- 返回子串出现的位置
  select ucase(name) from student; -- ucase/lcase转化大小写
  select left(name, 1) from student; -- 从左边数取n个字符, 可以被substring替代

  select length(name) from student; -- 字符串的长度
  select strcmp(name, newname) from student; -- 字符串的比较
  select strcat(name, 'is a good ', gender); -- 字符串的连接
  select substring(name, 1, 1); -- 字符串的截取, 
  -- 与C++substr不同的是, 第二个参数不是下标而是第n个字符
  select replace(name, substring(name, 1, 1), 'L') from student; -- 字符串替换

-- 数学函数
  select abs(-200);
  select conv(1024, 10, 2); -- 从10进制转化为2进制
  select ceiling(3.5); -- 向上取整
  select floor(3.5); -- 向下取整
  select format(3.1415936, 2) -- 保留2位小数
  select mod(20, 3) -- 求余
  select rand(); -- 返回[0, 1)的随机数

-- 其他函数
  select user(); -- 查看当前用户
  select password('root') -- 查看root密码(加密)
  select md5(user()); -- 查看字符串的md5值



--  查找字符串'10,A,B' 中逗号','出现的次数cnt。
  select length('10,A,B') - length(replace('10,A,B', ',', '')) as cnt;
