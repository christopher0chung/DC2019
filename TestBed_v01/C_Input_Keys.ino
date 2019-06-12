// Keypad libraries
#include <Keypad.h>
#include <Keypad_MC17.h>    // I2C i/o library for Keypad
#include <Wire.h>           // I2C library for Keypad_MC17

class C_Input_Keys
{
  public:
    Key keys[LIST_MAX];

    Keypad_MC17 kpd = Keypad_MC17( makeKeymap(keymap), rowPins, colPins, ROWS_key, COLS_key, I2CADDR );    // modify constructor for I2C i/o

    char keymap[ROWS_key][COLS_key] = {
      {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
      {'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'},
      {'q', 'r', 's', 't', 'u', 'v', 'w', 'x'},
      {'1', '2', '3', '4', '5', '6', '7', '8'}
    };

    void Prep()
    {
      // Keypad setup
      Serial.begin(9600);
      kpd.begin( );            // also starts wire library
      kpd.setDebounceTime(1);
    }

    void Update()
    {
      if (kpd.getKeys())
      {
        for (int i = 0; i < LIST_MAX; i++)
        {
          keys[i] = kpd.key[i];
        }
      }
    }

    int RowFromChar(char c)
    {
      if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h')
        return 0;
      else if (c == 'i' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'o' || c == 'p')
        return 1;
      else if (c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' || c == 'x')
        return 2;
      else if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8')
        return 3;
    }

    int ColFromChar(char c)
    {
      if (c == 'a' || c == 'i' || c == 'q' || c == '1')
        return 0;
      else if (c == 'b' || c == 'j' || c == 'r' || c == '2')
        return 1;
      else if (c == 'c' || c == 'k' || c == 's' || c == '3')
        return 2;
      else if (c == 'd' || c == 'l' || c == 't' || c == '4')
        return 3;
      else if (c == 'e' || c == 'm' || c == 'u' || c == '5')
        return 4;
      else if (c == 'f' || c == 'n' || c == 'v' || c == '6')
        return 5;
      else if (c == 'g' || c == 'o' || c == 'w' || c == '7')
        return 6;
      else if (c == 'h' || c == 'p' || c == 'x' || c == '8')
        return 7;
    }

    void StoreModel()
    {
      for (int i = 0; i < ROWS_key; i++)
      {
        for (int j = 0; j < COLS_key; j++)
        {
          Model_Key_Last[i][j] = Model_Key_Current[i][j];
        }
      }
    }

    void PrimeModel()
    {
      for (int i = 0; i < ROWS_key; i++)
      {
        for (int j = 0; j < COLS_key; j++)
        {
          Model_Key_Current[i][j] = IDLE;
        }
      }
    }

    void UpdateModel()
    {
      for (int i = 0; i < LIST_MAX; i++)
      {
        if (kpd.key[i].kcode != -1)
        {
          char c = kpd.key[i].kchar;
          int row = RowFromChar(c);
          int col = ColFromChar(c);
          Model_Key_Current[row][col] = kpd.key[i].kstate;
        }
      }
    }

  private:
    byte rowPins[ROWS_key] = {8, 9, 10, 11}; //connect to the row pinouts of the kpd
    byte colPins[COLS_key] = {0, 1, 2, 3, 4, 5, 6, 7}; //connect to the column pinouts of the kpd
};