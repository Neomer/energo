select 
	c.c_number,
	o.name,
	f.name,
     	max(EXTRACT(EPOCH FROM DATE (d.date)) + (d.itv * 1800)) as date
from counter c
left join feeder f on c.feeder = f.id
left join object o on f.object = o.id
left join data d on c.feeder = d.feeder
where d.channel=0
group by 
c.c_number,
f.name,
o.name;

select 
c.c_number,
o.name,
f.name,
data.feeder as feeder, 
data.date as date, 
MAX(data.itv) as interval 
from
counter c
left join (Select feeder, MAX(date) as max_date from data Group by feeder) as mdate on mdate.feeder = c.feeder
left join feeder f on f.id = c.feeder
left join data on data.date = mdate.max_date and data.feeder = mdate.feeder
left join object o on f.object = o.id
Group by c.c_number, f.name, data.feeder, data.date, o.name;