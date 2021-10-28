#include <iostream>
#include <string>

using namespace std;
int count_of_substrings(string src, string sub);
int resetOrientation(int x);

int main()
{
	setlocale(LC_ALL, "rus");
	string way = "SSSSSSLSSSSSLSSSLSSSSLSSS";
	//�������� �� ����� ������ S
	int volS = count(way.begin(), way.end(), 'S'); 
	if (volS > 50) {
		cout << "����� ����� ������ ���� �� ����� 50" << endl;
		return 0;
	}
	//�������� �� ����� ����� ������
	if (way.length() < 1 || way.length() > 200) {
		cout << "����� ������ ������ ���� �� 1 �� 200" << endl;
		return 0;
	}
	string historyMove = "S0.0"; //������� ���� �����
	string historyLastMove; //���������� ���������� ����
	string historyCash; //������� ���� ����� �� ����������� ���������� ���� (��������� ��� ������� count_of_substrings)

	int x = 0, y = 0; //��������� ����������
	int orientation = 0; //���������� ��� ����������� �����������, ��� 0 - ��� ������, 1 - ��� �����, 2 - ��� �����, 3 - ��� ����
	int countL = 0, countR = 0; //�������� ���������
	int step = 0; //������� �����
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
			historyLastMove = "S" + to_string(x) + "." + to_string(y); //���������� ���������� ���������� ����
			historyMove += "S" + to_string(x) + "." + to_string(y); //��������� ���������� ��������� ���� � �������
			historyCash = historyMove;
			historyCash.erase(historyMove.length() - 3, 3); //������� ���� ����� �� ����������� ���������� ���� (��������� ��� ������� count_of_substrings)
			if (step > 1 && (count_of_substrings(historyCash, historyLastMove) > 0)) { //�������� �� ���������� ���� �� 1 ���� � ����� ��������� ��������� � �������
				if (countL >= 3 || countR >= 3) { //�������� �� ���������� ������ 3 ��������� � ���� �������
					flag = true;
					break;
				}
			}
		}
		if (way[i] == 'L') { //������� ��� �������� ������
			orientation++;
			countL++;
			countR--;
		}
		if (way[i] == 'R') { //������� ��� �������� �������
			orientation--;
			countR++;
			countL--;
		}
		orientation = resetOrientation(orientation); //����� ���������� ��� �������������
	}
	if (flag)
		cout << "����� ������� " << step << " �����" << endl;
	else
		cout << "-1" << endl;
	return 0;
}

int count_of_substrings(string src, string sub) { //����� ��������� ��������� � �������
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

int resetOrientation(int x) //����� ���������� ��� �������������
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

//�������:
//SSLSLSLSSRSRS = 5
//LSSSS = -1
//SRSLSSLSSSLSLSSLS = 11
//SSSSSSLSSSSSLSSSLSSSSLSSS = 21
//SSLSSSSLSLSSRSRSSSRSSSRSSSSSSRSSSRS = 26
//SSSSSRSSSSSRSSSSSRSSSSRSSSSRSSSRSSSRSSRSSRSRSRS = 36