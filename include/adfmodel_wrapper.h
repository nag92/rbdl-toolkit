#ifndef AMBFMODEL_WRAPPER_H_INCLUDED
#define AMBFMODEL_WRAPPER_H_INCLUDED

#include <rbdl/rbdl.h>
#include <rbdl/rbdl_math.h>
#include <rbdl_model/BuildRBDLModel.h>
#include "rbdl_wrapper.h"
#include <unordered_map>

#define MODELTYPE_ADF "adf_model"

class TOOLKIT_DLLAPI ADFModelWrapper : public RBDLModelWrapper {
	public:
		ADFModelWrapper();
		std::string model_xml_string;
		void load(QString model_file);
		ModelInfo loadModelInfo(BuildRBDLModel&);
		std::vector<SegmentVisualInfo> loadSegmentInfo(BuildRBDLModel&);
};


#endif 

