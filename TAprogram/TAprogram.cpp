#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string toDop(int numPryam);
int to2(int num10);
int to10(int num2);

string toDop(int numPryam) //Перевод 2-чного в дополнительный код
{
	int num = 0, k = 0;
	while (numPryam != 0)
	{
		if (numPryam % 10 == 0) num += pow(10, k);
		numPryam /= 10;
		k++;
	}
	num = to10(num);
	num = to2(num + 1);
	string dop = to_string(num);
	while (dop.length() < 4) dop = "0" + dop;
	return dop;
}

int to2(int num10) //Перевод 10-чного в 2-чное
{
	int num10to2 = 0, j = 0;
	while (num10 != 0)
	{
		num10to2 += (num10 % 2) * pow(10, j);
		num10 /= 2;
		j++;
	}
	return num10to2;
}

int to10(int num2) //Перевод 2-чного в 10-чное
{
	int num2to10 = 0, i = 0;
	while (num2 != 0)
	{
		num2to10 += (num2 % 10) * pow(2, i);
		num2 /= 10;
		i++;
	}
	return num2to10;
}

string toPlav(long double num0) //Перевод 2-чного в формат с плавающей точкой
{
	int poryadok = 0;
	string znakS;
	if (num0 > 0) znakS = "0";
	else
	{
		znakS = "1";
		num0 = -num0;
	}
	while (num0 < 0.100000)
	{
		num0 *= 10;
		poryadok--;
	}
	while (num0 >= 1.000000)
	{
		num0 /= 10;
		poryadok++;
	}
	cout << "Порядок = " << poryadok << " Мантисса(прямой код) = " << znakS << "|" << to_string(num0).substr(0, 6) << endl;
	string poryadokS = to_string(to2(poryadok + 16)), mantissaS; //Порядок задаётся со смещением
	if (znakS == "1") mantissaS = toDop((int)round(num0 * 10000)); //При отрицательной мантиссе происходит перевод в доп код
	else mantissaS = to_string(num0).substr(2, 4); //При положительной мантиссе доп код = прям код
	while (poryadokS.length() < 5) poryadokS = "0" + poryadokS; //Дополнение длины порядка до 5 символов
	return (poryadokS + "|" + znakS + "|" + mantissaS); //Формирование числа в формате с плавающей точкой
}

int main()
{
	setlocale(LC_ALL, "rus");
	long double number2;
	cout << "/*Используйте значение 0 для выхода из программы.*/\n\nВведите 2-ичное число для перевода в формат с плавающей запятой:\n";
	cin >> number2;
	string number2S;
	bool is2 = true;
	int len2S;
	while (number2 != 0)
	{
		number2S = to_string(number2);
		if (number2S.substr(0, 1) == "-") number2S.erase(0, 1); //Удаление минуса числа для проверки остальных символов
		number2S.erase(number2S.find(","), 1);
		len2S = number2S.length();
		for (int i = 0; i < len2S; i++)
			if (number2S.substr(i, 1) != "0" and number2S.substr(i, 1) != "1") is2 = false; //Проверка на двоичность числа
		if (!is2) cout << "Введённое число не является 2-ичным\n";
		else cout << "Результат:\n" << toPlav(number2) << endl;
		cout << "\nВведите новое число для перевода в формат с плавающей запятой:\n";
		cin >> number2;
		is2 = true;
	}
	return 0;
}