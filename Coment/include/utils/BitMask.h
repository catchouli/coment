#ifndef __BITMASK_H__
#define __BITMASK_H__

// How many bits to have in the bitsets used for the component mask?
#define COMENT_NUM_BITS 32

#include "Bitset.h"

namespace coment
{
	typedef coment::Bitset<COMENT_NUM_BITS> BitMask;
}

#endif /* __BITMASK_H__ */
