#ifndef __HASHGENERATOR_H__
#define __HASHGENERATOR_H__

#include <typeinfo>

namespace coment
{
	class HashGenerator
	{
	public:
		static unsigned int hash(const char* value);

		template <typename T>
		static unsigned int hash();

	private:
		HashGenerator();
		HashGenerator(const HashGenerator&);
	};

	template <typename T>
	unsigned int HashGenerator::hash()
	{
		return hash(typeid(T).name());
	}
}

#endif /* __HASHGENERATOR_H__ */

