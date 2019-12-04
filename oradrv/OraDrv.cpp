#include "OraDrv.h"

OraSqlDrv::OraSqlDrv()
{
}

void errorProc(OCI_Error *err)
{
	qDebug(
                "code  : ORA-%05i\n"
                "msg   : %s\n"
                "sql   : %s\n",
                OCI_ErrorGetOCICode(err), 
                OCI_ErrorGetString(err),
                OCI_GetSql(OCI_ErrorGetStatement(err))
           );
}

bool OraSqlDrv::apply()
{
	return OCI_Commit(_conn);
}

bool OraSqlDrv::connect(QString host, QString login, QString pass, bool reconnect)
{
	if (!OCI_Initialize(errorProc, NULL, OCI_ENV_DEFAULT)) 
		return false;
	
	qDebug("OraSqlDrv::connect() - DB: %s Login: %s Pass: %s\n",
		host.toAscii().constData(),
		login.toAscii().constData(),
		pass.toAscii().constData());
	
	_conn = OCI_ConnectionCreate(host.toAscii().constData(),
								 login.toAscii().constData(),
								 pass.toAscii().constData(), 
								 OCI_SESSION_DEFAULT);
	if (!_conn)
	{
		qDebug("OraSqlDrv::connect() - Connection create fail!\n");
		return false;
	}
	_reconnect = reconnect;
	
	return isConnected();
}

bool OraSqlDrv::connect(QString host, QString login, QString pass, QString dbname, bool reconnect)
{
	return connect(host, login, pass, reconnect);
}

OraSqlResult * OraSqlDrv::exec(const char *query)
{
	if (!isConnected())
		return new OraSqlResult(_codec);
	qDebug("OraSqlDrv::exec() - SQL: %s", query);
	OCI_Statement * st = OCI_CreateStatement(_conn);
	if (!st)
		return 0;
	if (!OCI_Prepare(st, query))
		return 0;
	if (!OCI_Execute(st))
		return 0;
	return new OraSqlResult(_codec, st);
}

OraSqlResult * OraSqlDrv::exec(QString query)
{
	return exec(query.toAscii().constData());
}

void OraSqlDrv::close()
{
	if (_conn)
		OCI_ConnectionFree(_conn);
	OCI_Cleanup();
}

QTextCodec * OraSqlDrv::codec()
{
	return _codec;
}

void OraSqlDrv::setCodec(QTextCodec * codec)
{
	_codec = codec;
}

bool OraSqlDrv::isConnected()
{
	if (_conn)
		return OCI_IsConnected(_conn);
	else
		return false;
}

