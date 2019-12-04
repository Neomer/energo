select d.date, div(d.itv, 60 / d.itv_length) itv, ch.index as channel, 60 itv_length, sum(d.value) as value 
from data d 
left join channel ch on ch.id=d.channel 
left join counter c on c.id=ch.counter 
left join feeder f on f.id=c.feeder 
left join object o on o.id=f.object 
left join factory ft on ft.id=o.factory 
where ft.id=7 and d.dt >= '2012-03-01' and d.dt < '2012-04-01 00:00:00' and d.itv_length=30 
group by d.date, div(d.itv, 60 / d.itv_length) , ch.index, d.itv_length 
order by d.date, itv, ch.index;