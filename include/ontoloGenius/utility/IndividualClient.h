#ifndef INDIVIDUALCLIENT_H
#define INDIVIDUALCLIENT_H

#include "ontoloGenius/utility/ClientBase.h"

class IndividualClient : public ClientBase
{
public:
  IndividualClient(ros::NodeHandle* n) : ClientBase(n, "individual")
  {
  }

  std::vector<std::string> getOn(const std::string& name, const std::string& property);
  std::vector<std::string> getFrom(const std::string& property, const std::string& name, const std::string& selector = "");
  std::vector<std::string> getWith(const std::string& indiv_1, const std::string& indiv_2, const std::string& selector = "");
  std::vector<std::string> getDown(std::string& name);
  std::vector<std::string> getRelatedFrom(const std::string& name);
  std::vector<std::string> getType(const std::string& name);

private:

};

#endif
