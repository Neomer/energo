#ifndef ACDRV_GLOBAL_H
#define ACDRV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ACDRV_LIBRARY)
#  define ACDRVSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ACDRVSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ACDRV_GLOBAL_H
