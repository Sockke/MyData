-- 复合查询

-- 普通多表查询
-- 子查询
  -- 在where之后的子查询: 单行多行多列...
    模拟一张临时表作为where的筛选条件

    -- 1.查询和10号部门的工作相同的雇员的名字，岗位，工资，部门号，但是不包含10自己的
    select ename, job, sal, deptno from emp where job in 
    (select job from emp where deptno = 10) and deptno<>10;
    -- 2.显示工资比部门30的所有员工的工资高的员工的姓名、工资和部门号
    select ename, sal, deptno from emp where sal > all(select sal from emp where deptno = 30);
    -- 3.；显示工资比部门30的任意员工的工资高的员工的姓名、工资和部门号
    select ename, sal, deptno from emp where sal > any(select sal from emp where deptno = 30);
    -- 4.查询和SMITH的部门和岗位完全相同的所有雇员，不含SMITH本人
    select * from emp where (deptno, job) = 
    (select deptno, job from emp where ename = 'SMITH') and ename<>'SMITH';

  -- 在from之后的子查询
    模拟一张临时表作为from的查询表, 必须加别名
    一般是出现在聚合函数的构成的表
    --查找每个部门工资最高的人的姓名、工资、部门、最高工资
    select ename, sal, deptno, maxsal 
    from emp, (select max(sal) as maxsal from emp group by deptno) as tmp 
    where sal = maxsal;
    -- 显示每个部门的信息（部门名，编号，地址）和人员数量 
    select dname, dept.deptno, loc, nums 
    from dept, (select deptno, count(*) as nums from emp group by deptno) as tmp 
    where dept.deptno = tmp.deptno;

  -- 合并查询
   --union用的很少, union all可以联合2章表的内容做到可以重复
   --将工资大于2500或职位是MANAGER的人找出来
    select * from emp where sal > 2500 union all 
    select * from emp where job = 'MANAGER';
