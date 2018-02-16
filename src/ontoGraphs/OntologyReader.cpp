#include "ontoloGenius/ontoGraphs/OntologyReader.h"
#include <fstream>
#include "ontoloGenius/utility/error_code.h"
#include "ontoloGenius/ontoGraphs/Ontology.h"

#include "ontoloGenius/utility/utility.h"

OntologyReader::OntologyReader(ClassGraph* p_objTree, PropertyGraph* p_propTree, IndividualGraph* individual_graph)
{
  m_objTree = p_objTree;
  m_propTree = p_propTree;
  individual_graph_ = individual_graph;
  elemLoaded = 0;
}

OntologyReader::OntologyReader(Ontology& onto)
{
  m_objTree = &onto.classes_;
  m_propTree = &onto.properties_;
  individual_graph_ = &onto.individuals_;
  elemLoaded = 0;
}


int OntologyReader::readFromUri(std::string uri, bool individual)
{
  int nb_elem = 0;

  std::string response = "";
  int err = send_request("GET", uri, "", &response);

  if(err == NO_ERROR)
  {
    TiXmlDocument doc;
    doc.Parse((const char*)response.c_str(), 0, TIXML_ENCODING_UTF8);
    TiXmlElement* rdf = doc.FirstChildElement();
    if(individual == false)
      return read(rdf, uri);
    else
      return readIndividual(rdf, uri);
  }
  else
    return REQUEST_ERROR;
}

int OntologyReader::readFromFile(std::string fileName, bool individual)
{
  int nb_elem = 0;

  std::string response = "";
  std::string tmp = "";
  std::ifstream f(fileName);
  while(getline(f,tmp))
  {
    response += tmp;
  }

  TiXmlDocument doc;
  doc.Parse((const char*)response.c_str(), 0, TIXML_ENCODING_UTF8);
  TiXmlElement* rdf = doc.FirstChildElement();
  if(individual == false)
    return read(rdf, fileName);
  else
    return readIndividual(rdf, fileName);
}

