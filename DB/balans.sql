select dt.*, ch.name from (select d.date, d.itv, c.id, ch.index, sum(d.value)
from channel ch 
left join data d on d.channel=ch.id
left join counter c on c.id=ch.counter
left join feeder f on f.id=c.feeder
left join object o on o.id=f.object
where o.id=64
group by d.date, d.itv, c.id, ch.index
order by d.date, d.itv, ch.index) dt 
left join channel ch on ch.counter=dt.id;
