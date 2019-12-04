#ifndef PMDDRV_GLOBAL_H
#define PMDDRV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PMDDRV_LIBRARY)
#  define PMDDRVSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PMDDRVSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PMDDRV_GLOBAL_H
