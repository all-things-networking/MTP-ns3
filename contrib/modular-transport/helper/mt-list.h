#ifndef MT_LIST_H_
#define MT_LIST_H_

namespace ns3 {
  template<typename T>
  class list {
    vector<T> listVector;
    public:
      void add(T data);
      void remove(int i = 0);

      // used by compiler when indexing into a non-const list
      T& operator[] (int i);

      // used by compiler when indexing into a const list
      T operator[] (int i) const;
  };
}

#endif // MT_LIST_H