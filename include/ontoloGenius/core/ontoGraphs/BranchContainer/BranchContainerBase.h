#ifndef BRANCHCONTAINERBASE_H
#define BRANCHCONTAINERBASE_H

#include <string>
#include <vector>

class ValuedNode;
template <typename T> struct Branch_t;

template <typename B>
class BranchContainerBase
{
  static_assert(std::is_base_of<ValuedNode,B>::value, "B must be derived from ValuedNode");
public:
  BranchContainerBase() {}
  virtual ~BranchContainerBase() {}

  virtual B* find(const std::string& word) = 0;
  virtual std::vector<B*> find(bool (*comp)(B*, std::string, std::string), const std::string& word, const std::string& lang) = 0;
  virtual void load(std::vector<B*>& vect) = 0;
private:
};

#endif
