#ifndef MT_APP_H
#define MT_APP_H

#include <bitset>

namespace ns3 {
  // bit type
  template <size_t N>
  using bit = std::bitset<N>;

  // app_msg_t type
  class app_msg_t {
    public:
      int size;
      uint8_t * msg;

      app_msg_t(const app_msg_t& other, int size) : size{size}, msg{msg} {}
      
      app_msg_t operator=(const app_msg_t& other) {
        msg = other.msg;
      }

      app_msg_t operator=(uint8_t * other) {
        msg = other;
      }

      int len() { return size; }
  };

  // app_hdr_t type
  class app_hdr_t {
    public:
      int size;
      uint8_t * msg;
    
  };
}

#endif // MT_APP_HEADER_H