#ifndef BRANCHCONTAINERMAP_H
#define BRANCHCONTAINERMAP_H

#include <map>

#include "ontoloGenius/ontoGraphs/BranchContainer/BranchContainerBase.h"

template <typename B>
class BranchContainerMap : public BranchContainerBase<B>
{
public:
  BranchContainerMap() {}
  virtual ~BranchContainerMap() {}

  virtual B* find(std::string word);
  virtual void load(std::vector<B*>& vect);
private:
  std::map<std::string, B*> nodes_;
};

template <typename B>
B* BranchContainerMap<B>::find(std::string word)
{
  typename std::map<std::string, B*>::iterator it = nodes_.find(word);
  if(it == nodes_.end())
    return nullptr;
  else
    return it->second;
}

template <typename B>
void BranchContainerMap<B>::load(std::vector<B*>& vect)
{
  for(size_t i = 0; i < vect.size(); i++)
    nodes_[vect[i]->value_] = vect[i];
}

#endif