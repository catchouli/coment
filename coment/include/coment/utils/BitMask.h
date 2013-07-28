#ifndef COMENT_BITMASK_H
#define COMENT_BITMASK_H

// How many bits to have in the bitsets used for the component mask?
#define COMENT_NUM_BITS 32

#include "Bitset.h"

namespace coment
{
	typedef coment::Bitset<COMENT_NUM_BITS> BitMask;
}

#endif /* COMENT_BITMASK_H */
