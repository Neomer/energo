#ifndef ORADRV_GLOBAL_H
#define ORADRV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ORADRV_LIBRARY)
#  define ORADRVSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ORADRVSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ORADRV_GLOBAL_H
