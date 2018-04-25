
#include <Keypad.h>//header for keypad commands enabling

const byte ROWS = 4; // Four rows

const byte COLS = 4; // Three columns

// Define the Keymap

char keys[ROWS][COLS] = {

  {'D','C','B','A'},

  {'#','9','6','3'},

  {'0','8','5','2'},

  {'*','7','4','1'}

};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.

byte rowPins[ROWS] = { 0, 1, 2, 3 };

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.

byte colPins[COLS] = { 4, 5, 6, 7 };

//  Create the Keypad

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()

{
Serial.begin(9600);
  

}

void loop()

{

  char key = kpd.getKey(); //storing pressed key value in a char

  if (key != NO_KEY)

{
Serial.println(key);

  }

}                
