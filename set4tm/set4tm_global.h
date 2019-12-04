#ifndef SET4TM_GLOBAL_H
#define SET4TM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SET4TM_LIBRARY)
#  define SET4TMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SET4TMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SET4TM_GLOBAL_H
