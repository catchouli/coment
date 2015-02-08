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

#include <functional>

namespace std
{
  /* Specialisation for std::hash */
  template <>
  struct hash<coment::SignalType>
  {
    typedef coment::SignalType argument_type;
    typedef std::underlying_type<argument_type>::type underlying_type;
    typedef std::hash<underlying_type>::result_type result_type;

    result_type operator()(const argument_type& arg) const
    {
      std::hash<underlying_type> hasher;
      return hasher(static_cast<underlying_type>(arg));
    }
  };
}
