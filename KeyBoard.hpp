
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <Arduino.h>
#include <string>




const byte WiFiSgId = B00000001;
const byte WiFiId = B00000010;
const byte GPRSId = B00000100;
const byte LinkId = B00001000;
const byte RaioId = B00010000;
const byte BlueToId = B00100000;
const byte BatId = B01000000;
const byte MuteId = B10000000;

class KeyBoard
{
public:
    KeyBoard(int rxPin, int txPin);
    void KeyPadProcess();
    byte BindKey(byte Buffer[], int Size);
    char KeyPress(char code);
    char KeyNumber(char code);
    void KeyPadSetIcon(byte bit, bool sw);
    void KeyPadCrlIcons();
    void SetStrValue(String Value);
    void ShowIcons();
    void SetFloatValue(float Value);
    void ClrKeyPad();
    void ClearDisplay();
    void Wait();
    void Read();
    void Bind();
    void Bind(void (*callback)(String,float));
    void Ku(char code);
    String KeyPadValue = "";
    float LastValue = 0;
private:
    int WiFiSgIcon = 0;
    int WiFiIcon = 0;
    int GPRSIcon = 0;
    int LinkIcon = 0;
    int RaioIcon = 0;
    int BlueToIcon = 0;
    int BatIcon = 0;
    int MuteIcon = 0;
    boolean Key;
    byte KeyPadData[11] = {0};
    String Key_Display = "";

    byte Icons;
    char KeyPressed = 0;
    char ModeOperation = 0;
    char Key_Char;
    boolean Key_Pag = 0;
    int Key_Fn;
    int Key_Id;
    char Key_Now;
    char Key_Last;
    int Key_NPag = 0;
    boolean Key_Show = 0;
    bool StartCalc = true;
    boolean Volume_Mute = 1;
    long KeyTimer_Out;
    boolean KeyTimer_On;
    char MathOperation = 0;
    int Key_Tam[11] = {0, 30, 6, 6, 6, 6, 6, 8, 6, 8, 0};
    char Key_Tab[10][31] = {
        {'0'},
        {'1', '@', '#', '$', '_', '&', '-', '+', '(', ')', '/', '*', '"', 39, ':', ';', '!', '?', '~', '`', '|', '.', '^', '=', '{', '}', 92, ' ', '%', '[', ']'},
        {'2', 'A', 'a', 'B', 'b', 'C', 'c'},
        {'3', 'D', 'd', 'E', 'e', 'F', 'f'},
        {'4', 'G', 'g', 'H', 'h', 'I', 'i'},
        {'5', 'J', 'j', 'K', 'k', 'L', 'l'},
        {'6', 'M', 'm', 'N', 'n', 'O', 'o'},
        {'7', 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's'},
        {'8', 'T', 't', 'U', 'u', 'V', 'v'},
        {'9', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z'}};
    byte KeyPadDisplay[53] = {0x02, 0x00, 0x31, 0x02, 0x1C, 0x8F, 0x2D, 0x29, 0x01, 0x0C, 0x27, 0x01, 0x01, 0x2A, 0x01, 0x64, 0x29, 0x01, 0x40, 0x27, 0x01, 0x01, 0x2A, 0x01, 0x64, 0x29, 0x0D, 0xC0,
                              0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x01, 0x01, 0x2A, 0x01, 0x64, 0x29, 0x01, 0x97, 0x27, 0x01, 0x01, 0x03};
};
#endif
