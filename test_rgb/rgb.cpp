#include "tpl_os.h" // Inclut la bibliothèque TPL, qui fournit les primitives de l'OS temps-réel
#include "Arduino.h" // Inclut la bibliothèque Arduino
#include "stdio.h"
const int PIN_RED   = 6;
const int PIN_GREEN = 5;
const int PIN_BLUE  = 3;

void setup()
{
    pinMode(PIN_RED,OUTPUT);
    pinMode(PIN_BLUE,OUTPUT);
    pinMode(PIN_GREEN,OUTPUT);
	StartOS(OSDEFAULTAPPMODE);
	
}
TASK(lectureCapteurTask) // Définit une tâche nommée "lectureCapteurTask"
{
  analogWrite(PIN_GREEN, 0);
    
analogWrite(PIN_BLUE,  0); 
analogWrite(PIN_RED,   100);
delay(100);
  TerminateTask();
}
TASK( leTask){ 
  analogWrite(PIN_RED,   0);
analogWrite(PIN_GREEN, 0);
analogWrite(PIN_BLUE,  100); 
delay(100);
  TerminateTask();

}
TASK( green){ 
  analogWrite(PIN_RED,  0);

analogWrite(PIN_BLUE,  0);
 analogWrite(PIN_GREEN, 100);
delay(100);
  TerminateTask();

}