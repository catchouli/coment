#ifndef COMENT_CONFIG_H
#define COMENT_CONFIG_H

#if defined __clang__
#	if __has_include_next("unordered_map")
#		define COMENT_CONFIG_HAS_CPP11
#	endif
#endif

#endif /* COMENT_CONFIG_H */

