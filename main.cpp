#pragma once
#include <iostream>
#include <string>

using namespace std;

class String112 {
	char* str = nullptr;
	int len = 0;
public:
	String112() = default;

	String112(const char* str) {
		this->len = strlen(str);
		this->str = new char[this->len + 1];
		strcpy_s(this->str, this->len + 1, str);
	}

	explicit String112(int cnt, char s = '*') {
		this->len = cnt;
		this->str = new char[len + 1];
		for (int i = 0; i < len; i++) {
			this->str[i] = s;
		}
		this->str[len] = '\0';
	}

	String112(const char* str, int index) {
		this->len = index;
		this->str = new char[this->len + 1];
		for (int i = 0; i < this->len; i++) {
			this->str[i] = str[i];
		}
	}

	String112(const String112& str) {
		if (str.str != nullptr) {
			this->len = str.len;
			this->str = new char[this->len + 1];
			strcpy_s(this->str, this->len + 1, str.str);
		}
	}

	/*void setString(const char* str) {
		this->clear();
		if (str != nullptr) {
			this->len = strlen(str);
			char* n_str = new char[this->len + 1];
			strcpy_s(n_str, this->len + 1, str);
			this->str = n_str;
		}
	}*/

	String112& setString(const String112& right) {
		//s2.setString(s);
		this->clear();
		if (right.str != nullptr) {
			this->len = right.len;
			this->str = new char[this->len + 1];
			strcpy_s(this->str, this->len + 1, right.str);
		}
		return *this;
	}

	//s.getChar(int index)   // ���������� ��������� []
	char& operator[](int index) {
		return this->str[index];
	}

	// ���������� ��������� [] ��� ������������� � ����������� ������� � �������
	const char& operator[](int index) const {
		return this->str[index];
	}

	//  ���������� ������
	void addString(const String112& right) {
		//s.addString(s2);
		if (right.str == nullptr)
			return;
		if (this->str == nullptr) {
			this->setString(right);
			return;
		}
		this->len += right.len;
		char* n_str = new char[this->len + 1];
		strcpy_s(n_str, this->len + 1, this->str);
		strcat_s(n_str, this->len + 1, right.str);				//�������� right.str � ����� ������ n_str
		delete[] this->str;
		this->str = n_str;
	}

	// ������� ������
	void clear() {
		if (this->str != nullptr) {
			delete[] this->str;
			this->str = nullptr;
			this->len = 0;
		}
	}

	// ������ ������
	void printStr() const {
		if (this->str != nullptr)
			cout << this->str;
		cout << endl;
	}

	int lenght() const {
		return this->len;
	}

	// ����������
	~String112() {
		this->clear();
	}

	// +=
	String112& operator+=(const String112& s) {
		this->addString(s);
		return *this;
	}

	//  =
	String112& operator=(const String112& s) {
		// 1������ �� ����������������
		// ���������� ������� ���� �� �����������
		//if(this->str == s.str)
		if (this == &s)
			return *this;
		// 2 ����� �����������
		this->~String112();
		// 3 �������� ��� �� ������������ �����������
		if (s.str != nullptr) {
			this->len = s.len;
			this->str = new char[this->len + 1];
			strcpy_s(this->str, this->len + 1, s.str);
		}
		// ���������� ����
		return *this;
	}

	// ����������� �����������
	String112(String112&& obj) {
		swap(this->str, obj.str);
		swap(this->len, obj.len);
	}

	// �������� �����������
	String112& operator=(String112&& obj) {
		if (this == &obj)
			return *this;
		swap(this->str, obj.str);
		swap(this->len, obj.len);
		obj.clear();
		return *this;
	}

	//s.reverse() ���������� ������
	void reverse() {
		for (int i = 0; i < this->len / 2; i++) {
			swap(this->str[i], this->str[this->len - 1 - i]);
		}

	}

	//s.empty() ��������� ������ �� ������
	bool empty() const {
		return this->str == nullptr;
	}

	//s.replace('e','t'); �������� ��� ����� � �� t	
	void replace(char from, char to) {
		for (int i = 0; i < this->len; i++) {
			if (this->str[i] == from) {
				this->str[i] = to;
			}
		}

	}

	//remove('�') //������� ��� ��������� ������� �
	void remove(char a) {
		int count = 0;
		for (int i = 0; i < this->len; i++) {
			if (this->str[i] == a)
				count++;
		}
		char* n_str = new char[this->len - count + 1];
		for (int i = 0, k = 0; i < this->len + 1; i++) {
			if (this->str[i] != a) {
				n_str[k] = this->str[i];
				k++;
			}
		}
		this->len -= count;
		delete[]this->str;
		this->str = n_str;
	}

