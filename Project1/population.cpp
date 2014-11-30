#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

int const N = 20001;
char buffer[100];
char state;
map<int, int> bitArray[N];
bool flag;

int lowbit(int t)
{
    return t & (-t);
}

void modify(int i, int j, int delta)
{
    for (int x = i; x < N; x += lowbit(x))
        for (int y = j; y < N; y += lowbit(y))
            bitArray[x][y] += delta;
}

int sumOfRectangle(int i, int j)
{
    if (i == 0 || j == 0) return 0;
    int sum = 0;
    for (int x = i; x > 0; x -= lowbit(x))
        for (int y = j; y > 0; y -= lowbit(y))
            if (bitArray[x].find(y) != bitArray[x].end())
                sum += bitArray[x][y];
    return sum;
}

int query(int x1, int x2, int y1, int y2)
{
    return sumOfRectangle(x2, y2) - sumOfRectangle(x1 - 1, y2) - sumOfRectangle(x2, y1 - 1) + sumOfRectangle(x1 - 1, y1 - 1);
}

int main()
{
    flag = false;
    for (;;)
    {
        for (int i = 1; i < N; i++)
            bitArray[i].clear();
        for(;;)
        {
            if (gets(buffer) == NULL) flag = true;
            if (flag) break;
            if (strlen(buffer) == 1)
            {
                if (buffer[0] == 'E') break;
                state = buffer[0];
            }
            else
            if (buffer[0] >= '0' && buffer[0] <= '9')
            {
                int x1 = 0, x2 = 0, y1 = 0, y2 = 0, N = 0;
                if (state == 'I')
                {
                    sscanf(buffer, "%d%d%d", &x1, &y1, &N);
                    modify(x1, y1, N);
                }
                else
                {
                    sscanf(buffer, "%d%d%d%d", &x1, &x2, &y1, &y2);
                    printf("%d\n", query(x1, x2, y1, y2));
                }
            }
        }
        if (flag) break;
    }
    return 0;
}
