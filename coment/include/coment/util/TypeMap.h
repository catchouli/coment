#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>

namespace coment
{
    template <typename PointerType = void>
    class TypeMap
    {
    public:

        /** Add an object to this map, initialised by args... */
        template <typename T, typename... Args>
        T* add(Args... args);

        /** Get an object from this map */
        template <typename T>
        T* get() const;

        /** Get an object from this map */
        template <typename T>
        void remove();

        /** Get a vector of all elements for iteration */
        const std::vector<PointerType*>* getVector() const;

    private:

        /** All objects by type */
        std::unordered_map<std::type_index, std::shared_ptr<PointerType>> mObjects;

        /** Pointers to all objects */
        std::vector<PointerType*> mPointerVec;

    };

    /** Add an object to this map, initialised by args... */
    template <typename PointerType>
    template <typename T, typename... Args>
    T* TypeMap<PointerType>::add(Args... args)
    {
        // Make sure this type isn't already in the map
        remove<T>();

        // Initialise object
        auto ptr = std::make_shared<T>(args...);

        // Store it in map
        mObjects[typeid(T)] = ptr;

        // Add it to vector
        mPointerVec.push_back(ptr.get());

        // Return pointer
        return ptr.get();
    }

    /** Get an object from this map */
    template <typename PointerType>
    template <typename T>
    T* TypeMap<PointerType>::get() const
    {
        // Find object
        auto it = mObjects.find(typeid(T));

        // If not found, return nullptr
        if (it == mObjects.end())
            return nullptr;

        // Return pointer
        return static_cast<T*>(it->second.get());
    }

    /** Get an object from this map */
    template <typename PointerType>
    template <typename T>
    void TypeMap<PointerType>::remove()
    {
        // Check if we already have an object of this type
        auto mapIt = mObjects.find(typeid(T));
        if (mapIt != mObjects.end())
        {
            // We already have an object of this type, obtain it
            PointerType* ptr = (PointerType*)mapIt->second.get();

            // Remove it from the vector
            mPointerVec.erase(std::find(mPointerVec.begin(), mPointerVec.end(), ptr));

            // Remove it from the map
            mObjects.erase(mapIt);
        }
    }

    /** Get a vector of all elements for iteration */
    template <typename PointerType>
    const std::vector<PointerType*>* TypeMap<PointerType>::getVector() const
    {
        return &mPointerVec;
    }

}
