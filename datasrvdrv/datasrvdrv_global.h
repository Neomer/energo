#ifndef DATASRVDRV_GLOBAL_H
#define DATASRVDRV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATASRVDRV_LIBRARY)
#  define DATASRVDRVSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATASRVDRVSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DATASRVDRV_GLOBAL_H
