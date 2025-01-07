#ifndef __CARGO_H__
#define __CARGO_H__

#include <stdint.h>

#include <set>
#include <sstream>
#include <string>

class Cargo {
 private:
  std::string name;
  std::string source;
  std::string destination;
  uint64_t weight;
  std::set<std::string> properties;

 public:
  Cargo(const std::string & line);

  std::string getName() const { return name; }
  std::string getSource() const { return source; }
  std::string getDestination() const { return destination; }
  uint64_t getWeight() const { return weight; }
  const std::set<std::string> & getProperties() const { return properties; }

  bool hasProperty(const std::string & property) const;

  int getPropertyValue(const std::string & key) const;
  struct compareCargoByWeight {
    bool operator()(const Cargo & a, const Cargo & b) const {
      return a.getWeight() > b.getWeight();
    }
  };
};

#endif
