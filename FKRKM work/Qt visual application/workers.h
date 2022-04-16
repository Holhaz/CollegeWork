#ifndef WORKERS_H
#define WORKERS_H

#include <QMainWindow>

class workers
{
private:
    QString surname;
    int hours_worked;
    int hourly_traffic;
    int number_dependents;
    double salary;
public:
    workers();
    workers(QString, int, int, int);
    QString get_surname();
    int get_hours_worked();
    int get_hourly_traffic();
    int get_number_dependents();
    double get_salary();
    double calcul_salary();
    QString toString();
};

#endif // WORKERS_H
