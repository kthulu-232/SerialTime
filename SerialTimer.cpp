#include <Arduino.h>
#include "SerialTimer.h"
extern Timer clock1;
extern Timer clock2;
extern Timer clock3;

String inStr = "";
bool isStr = false;
/* -------------------------- Funciones de la clase ------------------------- */

Timer::Timer(int _pin)
{
    pin = _pin;
    pinMode(pin, OUTPUT);
}

void Timer::start_timer(void)
{
    if ((_current - _past >= isTime) && isTime > 0)
    {
        Serial.println("Time finished");
        digitalWrite(pin, !digitalRead(pin));
        on_off = true;
        isTime = 0;
    }
}

float Timer::timer_register()
{
    return isTime / 60000;
}

void Timer::set_timer(float time, unsigned long isPast)
{
    isTime = time * 60000;
    _past = isPast;
}

bool Timer::get_valor(void)
{
    _current = millis();
    start_timer();
    return on_off;
    if (on_off == true)
    {
        on_off = false;
    }
}

void Timer::switch_pin(bool estado)
{
    digitalWrite(pin, estado);
}

bool Timer::get_pin(void)
{
    bool _status;
    _status = digitalRead(pin);
    return _status;
}

/* --------------------- Menu para el control de timers --------------------- */

void menu(void)
{
    Serial.println("------------Timer-------------\n");
    Serial.println("1.Set Time\n2.ON_OFF Output\n");
    Serial.println("-------------------------------\n");
}

float Read_time(void)
{
    char inTime;
    float time_out = 0;
    if (Serial.available() > 0)
    {
        inTime = (char)Serial.read();
        inStr += inTime;
        if (inTime == '\n')
        {
            isStr = true;
        }
    }
    if (isStr)
    {
        time_out = inStr.toFloat();
        Serial.println("Time: ");
        Serial.print(time_out);
        Serial.print(" minutes\n");
        inStr = "";
        isStr = false;
    }
    return time_out;
}

int pin_select(void)
{
    char inTime;
    int time_out = 60;
    if (Serial.available() > 0)
    {
        inTime = (char)Serial.read();
        inStr += inTime;
        if (inTime == '\n')
        {
            isStr = true;
        }
    }
    if (isStr)
    {
        time_out = inStr.toInt();
        if (time_out > 0)
        {
            Serial.println("Selected timer: ");

            Serial.print(time_out);
        }
        inStr = " ";
        isStr = false;
    }
    return time_out;
}

void rx_menu(int n_timers)
{
    int isPin;
    float Time;
    int serial_on_off;
    unsigned long past;
    char _command;
    bool flag = false;
    if (Serial.available() > 0) //
    {
        _command = (char)Serial.read();
        flag = true;
    }
    if (flag == true)
    {
        flag = false;
        switch (_command)
        {
        case '1':
            Serial.println("Select a timer");
            _n_timers(n_timers);
            while (true)
            {
                isPin = pin_select();
                if (isPin > 0 && isPin < 60)
                {
                    break;
                }
            }
            Serial.println("\nEnter time:");
            while (true)
            {
                Time = Read_time();
                if (Time > 0.0)
                {
                    past = millis();
                    Serial.println("\nThe timer has started");
                    switch (isPin) // Aqui puedes agregar los casos que necesites
                    {
                    case 1:
                        clock1.set_timer(Time, past);
                        break;
                    case 2:
                        clock2.set_timer(Time, past);
                        break;
                    case 3:
                        clock3.set_timer(Time, past);
                        break;
                    }
                    menu();
                    break;
                }
            }
            break;
        case '2':
            Serial.println("Select a timer");
            _n_timers(n_timers);
            while (true)
            {
                isPin = pin_select();
                if (isPin > 0 && isPin < 60)
                {
                    break;
                }
            }
            Serial.println("\n0.OFF\n1.ON");
            while (true)
            {
                serial_on_off = pin_select();
                if (serial_on_off == 0 || serial_on_off == 1)
                {
                    Serial.println("\nOutput is on: ");
                    switch (isPin) // aqui tambien debes añadir el numero de casos necesarios
                    {
                    case 1:
                        clock1.switch_pin(serial_on_off);
                        Serial.println(clock1.get_pin());
                        break;
                    case 2:
                        clock2.switch_pin(serial_on_off);
                        Serial.println(clock2.get_pin());
                        break;
                    case 3:
                        clock3.switch_pin(serial_on_off);
                        Serial.println(clock3.get_pin());
                        break;
                    default:
                        Serial.println("Error");
                        break;
                    }
                    menu();
                    break;
                }
            }

            break;
        }
    }
}

void _n_timers(int __n)
{
    for (int z = 1; z <= __n; z++)
    {
        Serial.print(z);
        Serial.print(".Timer ");
        Serial.print(z);
        Serial.println("");
    }
}