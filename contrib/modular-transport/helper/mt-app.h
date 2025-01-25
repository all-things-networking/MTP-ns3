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
      int flow_id;

      app_msg_t(): size{0}, msg{nullptr}, flow_id{0} {}
      app_msg_t(const app_msg_t& other, int size) : size{size}, msg{other.msg} {}
      app_msg_t(uint8_t * other, int size) : size{size}, msg{other} {}
      app_msg_t(uint8_t * other, int size, int flow_id) : size{size}, msg{other}, flow_id{flow_id} {}

      app_msg_t& operator=(const app_msg_t& other) {
        if (this != &other) {
          size = other.size;
          flow_id = other.flow_id;
          msg = other.msg;
        }
        return *this;
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