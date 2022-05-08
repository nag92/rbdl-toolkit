#include "ROSJointUpdaterExtention.h"

ROSJointUpdaterExtention::ROSJointUpdaterExtention()
{
    int argc;
    char **argv;
    ros::init(argc, argv, "node_class");
}

void ROSJointUpdaterExtention::update(float current_time)
{
    unsigned int time_index = 0;

}


void ROSJointUpdaterExtention::joint_cb(const std_msgs::Float32MultiArray::ConstPtr& msg)
{


    

}