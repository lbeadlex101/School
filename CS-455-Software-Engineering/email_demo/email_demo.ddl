create database email_demo;

use email_demo;
create table email_list (id int primary key auto_increment, last_name varchar(100), email varchar(100));

insert into email_list (last_name, email) values ('alpha', 'abc@una.edu');
insert into email_list (last_name, email) values ('beta', 'def@una.edu');
insert into email_list (last_name, email) values ('charlie', 'ghl@una.edu');
insert into email_list (last_name, email) values ('delta', 'mno@una.edu');