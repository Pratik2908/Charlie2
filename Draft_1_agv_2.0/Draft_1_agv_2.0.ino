#include <LiquidCrystal.h>
#include <Keypad.h>//header for keypad commands enabling
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //definign lcd pins 
const int trig= 30, echo1= 31, echo2=32, echo3=33; //ultrasound pins 
//for the ultrasound 
int obs=0;
// setting var for the inc dec keys; 
int  SrcIndent=0, DstIndent=0;
// settign up the bool flags for 1/0 toggle 
bool SrcFlag=0,DstFlag=0,ConfirmFlag=0,Play=0,Pause=0,Reset=0;
//The array containing the various stations
String Src[]={"GRE","ASS","POL","MSE","SAM","WAX","DIA","CAS"};
String Dst[]={"GRE","ASS","POL","MSE","SAM","WAX","DIA","CAS"};
//String Final_Src[]={};
//String Final_Dst[1];
//Liquid Crystal init  
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = 
{
  {'D','C','B','A'},

  {'#','9','6','3'},

  {'0','8','5','2'},

  {'*','7','4','1'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 0, 1, 2, 3 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 4, 5, 6, 7 };
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//  Create the Keypad
void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2); 
  StartUltra(); //ultrasound Pin intialize
}

void loop()
{
 obs=Obstruction();// Function Handling Ultraosound
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
  if(SrcFlag==1);
  {
   lcd.clear(); 
   lcd.setCursor(0, 0);
   lcd.print("Set Source");
  }
  if (DstFlag==1);
  {
   lcd.clear(); 
   lcd.setCursor(0, 0);
   lcd.print("Set destination");
  }
  if (SrcFlag==1)
  {
   //lcd.clear();
   lcd.setCursor(1, 1);
   lcd.print( Src[SrcIndent]);
  }
  if (DstFlag==1)
  {
    lcd.setCursor(1, 1);
   lcd.print( Dst[DstIndent]);
  }
  if (Play==1)
  {
    lcd.clear();
    lcd.setCursor(1, 1);
     lcd.print("Play");
  }
  if (Pause==1)
  {  lcd.clear();
     lcd.setCursor(1,1); 
     lcd.print("Pause");
  }
  if (Reset==1)
     {
      lcd.clear();
      lcd.setCursor(1,1); 
     lcd.print("Reset"); 
     }
}

void Keypressed()
{
   char key = kpd.getKey(); //storing pressed key value in a char

   switch (key)
   {
    case 'A':
             if(DstFlag==1)
                {
                 DstFlag=0;
                 }
             if(SrcFlag==0)
               {
                SrcFlag=1; 
                }
               else SrcFlag=0;
               break;
    case 'B':
             if(SrcFlag==1)
               {
                SrcFlag=0;
                }
                if(DstFlag==0)
               { 
                DstFlag=1; 
                }
                else DstFlag=0;
                break;
    case 'C':
              if(SrcFlag==1)
                {
                  //transfer the alvue of the selected indent on the permanent vlaue 
                  SrcFlag=0;    
                }
                if(DstFlag==1)
                {
                  // transfer vlaue 
                  DstFlag=0; 
                }
                break;                   
    case 'D':
             Play=0;
             Pause=1;
             Reset=1;
             delay(10000);
             Reset=0;
             break;
    case '1':
               if (SrcFlag==1)
                  {
                   SrcIndent++;
                    if( SrcIndent==8)
                      {
                         SrcIndent=0;
                      }
                  }
               if (DstFlag==1)
                  {
                    DstIndent++;
                    if(DstIndent==8)
                      {
                      DstIndent=0;
                      }
                  }
               break;     
    case '2':
             break;
    case '3':
             break;
    case '4':
             if (SrcFlag==1) 
                {
                  SrcIndent--;
                }
                 if (DstFlag==1)
                    {
                       DstIndent--;
                     if(DstIndent==-1)
                       {
                         DstIndent==8;  
                       }
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
             if(Reset==0)
             {Play=1;
              Pause=0;
             }
            break;
    case '#':
            if(Reset==0)
               {
                Play=0;
                Pause=1;
               }
            break;           
   }        
  }



                
