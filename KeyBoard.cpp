#include "KeyBoard.hpp"
#include <Arduino.h>

KeyBoard::KeyBoard(int rxPin, int txPin)
{
  Serial.print("Connect \n");
  Serial.printf("rxPin %d\n", rxPin);
  Serial.printf("rxPin %d\n", txPin);
  Serial2.begin(9600, SERIAL_8N1, rxPin, txPin);
}

byte KeyBoard::BindKey(byte Buffer[], int Size)
{
  byte Lrc = 0;
  while (Size--)
  {
    Lrc ^= *Buffer++;
  }
  return (Lrc ^ 0x0C);
};


char KeyBoard::KeyPress(char code)
{
  switch (code)
  {
  case 0x09:
    return ('0');
    break;
  case 0x1F:
    return ('1');
    break;
  case 0x0F:
    return ('2');
    break;
  case 0x0E:
    return ('3');
    break;
  case 0x02:
    return ('4');
    break;
  case 0x01:
    return ('5');
    break;
  case 0x10:
    return ('6');
    break;
  case 0x05:
    return ('7');
    break;
  case 0x04:
    return ('8');
    break;
  case 0x03:
    return ('9');
    break;
  case 0x13:
    return ('.');
    break;
  case 0x0D:
    return ('=');
    break;
  case 0x17:
    return ('Q');
    break;
  case 0x16:
    return ('+');
    break;
  case 0x15:
    return ('-');
    break;
  case 0x14:
    return ('*');
    break;
  case 0x06:
    return ('/');
    break;
  case 0x07:
    return ('C');
    break;
  case 0x08:
    return ('A');
    break;
  case 0x0C:
    return ('B');
    break;
  case 0x1C:
    return ('S');
    break;
  case 0x1D:
    return ('L');
    break;
  case 0x1E:
    return ('P');
    break;
  default:
    return ('E');
    break;
  }
}
char KeyBoard::KeyNumber(char code)
{
  switch (code)
  {
  case ' ':
    return (0x00);
    break;
  case '0':
    return (0x5F);
    break;
  case '1':
    return (0x50);
    break;
  case '2':
    return (0x3D);
    break;
  case '3':
    return (0x79);
    break;
  case '4':
    return (0x72);
    break;
  case '5':
    return (0x6B);
    break;
  case '6':
    return (0x6F);
    break;
  case '7':
    return (0x53);
    break;
  case '8':
    return (0x7F);
    break;
  case '9':
    return (0x7B);
    break;
  case 'A':
    return (0x77);
    break;
  case 'B':
    return (0x6E);
    break;
  case 'C':
    return (0x0F);
    break;
  case 'D':
    return (0x7C);
    break;
  case 'E':
    return (0x2F);
    break;
  case 'F':
    return (0x27);
    break;
  case 'G':
    return (0x4F);
    break;
  case 'H':
    return (0x66);
    break;
  case 'I':
    return (0x40);
    break;
  case 'J':
    return (0x5C);
    break;
  case 'L':
    return (0x0E);
    break;
  case 'M':
    return (0x45);
    break;
  case 'N':
    return (0x64);
    break;
  case 'O':
    return (0x6C);
    break;
  case 'P':
    return (0x37);
    break;
  case 'Q':
    return (0x73);
    break;
  case 'R':
    return (0x24);
    break;
  case 'S':
    return (0x6B);
    break;
  case 'T':
    return (0x2E);
    break;
  case 'U':
    return (0x5E);
    break;
  case 'V':
    return (0x4C);
    break;
  case 'Y':
    return (0x7A);
    break;
  case 'X':
    return (0x76);
    break;
  case 'Z':
    return (0x3D);
    break;
  case '#':
    return (0x29);
    break;
  case '=':
    return (0x28);
    break;
  case '-':
    return (0x20);
    break;
  case '_':
    return (0x08);
    break;
  default:
    return (0);
    break;
  }
}
void KeyBoard::KeyPadSetIcon(byte bit, bool sw)
{ /* 7=Mute | 6=Bateria | 5=BlueTooth | 4=Raio | 3=Corrente ou Link | 2=GPRS | 1=WIFI palavra | 0=WIFI SINAL */
  byte a;
  byte b;
  switch (bit)
  {
  case 0:
    a = WiFiSgId;
    WiFiSgIcon = sw;
    break;
  case 1:
    a = WiFiId;
    WiFiIcon = sw;
    break;
  case 2:
    a = GPRSId;
    GPRSIcon = sw;
    break;
  case 3:
    a = LinkId;
    LinkIcon = sw;
    break;
  case 4:
    a = RaioId;
    RaioIcon = sw;
    break;
  case 5:
    a = BlueToId;
    BlueToIcon = sw;
    break;
  case 6:
    a = BatId;
    BatIcon = sw;
    break;
  case 7:
    a = MuteId;
    MuteIcon = sw;
    break;
  }
  b = a;
  if (sw)
  {
    Icons = Icons | a;
  }
  else
  {
    Icons = Icons & b;
  }
  KeyPadDisplay[28] = Icons;
}
void KeyBoard::KeyPadCrlIcons()
{
  this->WiFiSgIcon = 0;
  this->WiFiIcon = 0;
  this->GPRSIcon = 0;
  this->LinkIcon = 0;
  this->RaioIcon = 0;
  this->BlueToIcon = 0;
  this->BatIcon = 0;
  this->MuteIcon = 0;

  Icons = 0;
  KeyPadDisplay[28] = Icons;
  this->SetStrValue(KeyPadValue);
  Serial2.write(KeyPadDisplay, sizeof(KeyPadDisplay));
  Serial2.write(BindKey(KeyPadDisplay, sizeof(KeyPadDisplay)));
}

