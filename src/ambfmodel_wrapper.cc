#include <fstream>
#include <QFileInfo>
#include <QDir>
#include "ambfmodel_wrapper.h"
#include "util.h"

AMBFModelWrapper::AMBFModelWrapper() : RBDLModelWrapper()  {
	model_type = MODELTYPE_AMBF;
};

QString pathAppend(const QString& path1, const QString& path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}

void AMBFModelWrapper::load(QString model_file) 
{
	
    this->model_file = model_file;
	auto model_file_info = QFileInfo(model_file);
    rbdl_model = new RigidBodyDynamics::Model();
	auto last_pwd = QDir::currentPath();
	auto model_pwd = model_file_info.absoluteDir().absolutePath();
	QDir::setCurrent(model_pwd);
    std::ifstream model_file_stream(model_file.toStdString().c_str());
	model_file_stream.seekg(0, std::ios::end);
	model_xml_string.reserve(model_file_stream.tellg());
	model_file_stream.seekg(0, std::ios::beg);
	model_xml_string.assign((std::istreambuf_iterator<char>(model_file_stream)),
	                         std::istreambuf_iterator<char>());
	model_file_stream.close();
	std::string mesh_path; 

	
    try {
        BuildRBDLModel model( model_file.toStdString().c_str());
		mesh_path = model.getMeshPath();
		QString Qmesh_path =  QString::fromStdString(mesh_path);
		QString incorrectPath = QDir{model_pwd}.filePath(Qmesh_path);
		//std::cout << "incorrect path:" << incorrectPath;
		QString correctPath = QFileInfo{incorrectPath}.absoluteFilePath(); // removes the .
		std::cout << "correct path: " << correctPath.toStdString().c_str() << "\n";
		QDir::setCurrent(correctPath);
		//load relevant information from modelfile
		auto model_info = loadModelInfo(model);
		auto segments_info = loadSegmentInfo(model);
		//construct model from that info
		build3DEntity(model_info, segments_info);
		//return to original pwdmake
		

	} catch (std::exception& e) {
		std::ostringstream error_msg;
		
		error_msg <<model_file.toStdString().c_str() << "Error parsing AMBF file!\n" << e.what();
		throw RigidBodyDynamics::Errors::RBDLFileParseError(error_msg.str());
	}

}



ModelInfo AMBFModelWrapper::loadModelInfo(BuildRBDLModel &model) {
	QMatrix4x4 orientation(
		0., 1., 0., 0.,
		0., 0., 1., 0.,
		1., 0., 0., 0.,
		0., 0., 0., 1.
	);
	ModelInfo info = {
	                   orientation,
	                   1.
	                 };
	return info;
}


std::vector<SegmentVisualInfo> AMBFModelWrapper::loadSegmentInfo(BuildRBDLModel &model) {
	std::vector<SegmentVisualInfo> info;
	std::string path = model.getMeshPath();
	std::unordered_map<std::string, std::string> mesh_map;
	std::unordered_map<std::string, bodyParamPtr> bodies = model.getRBDLBodyToObjectMap();

	for ( auto link = bodies.begin(); link != bodies.end(); link++ ) 
	{
		//Get the data on the segment
		std::string segment_name = link->first;
		bodyParamPtr l = link->second;
		std::string mesh_name = l->MeshName();
		Vector3d location = l->Position();
		Vector3d orentation = l->Orientation();

		//Start building the segment data
		QString mesh_dir = findFile(mesh_name, true);
		//NEED TO UPDATE WITH THE MODEL PARAMS FROM FILE
		Vector3d mesh_translate(0., 0., 0.);
		float angle = 0.f;
		Vector3d axis = Vector3d(1., 0., 0.);
		QQuaternion mesh_rotation = QQuaternion::fromAxisAndAngle(QVector3D(axis[0], axis[1], axis[2]), angle);
		Vector3d visual_scale(1., 1., 1.);
		Vector3d visual_dimensions(1., 1., 1.);
		Vector3d visual_center(0., 0., 0.);

		Vector3d visual_color_rgb(1., 1., 1.);
		float visual_alpha = 1.0;
		QColor visual_color = QColor::fromRgbF(visual_color_rgb[0], visual_color_rgb[1], visual_color_rgb[2], visual_alpha);

		SegmentVisualInfo si = {
								segment_name,
								mesh_dir,
								to_qt_vector(mesh_translate),
								mesh_rotation,
								visual_color,
								to_qt_vector(visual_center),
								QVector3D(visual_dimensions[0] * visual_scale[0], visual_dimensions[1] * visual_scale[1], visual_dimensions[2] * visual_scale[2])
			                    };
		info.push_back(std::move(si));
	}
}