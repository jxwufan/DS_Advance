/*
 * main.cpp
 *
 *  Created on: 2014年11月29日
 *      Author: tom
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>

using namespace std;

int n;
int b;

int main()
{
    
	srand(time(0));
	n = rand() % 32768  ;
        fprintf(stdout, "%d\n", n);
    freopen("test.in", "w", stdout);
        bool flag = false;
	int i,j,k;
        char state = 'I';
        int counter = 0;
	while (n >= counter)
	{
                if (!flag)
                {
                    flag = true;
                    cout << state << endl;
                }
		if (state == 'I')
		{
			i = rand() % 20000+1;
			j = rand() % 20000+1;
			k = rand() % 10000+1;
			cout << i << ' ' << j << ' ' << k << endl;
                        counter++;
		}
		else
		{
			i = rand() % 20000+1;
			if (i!=20000) j = rand() % (20000 - i) + i + 1;
                        else j = 20000;
			cout << i << ' ' << j << ' ';
			i = rand() % 20000+1;
			if (i!=20000) j = rand() % (20000 - i) + i + 1;
                        else j = 20000;
			cout << i << ' ' << j << endl;
		}
		n--;
                k = rand() % 100;
                if (k > 90)
                {
                    if (state == 'I') state = 'Q';
                    else state = 'I';
                    cout << state << endl;
                }
	}
	cout << "E" << endl;
	return 0;
}


