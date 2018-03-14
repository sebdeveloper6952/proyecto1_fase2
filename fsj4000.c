/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"

int front_s_pin = 8;
int right_s_pin = 7;
int cont_vueltas = 0;
int dist = 20;

int main()
{  
  while(1)
  {
    // avanzar a pared
    drive_ramp(128,128);
    while(ping_cm(front_s_pin) > 21) { pause(5); }
    drive_ramp(0,0);
    
    cruzar_izquierda();
    
    // seguir pared derecha
    while(cont_vueltas != 0)
    {
      cruzar_derecha();
     
      // si hay algo, regresar a la izquierda
      if(ping_cm(front_s_pin) < dist)
      {
        cruzar_izquierda();
      }
      // derecha libre, ir a la derecha
      else
      {
        drive_goto(64,64);
        continue;
      }       
      
      // revisar frente
      // si hay algo, la unica opcion es cruzar a la izquierda
      if(ping_cm(front_s_pin) < dist)
      {
        cruzar_izquierda();
      }
      
      drive_goto(64,64);         
    }    
  }    
}

void cruzar_izquierda()
{
  drive_goto(-27,27);

  //drive_ramp(0,0);
  //drive_speed(-38.5,38);
  //pause(370);
  
  cont_vueltas--;
}

void cruzar_derecha()
{
  drive_goto(27,-27);
  
  //drive_ramp(0,0);
  //drive_speed(38.5,-38);
  //pause(370);
  
  cont_vueltas++;
}    
