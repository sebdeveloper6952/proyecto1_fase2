#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"

int front_s_pin = 8;
int right_s_pin = 7;
int turns = 0;
int dist = 15;
int move_dist = 32;

int main()
{
  while(1)
  {
    // avanzar hasta llegar a pared
    drive_ramp(64,64);
    while(ping_cm(front_s_pin) > dist) { pause(5); }
    drive_ramp(0,0);
    
    cruzar_izquierda();
    
    while(turns != 0)
    {
      // ver si hay pared a la derecha
      if(ping_cm(right_s_pin) > dist)
      {
        // cruzar a la derecha y avanzar una revolucion
        cruzar_derecha();
        if(ping_cm(front_s_pin > 110)) { drive_goto(96,96); } 
        else
        {
          drive_goto(20,20);
        }          
        continue;
      }      
    
      // si hay algo a la derecha, revisar frente
      if(ping_cm(front_s_pin) < dist)
      {
        // si no hay espacio enfrente, cruzar a la izquierda
        cruzar_izquierda();
      }
    
      // avanzar una revolucion
      drive_goto(move_dist, move_dist);        

  //drive_ramp(0,0);
    }
  }    
}

void cruzar_izquierda()
{
  drive_goto(-27,27);
  //drive_speed(-38.5,38);
  //pause(370);
  
  turns--;
}

void cruzar_derecha()
{
  drive_goto(27,-27);
  
  //drive_ramp(0,0);
  //drive_speed(38.5,-38);
  //pause(370);
  
  turns++;
} 
