#include <LiquidCrystal.h>
int  SrcIndent=0, DstIndent=0;
// settign up the bool flags for 1/0 toggle 
bool SrcFlag=0,DstFlag=0,ConfirmFlag=0,Play=0,Pause=0,Reset=0;
//The array containing the various stations
String Src[]={"GRE","ASS","POL","MSE","SAM","WAX","DIA","CAS"};
String Dst[]={"GRE","ASS","POL","MSE","SAM","WAX","DIA","CAS"};


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int Switch1=8, Switch2=9;
char rx_byte;
void setup() 
{
  Serial.begin(9600);

  lcd.begin(16, 2);
}
void loop()
{
  if (Serial.available() > 0)    // is a character available?
    rx_byte = Serial.read();       // get the character
Serial.println(rx_byte);
KeyPressed();
LCD_Display();
Serial.flush();
}


void KeyPressed()
{
  switch (rx_byte)
  {
    case 'A':
             if(DstFlag==1)
                {
                 DstFlag=0;
          //       Serial.println("Dst flag is now zero");
                 }
             if(SrcFlag==0)
               {
                SrcFlag=1; 
            //    Serial.println("Src flag is now one");
                }
               else
               {
                SrcFlag=0;
              // Serial.println("the SRC flg was made zero");
               }
               
               break;
    case 'B':
             if(SrcFlag==1)
               {
                SrcFlag=0;
               // Serial.println("Src flag is now zero");
                }
                if(DstFlag==0)
               { 
                DstFlag=1; 
               // Serial.println("Dst flag is now one");
                }
                else
                {
                  DstFlag=0;
                // Serial.println("the SRC flg was made zero");
                }
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

void LCD_Display()
{
 
  if(SrcFlag==1);
  {
   lcd.clear(); 
   lcd.setCursor(0, 0);
   lcd.print("Src=");
  }
  if (DstFlag==1);
  {
   lcd.clear(); 
   lcd.setCursor(8, 0);
   lcd.print("Dst=");
  }
  if (SrcFlag==1)
  {
   lcd.clear();
   lcd.setCursor(5,0);
   lcd.print( Src[SrcIndent]);
  }
  if (DstFlag==1)
  {
    lcd.setCursor(12, 0);
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
