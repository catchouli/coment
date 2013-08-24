#ifndef COMENT_SHAREDPTR_H
#define COMENT_SHAREDPTR_H

#include "Config.h"

#ifdef _MSC_VER
    #include <memory>
# elif defined COMENT_CONFIG_HAS_CPP11
    #include <memory>
#else
	#include <tr1/memory>
#endif

#endif /* COMENT_SHAREDPTR_H */

