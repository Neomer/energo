-- User energo_sys
CREATE ROLE energo_sys LOGIN
  ENCRYPTED PASSWORD md5('1234')
  NOSUPERUSER INHERIT NOCREATEDB NOCREATEROLE NOREPLICATION;

GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE data TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE channel TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE channel_names TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE connection TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE connection_type TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE counter TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE counter_type TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE object TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE feeder TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE factory TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE info TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE schedule TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE interview TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE model TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE point_codes TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE users TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE user_access TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE deliverypointgroup TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE plan TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE deliverypointgroup TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE deliverypoint TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE measuringpoint TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE measuringchannel TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE point_codes TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE balans TO energo_sys;
GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE balans_element TO energo_sys;

-- User energo_user
CREATE ROLE energo_user LOGIN
  ENCRYPTED PASSWORD md5('1234')
  NOSUPERUSER INHERIT NOCREATEDB NOCREATEROLE NOREPLICATION;

GRANT SELECT ON TABLE data TO energo_user;
GRANT SELECT ON TABLE channel TO energo_user;
GRANT SELECT ON TABLE channel_names TO energo_user;
GRANT SELECT ON TABLE connection TO energo_user;
GRANT SELECT ON TABLE connection_type TO energo_user;
GRANT SELECT ON TABLE counter TO energo_user;
GRANT SELECT ON TABLE counter_type TO energo_user;
GRANT SELECT ON TABLE object TO energo_user;
GRANT SELECT ON TABLE feeder TO energo_user;
GRANT SELECT ON TABLE factory TO energo_user;
GRANT SELECT ON TABLE info TO energo_user;
GRANT SELECT ON TABLE schedule TO energo_user;
GRANT SELECT ON TABLE interview TO energo_user;
GRANT SELECT ON TABLE model TO energo_user;
GRANT SELECT ON TABLE users TO energo_user;
GRANT SELECT ON TABLE user_access TO energo_user;
GRANT SELECT ON TABLE plan TO energo_user;
GRANT SELECT ON TABLE deliverypointgroup TO energo_user;
GRANT SELECT ON TABLE deliverypoint TO energo_user;
GRANT SELECT ON TABLE measuringpoint TO energo_user;
GRANT SELECT ON TABLE measuringchannel TO energo_user;
GRANT SELECT ON TABLE point_codes TO energo_user;
GRANT SELECT ON TABLE balans TO energo_user;
GRANT SELECT ON TABLE balans_element TO energo_user;

-- User energo_oper
CREATE ROLE energo_oper LOGIN
  ENCRYPTED PASSWORD md5('1234')
  NOSUPERUSER INHERIT NOCREATEDB NOCREATEROLE NOREPLICATION;

GRANT SELECT, UPDATE, INSERT ON TABLE data TO energo_oper;
GRANT SELECT ON TABLE channel TO energo_oper;
GRANT SELECT ON TABLE channel_names TO energo_oper;
GRANT SELECT ON TABLE connection TO energo_oper;
GRANT SELECT ON TABLE connection_type TO energo_oper;
GRANT SELECT ON TABLE counter TO energo_oper;
GRANT SELECT ON TABLE counter_type TO energo_oper;
GRANT SELECT ON TABLE object TO energo_oper;
GRANT SELECT ON TABLE feeder TO energo_oper;
GRANT SELECT ON TABLE factory TO energo_oper;
GRANT SELECT ON TABLE info TO energo_oper;
GRANT SELECT ON TABLE schedule TO energo_oper;
GRANT SELECT ON TABLE interview TO energo_oper;
GRANT SELECT ON TABLE model TO energo_oper;
GRANT SELECT ON TABLE users TO energo_oper;
GRANT SELECT ON TABLE user_access TO energo_oper;
GRANT SELECT, UPDATE, INSERT ON TABLE plan TO energo_oper;
GRANT SELECT ON TABLE deliverypointgroup TO energo_oper;
GRANT SELECT ON TABLE deliverypoint TO energo_oper;
GRANT SELECT ON TABLE measuringpoint TO energo_oper;
GRANT SELECT ON TABLE measuringchannel TO energo_oper;
GRANT SELECT ON TABLE point_codes TO energo_oper;
GRANT SELECT ON TABLE balans TO energo_oper;
GRANT SELECT ON TABLE balans_element TO energo_oper;

GRANT SELECT ON TABLE channels_by_object TO energo_oper;
GRANT SELECT ON TABLE channels_by_object TO energo_user;
GRANT SELECT, UPDATE, DELETE, INSERT ON TABLE channels_by_object TO energo_sys;

GRANT SELECT ON TABLE mchannels_by_object TO energo_oper;
GRANT SELECT ON TABLE mchannels_by_object TO energo_user;
GRANT SELECT, UPDATE, DELETE, INSERT ON TABLE mchannels_by_object TO energo_sys;

GRANT SELECT ON TABLE controlhourgroup TO energo_oper;
GRANT SELECT ON TABLE controlhourgroup TO energo_user;
GRANT SELECT, UPDATE, DELETE, INSERT ON TABLE controlhourgroup TO energo_sys;

GRANT SELECT ON TABLE controlhour TO energo_oper;
GRANT SELECT ON TABLE controlhour TO energo_user;
GRANT SELECT, UPDATE, DELETE, INSERT ON TABLE controlhour TO energo_sys;

GRANT SELECT ON TABLE controlhour2 TO energo_oper;
GRANT SELECT ON TABLE controlhour2 TO energo_user;
GRANT SELECT, UPDATE, DELETE, INSERT ON TABLE controlhour2 TO energo_sys;

GRANT SELECT ON TABLE access TO energo_oper;
GRANT SELECT ON TABLE access TO energo_user;
GRANT SELECT, UPDATE, DELETE, INSERT ON TABLE access TO energo_sys;

GRANT SELECT ON TABLE access_level TO energo_oper;
GRANT SELECT ON TABLE access_level TO energo_user;
GRANT SELECT, UPDATE, DELETE, INSERT ON TABLE access_level TO energo_sys;

GRANT SELECT ON TABLE operation_type TO energo_oper;
GRANT SELECT ON TABLE operation_type TO energo_user;
GRANT SELECT, UPDATE, DELETE, INSERT ON TABLE operation_type TO energo_sys;