#ifndef KP6_NEW_PASSENGER_H
#define KP6_NEW_PASSENGER_H
struct passenger{
char surname[32]; //фамилия
char name[3]; //инициалы
int Nbaggage; //количество вещей
int Wbaggage; //общий вес вещей
char destination[32]; //пункт назначения
char timedep[32]; //время вылета
char transfer[3]; //наличие пересадок(да/нет)
int children; //информация о детях(их количество)
};
typedef struct passenger passenger;
#endif