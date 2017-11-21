#ifndef UTILITIES_H
#define UTILITIES_H

#include <sstream>

template<typename Word>
std::ostream& write_raw(std::ostream& outs, Word value) {
  for (size_t size = sizeof(Word); size; --size, value >>= 8) {
    outs.put((char)(value & 0xFF));
  }
  return outs;
}

template<typename Word>
std::istream& read_raw(std::istream& ins, Word& value) {
  value = 0;
  size_t length = sizeof(Word);
  for (size_t i = 0; i < length; i++) {
    int byte = ins.get() << (8 * i);
    value |= byte;
  }
  return ins;
}

template <typename T>
std::string stringify(T array[], size_t begin, size_t size) {
  std::ostringstream ss;
  for (size_t i = begin; i < size; i += 1) {
    ss << array[i];
    if (i < size - 1) {
      ss << " ";
    }
  }
  return ss.str();
}

template <typename T>
std::string stringify(T array[], size_t size) {
  return stringify<T>(array, 0, size);
}

#endif