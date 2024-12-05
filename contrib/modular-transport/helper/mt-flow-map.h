#ifndef FLOW_MAP_H
#define FLOW_MAP_H

#include "mt-flow-id.h"

namespace ns3 {
  template<typename Value>
  class flow_map {
    Value defaultVal;
    std::unordered_map<flow_id, Value> flowMap;

    public:
      // deprecated: flow_map(int lower_limit, int upper_limit, bool (*drop_policy)(MTEvent *))

      flow_map(Value defaultVal) : defaultVal{defaultVal} {}

      // initializes defaultVal with a default-constructed Value (useful for objects)
      flow_map() : defaultVal{} {}

      // iterator
      using iterator = typename std::unordered_map<flow_id, Value>::iterator;
      iterator begin() { return flowMap.begin(); }
      iterator end() { return flowMap.end(); }
      iterator next(iterator it) { return ++it; }

      // subscript operator which sets and returns default value if necessary
      Value& operator[] (const int & key) {
        if (flowMap.find(key) == flowMap.end()) {
          flowMap[key] = defaultVal;
        }
        return flowMap[key];
      }

      // Value& operator[] (const int & key) {
      //   flow_id flowIdKey = (flow_id) key;
      //   return flowMap[flowIdKey];
      // }
      
      int size(){
        return flowMap.size();
      }
  };
}

#endif // FLOW_MAP_H