//  project by Vincenzo D'Agostino (vindagos@gmail.com)


#ifndef PLCQTLIB_GLOBAL_H
#define PLCQTLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLCQTLIB_LIBRARY)
#  define PLCQTLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLCQTLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PLCQTLIB_GLOBAL_H
