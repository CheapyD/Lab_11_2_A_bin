#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

enum Specialty { КН, ІТ, ПЗ, ВП, СА };

string specialtyStr[] = { "КН", "ІТ", "ПЗ", "ВП", "СА" };

struct Student
{
	char prizv[64];
	int kurs;
	Specialty specialty;
	int physics;
	int mathematics;
	int informatics;
};

void EnterSave(char* fname);
void LoadPrint(char* fname);
void CountMarks(char* fname, int& countPhysics, int& countMathematics, int& countInformatics);
void MinAverage(char* fname, double& MinAve);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char fname[61];
	char ch;
	double MinAve = 0.0;
	int countPhysics = 0;
	int countMathematics = 0;
	int countInformatics = 0;
	do
	{
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення та зберігання даних " << endl;
		cout << " [2] - завантаження та виведення даних" << endl;
		cout << " [3] - вивід найменшого середьного балу" << endl;
		cout << " [4] - вивід кількості 4 з кожного предмету" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> ch;
		cout << endl << endl << endl;
		switch (ch)
		{
		case '0':
			break;
		case '1':
			cin.get(); 
			cin.sync(); 
			cout << "Введіть ім'я файлу: "; cin.getline(fname, 61);
			EnterSave(fname);
			break;
		case '2':
			cin.get(); 
			cin.sync(); 
			cout << "Введіть ім'я файлу: "; cin.getline(fname, 61);
			LoadPrint(fname);
			break;
		case '3':
			MinAverage(fname, MinAve);
			cout << "Мінімальне середній бал: " << setprecision(2) << fixed << MinAve << endl;
			break;
		case '4':
			CountMarks(fname, countPhysics, countMathematics, countInformatics);
			cout << "Кількість 4 з фізики: " << countPhysics << endl;
			cout << "Кількість 4 з математики: " << countMathematics << endl;
			cout << "Кількість 4 з інформатики: " << countInformatics << endl;
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (ch != '0');

	system("pause");
	return 0;
}

void EnterSave(char* fname)
{
	ofstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}

	Student student;

	int specialty;
	char ch;
	int i = 0;
	do
	{
		cout << endl;
		cout << "Студент № " << i + 1 << ":" << endl;
		++i;
		cin.sync();
		cout << "Прізвище: "; 
		cin >> student.prizv;
		cout << "Курс: "; cin >> student.kurs;
		cout << "Спеціальність (0 - КН, 1 - ІТ, 2 - ПЗ, 3 - ВП, 4 - СА): ";
		cin >> specialty;
		student.specialty = (Specialty)specialty;
		cout << "Оцінка з фізики: "; cin >> student.physics;
		cout << "Оцінка з математики: "; cin >> student.mathematics;
		cout << "Оцінка з інформатики: "; cin >> student.informatics;
		if (!f.write((char*)&student, sizeof(Student)))
		{
			cerr << "Помилка запису файлу" << endl;
		}
		cout << "Продовжити? (Y/N) "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');
}

void LoadPrint(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка зчитування файлу '" << fname << "'" << endl;
		return;
	}

	Student student;
	int i = 0;

	cout << "==========================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Інформатика |"
		<< endl;
	cout << "---------------------------------------------------------------------------"
		<< endl;
	while (f.read((char*)&student, sizeof(Student)))
	{
		cout << "| " << setw(1) << right << i + 1 << " "; 
		cout << "| " << setw(9) << left << student.prizv
			 << "| " << setw(4) << left << student.kurs << " "
			 << "| " << setw(14) << left << specialtyStr[student.specialty]
			 << "| " << setw(6) << left << student.physics << " "
			 << "| " << setw(10) << left << student.mathematics << " "
			 << "| " << setw(11) << left << student.informatics << " " << "|" << endl;
		cout << "---------------------------------------------------------------------------"
			 << endl;
		++i;
	}
}

void CountMarks(char* fname, int& countPhysics, int& countMathematics, int& countInformatics)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка зчитування файлу '" << fname << "'" << endl;
		return;
	}

	Student student;

	countPhysics = 0;
	countMathematics = 0;
	countInformatics = 0;

	while (f.read((char*)&student, sizeof(Student)))
	{
		if (student.physics == 4)
			countPhysics++;
		if (student.mathematics == 4)
			countMathematics++;
		if (student.informatics == 4)
			countInformatics++;
	}
}

void MinAverage(char* fname, double& MinAve)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка зчитування файлу '" << fname << "'" << endl;
		return;
	}

	Student student;

	while (f.read((char*)&student, sizeof(Student)))
	{
		double average = (student.physics + student.mathematics + student.informatics) / 3.;
		MinAve = average;
		if (MinAve > average)
			MinAve = average;
	}
}