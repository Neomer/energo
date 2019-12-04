select 
	mp.id point, mc.channel, pcp.code pointcode, pcc.code channelcode
from measuringpoint mp 
left join measuringchannel mc on mc.mpoint=mp.id 
left join channel ch on ch.id = mc.channel
left join point_codes pcp on pcp.point = mp.id 
left join point_codes pcc on pcc.point = ch.id 
where pcp.code='182050001313201';