void KeyBoard::ShowIcons()
{
  /* 7=Mute | 6=Bateria | 5=BlueTooth | 4=Raio | 3=Corrente ou Link | 2=GPRS | 1=WIFI palavra | 0=WIFI SINAL */
  byte b = 0;
  if (this->WiFiSgIcon)
  {
    b = b | WiFiSgId;
  }
  if (this->WiFiIcon)
  {
    b = b | WiFiId;
  }
  if (this->GPRSIcon)
  {
    b = b | GPRSId;
  }
  if (this->LinkIcon)
  {
    b = b | LinkId;
  }
  if (this->RaioIcon)
  {
    b = b | RaioId;
  }
  if (this->BlueToIcon)
  {
    b = b | BlueToId;
  }
  if (this->BatIcon)
  {
    b = b | BatId;
  }
  if (this->MuteIcon)
  {
    b = b | MuteId;
  }
  KeyPadDisplay[28] = b;
  Icons = b;
  this->SetStrValue(KeyPadValue);
  Serial2.write(KeyPadDisplay, sizeof(KeyPadDisplay));
  Serial2.write(BindKey(KeyPadDisplay, sizeof(KeyPadDisplay)));
}

void KeyBoard::ClearDisplay()
{
  for (int i = 31; i <= 37; i++)
  {
    KeyPadDisplay[i] = 0x00;
  }
  KeyPadDisplay[38] = this->KeyNumber('0');
}

void KeyBoard::SetStrValue(String Value)
{
  int Digit = 38;

  for (int i = Value.length() - 1; i >= 0; --i)
  {
    if (Value[i] != '.')
    {
      KeyPadDisplay[Digit--] = this->KeyNumber(Value[i]);
      if (Value[i + 1] == '.')
      {
        KeyPadDisplay[Digit + 1] = KeyPadDisplay[Digit + 1] ^ 0x80;
      }
    }
  }
}

void KeyBoard::SetFloatValue(float Value)
{
  String Number = String(Value);
  int Decimal = 0;

  Decimal = Number.indexOf(".00");
  if (Decimal > 0)
  {
    Number.remove(Decimal);
  }
  this->SetStrValue(Number);
}

void KeyBoard::ClrKeyPad()
{
  Icons = KeyPadDisplay[28]; //Salva Icons
  this->Key = 0;
  KeyPadValue = "";
  this->ClearDisplay();
  KeyPadDisplay[28] = Icons; //Load icons
  this->SetStrValue(KeyPadValue);
  Serial2.write(KeyPadDisplay, sizeof(KeyPadDisplay));
  Serial2.write(BindKey(KeyPadDisplay, sizeof(KeyPadDisplay))); //CHECKSUM
}

void KeyBoard::Wait()
{
  while (this->Key == 0)
  {
    Read();
  }
}

