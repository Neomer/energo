select d.date, d.itv, ch.index, d.value from 
data d
left join channel ch on ch.id=d.channel
left join counter c on c.id=ch.counter
left join feeder f on f.id=c.feeder
left join object o on o.id=f.object
left join factory ft on ft.id=o.factory
where to_dt(d.date, d.itv) >= '2012-01-29 00:00:00' and to_dt(d.date, d.itv) <= '2012-01-30 00:00:00' and ft.id=10
group by
order by d.date, d.itv, ch.index, d.valu; 