/* -------------------------------------------------------------------------- */
/*                                Serial Timer                                */
/* -------------------------------------------------------------------------- */
/*
Esta libreria fue creada para poder  establcer un temporizador a un pin usado 
como salida y poder cambiar su estado en un tiempo determinado.

Si deseas usar mas de 3 timer puedes modificar el switch de los casos 1 y 2 de rx_menu,
agregando los timers que requieras 

para los objetos del timer declaralos  como clock'n'
*/
#ifndef SeriaTimer_h
#define SerialTimer_h
#include <Arduino.h>
#include <string.h>

/* -------------------------------- Funciones ------------------------------- */

float Read_time(void);
int pin_select(void);
void menu(void);
int pin_change(void);
void timers_display(void);
void rx_menu(int n_timers);
void _n_timers(int __n);

/* ---------------------------------- Clase --------------------------------- */

class Timer
{
public:
    Timer(int);
    void set_timer(float, unsigned long);
    void start_timer(void);
    bool get_valor(void);
    void switch_pin(bool);
    bool get_pin(void);
    float timer_register(void);

private:
    double isTime;
    unsigned long _current, _past;
    float Time;
    int pin;
    bool on_off = false;
};

#endif