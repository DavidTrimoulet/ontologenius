#ifndef ONTOGRAPH_H
#define ONTOGRAPH_H

#include <string>
#include <vector>
#include <unordered_set>
#include <stdint.h>
#include <random>

#include "ontoloGenius/core/ontoGraphs/Graphs/Graph.h"
#include "ontoloGenius/core/ontoGraphs/Branchs/Branch.h"

/*
This file use CRTP (curiously recurring template pattern)
be really carreful of how you use it
*/


template <typename B>
class OntoGraph : public Graph<B>
{
  static_assert(std::is_base_of<Branch_t<B>,B>::value, "B must be derived from Branch_t<B>");
public:
  OntoGraph() {}
  ~OntoGraph();

  void close();

  std::unordered_set<std::string> getDown(const std::string& value, int depth = -1);
  std::unordered_set<std::string> getUp(const std::string& value, int depth = -1);
  std::unordered_set<uint32_t> getDownId(const std::string& value, int depth = -1);
  std::unordered_set<uint32_t> getUpId(const std::string& value, int depth = -1);
  std::string getName(const std::string& value);
  std::unordered_set<std::string> find(const std::string& value);
  bool touch(const std::string& value);

  void getDown(B* branch, std::unordered_set<std::string>& res, int depth = -1, unsigned int current_depth = 0);
  void getUp(B* branch, std::unordered_set<std::string>& res, int depth = -1, unsigned int current_depth = 0);
  void getDownId(B* branch, std::unordered_set<uint32_t>& res, int depth = -1, unsigned int current_depth = 0);
  void getUpId(B* branch, std::unordered_set<uint32_t>& res, int depth = -1, unsigned int current_depth = 0);

  std::unordered_set<B*> getDownPtr(B* branch);
  void getDownPtr(B* branch, std::unordered_set<B*>& res);
  std::unordered_set<B*> getUpPtr(B* branch);
  void getUpPtr(B* branch, std::unordered_set<B*>& res);

  std::vector<B*> get()
  {
    std::vector<B*> out = branchs_;
    out.insert( out.end(), roots_.begin(), roots_.end() );
    return out;
  }

protected:
  std::vector<B*> branchs_;
  std::vector<B*> roots_;

  std::vector<B*> tmp_mothers_;

  int depth_;

  void link();
  void add_family(B* branch, uint8_t family);
  void amIA(B** me, std::vector<B*>& vect, const std::string& value, bool erase = true);
  void isMyMother(B* me, const std::string& mother, std::vector<B*>& vect, bool& find);
};

template <typename B>
OntoGraph<B>::~OntoGraph()
{
  for(size_t i = 0; i < branchs_.size(); i++)
    delete branchs_[i];

  for(size_t i = 0; i < roots_.size(); i++)
    delete roots_[i];

  branchs_.clear();
  roots_.clear();
}

template <typename B>
void OntoGraph<B>::close()
{
  for(size_t i = 0; i < tmp_mothers_.size(); i++)
    roots_.push_back(tmp_mothers_[i]);

  tmp_mothers_.clear();

  link();

  this->container_.load(roots_);
  this->container_.load(branchs_);
}

template <typename B>
std::unordered_set<std::string> OntoGraph<B>::getDown(const std::string& value, int depth)
{
  std::unordered_set<std::string> res;

  B* branch = this->container_.find(value);
  if(branch != nullptr)
    getDown(branch, res, depth);

  return res;
}

template <typename B>
std::unordered_set<std::string> OntoGraph<B>::getUp(const std::string& value, int depth)
{
  std::unordered_set<std::string> res;

  B* branch = this->container_.find(value);
  if(branch != nullptr)
    getUp(branch, res, depth);

  return res;
}

template <typename B>
std::unordered_set<uint32_t> OntoGraph<B>::getDownId(const std::string& value, int depth)
{
  std::unordered_set<uint32_t> res;

  B* branch = this->container_.find(value);
  if(branch != nullptr)
    getDownId(branch, res, depth);

  return res;
}

template <typename B>
std::unordered_set<uint32_t> OntoGraph<B>::getUpId(const std::string& value, int depth)
{
  std::unordered_set<uint32_t> res;

  B* branch = this->container_.find(value);
  if(branch != nullptr)
    getUpId(branch, res, depth);

  return res;
}


template <typename B>
std::string OntoGraph<B>::getName(const std::string& value)
{
  std::string res = "";

  B* branch = this->container_.find(value);
  if(branch != nullptr)
  {
    if(branch->dictionary_.find(this->language_) != branch->dictionary_.end())
      if(branch->dictionary_[this->language_].size())
      {
        std::unordered_set<size_t> tested;
        std::random_device rd;
        std::mt19937 gen(rd());

        size_t dic_size = branch->dictionary_[this->language_].size();
        std::uniform_int_distribution<> dis(0, dic_size - 1);

        while(tested.size() < dic_size)
        {
          size_t myIndex = dis(gen);
          std::string word = branch->dictionary_[this->language_][myIndex];
          if(word.find("_") == std::string::npos)
          {
            res = word;
            break;
          }
          tested.insert(myIndex);
        }
        if(res == "")
          res = branch->dictionary_[this->language_][0];
      }
      else
        res = value;
    else
      res = value;
  }

  return res;
}

