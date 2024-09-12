#ifndef FLOW_ID_H
#define FLOW_ID_H

#include <cstdlib>
#include <utility> // declval

  typedef int flow_id;

  // the rest of this is code for a template flow_id class that can take in any number of 
  //  parameters of the same type and stores them in a tuple

  // template initialized with varaidic parameter pack
  //   to allow as many of a particular type T as needed
  // template <typename... T>
  // class flow_id {
  //   // ensures T's can be compared with =
  //   std::static_assert((std::is_same_v<decltype(std::declval<T>() == std::declval<T>()), bool>),
  //     "All types must support operator==.");

  //   std::tuple<T...> id;

  //   public:
  //     // generic constructor
  //     flow_id(T... args) : id(args...) {}

  //     // constructor with perfect forwarding: useful for wrapper functions that want to pass forward
  //     //   the arguments they receive to the flow_id constructor
  //     flow_id(T&&... args) : id(std::forward<T>(args)...) {}

  //     bool operator==(const flow_id& other) const {
  //       return id == other.id;
  //     }

  //     // return id so that it can be used for hashing (in flow_map)
  //     const std::tuple<T...>& get_tuple() const {
  //       return id;
  //     }
  // };


// namespace std {
  // // primary template specialized below
  // template<typename> struct hash; 

  // // used in flow_map to hash flow_id's (if implemented as a template class with a tuple)
  // // for use as keys in the map to specialize the standard C++ hash struct for flow_id's specifically
  // template <typename... T>
  // struct hash<ns3::flow_id<T...>> { 
  //   std::size_t operator()(const ns3::flow_id<T...>& flowId) const {
  //     // reuse the default tuple hash function
  //     return std::hash<std::tuple<T...>>{}(flowId.get_tuple());  
  //   }
  // };
// }


#endif