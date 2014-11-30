#include <cstring>
#include <cstdio>
#include <map>

using namespace std; // For using the fucntions in the namespace std

int const N = 20001; // Constant for the range of cordinate
char buffer[100]; // Buffer for input data
char state; // Signal of operation
map<int, int> bitArray[N]; // The database of bit
bool flag; // Mark of EOF

int lowbit(int t)
{
    return t & (-t); 
}
// This function will calcuate the number of consective 0 in the last of the binary representation of t
// For the bit data structure

void modify(int i, int j, int delta)
{
    for (int x = i; x < N; x += lowbit(x))
        for (int y = j; y < N; y += lowbit(y))
            bitArray[x][y] += delta;
}
// Update bit's database
// Only the entries which related to the modified data will be updated

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
//This funtion will caculate all the entries which's coordinate is in the rectangle that's down-left coordinate is (1,1) and up-right coordinate is (i,j)

//The three functions will be discussed in the ducument concretely

int query(int x1, int x2, int y1, int y2)
{
    return sumOfRectangle(x2, y2) - sumOfRectangle(x1 - 1, y2) - sumOfRectangle(x2, y1 - 1) + sumOfRectangle(x1 - 1, y1 - 1);
}
//This funtion will caculate all the entries which's coordinate is in the rectangle that's down-left coordinate is (x1,y1) and up-right coordinate is (x2,y2)

int main()
{
    flag = false; //Set EOF had not came yet
    for (;;)
    {
        for (int i = 1; i < N; i++)
            bitArray[i].clear(); //Initialize the bit's database
        for(;;)
        {
            if (gets(buffer) == NULL) flag = true; // EOF is coming!!!
            if (flag) break; // Stop the program
            if (strlen(buffer) == 1) // A signal is coming
            {
                if (buffer[0] == 'E') break; // End of the test case
                state = buffer[0]; // Change the input state
            }
            else
            if (buffer[0] >= '0' && buffer[0] <= '9') // It's a operation on data
            {
                int x1 = 0, x2 = 0, y1 = 0, y2 = 0, N = 0; // Initialize some temp variable
                if (state == 'I') // People is coming in
                {
                    sscanf(buffer, "%d%d%d", &x1, &y1, &N); // Read the data of operation
                    modify(x1, y1, N); // Update database
                }
                else
                {
                    sscanf(buffer, "%d%d%d%d", &x1, &x2, &y1, &y2); // Read the data of operation
                    printf("%d\n", query(x1, x2, y1, y2)); // Output the query result
                }
            }
        }
        if (flag) break; // Stop the program 
    }
    return 0;
}
