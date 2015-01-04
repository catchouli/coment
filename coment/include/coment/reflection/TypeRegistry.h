#pragma once

#include <cstdio>
#include <unordered_map>
#include <vector>
#include <typeinfo>

#include "coment/DLL.h"
#include "coment/reflection/Macros.h"

namespace coment
{
    struct ComentTypeInfo
    {
        std::string name;
        const std::type_info* type_info;
    };

    struct TypeInfoRegistry
    {
        static std::unordered_map<std::string, ComentTypeInfo> COMENT_API typeInfoRegistry;
    };

    const ComentTypeInfo COMENT_API getTypeInfo(const char* name);
}