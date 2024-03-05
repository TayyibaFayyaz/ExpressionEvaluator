#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "HugeInteger.h"

using namespace std;

int Precedence(char op)
{
    if (op == '/' or op == '*')
    {
        return 2;
    }
    else if (op == '+' or op == '-')
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

vector<string> ConvertToPostFix(string S)
{
    vector<string> V;
    stack<char> Op;
    string R = "";
    int size = S.size();
    int i = 0;
    while (i < size)
    {
        if (isdigit(S[i]))
        {
            while (i < size and isdigit(S[i]))
            {
                R += S[i++];
            }
            V.push_back(R);
            i--;
            R.clear();
        }
        else if (i == 0 and S[i] == '-')
        {
            R += '-';
        }
        else if (S[i] == '(')
        {
            Op.push(S[i]);
        }
        else if (S[i] == ')')
        {
            while (Op.top() != '(')
            {
                R = Op.top();
                V.push_back(R);
                Op.pop();
            }
            Op.pop();
            R.clear();
        }
        else
        {
            while (!Op.empty() and Precedence(S[i]) <= Precedence(Op.top()) and Op.top() != '(')
            {
                R = Op.top();
                V.push_back(R);
                Op.pop();
            }
            Op.push(S[i]);
            R.clear();
        }
        i++;
    }
    while (!Op.empty())
    {
        R = Op.top();
        V.push_back(R);
        Op.pop();
    }
    return V;
}

bool IsOperator(string C)
{
    if (C == "+" || C == "-" || C == "*" || C == "/")
    {
        return true;
    }
    return false;
}

HugeInteger PostFixEvaluator(vector<string> V)
{
    HugeInteger R, O1, O2;
    for (int i = 0; i < V.size(); i++)
    {
        if (IsOperator(V[i]))
        {
            O1 = stoi(V[i-2]);
            O2 = stoi(V[i - 1]);
            if (V[i]=="+")
            {
                R = O1 + O2;
            }
            else if (V[i] == "-")
            {
                R = O1 - O2;
            }
            else if (V[i] == "*")
            {
                R = O1 * O2;
            }
            else if (V[i] == "/")
            {
                R = O1 / O2;
            }
            V.erase(V.begin() + i - 2, V.begin() + i + 1);
            V.insert(V.begin() + (i - 2),R.HItoS());
            i -= 3;
        }
    }
    R = stoi(V[0]);
    return R;
}

int main()
{
    string S = "-9*10-(23-25+10/5*2)";
    vector <string> V = ConvertToPostFix(S);
    HugeInteger R = PostFixEvaluator(V);
    for (int i = 0; i < V.size(); i++)
    {
        cout << V[i] << ' ';
    }
    cout << endl << R;
    
}