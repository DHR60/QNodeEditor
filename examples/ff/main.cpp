#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>

#include <nodes/DataModelRegistry>

#include "ExpressionSourceModel.hpp"
#include "ExpressionConstantModel.hpp"
#include "ExpressionStepRangeModel.hpp"
#include "ExpressionDisplayModel.hpp"
#include "MathFunctionModel.hpp"
#include "BoolConditionModel.hpp"
#include "BoolFunctionModel.hpp"
#include "IfConditionModel.hpp"
#include "PlotModel.hpp"
#include "IntervalConditionModel.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;

static std::shared_ptr<DataModelRegistry>
registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();
  ret->registerModel<ExpressionSourceModel>("IO");
  ret->registerModel<ExpressionConstantModel>("IO");
  ret->registerModel<ExpressionStepRangeModel>("IO");
  ret->registerModel<ExpressionDisplayModel>("IO");
  ret->registerModel<PlotModel>("IO");

  ret->registerModel<MathFunctionModel>("Operations");
  ret->registerModel<BoolConditionModel>("Operations");
  ret->registerModel<BoolFunctionModel>("Operations");
  ret->registerModel<IfConditionModel>("Operations");
  ret->registerModel<IntervalConditionModel>("Operations");

  return ret;
}


static
void
setStyle()
{
  ConnectionStyle::setConnectionStyle(
  R"(
  {
    "ConnectionStyle": {
      "ConstructionColor": "gray",
      "NormalColor": "black",
      "SelectedColor": "gray",
      "SelectedHaloColor": "deepskyblue",
      "HoveredColor": "deepskyblue",

      "LineWidth": 3.0,
      "ConstructionLineWidth": 2.0,
      "PointDiameter": 10.0,

      "UseDataDefinedColors": true
    }
  }
  )");
}


int
main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  setStyle();

  QWidget mainWidget;

  auto menuBar    = new QMenuBar();
  auto saveAction = menuBar->addAction("Save..");
  auto loadAction = menuBar->addAction("Load..");

  QVBoxLayout *l = new QVBoxLayout(&mainWidget);

  l->addWidget(menuBar);
  auto scene = new FlowScene(registerDataModels());
  l->addWidget(new FlowView(scene));
  l->setContentsMargins(0, 0, 0, 0);
  l->setSpacing(0);

  QObject::connect(saveAction, &QAction::triggered,
                   scene, &FlowScene::save);

  QObject::connect(loadAction, &QAction::triggered,
                   scene, &FlowScene::load);

  mainWidget.setWindowTitle("Field Function constructor");
  mainWidget.resize(800, 600);
  mainWidget.showNormal();

  return app.exec();
}
