
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
#include "homework_1/Comando.h"
#include "homework_1/Str.h"


char comando='a';

void information(const homework_1::Comando::ConstPtr& msg)
{
  comando= msg->comando;
}

void studente(const homework_1::Str::ConstPtr& msg)
{
  switch(comando){
    case 'a':
      ROS_INFO("\n[%s, %s, %s]\n ", msg->nome.c_str(), msg->eta.c_str(), msg->cdl.c_str() );
      break;
    case 'n':
      ROS_INFO("\n[%s]\n ", msg->nome.c_str());
      break;
    case 'e':
      ROS_INFO("\n[%s]\n ", msg->eta.c_str());
      break;
    case 'c':
      ROS_INFO("\n[%s]\n ", msg->cdl.c_str());
      break;
    default:  
      break;
  }

}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "last");
  ros::NodeHandle n;
  ros::Subscriber sub1 = n.subscribe("information", 1000, information);
  ros::Subscriber sub2 = n.subscribe("studente",1000, studente);
  ros::spin(); 
  return 0;
}
