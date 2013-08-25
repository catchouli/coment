#ifndef COMENT_MAP_H
#define COMENT_MAP_H

#include "Config.h"

#ifdef _MSC_VER
    #include <unordered_map>
# elif defined COMENT_CONFIG_HAS_CPP11
    #include <unordered_map>
#else
	#include <tr1/unordered_map>
#endif

#endif /* COMENT_MAP_H */

