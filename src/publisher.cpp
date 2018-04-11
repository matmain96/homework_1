
#include "ros/ros.h"
#include <sstream>
#include <iostream>
#include <string>
#include "homework_1/Str.h"

using namespace std;
int main(int argc, char **argv)
{
  ros::init(argc, argv, "publisher");

  ros::NodeHandle n;
  ros::Publisher details = n.advertise<homework_1::Str>("studente", 1000);
  std::string studente, corso, eta;
  ros::Rate loop_rate(1);

  cout << "Nome: ";
  std::getline(std::cin, studente);
  cout << "Età: ";
  std::getline(std::cin, eta);
  cout << "Nome corso: ";
  std::getline(std::cin, corso);
  
  while (ros::ok())
  {
    homework_1::Str msg;

    msg.nome = studente;
    msg.eta = eta;
    msg.cdl = corso;
    ROS_INFO("%s , %s, %s", msg.nome.c_str() , msg.eta.c_str(), msg.cdl.c_str());
    details.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
