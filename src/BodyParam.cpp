#include "BodyParam.h"

BodyParam::BodyParam(YAML::Node bodyNode)
{
    // Declare all the yaml parameters that we want to look for
    Utilities utilities;

    YAML::Node name = bodyNode["name"];
    if(!name.IsDefined()) utilities.throwExceptionMessage("name in Body Params");
    name_ = utilities.trimTrailingSpaces(name);

    YAML::Node mass = bodyNode["mass"];
    if(!mass.IsDefined()) utilities.throwExceptionMessage("mass in Body Params");
    mass_ = mass.as<double>();
    if(mass_ == 0.0) mass_ = 0.0000001;

    YAML::Node inertia = bodyNode["inertia"];
    if(!inertia.IsDefined()) utilities.throwExceptionMessage("inertia in Body Params");
    inertia_ = utilities.vectorToMatrix3d(&inertia);

    YAML::Node inertial_offset = bodyNode["inertial offset"];
    if(!inertial_offset.IsDefined()) utilities.throwExceptionMessage("inertia offset in Body Params");

    YAML::Node inertial_offset_position = inertial_offset["position"];
    if(!inertial_offset_position.IsDefined()) utilities.throwExceptionMessage("inertia offset position in Body Params");
    inertial_offset_position_ = utilities.toXYZ(&inertial_offset_position);

    YAML::Node inertial_offset_orientation = inertial_offset["orientation"];
    if(!inertial_offset_orientation.IsDefined()) utilities.throwExceptionMessage("inertia offset orientation in Body Params");
    inertial_offset_orientation_ = utilities.toRPY(&inertial_offset_orientation);

    utilities.~Utilities();
}

BodyParam::~BodyParam() {

}
