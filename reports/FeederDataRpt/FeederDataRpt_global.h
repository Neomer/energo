#ifndef FEEDERDATARPT_GLOBAL_H
#define FEEDERDATARPT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FEEDERDATARPT_LIBRARY)
#  define FEEDERDATARPTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FEEDERDATARPTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FEEDERDATARPT_GLOBAL_H
