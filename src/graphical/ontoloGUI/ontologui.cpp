#include "include/ontoloGenius/graphical/ontoloGUI/ontologui.h"
#include "include/ontoloGenius/graphical/ontoloGUI/qpushbuttonextended.h"
#include "ui_ontologui.h"

#include "ontologenius/OntologeniusService.h"

ontoloGUI::ontoloGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ontoloGUI)
{
    ui->setupUi(this);

    QObject::connect(ui->Class_getName, SIGNAL(hoverEnter()),this, SLOT(ClasshoverEnterSlot()));
    QObject::connect(ui->Class_getName, SIGNAL(hoverLeave()),this, SLOT(ClasshoverLeaveSlot()));
    QObject::connect(ui->Class_find, SIGNAL(hoverEnter()),this, SLOT(ClasshoverEnterSlot()));
    QObject::connect(ui->Class_find, SIGNAL(hoverLeave()),this, SLOT(ClasshoverLeaveSlot()));
    QObject::connect(ui->Class_getUp, SIGNAL(hoverEnter()),this, SLOT(ClasshoverEnterSlot()));
    QObject::connect(ui->Class_getUp, SIGNAL(hoverLeave()),this, SLOT(ClasshoverLeaveSlot()));
    QObject::connect(ui->Class_getDown, SIGNAL(hoverEnter()),this, SLOT(ClasshoverEnterSlot()));
    QObject::connect(ui->Class_getDown, SIGNAL(hoverLeave()),this, SLOT(ClasshoverLeaveSlot()));
    QObject::connect(ui->Class_getDisjoint, SIGNAL(hoverEnter()),this, SLOT(ClasshoverEnterSlot()));
    QObject::connect(ui->Class_getDisjoint, SIGNAL(hoverLeave()),this, SLOT(ClasshoverLeaveSlot()));

    QObject::connect(ui->ObjectProperty_getName, SIGNAL(hoverEnter()),this, SLOT(objectPropertyhoverEnterSlot()));
    QObject::connect(ui->ObjectProperty_getName, SIGNAL(hoverLeave()),this, SLOT(objectPropertyhoverLeaveSlot()));
    QObject::connect(ui->ObjectProperty_find, SIGNAL(hoverEnter()),this, SLOT(objectPropertyhoverEnterSlot()));
    QObject::connect(ui->ObjectProperty_find, SIGNAL(hoverLeave()),this, SLOT(objectPropertyhoverLeaveSlot()));
    QObject::connect(ui->ObjectProperty_getDisjoint, SIGNAL(hoverEnter()),this, SLOT(objectPropertyhoverEnterSlot()));
    QObject::connect(ui->ObjectProperty_getDisjoint, SIGNAL(hoverLeave()),this, SLOT(objectPropertyhoverLeaveSlot()));
    QObject::connect(ui->ObjectProperty_getDomain, SIGNAL(hoverEnter()),this, SLOT(objectPropertyhoverEnterSlot()));
    QObject::connect(ui->ObjectProperty_getDomain, SIGNAL(hoverLeave()),this, SLOT(objectPropertyhoverLeaveSlot()));
    QObject::connect(ui->ObjectProperty_getDown, SIGNAL(hoverEnter()),this, SLOT(objectPropertyhoverEnterSlot()));
    QObject::connect(ui->ObjectProperty_getDown, SIGNAL(hoverLeave()),this, SLOT(objectPropertyhoverLeaveSlot()));
    QObject::connect(ui->ObjectProperty_getInverse, SIGNAL(hoverEnter()),this, SLOT(objectPropertyhoverEnterSlot()));
    QObject::connect(ui->ObjectProperty_getInverse, SIGNAL(hoverLeave()),this, SLOT(objectPropertyhoverLeaveSlot()));
    QObject::connect(ui->ObjectProperty_getRange, SIGNAL(hoverEnter()),this, SLOT(objectPropertyhoverEnterSlot()));
    QObject::connect(ui->ObjectProperty_getRange, SIGNAL(hoverLeave()),this, SLOT(objectPropertyhoverLeaveSlot()));
    QObject::connect(ui->ObjectProperty_getUp, SIGNAL(hoverEnter()),this, SLOT(objectPropertyhoverEnterSlot()));
    QObject::connect(ui->ObjectProperty_getUp, SIGNAL(hoverLeave()),this, SLOT(objectPropertyhoverLeaveSlot()));

    QObject::connect(ui->DataProperty_getName, SIGNAL(hoverEnter()),this, SLOT(dataPropertyhoverEnterSlot()));
    QObject::connect(ui->DataProperty_getName, SIGNAL(hoverLeave()),this, SLOT(dataPropertyhoverLeaveSlot()));
    QObject::connect(ui->DataProperty_find, SIGNAL(hoverEnter()),this, SLOT(dataPropertyhoverEnterSlot()));
    QObject::connect(ui->DataProperty_find, SIGNAL(hoverLeave()),this, SLOT(dataPropertyhoverLeaveSlot()));
    QObject::connect(ui->DataProperty_getDisjoint, SIGNAL(hoverEnter()),this, SLOT(dataPropertyhoverEnterSlot()));
    QObject::connect(ui->DataProperty_getDisjoint, SIGNAL(hoverLeave()),this, SLOT(dataPropertyhoverLeaveSlot()));
    QObject::connect(ui->DataProperty_getDomain, SIGNAL(hoverEnter()),this, SLOT(dataPropertyhoverEnterSlot()));
    QObject::connect(ui->DataProperty_getDomain, SIGNAL(hoverLeave()),this, SLOT(dataPropertyhoverLeaveSlot()));
    QObject::connect(ui->DataProperty_getDown, SIGNAL(hoverEnter()),this, SLOT(dataPropertyhoverEnterSlot()));
    QObject::connect(ui->DataProperty_getDown, SIGNAL(hoverLeave()),this, SLOT(dataPropertyhoverLeaveSlot()));
    QObject::connect(ui->DataProperty_getRange, SIGNAL(hoverEnter()),this, SLOT(dataPropertyhoverEnterSlot()));
    QObject::connect(ui->DataProperty_getRange, SIGNAL(hoverLeave()),this, SLOT(dataPropertyhoverLeaveSlot()));
    QObject::connect(ui->DataProperty_getUp, SIGNAL(hoverEnter()),this, SLOT(dataPropertyhoverEnterSlot()));
    QObject::connect(ui->DataProperty_getUp, SIGNAL(hoverLeave()),this, SLOT(dataPropertyhoverLeaveSlot()));

    QObject::connect(ui->Individual_getDistinct, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getDistinct, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getRelatedFrom, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getRelatedFrom, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getRelatedOn, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getRelatedOn, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getRelatedWith, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getRelatedWith, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getRelationFrom, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getRelationFrom, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getRelationOn, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getRelationOn, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getRelationWith, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getRelationWith, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getSame, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getSame, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getUp, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getUp, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getOn, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getOn, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getFrom, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getFrom, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getWith, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getWith, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getName, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getName, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_find, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_find, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_getType, SIGNAL(hoverEnter()),this, SLOT(IndividualhoverEnterSlot()));
    QObject::connect(ui->Individual_getType, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));
    QObject::connect(ui->Individual_select, SIGNAL(hoverEnter()),this, SLOT(IndividualCheckBoxhoverEnterSlot()));
    QObject::connect(ui->Individual_select, SIGNAL(hoverLeave()),this, SLOT(IndividualhoverLeaveSlot()));

    QObject::connect(ui->Class_getName, SIGNAL(clicked()),this, SLOT(classClickedSlot()));
    QObject::connect(ui->Class_find, SIGNAL(clicked()),this, SLOT(classClickedSlot()));
    QObject::connect(ui->Class_getUp, SIGNAL(clicked()),this, SLOT(classClickedSlot()));
    QObject::connect(ui->Class_getDown, SIGNAL(clicked()),this, SLOT(classClickedSlot()));
    QObject::connect(ui->Class_getDisjoint, SIGNAL(clicked()),this, SLOT(classClickedSlot()));

    QObject::connect(ui->ObjectProperty_getName, SIGNAL(clicked()),this, SLOT(objectPropertyClickedSlot()));
    QObject::connect(ui->ObjectProperty_find, SIGNAL(clicked()),this, SLOT(objectPropertyClickedSlot()));
    QObject::connect(ui->ObjectProperty_getDisjoint, SIGNAL(clicked()),this, SLOT(objectPropertyClickedSlot()));
    QObject::connect(ui->ObjectProperty_getDomain, SIGNAL(clicked()),this, SLOT(objectPropertyClickedSlot()));
    QObject::connect(ui->ObjectProperty_getDown, SIGNAL(clicked()),this, SLOT(objectPropertyClickedSlot()));
    QObject::connect(ui->ObjectProperty_getInverse, SIGNAL(clicked()),this, SLOT(objectPropertyClickedSlot()));
    QObject::connect(ui->ObjectProperty_getRange, SIGNAL(clicked()),this, SLOT(objectPropertyClickedSlot()));
    QObject::connect(ui->ObjectProperty_getUp, SIGNAL(clicked()),this, SLOT(objectPropertyClickedSlot()));

    QObject::connect(ui->DataProperty_getName, SIGNAL(clicked()),this, SLOT(dataPropertyClickedSlot()));
    QObject::connect(ui->DataProperty_find, SIGNAL(clicked()),this, SLOT(dataPropertyClickedSlot()));
    QObject::connect(ui->DataProperty_getDisjoint, SIGNAL(clicked()),this, SLOT(dataPropertyClickedSlot()));
    QObject::connect(ui->DataProperty_getDomain, SIGNAL(clicked()),this, SLOT(dataPropertyClickedSlot()));
    QObject::connect(ui->DataProperty_getDown, SIGNAL(clicked()),this, SLOT(dataPropertyClickedSlot()));
    QObject::connect(ui->DataProperty_getRange, SIGNAL(clicked()),this, SLOT(dataPropertyClickedSlot()));
    QObject::connect(ui->DataProperty_getUp, SIGNAL(clicked()),this, SLOT(dataPropertyClickedSlot()));

    QObject::connect(ui->Individual_getDistinct, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getRelatedFrom, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getRelatedOn, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getRelatedWith, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getRelationFrom, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getRelationOn, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getRelationWith, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getSame, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getUp, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getOn, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getFrom, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getWith, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getName, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_find, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));
    QObject::connect(ui->Individual_getType, SIGNAL(clicked()),this, SLOT(individualClickedSlot()));

    QObject::connect(ui->CloseButton, SIGNAL(clicked()),this, SLOT(closeOntologySlot()));
}

