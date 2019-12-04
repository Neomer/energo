#include "SchemeObjectSetting.h"

SchemeObjectSetting::SchemeObjectSetting(QString name, QVariant value, QString description, QString help)
{
	_name = name;
	_description = description;
	_help = help;
	_value = value;
}

QString SchemeObjectSetting::name() const
{
	return _name;
}

QString SchemeObjectSetting::description() const
{
	return _description;
}

QString SchemeObjectSetting::help() const
{
	return _help;
}

void SchemeObjectSetting::setValue(QVariant value)
{
	_value = value;
}


QVariant SchemeObjectSetting::value() const
{
	return _value;
}
