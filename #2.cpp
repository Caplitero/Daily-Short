
#include <iostream>
using namespace std;
int main()
{
	int n, p = 1;
	bool ok = 0;
	cin >> n;
	while (n != 0)
	{
		int c = n % 10;
		n /= 10;
		if (c % 2)
		{
			ok = 1;
			p = c * p;
		}

	}
	if (!ok)p = -1;
	cout << p;

	return 0;
}