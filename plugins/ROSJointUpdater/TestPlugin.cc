#include "TestPlugin.h"
#include <iostream>
#include <clocale>

#include <QFileDialog>
#include <QMessageBox>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <Qt3DExtras>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>

#include <parser.hpp>
#include <toolkit_errors.h>
#include <rbdl_wrapper.h>



using namespace RigidBodyDynamics::Math;

TestPlugin::TestPlugin() {
	parentApp = NULL;
}

TestPlugin::~TestPlugin() {
}

void TestPlugin::init(ToolkitApp* app) {
	//save reference to parent ToolkitApp 
	parentApp = app;

	load_file_trigger = new QAction("Load Motion Markers");
	parentApp->addFileAction(load_file_trigger);

	connect(load_file_trigger, SIGNAL(triggered(bool)), this, SLOT(action_load_data()));

	

	//display model markers of all loaded models
	auto all_models = parentApp->getLoadedModels();
	for (auto model : *all_models) {
		addModelMarkersToModel(model);
	}

	connect(parentApp, SIGNAL(model_loaded(RBDLModelWrapper*)), this, SLOT(addModelMarkersToModel(RBDLModelWrapper*)));
	connect(parentApp, &ToolkitApp::reloaded_model, this, &TestPlugin::reload);
}


void TestPlugin::addModelMarkersToModel(RBDLModelWrapper *rbdl_model) {
	if (rbdl_model->getModelType() == MODELTYPE_LUA) {
		LuaModelWrapper *model = (LuaModelWrapper*)rbdl_model;
		unsigned int segment_cnt = model->model_luatable["frames"].length();
		for(int i=1; i<=segment_cnt; i++) {
			std::string segment_name = model->model_luatable["frames"][i]["name"].get<std::string>();
			std::vector<LuaKey> keys= model->model_luatable["frames"][i]["markers"].keys();

			for (auto marker_name : keys) {
				Vector3d marker_position = model->model_luatable["frames"][i]["markers"][marker_name.string_value.c_str()].getDefault(Vector3d(0.,0.,0.));
				//marker_position = model->axis_transform * marker_position;

			}
		}
	} else {
		parentApp->showWarningDialog("Loading model markes from this model type is not supported.");
	}
}


void TestPlugin::reload(RBDLModelWrapper* model) 
{
	
}
