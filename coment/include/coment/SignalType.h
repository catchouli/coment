#pragma once

#include <boost/tti/has_member_function.hpp>

namespace coment
{
    /* The signals used for events */
    enum class SignalType
    {
        OnEntityAdded,
        OnEntityRemoved,
        PreUpdate,
        OnUpdate,
        PostUpdate
    };

    // Generate type traits for testing the existence of member functions, which can then be checked with
    // has_member_function_test<type, returntype, boost::mlp::vector<argtypes>>::value
    BOOST_TTI_HAS_MEMBER_FUNCTION(onEntityAdded);
    BOOST_TTI_HAS_MEMBER_FUNCTION(onEntityRemoved);
    BOOST_TTI_HAS_MEMBER_FUNCTION(preUpdate);
    BOOST_TTI_HAS_MEMBER_FUNCTION(onUpdate);
    BOOST_TTI_HAS_MEMBER_FUNCTION(postUpdate);
}