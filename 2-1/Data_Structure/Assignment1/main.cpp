#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void divide(const int, const int, int&, int&);

int main(void)
{
	int num1, num2;
	int q, r;
	while(true)
	{
		try
		{
			cout << "몫과 나머지를 구하는 나눗셈 연산을 실행합니다.." << endl;
			cout <<"두 수 입력(공백 구분) : ";
			cin >> num1 >> num2;
			if(!num2)
				throw num2;
			divide(num1, num2, q, r);
			cout << "연산 성공.." << endl;
			cout << num1 << " / " << num2 << " = " << q << endl;
			cout <<	num1 << " % " << num2 << " = " << r << endl;
			cout << "프로그램 종료.." << endl;
			break;
		}
		catch(int n)
		{
			cout << n << "으로는 나눌 수 없습니다.." << endl;
			cout << "프로그램을 다시 실행합니다.." << endl << endl;
		}
	}
	return 0;
}
void divide(const int n1, const int n2, int& q, int& r)
{
	q = n1 / n2;
	r = n1 % n2;
}
