
#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ROWS = 11;
const int COLS = 15;

struct Position
{
    int row;
    int col;
};

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    char maze[ROWS][COLS];

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            maze[r][c] = 'W';
        }
    }

    Position player = { 1, 1 };
    Position finish = { ROWS - 2, COLS - 2 };

    stack<Position> generationStack;
    generationStack.push(player);
    maze[player.row][player.col] = ' ';

    int rowMoves[] = { -2, 2, 0, 0 };
    int colMoves[] = { 0, 0, -2, 2 };

    while (!generationStack.empty())
    {
        Position current = generationStack.top();

        int possible[4];
        int count = 0;

        for (int i = 0; i < 4; i++)
        {
            int nr = current.row + rowMoves[i];
            int nc = current.col + colMoves[i];

            if (nr > 0 && nr < ROWS - 1 &&
                nc > 0 && nc < COLS - 1 &&
                maze[nr][nc] == 'W')
            {
                possible[count] = i;
                count++;
            }
        }

        if (count == 0)
        {
            generationStack.pop();
        }
        else
        {
            int choice = possible[rand() % count];

            int nr = current.row + rowMoves[choice];
            int nc = current.col + colMoves[choice];

            maze[current.row + rowMoves[choice] / 2]
                [current.col + colMoves[choice] / 2] = ' ';

            maze[nr][nc] = ' ';

            generationStack.push({ nr, nc });
        }
    }

    maze[finish.row][finish.col] = ' ';

    stack<Position> movementHistory;
    movementHistory.push(player);

    char move;

    while (true)
    {
        cout << "\n";

        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                if (r == player.row && c == player.col)
                {
                    cout << "P ";
                }
                else if (r == finish.row && c == finish.col)
                {
                    cout << "F ";
                }
                else
                {
                    cout << maze[r][c] << ' ';
                }
            }

            cout << endl;
        }

        if (player.row == finish.row &&
            player.col == finish.col)
        {
            cout << "\nCongratulations! You escaped the maze!"
                << endl;
            cout << "Positions visited: "
                << movementHistory.size() << endl;
            break;
        }

        cout << "\nW = Up, A = Left, S = Down, D = Right";
        cout << "\nQ = Quit";
        cout << "\nYour move: ";
        cin >> move;

        if (move == 'q' || move == 'Q')
        {
            cout << "You quit the maze." << endl;
            break;
        }

        int newRow = player.row;
        int newCol = player.col;

        if (move == 'w' || move == 'W')
        {
            newRow--;
        }
        else if (move == 's' || move == 'S')
        {
            newRow++;
        }
        else if (move == 'a' || move == 'A')
        {
            newCol--;
        }
        else if (move == 'd' || move == 'D')
        {
            newCol++;
        }
        else
        {
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        if (newRow >= 0 && newRow < ROWS &&
            newCol >= 0 && newCol < COLS &&
            maze[newRow][newCol] == ' ')
        {
            player.row = newRow;
            player.col = newCol;
            movementHistory.push(player);
        }
        else
        {
            cout << "You cannot walk through a wall!" << endl;
        }
    }

    return 0;
}