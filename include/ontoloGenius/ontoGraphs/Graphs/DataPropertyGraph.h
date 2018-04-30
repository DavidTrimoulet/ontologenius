#include <string>
#include <vector>
#include <set>
#include <map>
#include <stdint.h>

#include "ontoloGenius/ontoGraphs/Graphs/OntoGraph.h"
#include "ontoloGenius/ontoGraphs/Graphs/ClassGraph.h"
#include "ontoloGenius/ontoGraphs/Graphs/ObjectPropertyGraph.h"

#ifndef DATAPROPERTYGRAPH_H
#define DATAPROPERTYGRAPH_H

struct DataPropertyBranch_t;

class DataPropertyBranch_t : public Branch_t<DataPropertyBranch_t>
{
public:
  std::vector<DataPropertyBranch_t*> disjoints_;
  std::vector<ClassBranch_t*> domains_;
  std::vector<std::string> ranges_;
  Properties_t properties_;

  DataPropertyBranch_t(std::string value) : Branch_t(value) {};
};

struct DataPropertyVectors_t
{
   std::vector<std::string> mothers_;
   std::vector<std::string> disjoints_;
   std::vector<std::string> domains_;
   std::vector<std::string> ranges_;
   Properties_t properties_;
   std::map<std::string, std::string> dictionary_;
};

class GraphDrawer;
class IndividualGraph;

class DataPropertyGraph : public OntoGraph<DataPropertyBranch_t>
{
  friend GraphDrawer;
  friend IndividualGraph;
public:
  DataPropertyGraph(ClassGraph* class_graph) {class_graph_ = class_graph; }
  ~DataPropertyGraph() {}

  void add(std::string value, DataPropertyVectors_t& property_vectors);
  void add(std::vector<std::string>& disjoints);

  std::set<std::string> getDisjoint(std::string& value);
  std::set<std::string> getDomain(std::string& value);
  std::set<std::string> getRange(std::string& value);
  std::set<std::string> select(std::set<std::string> on, std::string selector);

private:
  ClassGraph* class_graph_;

  void isMyDisjoint(DataPropertyBranch_t* me, std::string disjoint, std::vector<DataPropertyBranch_t*>& vect, bool& find, bool all = true)
  {
    if(find)
      return;

    for(unsigned int i = 0; i < vect.size(); i++)
      if(disjoint == vect[i]->value_)
      {
        me->disjoints_.push_back(vect[i]);
        if(all)
          vect[i]->disjoints_.push_back(me);
        find = true;
        break;
      }
  }

  void isMyDomain(DataPropertyBranch_t* me, std::string domain, std::vector<ClassBranch_t*>& vect, bool& find)
  {
    if(find)
      return;

    for(unsigned int i = 0; i < vect.size(); i++)
      if(domain == vect[i]->value_)
      {
        me->domains_.push_back(vect[i]);
        find = true;
        break;
      }
  }
};

#endif /* DATAPROPERTYGRAPH_H */