template <typename B>
bool OntoGraph<B>::touch(const std::string& value)
{
  B* branch = this->container_.find(value);
  if(branch != nullptr)
    return true;
  else
    return false;
}

template <typename B>
void OntoGraph<B>::link()
{
  depth_ = 0;

  uint8_t nb_root_family = roots_.size();
  for(uint8_t root_i = 0; root_i < roots_.size(); root_i++)
  {
    roots_[root_i]->family = 256/(nb_root_family+1) * root_i;
    for(size_t i = 0; i < roots_[root_i]->childs_.size(); i++)
      add_family(roots_[root_i]->childs_[i], roots_[root_i]->family);
  }
}

template <typename B>
void OntoGraph<B>::add_family(B* branch, uint8_t family)
{
  branch->family += family/branch->nb_mothers_;
  for(size_t i = 0; i < branch->childs_.size(); i++)
  {
    depth_++;
    if(depth_ < 20)
      add_family(branch->childs_[i], family/branch->nb_mothers_);
    depth_--;
  }
}

template <typename B>
void OntoGraph<B>::amIA(B** me, std::vector<B*>& vect, const std::string& value, bool erase)
{
  if(*me == nullptr)
    for(size_t i = 0; i < vect.size(); i++)
    {
      if(vect[i]->value() == value)
      {
        *me = vect[i];
        if(erase)
          vect.erase(vect.begin() + i);
        break;
      }
    }
}

template <typename B>
void OntoGraph<B>::isMyMother(B* me, const std::string& mother, std::vector<B*>& vect, bool& find)
{
  if(find)
    return;

  for(size_t i = 0; i < vect.size(); i++)
    if(mother == vect[i]->value())
    {
      vect[i]->childs_.push_back(me);
      me->setSteady_mother(vect[i]);
      find = true;
      break;
    }
}

template <typename B>
void OntoGraph<B>::getDown(B* branch, std::unordered_set<std::string>& res, int depth, unsigned int current_depth)
{
  if(current_depth < (unsigned int)depth)
  {
    size_t size = branch->childs_.size();
    current_depth++;
    for(size_t i = 0; i < size; i++)
      getDown(branch->childs_[i], res, depth, current_depth);
  }

  res.insert(branch->value());
}

template <typename B>
void OntoGraph<B>::getUp(B* branch, std::unordered_set<std::string>& res, int depth, unsigned int current_depth)
{
  if(current_depth < (unsigned int)depth)
  {
    size_t size = branch->mothers_.size();
    current_depth++;
    for(size_t i = 0; i < size; i++)
      getUp(branch->mothers_[i], res, depth, current_depth);
  }

  res.insert(branch->value());
}

template <typename B>
void OntoGraph<B>::getDownId(B* branch, std::unordered_set<uint32_t>& res, int depth, unsigned int current_depth)
{
  if(current_depth < (unsigned int)depth)
  {
    size_t size = branch->childs_.size();
    current_depth++;
    for(size_t i = 0; i < size; i++)
      getDownId(branch->childs_[i], res, depth, current_depth);
  }

  res.insert(branch->get());
}

template <typename B>
void OntoGraph<B>::getUpId(B* branch, std::unordered_set<uint32_t>& res, int depth, unsigned int current_depth)
{
  if(current_depth < (unsigned int)depth)
  {
    size_t size = branch->mothers_.size();
    current_depth++;
    for(size_t i = 0; i < size; i++)
      getUpId(branch->mothers_[i], res, depth, current_depth);
  }

  res.insert(branch->get());
}

template <typename B>
std::unordered_set<B*> OntoGraph<B>::getDownPtr(B* branch)
{
  std::unordered_set<B*> res;
  getDownPtr(branch, res);
  return res;
}

template <typename B>
void OntoGraph<B>::getDownPtr(B* branch, std::unordered_set<B*>& res)
{
  res.insert(branch);
  size_t size = branch->childs_.size();
  for(size_t i = 0; i < size; i++)
    getDownPtr(branch->childs_[i], res);
}

template <typename B>
std::unordered_set<B*> OntoGraph<B>::getUpPtr(B* branch)
{
  std::unordered_set<B*> res;
  getUpPtr(branch, res);
  return res;
}

template <typename B>
void OntoGraph<B>::getUpPtr(B* branch, std::unordered_set<B*>& res)
{
  res.insert(branch);
  size_t size = branch->mothers_.size();
  for(size_t i = 0; i < size; i++)
    getUpPtr(branch->mothers_[i], res);

}

template <typename D>
bool comparator(D* branch, std::string value, std::string lang)
{
  if(branch->dictionary_.find(lang) != branch->dictionary_.end())
    for(size_t i = 0; i < branch->dictionary_[lang].size(); i++)
      if(branch->dictionary_[lang][i] == value)
        return true;
  return false;
}

template <typename B>
std::unordered_set<std::string> OntoGraph<B>::find(const std::string& value)
{
  std::unordered_set<std::string> res;
  std::vector<B*> branch = this->container_.find(&comparator<B>, value, this->language_);
  for(size_t i = 0; i < branch.size(); i++)
    res.insert(branch[i]->value());

  return res;
}

#endif