int OntologyReader::read(TiXmlElement* rdf, std::string name)
{
  if(rdf == NULL)
  {
      std::cerr << "Failed to load file: No root element."<< std::endl;
      return OTHER;
  }
  else
  {
    std::cout << name << std::endl;
    std::cout << "************************************" << std::endl;
    std::cout << "+ sub       | > domain  | @ language" << std::endl;
    std::cout << "- disjoint  | < range   | " << std::endl;
    std::cout << "/ inverse   | * type    | " << std::endl;
    std::cout << "************************************" << std::endl;
    std::cout << "├── Class" << std::endl;
    for(TiXmlElement* elem = rdf->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
      read_class(elem);
    std::cout << "├── Description" << std::endl;
    for(TiXmlElement* elem = rdf->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
      read_description(elem);
    std::cout << "├── Property" << std::endl;
    for(TiXmlElement* elem = rdf->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
      read_property(elem);

    std::cout << "└── "<< elemLoaded << " readed ! " << std::endl;
    return NO_ERROR;
  }
}

void OntologyReader::displayIndividualRules()
{
  std::cout << "************************************" << std::endl;
  std::cout << "+ sub        | = same" << std::endl;
  std::cout << "^ related    | @ language" << std::endl;
  std::cout << "************************************" << std::endl;
}

int OntologyReader::readIndividual(TiXmlElement* rdf, std::string name)
{
  if(rdf == NULL)
  {
      std::cerr << "Failed to load file: No root element."<< std::endl;
      return OTHER;
  }
  else
  {
    std::cout << name << std::endl;
    std::cout << "├── Individuals" << std::endl;
    for(TiXmlElement* elem = rdf->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
      read_individual(elem);
    std::cout << "├── Description" << std::endl;
    for(TiXmlElement* elem = rdf->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
      read_individual_description(elem);

    std::cout << "└── "<< elemLoaded << " readed ! " << std::endl;
    return NO_ERROR;
  }
}

void OntologyReader::read_class(TiXmlElement* elem)
{
  std::string elemName = elem->Value();
  if(elemName == "owl:Class")
  {
    std::string node_name = "";
    ObjectVectors_t object_vector;
    const char* attr = elem->Attribute("rdf:about");
    if(attr != NULL)
    {
      std::cout << "│   ├──" << get_name(std::string(attr)) << std::endl;
      node_name = get_name(std::string(attr));
      for(TiXmlElement* subElem = elem->FirstChildElement(); subElem != NULL; subElem = subElem->NextSiblingElement())
      {
        std::string subElemName = subElem->Value();

        if(subElemName == "rdfs:subClassOf")
          push(object_vector.mothers_, subElem, "+");
        else if(subElemName == "owl:disjointWith")
          push(object_vector.disjoints_, subElem, "-");
        else if(subElemName == "rdfs:label")
          pushLang(object_vector.dictionary_, subElem);
      }
    }
    m_objTree->add(node_name, object_vector);
    elemLoaded++;
  }
}

void OntologyReader::read_individual(TiXmlElement* elem)
{
  std::string elemName = elem->Value();
  if(elemName == "owl:NamedIndividual")
  {
    std::string node_name = "";
    IndividualVectors_t individual_vector;
    const char* attr = elem->Attribute("rdf:about");
    if(attr != NULL)
    {
      std::cout << "│   ├──" << get_name(std::string(attr)) << std::endl;
      node_name = get_name(std::string(attr));
      for(TiXmlElement* subElem = elem->FirstChildElement(); subElem != NULL; subElem = subElem->NextSiblingElement())
      {
        std::string subElemName = subElem->Value();

        if(subElemName == "rdf:type")
          push(individual_vector.is_a_, subElem, "+");
        else if(subElemName == "owl:sameAs")
          push(individual_vector.same_as_, subElem, "=");
        else
        {
          std::string ns = subElemName.substr(0,subElemName.find(":"));
          if((ns != "owl") && (ns != "rdf") && (ns != "rdfs"))
          {
            std::string property = subElemName.substr(subElemName.find(":")+1);
            push(individual_vector.properties_name_, property, "+");
            push(individual_vector.properties_on_, subElem, "^");
          }
        }
      }
    }
    individual_graph_->add(node_name, individual_vector);
    elemLoaded++;
  }
}

void OntologyReader::read_description(TiXmlElement* elem)
{
  std::string elemName = elem->Value();
  if(elemName == "rdf:Description")
  {
    std::vector<std::string> disjoints;
    bool isDisjointAll = false;
    for(TiXmlElement* subElem = elem->FirstChildElement(); subElem != NULL; subElem = subElem->NextSiblingElement())
    {
      std::string subElemName = subElem->Value();
      const char* subAttr;
      if(subElemName == "rdf:type")
      {
        subAttr = subElem->Attribute("rdf:resource");
        if(subAttr != NULL)
        {
          if(get_name(std::string(subAttr)) == "AllDisjointClasses")
            isDisjointAll = true;
        }
      }
      else if(subElemName == "owl:members")
      {
        subAttr = subElem->Attribute("rdf:parseType");
        if(subAttr != NULL)
        {
          if(std::string(subAttr) == "Collection")
          {
            for(TiXmlElement* subSubElem = subElem->FirstChildElement(); subSubElem != NULL; subSubElem = subSubElem->NextSiblingElement())
            {
              std::string subSubElemName = subSubElem->Value();
              const char* subSubAttr;
              if(subSubElemName == "rdf:Description")
              {
                subSubAttr = subSubElem->Attribute("rdf:about");
                if(subSubAttr != NULL)
                {
                  if(subSubElem == subElem->FirstChildElement())
                    std::cout << "│   ├───┬── -";
                  else if(subSubElem->NextSiblingElement() == NULL)
                    std::cout << "│   │   └── -";
                  else
                    std::cout << "│   │   ├── -";
                  std::cout << get_name(std::string(subSubAttr)) << std::endl;
                  disjoints.push_back(get_name(std::string(subSubAttr)));
                }
              }
            }
          }
        }
      }
    }
    m_objTree->add(disjoints);
    disjoints.clear();
  } // end if(elemName == "rdf:Description")
}

void OntologyReader::read_individual_description(TiXmlElement* elem)
{

}

void OntologyReader::read_property(TiXmlElement* elem)
{
  std::string elemName = elem->Value();
  if(elemName == "owl:ObjectProperty")
  {
    std::string node_name = "";
    PropertyVectors_t propertyVectors;
    const char* attr = elem->Attribute("rdf:about");
    if(attr != NULL)
    {
      std::cout << "│   ├──" << get_name(std::string(attr)) << std::endl;
      node_name = get_name(std::string(attr));
      for(TiXmlElement* subElem = elem->FirstChildElement(); subElem != NULL; subElem = subElem->NextSiblingElement())
      {
        std::string subElemName = subElem->Value();

        if(subElemName == "rdfs:subPropertyOf")
          push(propertyVectors.mothers_, subElem, "+");
        else if(subElemName == "owl:disjointWith")
          push(propertyVectors.disjoints_, subElem, "-");
        else if(subElemName == "owl:inverseOf")
          push(propertyVectors.inverses_, subElem, "/");
        else if(subElemName == "rdfs:domain")
          push(propertyVectors.domains_, subElem, ">");
        else if(subElemName == "rdfs:range")
          push(propertyVectors.ranges_, subElem, "<");
        else if(subElemName == "rdf:type")
          push(propertyVectors.properties_, subElem, "*");
        else if(subElemName == "rdfs:label")
          pushLang(propertyVectors.dictionary_, subElem);
      }
    }

    m_propTree->add(node_name, propertyVectors);
    elemLoaded++;
  }
}

void OntologyReader::push(Properties_t& properties, TiXmlElement* subElem, std::string symbole, std::string attribute)
{
  const char* subAttr;
  subAttr = subElem->Attribute(attribute.c_str());
  if(subAttr != NULL)
  {
    std::string property = get_name(std::string(subAttr));
    if(property == "AsymmetricProperty")
      properties.antisymetric_property_ = true;
    else if(property == "TransitiveProperty")
      properties.transitive_property_ = true;
    else if(property == "FunctionalProperty")
      properties.functional_property_ = true;
    else if(property == "InverseFunctionalProperty")
      properties.inverse_functional_property_ = true;
    else if(property == "IrreflexiveProperty")
      properties.irreflexive_property_ = true;
    else if(property == "ReflexiveProperty")
      properties.reflexive_property_ = true;
    else if(property == "SymmetricProperty")
      properties.symetric_property_ = true;
    else
      property = "";

    if(property != "")
      std::cout << "│   │   ├── " << symbole << property << std::endl;
  }
}

void OntologyReader::pushLang(std::map<std::string, std::string>& dictionary, TiXmlElement* subElem)
{
  const char* subAttr;
  subAttr = subElem->Attribute("xml:lang");
  if(subAttr != NULL)
  {
    std::string lang = get_name(std::string(subAttr));

    const char* value;
    value = subElem->GetText();
    dictionary[lang] = std::string(value);

    if((lang != "") && (value != ""))
      std::cout << "│   │   ├── " << "@" << lang << " : " << dictionary[lang] << std::endl;
  }
}