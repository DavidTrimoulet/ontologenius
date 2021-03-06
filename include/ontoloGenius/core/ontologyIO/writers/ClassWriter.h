#ifndef CLASSWRITER_H
#define CLASSWRITER_H

#include "ontoloGenius/core/ontologyIO/writers/NodeWriter.h"

#include <string>
#include <vector>

class ClassGraph;
class ClassBranch_t;

class ClassWriter : private NodeWriter
{
public:
  ClassWriter(ClassGraph* class_graph) {class_graph_ = class_graph; };
  ~ClassWriter() {};

  void write(FILE* file);
  void writeGeneralAxioms(FILE* file);

private:
  ClassGraph* class_graph_;

  void writeClass(ClassBranch_t* branch);
  void writeSubClassOf(ClassBranch_t* branch);
  void writeDisjointWith(ClassBranch_t* branch);
  void writeDisjointWith(std::vector<ClassBranch_t*>& classes);
  void getDisjoints(ClassBranch_t* class_branch, std::vector<std::string>& disjoints_current);
  void removeDifferents(std::vector<std::string>& disjoints_current, std::vector<std::string>& disjoints_class);
};

#endif
