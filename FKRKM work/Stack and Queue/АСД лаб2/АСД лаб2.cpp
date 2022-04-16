#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <regex> 

struct List
{
	int d;
	List* next;
};

//прототипи
void input_queue(List**, List**);

void queue_processing(List**, List**, List**);

void stack_processing(List**);

void del_el_list(List**);

int correct_input();

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	List* pfirst = NULL, * plast = NULL, * pstack_f = NULL;
	List** first = &pfirst; //вказівник на вказівник на "голову черги"
	List** last = &plast; //вказівник на вказівник на "хвіст черги»"
	List** stack_f = &pstack_f; //вказівник на вказівник на початок стеку
	int b;
	do
	{
		cout << "\n\n\t\t\tМЕНЮ РОБОТИ З ЧЕРГОЮ І СТЕКОМ\n\n"
			<< "\t1. Формування черги\n\n"
			<< "\t2. Обробка черги\n\n"
			<< "\t3. Обробка стеку\n\n"
			<< "\t4. Видалення стеку\n\n"
			<< "\t0. Вихiд з програми"
			<< "\n\n\tВаш вибiр: ";

		b = correct_input();

		switch (b) //меню вибору
		{
		case 1:
		{
			input_queue(first, last);
			break;
		}
		case 2:
		{
			if (*first)
			{
				queue_processing(first, last, stack_f);
			}
			else
			{
				cout << "\n\n\t\tЧерга пуста.";
			}
			cout << "\n\n";
			system("pause");
			break;
		}
		case 3:
		{
			if (*stack_f)
			{
				stack_processing(stack_f);
			}
			else
			{
				cout << "\n\n\t\tCтек пустий.";
			}
			cout << "\n\n";
			system("pause");
			break;
		}
		case 4:
		{
			if (*stack_f)
			{
				del_el_list(stack_f);
			}
			else
			{
				cout << "\n\n\t\tCтек пустий.";
			}
			cout << "\n\n";
			system("pause");
			break;
		}
		case 0:
		{
			break;
		}
		}
		system("cls");
	} while (b);

	cout << "\n\t\tДо побачення!" << "\n";
	system("pause");
}

void input_queue(List** first, List** last) 
{
	List* work;
	List* f = *first; //фіксуємо адресу початку черги
	List* l = *last; //фіксуємо адресу кінця черги

	char c = 'y';
	while (c == 'y') //Формування черги поки цього хоче користувач
	{
		if (f == NULL && l == NULL) //Створення черги
		{
			work = new List;
			work->next = NULL;
			f = work; l = work;
			cout << "\n\t\tВведіть елемент: ";
			work->d = correct_input();
		}
		else
		{
			work = new List;
			work->next = NULL;
			l->next = work;
			cout << "\n\t\tВведіть елемент: ";
			work->d = correct_input();
			l = work;
		}

		*first = f; //повертаємо адресу початку черги
		*last = l; //повертаємо адресу кінця черги

		cout << "\n\t\tПродовжити ? y - так, інша клавіша - ні: ";
		cin >> c;
	}
	cin.ignore();
}

void queue_processing(List** first, List** last, List** stack_f) //обробка черги
{
	List* work, * stack;
	List* f = *first; //фіксуємо адресу початку черги
	List* s_f = *stack_f; //фіксуємо адресу початку стеку
	float P = 1;
	bool flag = false, flag2 = false; //флаг для перевірки наявності від’ємних елементів

	cout << endl << "\t\t\t\tОБРОБКА СТЕКУ" << "\n\t\t";
	while (f)
	{
		if (f->d < 0) //якщо від’ємні елементи, то рахуємо їх добуток
		{
			P *= f->d;
			flag = true;
		}
		else if (f->d > 0) //якщо додатні елементи, то поміщаємо в стек
		{
			stack = new List;
			stack->next = s_f;
			s_f = stack;
			stack->d = f->d;
			flag2 = true;
		}
		work = f;
		f = f->next;
		delete work; //видалення з черги
	};

	*last = *first = f; //повертаємо адресу початку і кінця черги (NULL)
	*stack_f = s_f; //повертаємо адресу початку стеку
	//if (flag) //перевірка на наявність від’ємних елементів 
	//	cout << "\n\t\tДобуток від’ємних елементів черги: " << P;
	//else
	//	cout << "\n\t\tВід’ємних елементів черги не виявлено.";
	if (!flag2) //перевірка на наявність додатніх елементів 
		cout << "\n\t\tДодатніх елементів не виявлено.";
}

void stack_processing(List** stack_f) //обробка стеку
{
	cout << endl << "\t\t\t\tОБРОБКА СТЕКУ" << "\n\t\t";
	List* s_f = *stack_f, *work; //фіксуємо адресу початку стеку
	int length = 0;
	while (s_f) //підрахунок кількісті елементів в стеку
	{
		work = s_f;
		length++;
		s_f = s_f->next;
		delete work; //видалення з стеку
	};
	*stack_f = s_f; //повертаємо адресу початку стеку
	cout << "\n\t\tКількість елементів стеку: " << length;
}

void del_el_list(List** stack_f) //видалення стеку
{
	List* s_f = *stack_f, * work2;
	while (s_f) 
	{
		work2 = s_f;
		s_f = s_f->next;
		delete work2;
	}
	*stack_f = s_f;  //повертаємо адресу початку стеку (NULL)
}

int correct_input() //перевірка коректного вводу
{
	const regex regular("(\\+|-)?[[:digit:]]+");
	smatch m;
	string number;
	while (true) {
		cin >> number;
		if (regex_match(number, m, regular)) {
			break;
		}
		cout << "\n\t\tПомилка. Спробуйте знову: ";
	}
	return stoi(number);
}
