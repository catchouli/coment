#ifndef COMENT_FUNCTIONS_H
#define COMENT_FUNCTIONS_H

namespace coment
{
	// Remove the first instance equal to value by replacing it with the last element
	template <typename T>
	void removeFirst(std::vector<T>& array, const T& value)
	{
		for (unsigned int i = 0; i < array.size(); ++i)
		{
			if (array[i] == value)
			{
				// Replace with last
				array[i] = array[array.size()-1];

				// Remove last
				array.pop_back();

				// End search
				return;
			}
		}
	}

	// Remove all instances equal to value by replacing it with the last element
	template <typename T>
	void removeAll(std::vector<T>& array, const T& value)
	{
		for (unsigned int i = 0; i < array.size(); ++i)
		{
			if (array[i] == value)
			{
				// Replace with last
				array[i] = array[array.size()-1];

				// Remove last
				array.pop_back();
			}
		}
	}
}

#endif /* COMENT_FUNCTIONS_H */

