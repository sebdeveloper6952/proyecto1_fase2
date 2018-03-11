/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"

int sensor_pin = 8;
int cont_vueltas = 0;

int main()
{
  while(1)
  {
    // avanzar a pared
    drive_ramp(128,128);
    while(ping_cm(sensor_pin) > 21) { pause(5); }
    drive_ramp(0,0);
    
    cruzar_izquierda();
    
    // seguir pared derecha
    while(cont_vueltas != 0)
    {
      cruzar_derecha();
     
      // si hay algo, regresar a la izquierda
      if(ping_cm(sensor_pin) < 21)
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
      if(ping_cm(sensor_pin) < 21)
      {
        cruzar_izquierda();
      }
      
      // si el frente esta libre avanzar una revolucion
      if(ping_cm(sensor_pin) > 26)
      { 
        drive_goto(64,64);
      }             
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
