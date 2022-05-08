#ifndef ROS_JOINT_UPDATER_EXTENTION_H_INCLUDED
#define ROS_JOINT_UPDATER_EXTENTION_H_INCLUDED

#include <QWidget>
#include <QString>

#include <vector>
#include "ros/ros.h"
#include "toolkit_interfaces.h"
#include "std_msgs/Float32MultiArray.h"
#include "toolkit_config.h"
#include "util.h"

class TOOLKIT_PLUGIN_DLLAPI ROSJointUpdaterExtention: public WrapperExtension {
    private:
        // ... all private variables holding extension data
       ros::NodeHandle nh_;
       void joint_cb(const std_msgs::Float32MultiArray::ConstPtr& msg);
    public:
       ROSJointUpdaterExtention();
       
	   std::string getExtensionName();
	   void update(float current_time);
};

#endif 