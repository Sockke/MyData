-- create database --
create database if not exists shop;

-- use database --
use shop;

-- create table --
create table goods (
	goods_id int unsigned primary key auto_increment,
	goods_name varchar(30) not null,
	unitprice double(7, 2) not null,
	category varchar(30) not null,
	provider varchar(30) not null
);

create table customer (
	customer_id int unsigned primary key auto_increment,
	name varchar(20) not null,
	address varchar(40) default null,
	email varchar(40) default null,
	gender enum('男', '女', '保密') default 3,
	card_id char(18) not null
);

create table purchase (
	order_id int unsigned primary key auto_increment,
	customer_id int unsigned,
	goods_id int unsigned,
	nums int unsigned default 1
	foreign key(customer_id) references customer(customer_id),
	foreign key(goods_id) references goods(goods_id)
);
