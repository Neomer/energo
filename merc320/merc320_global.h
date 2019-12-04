#ifndef MERC320_GLOBAL_H
#define MERC320_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MERC320_LIBRARY)
#  define MERC320SHARED_EXPORT Q_DECL_EXPORT
#else
#  define MERC320SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MERC320_GLOBAL_H
