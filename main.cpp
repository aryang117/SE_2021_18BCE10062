#include <bits/stdc++.h>
using namespace std;
class board
{
private:
    vector<vector<string>> boardLayout = vector<vector<string>>(5, vector<string>(5, "-"));

public:
    board()
    {
        for (vector<string> i : boardLayout)
        {
            for (auto j : i)
            {
                cout << j << "\t";
            }
            cout << "\n";
        }
    }

    void updateBoard(unordered_map<string, vector<int>> locs, int playerID)
    {

        char playerName = playerID == 1 ? 'A' : 'B';

        for (auto i : locs)
        {
            boardLayout[i.second[0]][i.second[1]] = playerName + i.first;
        }
    }

    void printBoard()
    {
        for (int i = 0; i < boardLayout.size(); i++)
        {
            for (int j = 0; j < boardLayout[i].size(); j++)
            {
                cout << boardLayout[i][j] << "\t";
            }
            cout << "\n";
        }
    }
};

class player
{
    unordered_map<string, vector<int>> pawns;
    int playerID;

public:
    player(int id)
    {
        playerID = id;
    }

    unordered_map<string, vector<int>> setInitLoc(vector<string> loc, board b)
    {

        int locX = playerID == 1 ? 0 : 4;

        for (int i = 0; i < loc.size(); i++)
        {
            pawns[loc[i]].push_back(locX);
            pawns[loc[i]].push_back(i);
        }

        return pawns;
    }
};

int main()
{
    board b;
    player P1(1), P2(2);

    vector<string> initLocation;
    string loc;
    cout << "Player 1 input:";

    for (int i = 0; i < 5; i++)
    {
        cin >> loc;
        initLocation.push_back(loc);
    }

    b.updateBoard(P1.setInitLoc(initLocation, b), 1);
    b.printBoard();

    for (int i = 0; i < 5; i++)
    {
        cin >> loc;
        initLocation.push_back(loc);
    }

    b.updateBoard(P2.setInitLoc(initLocation, b), 2);
    b.printBoard();

    return 0;
}