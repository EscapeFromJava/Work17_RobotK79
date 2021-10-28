#include <iostream>
#include <string>

using namespace std;
int count_of_substrings(string src, string sub);
int resetOrientation(int x);

int main()
{
	setlocale(LC_ALL, "rus");
	string way = "SSSSSSLSSSSSLSSSLSSSSLSSS";
	//проверка на лимит команд S
	int volS = count(way.begin(), way.end(), 'S'); 
	if (volS > 50) {
		cout << "Число шагов должно быть не более 50" << endl;
		return 0;
	}
	//проверка на общее число команд
	if (way.length() < 1 || way.length() > 200) {
		cout << "Число команд должно быть от 1 до 200" << endl;
		return 0;
	}
	string historyMove = "S0.0"; //история всех шагов
	string historyLastMove; //координаты последнего шага
	string historyCash; //история всех шагов за исключением последнего шага (требуется для функции count_of_substrings)

	int x = 0, y = 0; //начальные координаты
	int orientation = 0; //переменная для определения направления, где 0 - шаг вправо, 1 - шаг вверх, 2 - шаг влево, 3 - шаг вниз
	int countL = 0, countR = 0; //счетчики поворотов
	int step = 0; //счетчик шагов
	bool flag = false;
	for (int i = 0; i < way.length(); i++) {
		if (way[i] == 'S') {
			/*orientation = resetOrientation(orientation);*/
			if (orientation == 0) {
				x++;
				step++;
			}
			if (orientation == 1) {
				y++;
				step++;
			}
			if (orientation == 2) {
				x--;
				step++;
			}
			if (orientation == 3) {
				y--;
				step++;
			}
			historyLastMove = "S" + to_string(x) + "." + to_string(y); //записываем координаты последнего шага
			historyMove += "S" + to_string(x) + "." + to_string(y); //добавляет координаты посленего шага в историю
			historyCash = historyMove;
			historyCash.erase(historyMove.length() - 3, 3); //история всех шагов за исключением последнего шага (требуется для функции count_of_substrings)
			if (step > 1 && (count_of_substrings(historyCash, historyLastMove) > 0)) { //проверка на выполнение хотя бы 1 шага и поиск последних координат в истории
				if (countL >= 3 || countR >= 3) { //проверка на выполнение подряд 3 поворотов в одну сторону
					flag = true;
					break;
				}
			}
		}
		if (way[i] == 'L') { //условие для поворота налево
			orientation++;
			countL++;
			countR--;
		}
		if (way[i] == 'R') { //условие для поворота направо
			orientation--;
			countR++;
			countL--;
		}
		orientation = resetOrientation(orientation); //сброс ориентации при необходимости
	}
	if (flag)
		cout << "Будет сделано " << step << " шагов" << endl;
	else
		cout << "-1" << endl;
	return 0;
}

int count_of_substrings(string src, string sub) { //поиск последних координат в истории
	int start = 0;
	int count = 0;
	int pos = 0;
	for (;;) {
		pos = src.find(sub.c_str(), start);
		if (pos != -1) {
			start = pos + sub.size();
			count++;
		}
		else {
			break;
		}
	}
	return count;
}

int resetOrientation(int x) //сброс ориентации при необходимости
{
	if ((x == 4) || (x == -4)) {
		x = 0;
	}
	if ((x == 5) || (x == -3)) {
		x = 1;
	}
	if ((x == 6) || (x == -2)) {
		x = 2;
	}
	if ((x == 7) || (x == -1)) {
		x = 3;
	}
	return x;
}

//примеры:
//SSLSLSLSSRSRS = 5
//LSSSS = -1
//SRSLSSLSSSLSLSSLS = 11
//SSSSSSLSSSSSLSSSLSSSSLSSS = 21
//SSLSSSSLSLSSRSRSSSRSSSRSSSSSSRSSSRS = 26
//SSSSSRSSSSSRSSSSSRSSSSRSSSSRSSSRSSSRSSRSSRSRSRS = 36