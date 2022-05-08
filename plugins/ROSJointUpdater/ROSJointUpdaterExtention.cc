#include "ROSJointUpdaterExtention.h"

ROSJointUpdaterExtention::ROSJointUpdaterExtention()
{
    int argc;
    char **argv;
    ros::init(argc, argv, "node_class");
    ros::Subscriber sub = nh_.subscribe("/number", 1000, &ROSJointUpdaterExtention::joint_cb, this);
}

void ROSJointUpdaterExtention::update(float current_time)
{
    unsigned int time_index = 0;

}


void ROSJointUpdaterExtention::joint_cb(const std_msgs::Float32MultiArray::ConstPtr& msg)
{


    

}