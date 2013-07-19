#ifndef __COMENT_MAP_H__
#define __COMENT_MAP_H__

#ifdef _MSC_VER
	#include <unordered_map>

	#define COMENT_MAP std::unordered_map
#else
	#include <tr1/unordered_map>

	#define COMENT_MAP std::tr1::unordered_map
#endif

#endif /* __COMENT_MAP_H__ */

