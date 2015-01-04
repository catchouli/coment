#pragma once

/** Register a component with the type info registry */
#define REGISTER_COMPONENT(type) \
    namespace \
    { \
        struct type ## Register \
                        { \
            type ## Register() \
                                        { \
                coment::ComentTypeInfo type_info; \
                type_info.name = #type; \
                type_info.type_info = &typeid(type); \
                coment::TypeInfoRegistry::typeInfoRegistry[#type] = type_info; \
                                        } \
            \
        } type ## Register; \
    }