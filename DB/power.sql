select 
d.date, div(d.itv, 2) as itv, sum(d.value * b.direction) 
from balans_element b 
left join data d on b.channel=d.channel 
where 
b.balans=1 and 
d.dt>='2012-05-04' and d.dt<'2012-05-05' 
and d.itv_length=30 
and 
div(d.itv, 2) IN 
(select ch.hour from
controlhourgroup chg
left join controlhour ch on ch.gid=chg.id
where 
chg.id=1 and
ch.year=2012 and
ch.month=5)
and 
d.date NOT IN (select * from calendar where dt>'2012-05-04' and dt<'2012-05-05')
group by d.date, div(d.itv, 2) order by d.date, itv;