ontoloGUI::~ontoloGUI()
{
    delete ui;
}

void ontoloGUI::wait()
{
  QString html = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                  "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                  "p, li { white-space: pre-wrap; }"
                  "</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">"
                  "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#a40000;\">Wainting for </span><span style=\" font-size:12pt; font-weight:600; color:#a40000;\">ontoloGenius</span></p></body></html>";
  ui->InfoArea->setHtml(html);
  ros::service::waitForService("ontologenius/arguer", -1);
}

void ontoloGUI::start()
{
  QString html = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                  "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                  "p, li { white-space: pre-wrap; }"
                  "</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">"
                  "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:#4e9a06;\">OntoloGenius</span><span style=\" font-size:12pt; color:#4e9a06;\"> detected</span></p></body></html>";
  ui->InfoArea->setHtml(html);
}

void ontoloGUI::ClasshoverEnterSlot()
{
  ui->ClassDescription->setText(((QPushButtonExtended*)sender())->whatsThis());
}

void ontoloGUI::ClasshoverLeaveSlot()
{
  ui->ClassDescription->setText("");
}

void ontoloGUI::objectPropertyhoverEnterSlot()
{
  ui->ObjectPropertyDescription->setText(((QPushButtonExtended*)sender())->whatsThis());
}

void ontoloGUI::objectPropertyhoverLeaveSlot()
{
  ui->ObjectPropertyDescription->setText("");
}

