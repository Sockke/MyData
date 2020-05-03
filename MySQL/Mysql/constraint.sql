-- mysql的约束规则 -- 
-- constraint --
	-- null --
	name varchar(20) not null

	-- primary key --
  -- 非空, 唯一
	id int unsigned primary key  
	primary key(id, name) -- 复合主键
	alter table class drop primary key; -- 删除主键
	alter table class add primary key(id, name); -- 添加主键

	-- auto_increment --
	-- 唯一, 一般搭配主键使用
	id int(6) unsigned primary key auto_increment
  select last_insert_id(); -- 查看最后一次插入时, 第一个数据的自增id
  truncate test; -- 清空表, 同时将自增主键的值重置

	-- unique --
	-- 可以为空, 唯一
	email varchar(30) unique -- 一般用于qq号, email等

	-- foreign --
	-- 关联两表, 两表中的某些字段一一对应
	-- 并且对应字段的类型必须一致
	foreign key(class_id) references myclass(id) -- 一般用于有关联的两张表

-- other constraint --
	-- comment --
	name varchar(20) comment '姓名'

	-- zerofill --
  -- 空位补0
	int(6) zerofill


