
 
#include "ros/ros.h"
#include <iostream>
#include <string>
#include <termios.h>
#include "homework_1/Comando.h"

using namespace std;


//lettura da tastiera non bloccante
char getch()
{
    struct termios old, newt; //due strutture di tipo termios, una per ogni terminale

    tcgetattr( STDIN_FILENO, &old); //metto il contenuto del File Descriptior STDIN_FILENO dentro la mia struttura
    newt = old; //utilizzo una struttura secondaria con gli stessi valori della prima
    newt.c_lflag &= ~( ICANON | ECHO ); //rimuovo la funzionalità canonica ed echo, così da non avere un inserimento bloccante
    newt.c_cc[VMIN]=0;
    newt.c_cc[VTIME]=0;
     //c_cc sono i caratteri di controllo
     //settiamo dei valori a VMIN e VTIME in modo da tener sotto controllo quando read ritorna un risultato
     //VTIME indica la distanza temporale tra un byte e l'altro
     //VMIN indica quanti caratteri sono ricevibili, in questo caso riceve solo il primo carattere 
     
    tcsetattr( STDIN_FILENO, TCSANOW, &newt ); //carica le modifiche appena effettuate sul filedescriptor da cui abbiamo preso le info precedentemente
    char c;
    if (read(0, &c, 1) < 0) //effettua una read
      perror ("read()");
    tcsetattr( STDIN_FILENO, TCSANOW, &old ); //ripristina le impostazioni iniziali
    return c;
}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "half"); //init del programma
  ros::NodeHandle a;
  ros::Publisher info = a.advertise<homework_1::Comando>("information", 1000); //creo il topic inerente a quale comando inviare
  ros::Rate loop_rate(1); //come da richiesta pongo il rate a 1 secondo
  cout << "MENU:\n -a: visualizza l'intero messaggio \n -e: visualizza l'età del soggetto\n -n: visualizza il nome del soggetto\n -c: visualizza il corso di laurea del soggetto\n";
  //visualizzazione menù
  char comando='a'; //comando di visualizzazione di default
  char svalue=comando; // char per il controllo del corretto inserimento
  while (ros::ok())
  {
    homework_1::Comando msg;
    char comando=getch(); //inserimento
    if(comando != 'a' && comando != 'n' && comando != 'c' && comando != 'e' && comando != 'E'  && comando != 'C' && comando != 'N' && comando != 'A' ){
      comando=svalue; //se non vengono rispettati i canoni indicati allora non c'è nessun cambio del comando
    }
    else { //aggiornamento comando e variabile di supporto
      cout << "\n  E' stato premuto il tasto " << comando << "!\n controlla le nuove informazioni! \n" ;
      svalue=comando; 
    }
    msg.comando = comando; //modifichiamo msg 
  //  ROS_INFO("\n invio il comando [%c]\n ", msg.comando);
    info.publish(msg); //invio il comando
    ros::spinOnce();
    loop_rate.sleep(); 
  }
  return 0;
}
