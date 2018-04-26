#include <LiquidCrystal.h>
#include <Keypad.h>//header for keypad commands enabling
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //definign lcd pins
const int trig= 30, echo1= 31, echo2=32, echo3=33; //ultrasound pins
//for the ultrasound
int obs=0;
// setting var for the inc dec keys;
int  SrcIndent = 0, DstIndent = 0;
int FinalSrc = 0, FinalDst = 0;
// settign up the bool flags for 1/0 toggle
volatile int SrcFlag = 0, DstFlag = 0 , Play = 0, Pause = 0, Reset = 0;
//The array containing the various stations
String Src[] = {"GRE", "ASS", "POL", "MSE", "SAM", "WAX", "DIA", "CAS"};
String Dst[] = {"GRE", "ASS", "POL", "MSE", "SAM", "WAX", "DIA", "CAS"};
//Liquid Crystal init
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] =
{
  {'D', 'C', 'B', 'A'},

  {'#', '9', '6', '3'},

  {'0', '8', '5', '2'},

  {'*', '7', '4', '1'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 8, 9, 10, 11 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 12, 13, A0, A1 };
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//  Create the Keypad
void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
   StartUltra(); //ultrasound Pin intialize
  //Serial.begin(9600);
}

void loop()
{
  // Serial.println(SrcFlag);
  //Serial.println(DstFlag);
  // obs=Obstruction();// Function Handling Ultraosound
  Keypressed(); //Function Handling Pressing of keys
  LCD_Display(); //Function Handling Display on the LCD
}

/*Functions Start*/

void StartUltra()
{
  pinMode(trig, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
}

  int Obstruction()
  {
  long duration1 , duration2, duration3;
  int distance1, distance2, distance3;
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  duration1=pulseIn(echo1, HIGH);
  duration2=pulseIn(echo2, HIGH);
  duration3=pulseIn(echo3, HIGH);

  distance1= duration1*(0.034/2);
  distance2= duration2*(0.034/2);
  distance3= duration3*(0.034/2);

  if((distance1< 10) || (distance2< 10) || (distance3< 10))
    {
     return 1;
    }
  else return 0;

  }

void LCD_Display()
{
  if(obs==1)
    {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Halt");
    }
  if (SrcFlag == 1)
  {
    //  lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SRC=");
    lcd.setCursor(5, 0);
    lcd.print( Src[SrcIndent]);
  }
  //  if(SrcFlag==0)
  //  {
  //    lcd.clear();
  //  }
  if (DstFlag == 1)
  {
    //lcd.clear();
    lcd.setCursor(9, 0);
    lcd.print("DST=");
    lcd.setCursor(13, 0);
    lcd.print( Dst[DstIndent]);
  }
  //    if (SrcFlag==1)
  //    {
  //     //lcd.clear();
  //     lcd.setCursor(6, 0);
  //     lcd.print( Src[SrcIndent]);
  //    }
  //    if (DstFlag==1)
  //    {
  //      lcd.setCursor(13, 0);
  //     lcd.print( Dst[DstIndent]);
  //    }
  if (Play == 1)
  {

    lcd.clear();
    if(FinalSrc==FinalDst)
    {
      lcd.print("Error"); 
    }
    lcd.setCursor(5, 0);
    lcd.print("Play");
  }
  if (Pause == 1 )
  { lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Pause");
    delay(1000);
    lcd.clear();
    FinalSrc=0;
    FinalDst=0;
    Pause = 0;

  }
  if (Reset == 1)
  {
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("Reset");
  }
}

void Keypressed()
{
  char key = kpd.getKey(); //storing pressed key value in a char

  switch (key)
  {
    case 'A':
      if (DstFlag == 1)
      {

        DstFlag = 0;
       // Serial.println(DstFlag);
       // Serial.println(SrcFlag);
       // Serial.println("DSt Flag made zero");
      }
      if (SrcFlag == 0)
      {

        //Serial.println("Src Flag made one");
        SrcFlag = 1;
        //Serial.println(DstFlag);
        //Serial.println(SrcFlag);
      }
      else if (SrcFlag == 1)
      {
        SrcFlag = 0;
        //Serial.println(DstFlag);
        //Serial.println(SrcFlag);
        //Serial.println("The Src FLag going from one to zero");

      }
      break;
    case 'B':
      if (SrcFlag == 1)
      {
        SrcFlag = 0;
        //Serial.println(DstFlag);
        //Serial.println(SrcFlag);
        //Serial.println("SRC Flag made zero");
      }
      if (DstFlag == 0)
      {
        DstFlag = 1;
        //Serial.println(DstFlag);
        //Serial.println(SrcFlag);
        //Serial.println("Dst Flag made one");
      }
      else if (DstFlag == 1)
      {
        DstFlag = 0;
        //Serial.println(DstFlag);
        //Serial.println(SrcFlag);
        //Serial.println("The Dst FLag going from one to zero");

      }
      break;
    case 'C':
      if (SrcFlag == 1)
      {
        FinalSrc = SrcIndent;
        SrcFlag = 0;
        //Serial.println(FinalSrc);
      }
      if (DstFlag == 1)
      {
        FinalDst = DstIndent;
        DstFlag = 0;
        //Serial.println(FinalDst);
      }
      lcd.clear();
      break;
    case 'D':
      Play = 0;
      Pause = 1;
      Reset = 1;
      lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("RESET");
      delay(10000);
      Reset = 0;
      break;
    case '1':
      if (SrcFlag == 1)
      {
        SrcIndent++;
        if ( SrcIndent == 8)
        {
          SrcIndent = 0;
        }
      }
      //Serial.print("This pressing Key one");
      //Serial.println(SrcIndent);
      if (DstFlag == 1)
      {
        DstIndent++;
        if (DstIndent == 8)
        {
          DstIndent = 0;
        }
        //Serial.print("This pressing Key one");
        //Serial.println(DstIndent);
      }
      break;
    case '2':
      break;
    case '3':
      break;
    case '4':
      if (SrcFlag == 1)
      {
        SrcIndent--;
      }
      if (SrcIndent == -1)
      {
        //Serial.println("andar gaya");
        SrcIndent = 7;
      }
      //Serial.print("This pressing Key one");
      //Serial.println(SrcIndent);
      if (DstFlag == 1)
      {
        DstIndent--;
        if (DstIndent == -1)
        {
        //  Serial.println("andar gaya");
          DstIndent = 7;
        }
        //Serial.print("This pressing Key one");
        //Serial.println(DstIndent);
      }
      break;
    case '5':
      break;
    case '6':
      break;
    case '7':
      break;
    case '8':
      break;
    case '9':
      break;
    case '0':
      break;
    case '*':
      if (Reset == 0)
      {
        SrcFlag = 0;
        DstFlag = 0;
        Play = 1;
        Pause = 0;
        FinalSrc = SrcIndent;
        FinalDst = DstIndent;
        //Serial.print("FinalSrc=");
        //Serial.println(FinalSrc);
        //Serial.print("FinalDst=");
        //Serial.print(FinalDst);

      }
      break;
    case '#':
      if (Reset == 0)
      {
        Play = 0;
        Pause = 1;

      }
      break;
  }
}




