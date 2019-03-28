#include "panda_softhand_safety/collision_evader.h"
#include "panda_softhand_safety/SafetyInfo.h"

int main(int argc, char** argv) {
    
    ros::init (argc, argv, "panda_softhand_safety_node");
    ros::NodeHandle nh;

    // Safety info message
    panda_softhand_safety::SafetyInfo safety_info_msg;

    // Collision evader object
    panda_softhand_safety::CollisionEvader collision_evader(nh);

    // Starting to spin
    while (ros::ok()) {
        
        ros::spinOnce();

        // Resetting the message
        safety_info_msg.header.stamp = ros::Time::now();
        safety_info_msg.collision = false;
        safety_info_msg.joint_position_limits = false;
        safety_info_msg.joint_velocity_limits = false;
        safety_info_msg.joint_acceleration_limits = false;

        // Checking for collisions
        if (collision_evader.CheckCollision()){
            safety_info_msg.collision = true;
            ROS_ERROR("A collision found!");
        }
    }

    ros::shutdown();
    return 0;
}