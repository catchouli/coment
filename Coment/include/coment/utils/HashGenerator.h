#ifndef __HASHGENERATOR_H__
#define __HASHGENERATOR_H__

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
}

#endif /* __HASHGENERATOR_H__ */