void KeyBoard::Read()
{

  if (Serial2.available())
  {

    for (int i = 0; i < 11; i++)
    {
      this->KeyPadData[i] = Serial2.read();
    }
    if ((this->KeyPadData[4] == 0xA3) and (this->KeyPadData[7] == 0x01))
    {

      KeyPressed = this->KeyPress(this->KeyPadData[8]);

      Key_Char = 0;

      Key_Pag = 0;

      if ((KeyPressed >= '0') and (KeyPressed <= '9'))
      {
        if (ModeOperation == 'B')
        {
          KeyPadValue = "";
        }
        ModeOperation = 'N';
        if (KeyPadValue == "")
        {
          this->ClearDisplay();
        }
        if (!((KeyPadValue == "0") and (KeyPressed == '0')))
        {
          if ((KeyPadValue.length() < 8) or ((KeyPadValue.length() == 8) and (KeyPadValue.indexOf('.') > 0)))
          {
            if (KeyPadValue == "0")
            {
              KeyPadValue = "";
            }
            KeyPadValue = KeyPadValue + KeyPressed;
          }
        }

        if (KeyPressed == '1')
        {
          Key_Pag = 1;
        };
        int k = (int)KeyPressed - 48;
        int t = Key_Tam[k];
        int ta = 0;
        int tb = t;

        Key_Last = Key_Now;
        if (Key_Now == KeyPressed)
        {
          Key_Id++;
          if (Key_Id > t)
          {
            Key_Id = 0;
          }
          if (KeyPressed == '1')
          {
            if (Key_Id > 17)
            {
              Key_NPag = 1;
            }
            else
            {
              Key_NPag = 0;
            }
          }
        }
        else
        {
          Key_Id = 0;
          Key_NPag = 0; //Tecla 1
          Key_Show = 1;
        }
        Key_Now = KeyPressed;

        if (Key_Show)
        {
          if (KeyPressed == '1')
          {
            if (Key_NPag == 0)
            {
              ta = 0;
              tb = 17;
            }
            else
            {
              ta = 18;
              tb = t;
            }
          };
          for (; ta < tb + 1; ta++)
          {
            Key_Display += Key_Tab[(int)KeyPressed - 48][ta];
          }
        }

        if (Key_Now == KeyPressed)
        {
          Key_Char = Key_Tab[(int)KeyPressed - 48][Key_Id];
        }

        if (Key_Display == 0)
        {
          Key_Display = KeyPressed;
        }
      }

      if (KeyPressed == 'L')
      {
        Key = 1;
      }
    }
  }
  Serial.println(KeyPressed);
}
void KeyBoard::Bind()
{

  if (Serial2.available())
  {
    for (int i = 0; i < 11; i++)
    {
      this->KeyPadData[i] = Serial2.read();
    }

    if ((this->KeyPadData[4] == 0xA3) and (this->KeyPadData[7] == 0x01))
    {
      KeyPressed = this->KeyPress(this->KeyPadData[8]);

      if ((KeyPressed >= '0') && (KeyPressed <= '9') || (KeyPressed == '.'))
      {
        if (ModeOperation == 'B')
        {
          KeyPadValue = "";
        }
        ModeOperation = 'N';
        if (KeyPadValue == "")
        {
          this->ClearDisplay();
        }
        if (!((KeyPadValue == "0") and (KeyPressed == '0')))
        {
          if ((KeyPadValue.length() < 8) or ((KeyPadValue.length() == 8) and (KeyPadValue.indexOf('.') > 0)))
          {
            KeyPadValue = KeyPadValue + KeyPressed;
          }
        }
      }

      if (KeyPressed == 'A')
      {
        this->ClearDisplay();
        ModeOperation = 'C';
        KeyPadValue = "";
        LastValue = 0;
        StartCalc = true;
      }

      if (KeyPressed == 'C')
      {
        this->ClearDisplay();
        KeyPadValue = "";
      }

      if ((KeyPressed == '=') or (KeyPressed == '+') or (KeyPressed == '-') or (KeyPressed == '*') or (KeyPressed == '/'))
      {
        switch (MathOperation)
        {
        case '+':
          LastValue = LastValue + KeyPadValue.toFloat();
          break;
        case '-':
          LastValue = LastValue - KeyPadValue.toFloat();
          break;
        case '*':
          LastValue = LastValue * KeyPadValue.toFloat();
          break;
        case '/':
          LastValue = LastValue / KeyPadValue.toFloat();
          break;
        default:
          if (StartCalc)
          {
            LastValue = KeyPadValue.toFloat();
          };
          break;
        }
        if (KeyPressed == '=')
        {
          this->ClearDisplay();
          MathOperation = 0;
          this->SetFloatValue(LastValue);
        }
        else
        {
          MathOperation = KeyPressed;
        }
        KeyPadValue = "";
        StartCalc = false;
      }

      if (KeyPressed == 'B')
      {
        this->ClearDisplay();
        //strip.ClearTo(black);
        ModeOperation = 'B';
      } //B

      if (KeyPressed == 'S')
      {
        this->ClearDisplay();
        ModeOperation = 'S';
        Volume_Mute = !Volume_Mute;
        MuteIcon = Volume_Mute;
        if (Volume_Mute)
        {
          KeyPadValue = "AUDIO OF";
        }
        else
        {
          KeyPadValue = "AUDIO ON";
        }
        this->ShowIcons();
        KeyTimer_Out = millis(); // Inicia KeyTimer;
        KeyTimer_On = 1;
      }

      if (KeyPressed == 'L')
      {
      }

      if (KeyPressed == 'P')
      {
      }

      if (KeyPressed == 'Q')
      {
      }
      Serial.println("KeyPadDisplay");
      this->SetStrValue(KeyPadValue);
      Serial2.write(KeyPadDisplay, sizeof(KeyPadDisplay));
      Serial2.write(BindKey(KeyPadDisplay, sizeof(KeyPadDisplay)));
    }
  }
}
void KeyBoard::Bind(void (*callback)(String,float))
{

  if (Serial2.available())
  {
    for (int i = 0; i < 11; i++)
    {
      this->KeyPadData[i] = Serial2.read();
    }

    if ((this->KeyPadData[4] == 0xA3) and (this->KeyPadData[7] == 0x01))
    {
      KeyPressed = this->KeyPress(this->KeyPadData[8]);

      if ((KeyPressed >= '0') && (KeyPressed <= '9') || (KeyPressed == '.'))
      {
        if (ModeOperation == 'B')
        {
          KeyPadValue = "";
        }
        ModeOperation = 'N';
        if (KeyPadValue == "")
        {
          this->ClearDisplay();
        }
        if (!((KeyPadValue == "0") and (KeyPressed == '0')))
        {
          if ((KeyPadValue.length() < 8) or ((KeyPadValue.length() == 8) and (KeyPadValue.indexOf('.') > 0)))
          {
            KeyPadValue = KeyPadValue + KeyPressed;
          }
        }
      }

      if (KeyPressed == 'A')
      {
        this->ClearDisplay();
        ModeOperation = 'C';
        KeyPadValue = "";
        LastValue = 0;
        StartCalc = true;
      }

      if (KeyPressed == 'C')
      {
        this->ClearDisplay();
        KeyPadValue = "";
      }

      if ((KeyPressed == '=') or (KeyPressed == '+') or (KeyPressed == '-') or (KeyPressed == '*') or (KeyPressed == '/'))
      {
        switch (MathOperation)
        {
        case '+':
          LastValue = LastValue + KeyPadValue.toFloat();
          break;
        case '-':
          LastValue = LastValue - KeyPadValue.toFloat();
          break;
        case '*':
          LastValue = LastValue * KeyPadValue.toFloat();
          break;
        case '/':
          LastValue = LastValue / KeyPadValue.toFloat();
          break;
        default:
          if (StartCalc)
          {
            LastValue = KeyPadValue.toFloat();
          };
          break;
        }
        if (KeyPressed == '=')
        {
          this->ClearDisplay();
          MathOperation = 0;
          this->SetFloatValue(LastValue);
        }
        else
        {
          MathOperation = KeyPressed;
        }
        KeyPadValue = "";
        StartCalc = false;
      }

      if (KeyPressed == 'B')
      {
        this->ClearDisplay();
        //strip.ClearTo(black);
        ModeOperation = 'B';
      } //B

      if (KeyPressed == 'S')
      {
        this->ClearDisplay();
        ModeOperation = 'S';
        Volume_Mute = !Volume_Mute;
        MuteIcon = Volume_Mute;
        if (Volume_Mute)
        {
          KeyPadValue = "AUDIO OF";
        }
        else
        {
          KeyPadValue = "AUDIO ON";
        }
        this->ShowIcons();
        KeyTimer_Out = millis(); // Inicia KeyTimer;
        KeyTimer_On = 1;
      }

      if (KeyPressed == 'L')
      {
      }

      if (KeyPressed == 'P')
      {
      }

      if (KeyPressed == 'Q')
      {
      }
      this->SetStrValue(KeyPadValue);
      Serial2.write(KeyPadDisplay, sizeof(KeyPadDisplay));
      Serial2.write(BindKey(KeyPadDisplay, sizeof(KeyPadDisplay)));
      callback(String(KeyPadValue),LastValue);
    }
  }
}