#ifndef SCHEMEOBJECTSETTING_H
#define SCHEMEOBJECTSETTING_H

#include <QString>
#include <QVariant>

class SchemeObjectSetting
{
	public:
		SchemeObjectSetting(QString name, QVariant value = QVariant(), QString description = QString(), QString help = QString());

		QString name() const;
		QString description() const;
		QString help() const;

		void setValue(QVariant value);
		QVariant value() const;

	private:
		QString _name;
		QString _description;
		QString _help;
		QVariant _value;
};

#endif // SCHEMEOBJECTSETTING_H
