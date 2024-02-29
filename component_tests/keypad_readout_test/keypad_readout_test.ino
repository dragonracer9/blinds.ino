/******************************************************************
|| Connect to the USB for debugging (9600 baud) 
||
|| @connections
|| Keypad pin from 2 to 10 not including 7 
||        row:  10, 9, 8, 7
||        cols: 5, 4, 3, 2
|| 
*******************************************************************/

#include <Keypad.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

//define the two-dimensional array on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int carriage = 0; 

void setup(){
  Serial.begin(9600);  
}
  
void loop(){
  char key = customKeypad.getKey();
  
  if (key){
    Serial.println("");
    Serial.println("________________");
    Serial.print("Button pressed: ");
    Serial.println(key);
    Serial.print("Carriage: ");
    Serial.println(carriage);
  }
}