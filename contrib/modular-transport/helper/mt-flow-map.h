#ifndef FLOW_MAP_H
#define FLOW_MAP_H

#include "mt-flow-id.h"


namespace ns3 {
  template<typename Value>
  class flow_map {
    Value defaultVal;
    std::unordered_map<flow_id, Value> flowMap;

    public:
      flow_map(Value defaultVal) : defaultVal(defaultVal) {}

      // subscript operator which sets and returns default value if necessary
      Value& operator[] (const flow_id & key) {
        if (flowMap.find(key) == flowMap.end()) {
          flowMap[key] = defaultVal;
        }
        return flowMap[key];
      }
  };
}

#endif // FLOW_MAP_H