	//find('�'); //������ ������� ��������� ������� �	  //-1 - ��� �������, > -1 ��������������� ����� ������� �� 1		
	int find(char a) const {
		for (int i = 0; i < this->len; i++) {
			if (this->str[i] == a)
				return i + 1;
		}
		return -1;
	}

	//s.erase(index) ������� ������ �� ������
	void erase(int index) {
		if (this->str == nullptr)
			return;

		if (this->len < index || index == 0)
			return;

		char* n_str = new char[this->len];
		for (int i = 0, j = 0; i < this->len + 1; i++) {
			if ((i + 1) != index) {
				n_str[j] = this->str[i];
				j++;
			}
		}
		this->len--;
		delete[] this->str;
		this->str = n_str;
	}

	//s.insert(index,"hello") �������� � ������ ������ hello
	void insert(int index, const String112 right) {

		if (right.str == nullptr)
			return;
		if (this->str == nullptr) {
			this->setString(right);
			return;
		}

		if (this->len < index || index == 0)
			return;

		int n_len;
		n_len = this->len + right.len;
		char* n_str = new char[n_len + 1];
		for (int i = 0, k = 0; i < n_len + 1; i++) {
			if (i < index) {
				n_str[i] = this->str[i];
			}
			else if (i == index || i < index + right.len) {
				n_str[i] = right.str[k++];
			}
			else {
				n_str[i] = this->str[i - right.len];
			}
		}
		this->len = n_len + 1;
		delete[] this->str;
		this->str = n_str;
	}

	friend ostream& operator<<(ostream& os, const String112& s);
	friend istream& operator>>(ostream& is, String112& s);
	friend bool operator==(const String112& a, const String112& b);
	friend bool operator!=(const String112& a, const String112& b);
	friend bool operator>(const String112& a, const String112& b);
	friend bool operator<(const String112& a, const String112& b);
	friend bool operator>=(const String112& a, const String112& b);
	friend bool operator<=(const String112& a, const String112& b);
};


//���� ������� �� ����� ������������
//������� ����
// ���� � ���� ���������� ��������� ��� ��������� ����������, ���������� ������������� ����������� ����������� � ��� �������� ������������
// ���� ���� ��������� - ��� ��� ������ ����������!!!


//��������� ���� �� ����� � ����������� ==
bool operator==(const String112& a, const String112& b) {
	// ���� ��� �������� ��������� <, >= � �.�.
	if (a.len != b.len)
		return false;

	for (int i = 0; i < a.len; i++) {
		if (a.str[i] != b.str[i])
			return false;
	}
	return true;
}

// �������� ����� �� ����������� !=
bool operator!=(const String112& a, const String112& b) {
	if (a.len != b.len)
		return true;

	for (int i = 0; i < a.len; i++) {
		if (a.str[i] != b.str[i])
			return true;
	}
	return false;
}

// ��������� ����� >
bool operator>(const String112& a, const String112& b) {
	if (a.len > b.len)
		return true;
	else if (a.len < b.len)
		return false;

	for (int i = 0; i < a.len; i++) {
		if (a.str[i] > b.str[i]) {
			return true;
		}
	}
	return false;
}

// ��������� ����� <
bool operator<(const String112& a, const String112& b) {
	if (a.len < b.len)
		return true;
	else if (a.len > b.len)
		return false;

	for (int i = 0; i < a.len; i++) {
		if (a.str[i] < b.str[i]) {
			return true;
		}
	}
	return false;
}

// ��������� ����� >=
bool operator>=(const String112& a, const String112& b) {
	if (a == b || a > b)
		return true;
	return false;
}

// ��������� ����� <=
bool operator<=(const String112& a, const String112& b) {
	if (a == b || a < b)
		return true;
	return false;
}


ostream& operator<<(ostream& os, const String112& s) {
	//s.printStr();
	os << s.str;
	return os;
}

istream& operator>>(istream& is, String112& s) {
	char* str = new char[1000];
	//is.getline(str, 1000);											// ������� ��� ���������� ��������
	is >> str;
	s.setString(str);
	delete[]str;
	return is;
}

String112 operator+(const String112& s, const String112& b) {
	String112 tmp = s;
	tmp += b;
	return tmp;
}


void main()
{
	String112 s("l Welcome! Hello world");
	String112 s5("Hello , this is c++");
	String112 s6(" my friends");



	//s5.insert(6, s6);
	//cout << s5 << endl;
	//String112 s6 ="qwerty";
	//s5.addString(s6);
	//cout << s5 << endl;
	//cout << s << endl;
	//cout << s.find('a');
}

