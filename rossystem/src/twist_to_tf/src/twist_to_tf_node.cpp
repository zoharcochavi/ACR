#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Twist.h>

std::string reference_name;

void twistCallback(const geometry_msgs::Twist& msg) {
	static tf::TransformBroadcaster br;
	tf::Transform transform;
	tf::Quaternion q;
	
	transform.setOrigin( tf::Vector3(msg.linear.x, msg.linear.y, 0.0) );
	q.setRPY(0, 0, msg.angular.z);
	transform.setRotation(q);
	
	br.sendTransform(
		tf::StampedTransform(transform, ros::Time::now(), "base_link", reference_name)
	);
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "my_tf_broadcaster");
  
	if (argc != 2) {
	      ROS_ERROR("need reference name");
	      return -1;
	}
	reference_name = argv[1];
	
	ros::NodeHandle node;
	ros::Subscriber sub = node.subscribe("/cmd_vel", 10, &twistCallback);
	
	ros::spin();
	return 0;
};
