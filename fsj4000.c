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
    
    // cruzar izquierda
    drive_goto(-26,26);
    cont_vueltas = -1;
    
    // seguir pared derecha
    while(cont_vueltas != 0)
    {
      // revisar a la derecha
      drive_goto(26,-26);
      cont_vueltas++;
      // si hay algo, regresar a la izquierda
      if(ping_cm(sensor_pin) < 21)
      {
        drive_goto(-26,26);
        cont_vueltas--;
      }
      // derecha libre, ir a la derecha
      else
      {
        drive_goto(64,64); 
      }        
      
      // revisar frente
      // si hay algo, la unica opcion es cruzar a la izquierda
      if(ping_cm(sensor_pin) < 21)
      {
        drive_goto(-26,26);
        cont_vueltas--;
      }
      
      // avanzar una revolucion
      drive_goto(64,64);
    }    
  }    
}
