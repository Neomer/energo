TEMPLATE = subdirs

DSTPATH=$$OUT_PWD

INCLUDE = 0

SUBDIRS += conf \
    report \
    ReportEngine \
	Reports \
    pgredrv \
    scheduler \
    updater_srv \
    updater \
    #siconC10v2 \
    #merc320 \
    acdrv \
    qextserialport \
    oradrv \
    pgtest2 \
    #DataServer \
    #datasrvdrv \
    #pmddrv
    xmlimport \
    planning \
    sceditor \
    time \
    energomera \
    energo_db

OTHER_FILES = TODO

VAR = $$find(QT_VERSION, 4.6.*)

!isEmpty(VAR)
{
	message(QT 4.6.* version detected)
	SUBDIRS += \
		recv \
		set4tm \
		GSMConnection \
}

# ”казывать проекты, которые не нужно компилить
contains(INCLUDE, 1) {
	SUBDIRS -= \
		recv \
		set4tm \
		GSMConnection \
}
















