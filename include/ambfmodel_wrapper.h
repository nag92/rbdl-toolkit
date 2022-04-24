#ifndef AMBFMODEL_WRAPPER_H_INCLUDED
#define AMBFMODEL_WRAPPER_H_INCLUDED

#include <rbdl/rbdl.h>
#include <rbdl/rbdl_math.h>
#include "BuildRBDLModel.h"
#include "rbdl_wrapper.h"

#define MODELTYPE_AMBF "ambf_model"

class TOOLKIT_DLLAPI AMBFModelWrapper : public RBDLModelWrapper {
	public:
		AMBFModelWrapper();

		std::string model_xml_string;

		void load(QString model_file);
		ModelInfo loadModelInfo();
		std::vector<SegmentVisualInfo> loadSegmentInfo();
};


#endif 

