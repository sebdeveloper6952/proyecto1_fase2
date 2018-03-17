//---------- LIBRERIAS IMPORTADAS----------------------------------

#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"



//---------- ESPACIO DE VARIABLES---------------------------------

int front_s_pin = 8;
int right_s_pin = 7;
int turns = 0;
int dist = 15;
int move_dist = 32;

//----------- CODIGO PRINCIPAL -----------------------------------

int main()
{
  while(1)
  {
    // avanzar hasta llegar a pared
    drive_ramp(64,64);
    while(ping_cm(front_s_pin) > dist) { pause(5); }
    drive_ramp(0,0);
    
    //al llegar a una pared, cruza a la izquierda para manterner la pared siempre a su derecha, y entra al loop principal 
    cruzar_izquierda();
    
    //El robot entrara a este loop, si el contador de las vueltas no es cero. En caso sea cero, esto indica que ya supero el obstaculo y sale del loop.
    while(turns != 0)
    {
      // ver si la pared que se encuentra a su derecha esta a una distancia mayor de la maxima tolerada. 
      if(ping_cm(right_s_pin) > dist)
      {
        // cruzar a la derecha, y avanza revolucion y media si la distancia lo permite.
        cruzar_derecha();
        if(ping_cm(front_s_pin > 110)) { drive_goto(96,96); } 
        
        //si la distancia es menor, avanza solo 20 ticks de las ruedas para no chocar con ningun obstaculo.. 
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
    }
  }    
}


//----------------------- DEFINICION DE FUNCIONES ----------------------------------------------------

//mueve las ruedas del robot 27 ticks en sentidos opuestos para lograr que el robot cruce a la izquierda. Le resta al contador para poder hacer cumplir la condicion del loop.
void cruzar_izquierda()
{
  drive_goto(-27,27);
  turns--;
}


//mueve las ruedas del robot 27 ticks en sentidos opuestos para lograr que el robot cruce a la derecha. Le suma al contador para poder hacer cumplir la condicion del loop.
void cruzar_derecha()
{
  drive_goto(27,-27);
  turns++;
} 

