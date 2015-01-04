#include "coment/reflection/TypeRegistry.h"

namespace coment
{
    std::unordered_map<std::string, ComentTypeInfo> COMENT_API TypeInfoRegistry::typeInfoRegistry;
    
    const ComentTypeInfo COMENT_API getTypeInfo(const char* name)
    {
        return TypeInfoRegistry::typeInfoRegistry[name];
    }
}