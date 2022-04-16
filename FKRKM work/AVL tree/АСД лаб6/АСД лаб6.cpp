#include <iostream>
#include <regex>
#include <windows.h>

using namespace std;

struct node
{
    int info;
    int h;
    node* left;
    node* right;
};

int correct_input() //перевірка коректного вводу
{ 
	const regex regular("^[-+]?[0-9]*[.,]?[0-9]+(?:[eE][-+]?[0-9]+)?");
	smatch m;
	string number;

	while (true) {
		cin >> number;
		if (regex_match(number, m, regular)) {
			break;
		}
		cout << "\t\tВведiть ще раз: ";
	}

	return stoi(number);
}

void print_tree(node* p, int level)
{
	if (p) {
		print_tree(p->right, level + 1);

		for (int i = 0; i < level; i++) cout << "   ";
		cout << p->info << endl;

		print_tree(p->left, level + 1);
	}
}

int height(node* p)
{
    return p ? p->h : 0;
}

int bfactor(node* p)
{
    return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
    int h1 = height(p->left);
    int h2 = height(p->right);
    if (h1 > h2) p->h = h1 + 1;
    else p->h = h2 + 1;
}

node* rotateright(node* p) // правий поворот навколо p
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q) // лівий поворот навколо q
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не потрібна
}

node* insert(node* p, int k) // вставка ключа k в дерево з корнем p
{
    if (p == NULL)
    {
        p = new node;
        p->info = k;
        p->h = 0;
        p->left = NULL;
        p->right = NULL;
    }
    else
        if (k < p->info)
            p->left = insert(p->left, k);
        else
            p->right = insert(p->right, k);

    return balance(p);
}

node* create_balance_tree() //формування дерева
{
	node* p = nullptr;
	int k;
	char choice;

	do
	{
		cout << "\n\t\tВведіть інформативну частину дерева: ";
		k = correct_input();

		p = insert(p, k);

		cout << "\n\t\tПродовжити ? (y - так, інша клавіша - ні): ";
		cin >> choice;
		cin.ignore();
	}
	while (choice == 'y');

	cout << "\n\t\tСТВОРЕНЕ ДЕРЕВО\n\n";
	print_tree(p, 1);

	return p;
}

int search(node* p, int value)
{
	while (p != NULL)
	{
		if (p->info == value)
			return true;
		else if (value < p->info)
			p = p->left;
		else
			p = p->right;
	}
	return false;
}

void search_tree(node* p)
{
	int value;

	cout << "\n\t\tВведіть елемент, який будемо шукати: ";
	value = correct_input();

	if (search(p, value))
		cout << "\n\t\tЕлемент \"" << value << "\" знайдено в дереві.";
	else
		cout << "\n\t\tЕлемент \"" << value << "\" не знайдено в дереві.";
}

node* delete_tree(node* bale)
{
	node* work;
	work = bale;
	if (work->left != NULL) work->left = delete_tree(work->left);
	if (work->right != NULL) work->right = delete_tree(work->right);
	delete work; bale = NULL; return (bale);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	node* root = nullptr;

	int choice;
	do {
		cout << "\n\n\t\t\tМЕНЮ РОБОТИ З БІНАРНИМ ДЕРЕВОМ\n\n"
			<< "\t1. Формування збалансованого бінарного дерево\n\n"
			<< "\t2. Виведення дерева\n\n"
			<< "\t3. Пошук елемента в дереві\n\n"
			<< "\t4. Видалення дерева\n\n"
			<< "\t0. Вихiд з програми"
			<< "\n\n\tВаш вибiр: ";

		choice = correct_input();
		switch (choice) {
		case 1: {
			system("cls");
			if (root == nullptr)
				root = create_balance_tree();
			else
				cout << "\n\n\t\tСпочатку видаліть дерево.";
			cout << "\n\n";

			system("pause");
			break;
		}

		case 2: {
			system("cls");
			if (root != nullptr)
			{
				cout << endl << "\t\t\t\tВИ ВВЕЛИ" << "\n\t\t" << endl;;
				print_tree(root, 1);
			}
			else
				cout << "\n\n\t\tСпочатку введіть дерево.";
			cout << "\n\n";
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			if (root != nullptr)
			{
				search_tree(root);
			}
			else
				cout << "\n\n\t\tСпочатку введіть дерево.";
			cout << "\n\n";
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			if (root != nullptr)
			{
				print_tree(root, 1);
				cout << "\n\t\tДЕРЕВО ВИДАЛЕНО";
				delete_tree(root);
				root = NULL;
			}
			else
				cout << "\n\n\t\tСпочатку введіть дерево.";
			cout << "\n\n";
			system("pause");
			break;
		}
		case 0: {
			cout << "\n\n";
			system("pause");
			break;
		}
		}
		system("cls");
	} while (choice);

	if (root != nullptr) {
		delete root;
	}

	cout << "\n\t\tКінець програми!" << "\n";
	system("pause");
}

