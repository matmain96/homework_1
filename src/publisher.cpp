
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
  ros::Publisher details = n.advertise<homework_1::Str>("studente", 1000); //crea il topic studente
  std::string studente, corso, eta; //crea le tre stringhe per l'inserimento da tastiera
  ros::Rate loop_rate(1);
  cout << "Nome: ";
  std::getline(std::cin, studente); //inserisce nome
  cout << "Età: ";
  std::getline(std::cin, eta); //inserisce età
  cout << "Nome corso: ";
  std::getline(std::cin, corso); //inserisce corso di laurea
    
      while (ros::ok())
      {
        homework_1::Str msg;
        //inserisce le tre stringhe nel messaggio da inviare
        msg.nome = studente; 
        msg.eta = eta;
        msg.cdl = corso;
        ROS_INFO("%s , %s, %s", msg.nome.c_str() , msg.eta.c_str(), msg.cdl.c_str()); //visualizza a schermo ciò che invia
        details.publish(msg); //invia il messaggio scritto 
        ros::spinOnce();
        loop_rate.sleep();
      }
  return 0;
}
