#include "workers.h"

using namespace std;

workers::workers()
{
    surname = "";
    hours_worked = 0;
    hourly_traffic = 0;
    number_dependents = 0;
}

workers::workers(QString surname, int hours_worked, int hourly_traffic, int number_dependents)
{
    this->surname = surname;
    this->hours_worked = hours_worked;
    this->hourly_traffic = hourly_traffic;
    this->number_dependents = number_dependents;  
}

QString workers::get_surname(){return this->surname;}
int workers::get_hours_worked() {return this->hours_worked;}
int workers::get_hourly_traffic() {return this->hourly_traffic;}
int workers::get_number_dependents () {return this->number_dependents;}
double workers::get_salary(){return this->salary;};

double workers::calcul_salary()
{
    salary = hours_worked * hourly_traffic;

    salary -= salary * 0.03;

    if(number_dependents == 0)
        salary -= salary * 0.16;
    else if(number_dependents == 1)
        salary -= salary * 0.1;
    else
        salary -= salary * 0.07;

    return salary;
}

QString workers::toString()
{
    return QString("Прізвище: ") + surname + "; "
             + "Кількість відпрацьованих годин: " + QString::number(hours_worked) + "; "
             + "Погодинний тариф: " + QString::number(hourly_traffic) + "; "
             + "Кількість утриманців: " + QString::number(number_dependents) + "; "
             + "Заробітна плата: " + QString::number(calcul_salary()) + ".";
}
