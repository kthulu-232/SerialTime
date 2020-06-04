#include <Arduino.h>
#include <string.h>
#include "SerialTimer.h"
//* Objects
Timer clock1(2);
Timer clock2(3);
Timer clock3(4);
//* Variables
bool TX_flag = false;
char incommand;

void setup()
{
  Serial.begin(115200);
  menu();
}

void loop()
{
  rx_menu(3); // menu to configure  timers and configure how many timers there are

  clock1.get_valor(); // read if the time is complete
  clock2.get_valor();
}
