#include "ros/ros.h"
#include "udp.h"
#include "string"
#include "roseus/StringStamped.h"

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "udp_comm");
    ros::NodeHandle nh;

    int server_port = 5000;
    std::string server_address = "localhost";

    if (!ros::param::get("/udp_comm/server_address", server_address))
    {
        ROS_ERROR_STREAM("Parameter " << ros::this_node::getName() << "/server_address not found."); 
    }
    if (!ros::param::get("/udp_comm/server_port", server_port))
    {
        ROS_ERROR_STREAM("Parameter " << ros::this_node::getName() << "/server_port not found."); 
    }

    udp_client_server::udp_server server = udp_client_server::udp_server(server_address, server_port);

    //string publisher
    ros::Publisher pub = nh.advertise<roseus::StringStamped>("/received_udp", 1000);

    while (ros::ok()) 
    {
        char msg[1500];
        int size = server.recv(msg, sizeof(msg));

        std::string hex_data;
        for(int i = 0; i < size - 1; i++)
        {
            std::stringstream ss;
            ss << std::hex << (int)msg[i];
            hex_data += ss.str();
        }
        roseus::StringStamped msg_out;
        msg_out.data = hex_data;
        msg_out.header.stamp = ros::Time::now();
        pub.publish(msg_out);
        
        ros::spinOnce();
    }

    return 0;
}
