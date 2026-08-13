#include <iostream>
#include <vector>
using namespace std;
void tileBoard(vector<vector<int>> &board, int size, int row, int col, int missingRow, int missingCol, int &tileCount)
{
    if (size == 1)
        return;
    int half = size / 2;
    int cornertile = ++tileCount;
    if (missingRow < row + half && missingCol < col + half)
        tileBoard(board, half, row, col, missingRow, missingCol, tileCount);
    else
    {
        board[row + half - 1][col + half - 1] = cornertile;
        tileBoard(board, half, row, col, row + half - 1, col + half - 1, tileCount);
    }
    if (missingRow < row + half && missingCol >= col + half)
        tileBoard(board, half, row, col + half, missingRow, missingCol, tileCount);
    else
    {
        board[row + half - 1][col + half] = cornertile;
        tileBoard(board, half, row, col + half, row + half - 1, col + half, tileCount);
    }
    if (missingRow >= row + half && missingCol < col + half)
        tileBoard(board, half, row + half, col, missingRow, missingCol, tileCount);
    else
    {
        board[row + half][col + half - 1] = cornertile;
        tileBoard(board, half, row + half, col, row + half, col + half - 1, tileCount);
    }
    if (missingRow >= row + half && missingCol >= col + half)
        tileBoard(board, half, row + half, col + half, missingRow, missingCol, tileCount);
    else
    {
        board[row + half][col + half] = cornertile;
        tileBoard(board, half, row + half, col + half, row + half, col + half, tileCount);
    }
}
void runCase(int n, int missingRow, int missingCol)
{
    vector<vector<int>> board(n, vector<int>(n, 0));
    int tileCount = 0;
    tileBoard(board, n, 0, 0, missingRow, missingCol, tileCount);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}
int main()
{
    int n[] = {2, 2, 4, 4, 8};
    int mr[] = {0, 1, 0, 2, 5};
    int mc[] = {0, 1, 0, 3, 5};
    for (int i = 0; i < 5; i++)
    {
        cout << "test case " << i + 1 << ": board size " << n[i] << " missing cell at " << mr[i] << " " << mc[i] << endl;
        runCase(n[i], mr[i], mc[i]);
    }
    return 0;
}
