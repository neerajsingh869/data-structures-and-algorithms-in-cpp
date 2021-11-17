#include <iostream>
#include <stack>
#include <string>
using namespace std;

string reverse(string s)
{
    string result = "";
    for (int i = s.size() - 1; i >= 0; i--)
    {   
        if(s[i] == ')')
            result += '(';
        else if(s[i] == '(')
            result += ')';
        else{
            result += s[i];
        }
    }
    return result;
}

/* precedence(op) -> Function will return higher value for operator with higher precedence */
int precedence(char op)
{
    if (op == '^')
    {
        return 3;
    }
    else if (op == '/' || op == '*')
    {
        return 2;
    }
    else if (op == '+' || op == '-')
    {
        return 1;
    }
    // For all other cases
    else
    {
        return -1;
    }
}

string infixToPrefix(string infixExp)
{
    stack<char> tempHold;
    string PrefixExp = "";
    for (int i = 0; i < infixExp.length(); i++)
    {
        // If the element is operand, then store it in the string
        if ((infixExp[i] >= 'a' && infixExp[i] <= 'z') || (infixExp[i] >= 'A' && infixExp[i] <= 'Z'))
        {
            PrefixExp += infixExp[i];
        }
        // If the element is (, then push it into the stack
        else if (infixExp[i] == '(')
        {
            tempHold.push(infixExp[i]);
        }
        // If the element is ), then pop and store top element of stack until the top is (
        else if (infixExp[i] == ')')
        {
            while (!tempHold.empty() && tempHold.top() != '(')
            {
                PrefixExp += tempHold.top();
                tempHold.pop();
            }
            // Pop the opening round bracket
            if (!tempHold.empty())
            {
                tempHold.pop();
            }
        }
        /* If the element is operator, then first check the predence of the top element
        of stack and the element. If the element has higher precedence, then push it into
        the stack else pop the top element of the stack and push the element only
        above lower predecence top */
        else
        {
            /* precedence(op) -> Function will return some integer.
            The integer will be higher for operator with higher precedence */
            while (!tempHold.empty() && (precedence(tempHold.top()) >= precedence(infixExp[i])))
            {
                PrefixExp += tempHold.top();
                tempHold.pop();
            }
            tempHold.push(infixExp[i]);
        }
        // cout<<PrefixExp<<endl;
    }
    // Removing the last element of the stack
    while (!tempHold.empty())
    {
        PrefixExp += tempHold.top();
        tempHold.pop();
    }
    return reverse(PrefixExp);
}

int main()
{
    string infixExp;
    cin >> infixExp;
    cout << infixToPrefix(reverse(infixExp));
    return 0;
}
// (a-b/c)*(a/k-l) Ans => *-a/ac-/akl
// ((A*(B+C))/D) Ans => /*A+BCD
// ((a-b/c)*(a/k-l)) Ans => *-a/ac-/akl