void ontoloGUI::dataPropertyhoverEnterSlot()
{
  ui->DataPropertyDescription->setText(((QPushButtonExtended*)sender())->whatsThis());
}

void ontoloGUI::dataPropertyhoverLeaveSlot()
{
  ui->DataPropertyDescription->setText("");
}

void ontoloGUI::IndividualCheckBoxhoverEnterSlot()
{
  ui->IndividualDescription->setText(((QCheckBoxExtended*)sender())->whatsThis());
}

void ontoloGUI::IndividualhoverEnterSlot()
{
  ui->IndividualDescription->setText(((QPushButtonExtended*)sender())->whatsThis());
}

void ontoloGUI::IndividualhoverLeaveSlot()
{
  ui->IndividualDescription->setText("");
}

void ontoloGUI::classClickedSlot()
{
  ros::ServiceClient client = n_->serviceClient<ontologenius::OntologeniusService>("ontologenius/class");

  ontologenius::OntologeniusService srv;
  srv.request.action = ((QPushButtonExtended*)sender())->text().toStdString();
  srv.request.param = ui->classParameter->text().toStdString();
  QString text = ((QPushButtonExtended*)sender())->text() + " : " + ui->classParameter->text();
  ui->ClassDescription->setText(text);

  if(!client.call(srv))
    displayErrorInfo("ontologenius/class client call failed");
  else
  {
    std::string res = vector2string(srv.response.values);
    ui->ResultArea->setText(QString::fromStdString(res));
    if(srv.response.code == 3)
      displayUnClosed();
  }
}

