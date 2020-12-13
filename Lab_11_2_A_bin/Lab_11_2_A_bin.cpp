#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

enum Specialty { ��, ��, ��, ��, �� };

string specialtyStr[] = { "��", "��", "��", "��", "��" };

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
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� �� ��������� ����� " << endl;
		cout << " [2] - ������������ �� ��������� �����" << endl;
		cout << " [3] - ���� ���������� ���������� ����" << endl;
		cout << " [4] - ���� ������� 4 � ������� ��������" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> ch;
		cout << endl << endl << endl;
		switch (ch)
		{
		case '0':
			break;
		case '1':
			cin.get(); 
			cin.sync(); 
			cout << "������ ��'� �����: "; cin.getline(fname, 61);
			EnterSave(fname);
			break;
		case '2':
			cin.get(); 
			cin.sync(); 
			cout << "������ ��'� �����: "; cin.getline(fname, 61);
			LoadPrint(fname);
			break;
		case '3':
			MinAverage(fname, MinAve);
			cout << "̳������� ������� ���: " << setprecision(2) << fixed << MinAve << endl;
			break;
		case '4':
			CountMarks(fname, countPhysics, countMathematics, countInformatics);
			cout << "ʳ������ 4 � ������: " << countPhysics << endl;
			cout << "ʳ������ 4 � ����������: " << countMathematics << endl;
			cout << "ʳ������ 4 � �����������: " << countInformatics << endl;
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
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
		cout << "������� � " << i + 1 << ":" << endl;
		++i;
		cin.sync();
		cout << "�������: "; 
		cin >> student.prizv;
		cout << "����: "; cin >> student.kurs;
		cout << "������������ (0 - ��, 1 - ��, 2 - ��, 3 - ��, 4 - ��): ";
		cin >> specialty;
		student.specialty = (Specialty)specialty;
		cout << "������ � ������: "; cin >> student.physics;
		cout << "������ � ����������: "; cin >> student.mathematics;
		cout << "������ � �����������: "; cin >> student.informatics;
		if (!f.write((char*)&student, sizeof(Student)))
		{
			cerr << "������� ������ �����" << endl;
		}
		cout << "����������? (Y/N) "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');
}

void LoadPrint(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "������� ���������� ����� '" << fname << "'" << endl;
		return;
	}

	Student student;
	int i = 0;

	cout << "==========================================================================="
		<< endl;
	cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | ����������� |"
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
		cerr << "������� ���������� ����� '" << fname << "'" << endl;
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
		cerr << "������� ���������� ����� '" << fname << "'" << endl;
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