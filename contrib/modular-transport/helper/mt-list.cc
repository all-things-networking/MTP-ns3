#include "mt-list.h"

namespace ns3 {
  template<typename T>
  void list<T>::add(T data) {
    listVector.push_back(data);
  }

  template<typename T>
  void list<T>::remove(int i) {
    listVector.erase(listVector.begin() + i);
  }

  template<typename T>
  T& list<T>::operator[] (int i) {
    return listVector[i];
  }

  template<typename T>
  T list<T>::operator[] (int i) const {
    return listVector[i];
  }
}