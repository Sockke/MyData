-- 内外连查询

-- 内连查询: 就是普通的查询
  --显示SMITH的名字和部门名称
  select ename, dname from emp, dept where emp.deptno = dept.deptno and ename = 'SMITH';
  select ename, dname from emp inner join dept 
  on emp.deptno = dept.deptno and ename = 'SMITH';

-- 外连查询
  -- 左外连接: 将左表作为主表, 所有的行必须显示
  -- 右外连接: 将右表作为主表, 所有的行必须显示
  -- 其实有一个左外查询即可
    --对stu表和exam表联合查询，把所有的成绩都显示出来，
    --即使这个成绩没有学生与它对应，也要显示出来
    select * from stu left join exam on stu.id = exam.id;

