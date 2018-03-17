#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"

int front_s_pin = 8;
int right_s_pin = 7;
int turns = 0;
int dist = 20;
int distancia = 64;
int distancia2 = 27;
int distancia3 = -27;

int vel = 128;

int main()
{
  while(1)
  {
    // avanzar hasta llegar a pared, luego de eso cruzar a la izquierda 
    
	
	drive_ramp(vel, vel);
    while(ping_cm(front_s_pin) > dist) { pause(5); } 
    drive_ramp(0,0);

    
    cruzar_izquierda();
    
	//while para validar los giros 
    while(turns != 0)
    {
      // ver si hay pared a la derecha
      
	  if(ping_cm(right_s_pin) > dist)
      {
        // cruzar a la derecha y avanzar una revolucion
        cruzar_derecha();
        drive_goto(distancia,distancia);
        continue;
      }
    
      // si hay algo a la derecha, revisar frente
      if(ping_cm(front_s_pin) < dist)
      {
        // si no hay espacio enfrente, cruzar a la izquierda
        cruzar_izquierda();
      }
    
      // avanzar una revolucion
      drive_goto(distancia, distancia);
    }
  }    
}

//cruza a la izquierda 
void cruzar_izquierda()
{
  drive_goto(distancia3 , distancia2);

  //drive_ramp(0,0);
  //drive_speed(-38.5,38);
  //pause(370);
  
  // disminuye el contador cada vez que el robot cruce a la izquierda
  turns--;
}
// cruza a la derecha
void cruzar_derecha()
{
  drive_goto(distancia2, distancia3);
  
  //drive_ramp(0,0);
  //drive_speed(38.5,-38);
  //pause(370);
  
  // aumenta el contador cada vez que el robot cruce a la izquierda
  turns++;
} 
