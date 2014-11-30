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
        int x;
        int y;
        int N;
        Operation(int x, int y, int N) :
            x(x), y(y), N(N) {}
};

vector<Operation> operations;

int main()
{
    bool flag;
    flag = false;
    for(;;){
        operations.clear();
        for(;;)
        {
            char buffer[100];
            char state;
            if (gets(buffer) == NULL) flag = true;
            if (flag) break;
            if (strlen(buffer) == 1)
            {
                if (buffer[0] == 'E') break;
                state = buffer[0];
            }
            else
            {
                if (buffer[0] < '0' || buffer[0] > '9') break;
                int x1 = 0, x2 = 0, y1 = 0, y2 = 0, N = 0;
                if (state == 'I')
                {
                    sscanf(buffer, "%d%d%d", &x1, &y1, &N);
                    operations.push_back(Operation(x1, y1, N));
                }
                else
                {
                    sscanf(buffer, "%d%d%d%d", &x1, &x2, &y1, &y2);
                    int result = 0;
                    for (int i = 0; i < operations.size(); i++)
                        if ( (x1 <= operations[i].x) && (x2 >= operations[i].x) && (y1 <= operations[i].y) && (y2 >= operations[i].y) ) result += operations[i].N;
                    printf("%d\n", result);
                }
            }
        }
        if (flag) break;
    }
    return 0;
}


