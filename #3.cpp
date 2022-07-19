

#include <iostream>
using namespace std;
int main()
{
	int n, k = 1, s = 2;
	cin >> n;
	while (k < n)
	{
		k += s;
		s++;
	}
	cout << k - n + 1;
}