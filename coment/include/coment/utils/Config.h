#ifndef COMENT_CONFIG_H
#define COMENT_CONFIG_H

#if defined __clang__ && __has_include_next("unordered_map")
#   define COMENT_CONFIG_HAS_CPP11
#endif

#endif /* COMENT_CONFIG_H */

