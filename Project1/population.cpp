#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

class Operation
{
    public:
        char type;
        int x1;
        int x2;
        int y1;
        int y2;
        int N;
        Operation(int x1, int x2, int y1, int y2, int N, char type) :
            x1(x1), x2(x2), y1(y1), y2(y2), N(N), type(type) {}
};

vector<Operation> operations;
vector<int> xs;
vector<int> ys;
map<int,int> xmap;
map<int,int> ymap;
int xsize;
int ysize;
long long **bitArray;

void input()
{
    for(;;)
    {
        char buffer[100];
        char state;
        gets(buffer);
        if (strlen(buffer) == 1)
        {
            if (buffer[0] == 'E') break;
            state = buffer[0];
        }
        else
        {
            int x1 = 0, x2 = 0, y1 = 0, y2 = 0, N = 0;
            if (state == 'I')
            {
                sscanf(buffer, "%d%d%d", &x1, &y1, &N);
                xs.push_back(x1);
                ys.push_back(y1);
            }
            else
            {
                sscanf(buffer, "%d%d%d%d", &x1, &x2, &y1, &y2);
                xs.push_back(x1);
                xs.push_back(x2);
                ys.push_back(y1);
                ys.push_back(y2);
            }
            operations.push_back(Operation(x1, x2, y1, y2, N, state));
        }
    }
}

int lowbit(int t)
{
    return t & (-t);
}

void modify(int i, int j, int delta)
{
    for (int x = i; x <= xsize; x += lowbit(x))
        for (int y = j; y <= ysize; y += lowbit(y))
            bitArray[x][y] += delta;
}

long long sumOfRectangle(int i, int j)
{
    if (i == 0 || j == 0) return 0;
    long long sum = 0;
    for (int x = i; x > 0; x -= lowbit(x))
        for (int y = j; y > 0; y -= lowbit(y))
            sum += bitArray[x][y];
    return sum;
}

long long query(int x1, int x2, int y1, int y2)
{
    return sumOfRectangle(x2, y2) - sumOfRectangle(x1 - 1, y2) - sumOfRectangle(x2, y1 - 1) + sumOfRectangle(x1 - 1, y1 - 1);
}

int main()
{
    input();

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    int counter = 1;
    for (int i = 0; i < xs.size(); i++)
        if (xmap[xs[i]] == 0) xmap[xs[i]] = counter++;
    counter = 1;
    for (int i = 0; i < ys.size(); i++)
        if (ymap[ys[i]] == 0) ymap[ys[i]] = counter++;
    
    xsize = xmap.size();
    bitArray = new long long*[xsize + 1];
    ysize = ymap.size();
    for (int i = 1; i <= xsize; i++)
    {
        bitArray[i] = new long long[ysize + 1];
        memset(bitArray[i], 0, sizeof(bitArray[i])); 
    }

    for (int i = 0; i < operations.size(); i++)
        if (operations[i].type == 'I') modify(xmap[operations[i].x1], ymap[operations[i].y1], operations[i].N);
        else printf("%lld\n", query(xmap[operations[i].x1], xmap[operations[i].x2], ymap[operations[i].y1], ymap[operations[i].y2]));
  
    return 0;
}