void ontoloGUI::objectPropertyClickedSlot()
{
  ros::ServiceClient client = n_->serviceClient<ontologenius::OntologeniusService>("ontologenius/object_property");

  ontologenius::OntologeniusService srv;
  srv.request.action = ((QPushButtonExtended*)sender())->text().toStdString();
  srv.request.param = ui->objectPropertyParameter->text().toStdString();
  QString text = ((QPushButtonExtended*)sender())->text() + " : " + ui->objectPropertyParameter->text();
  ui->ObjectPropertyDescription->setText(text);

  if(!client.call(srv))
    displayErrorInfo("ontologenius/object_property client call failed");
  else
  {
    std::string res = vector2string(srv.response.values);
    ui->ResultArea->setText(QString::fromStdString(res));
    if(srv.response.code == 3)
      displayUnClosed();
  }
}

void ontoloGUI::dataPropertyClickedSlot()
{
  ros::ServiceClient client = n_->serviceClient<ontologenius::OntologeniusService>("ontologenius/data_property");

  ontologenius::OntologeniusService srv;
  srv.request.action = ((QPushButtonExtended*)sender())->text().toStdString();
  srv.request.param = ui->dataPropertyParameter->text().toStdString();
  QString text = ((QPushButtonExtended*)sender())->text() + " : " + ui->dataPropertyParameter->text();
  ui->DataPropertyDescription->setText(text);

  if(!client.call(srv))
    displayErrorInfo("ontologenius/data_property client call failed");
  else
  {
    std::string res = vector2string(srv.response.values);
    ui->ResultArea->setText(QString::fromStdString(res));
    if(srv.response.code == 3)
      displayUnClosed();
  }
}

void ontoloGUI::individualClickedSlot()
{
  ros::ServiceClient client = n_->serviceClient<ontologenius::OntologeniusService>("ontologenius/individual");

  ontologenius::OntologeniusService srv;
  if(ui->Individual_select->checkState() == 0)
    srv.request.action = ((QPushButtonExtended*)sender())->text().toStdString();
  else
    srv.request.action = "select:" + ((QPushButtonExtended*)sender())->text().toStdString();
  srv.request.param = ui->individualParameter->text().toStdString();
  QString text = ((QPushButtonExtended*)sender())->text() + " : " + ui->individualParameter->text();
  ui->IndividualDescription->setText(text);

  if(!client.call(srv))
    displayErrorInfo("ontologenius/individual client call failed");
  else
  {
    std::string res = vector2string(srv.response.values);
    ui->ResultArea->setText(QString::fromStdString(res));
    if(srv.response.code == 3)
      displayUnClosed();
  }
}

