/*
update object set conn_str='test connection string';
update counter_type set module='set4tm';
select c.id, c.c_number as number, c.address, ct.name, ct.module from counter c left join counter_type ct on c.type=ct.id where c.id=1 order by c.id;
*/

/*
insert into feeder (name, object) values ('f1', 33), ('f2', 33), ('f3', 34), ('f4', 35), ('f5', 36), ('f6', 36);
*/

select c.id, c.c_number as number, c.address, ct.name, ct.module, o.connection, o.conn_str, f.name 
from counter c 
left join counter_type ct on c.type=ct.id 
left join feeder f on c.feeder=f.id 
left join object o on f.object=o.id 
where c.id=1 order by c.id;

