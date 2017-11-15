#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>

const char DELIM = ',';

class Collection;

struct Key {
  const enum Type {
    INTEGER,
    STRING,
  } type;
  const size_t pos;  // TODO: this should be part of record
  const std::string name;
  Key(size_t pos, std::string name, Type type)
    : type(type), pos(pos), name(name) {}
  Key(const Key& other) : type(other.type), pos(other.pos), name(other.name) {}
};

struct Field {
  const union Data {
    int integer;
    std::string* string;
  } data;
  Key key;
  Field(Data data, Key key) : data(data), key(key) {}
  ~Field();
  std::string str() const;
  bool operator<(const Field& other) const;
  bool operator>(const Field& other) const;
  bool operator<=(const Field& other) const;
  bool operator>=(const Field& other) const;
  bool operator==(const Field& other) const;
};

class Index {
public:
  static Index* from_csv(std::string file_name);
  size_t get(size_t i);
  size_t operator[](size_t i);
  ~Index();
  size_t size() const;
private:
  typedef size_t Word;
  Index(std::string file_name);
  const std::string file_name;
  size_t size_;
  std::fstream stream;
};

typedef std::pair<std::string, Key> key_pair_t;

class Collection {
public:
  class Record {
  public:
    const size_t offset;
    Field get(std::string key_name);
    Field get(Key key);
    Field operator[](std::string key_name);
    Field operator[](Key key);
  private:
    friend class Collection;
    Record(Collection& collection, size_t offset);
    Collection& collection;
  };

  const std::string file_name;
  Collection(const std::string& file_name);
  ~Collection();
  Collection sort(std::string str, std::vector<std::string> keys);
  Collection sort(std::string str, std::vector<Key> keys);
  Record get(size_t row);
  Record operator[](size_t row);
  size_t size() const;
private:
  friend class Record;
  std::ifstream input;
  std::map<std::string, Key> keys_;
  Index* index;

  void seek(size_t pos);
  size_t cur_pos();

  void init_file();
  void init_keys();
  void init_index();
};