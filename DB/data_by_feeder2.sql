SELECT 
o.name as object, ch.feeder as id, ch.f_name as name, ch.name as cname, d.channel, d.value, d.value / ch.kt cdiff
FROM 
(
	SELECT 
	f.id, ch.index AS channel, sum(d.value) AS value 
	FROM data d 
	LEFT JOIN channel ch ON ch.id = d.channel 
	LEFT JOIN counter c ON c.id = ch.counter 
	LEFT JOIN feeder f ON f.id = c.feeder 
	LEFT JOIN object o ON o.id = f.object 
	left join factory ft on ft.id=o.factory 
	WHERE ft.id = 1 AND d.dt >= '2012-05-01 00:00:00'::timestamp without time zone AND d.dt < '2012-06-01 00:00:00'::timestamp without time zone AND d.itv_length = 30 
	GROUP BY f.id, ch.index 
) d 
left join 
(
	select 
	o.id as object, f.id as feeder, f.name as f_name, ch.id, ch.index, ch.name, f.kt_h / f.kt_l * f.kn_h / f.kn_l kt
	from channel ch 
	LEFT JOIN counter c ON c.id = ch.counter 
	LEFT JOIN feeder f ON f.id = c.feeder 
	LEFT JOIN object o ON o.id = f.object 
	left join factory ft on ft.id=o.factory 
	WHERE ft.id = 1 
) ch on d.id = ch.feeder and d.channel=ch.index 
left join object o on o.id=ch.object 
ORDER BY o.name, ch.f_name, d.channel;