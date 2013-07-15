#include "coment/utils/HashGenerator.h"

namespace coment
{
	// djb2 string hashing function from http://www.cse.yorku.ca/~oz/hash.html
	unsigned int HashGenerator::hash(const char* value)
	{
		int c;
		unsigned int hash = 5381;

		while ((c = *value++))
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

		return hash;
	}
}
