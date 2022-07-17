
#include <iostream>
using namespace std;
int main()
{
	int n, max = 0;
	cin >> n;
	cin >> max;
	for (int i = 0; i < n - 1; i++)
	{
		int a;
		cin >> a;
		if (a > max)max = a;
	}
	cout << max;
	return 0;
}