void ontoloGUI::closeOntologySlot()
{
  ros::ServiceClient client = n_->serviceClient<ontologenius::OntologeniusService>("ontologenius/actions");

  ontologenius::OntologeniusService srv;
  srv.request.action = "close";

  if(!client.call(srv))
    displayErrorInfo("ontologenius/actions client call failed");
  else
  {
    std::string res = vector2string(srv.response.values);
    ui->ResultArea->setText(QString::fromStdString(res));
    start();
  }
}

void ontoloGUI::ArguerClickedSlot(int)
{
  ros::ServiceClient client = n_->serviceClient<ontologenius::OntologeniusService>("ontologenius/arguer");

  ontologenius::OntologeniusService srv;
  if(((QCheckBoxExtended*)sender())->isChecked())
    srv.request.action = "activate";
  else
    srv.request.action = "deactivate";
  srv.request.param = ((QCheckBoxExtended*)sender())->text().toStdString();

  if(!client.call(srv))
    displayErrorInfo("ontologenius/arguer client call failed");
  else
  {
    std::string res = vector2string(srv.response.values);
    ui->ResultArea->setText(QString::fromStdString(res));
  }
}

void ontoloGUI::ArguerhoverEnterSlot()
{
  size_t index = getArguerIndex((QCheckBoxExtended*)sender());
  ui->ArguerDescription->setText(QString::fromStdString(arguers_description_[index]));
}

void ontoloGUI::ArguerhoverLeaveSlot()
{
  ui->ArguerDescription->setText("");
}

void ontoloGUI::displayUnClosed()
{
  QString html = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                  "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                  "p, li { white-space: pre-wrap; }"
                  "</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">"
                  "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#a40000;\">Ontology is not </span><span style=\" font-size:12pt; font-weight:600; color:#a40000;\">closed</span></p></body></html>";
  ui->InfoArea->setHtml(html);
}

void ontoloGUI::loadArguers()
{
  ros::ServiceClient client = n_->serviceClient<ontologenius::OntologeniusService>("ontologenius/arguer");

  ontologenius::OntologeniusService srv;
  srv.request.action = "list";

  if(!client.call(srv))
    displayErrorInfo("ontologenius/arguer client call failed");
  else
  {
    arguers_names_ = srv.response.values;
    ui->ResultArea->setText("");

    constructArguersCheckBoxs();
  }
}

void ontoloGUI::constructArguersCheckBoxs()
{
  for(size_t i = 0; i < arguers_names_.size(); i++)
  {
    arguers_description_.push_back(getArguerDescription(arguers_names_[i]));
    QCheckBoxExtended* box = new QCheckBoxExtended(QString::fromStdString(arguers_names_[i]), this);
    ui->ArguerListLayout->addWidget(box);
    QObject::connect(box, SIGNAL(stateChanged(int)),this, SLOT(ArguerClickedSlot(int)));
    QObject::connect(box, SIGNAL(hoverEnter()),this, SLOT(ArguerhoverEnterSlot()));
    QObject::connect(box, SIGNAL(hoverLeave()),this, SLOT(ArguerhoverLeaveSlot()));
  }
}

size_t ontoloGUI::getArguerIndex(QCheckBoxExtended* box)
{
  size_t index =0;
  for(size_t i = 0; i < arguers_names_.size(); i++)
    if(arguers_names_[i] == box->text().toStdString())
    {
      index = i;
      break;
    }
  return index;
}

std::string ontoloGUI::getArguerDescription(std::string box)
{
  ros::ServiceClient client = n_->serviceClient<ontologenius::OntologeniusService>("ontologenius/arguer");

  ontologenius::OntologeniusService srv;
  srv.request.action = "getDescription";
  srv.request.param = box;

  if(!client.call(srv))
    displayErrorInfo("ontologenius/arguer client call failed");
  else
    return vector2string(srv.response.values);

  return "";
}

void ontoloGUI::displayErrorInfo(std::string text)
{
  std::string html = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                  "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                  "p, li { white-space: pre-wrap; }"
                  "</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">"
                  "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#a40000;\">" + text + "</span></p></body></html>";
  ui->InfoArea->setHtml(QString::fromStdString(html));
}

std::string ontoloGUI::vector2string(std::vector<std::string> vect)
{
  std::string res;
  for(size_t i = 0; i < vect.size(); i++)
    res += vect[i] + "\n";
  return res;
}
