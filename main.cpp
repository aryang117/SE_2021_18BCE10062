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

    void updateBoardInit(unordered_map<string, vector<int>> locs, int playerID)
    {

        char playerName = playerID == 1 ? 'A' : 'B';

        for (auto i : locs)
        {
            boardLayout[i.second[0]][i.second[1]] = playerName + i.first;
        }
    }

    void updateBoardMove(unordered_map<string, vector<int>> P1locs, unordered_map<string, vector<int>> P2locs)
    {

        for (int i = 0; i < boardLayout.size(); i++)
        {
            for (int j = 0; j < boardLayout[i].size(); j++)
            {
                boardLayout[i][j] = "-";
            }
        }

        for (auto i : P1locs)
        {
            boardLayout[i.second[0]][i.second[1]] = 'A' + i.first;
        }

        for (auto i : P2locs)
        {
            boardLayout[i.second[0]][i.second[1]] = 'B' + i.first;
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

    unordered_map<string, vector<int>> setInitLoc(vector<string> loc)
    {

        int locX = playerID == 1 ? 0 : 4;

        for (int i = 0; i < loc.size(); i++)
        {
            pawns[loc[i]].push_back(locX);
            pawns[loc[i]].push_back(i);
        }

        return pawns;
    }

    unordered_map<string, vector<int>> getPlayerLoc()
    {

        return pawns;
    }

    unordered_map<string, vector<int>> setPlayerMove(string pawnID, char move)
    {
        switch (move)
        {
        case 'F':
            pawns[pawnID][0]++;
            break;
        case 'B':
            pawns[pawnID][0]--;
            break;
        case 'L':
            pawns[pawnID][1]++;
            break;
        case 'R':
            pawns[pawnID][1]--;
            break;
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

    b.updateBoardInit(P1.setInitLoc(initLocation), 1);
    b.printBoard();

    cout << "Player 2 input:";
    for (int i = 0; i < 5; i++)
    {
        cin >> loc;
        initLocation.push_back(loc);
    }

    b.updateBoardInit(P2.setInitLoc(initLocation), 2);
    b.printBoard();

    string playerMove;
    cin >> playerMove;

    b.updateBoardMove(P1.setPlayerMove(playerMove.substr(0, 2), playerMove[playerMove.size() - 1]), P2.getPlayerLoc());

    b.printBoard();
    return 0;
}