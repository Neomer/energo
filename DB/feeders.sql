select d.*, f.name || ' ' || ch.name colname
from
(select 
d.date, div(d.itv, 60 / d.itv_length) itv, ch.id as channel, 60 itv_length, cbo.fid, sum(d.value) as value 
from data d 
left join channel ch on ch.id=d.channel 
left join channels_by_object cbo on cbo.chid=ch.id 
where cbo.ftid=1 and ch.type=1 and d.dt >= '2012-03-01' and d.dt < '2012-04-01' and d.itv_length=30 
group by d.date, div(d.itv, 60 / d.itv_length) , cbo.fid, ch.id, d.itv_length 
order by d.date, itv, ch.id) d
left join feeder f on d.fid = f.id
left join channel ch on d.channel = ch.id;