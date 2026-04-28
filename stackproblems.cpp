#include <iostream>
#include<string>
#include<stack>
using namespace std;
class stackproblems {
    string input;
    string postfix="";
    stack<char> operations=stack<char>();
    stack<int>result;
public:
    stackproblems(string userinput) {
        input = userinput;
    }
    string infixtopostfix() {
        for (int i = 0; i < input.length(); i++) {
            bool check = false;
            if (postfix.empty()) {
                if (input[i] == '-') {
                    postfix.push_back('0');
                    operations.push(input[i]);
                    continue;
                }
            }
            if (!operations.empty()) {
                if (operations.top() == '(') {
                    if (input[i] == '-') {
                        for(int j=i-1;j>=0;j--){
                            if (input[j] == ' ') {
                                continue;
                            }
                            else if (input[j] == '(') {
                                check = true;
                                postfix.push_back('0');
                                operations.push(input[i]);
                                break;
                            }
                            else {
                                break;
                            }
                        }
                    }
                }
            }
            if (check) {
                continue;
            }
            if (input[i] == '+' || input[i] == '-') {
                if (!operations.empty()) {
                    while (operations.top() == '+' || operations.top() == '-') {
                        postfix.push_back(operations.top());
                        operations.pop();
                        if (operations.empty()) {
                            break;
                        }
                    }
                }
                operations.push(input[i]);
            }
            else if (input[i] == ' ') {
                continue;
            }
            else if (input[i] == '(') {
                operations.push(input[i]);
            }
            else if (input[i] == ')') {
                while (!operations.empty() && operations.top() != '(') {
                    postfix.push_back(operations.top());
                    operations.pop();
                }
                if (!operations.empty() && operations.top() == '(') {
                    operations.pop();
                }
            }
            else {
                postfix.push_back(input[i]);
            }
        }
        while (!operations.empty()) {
            postfix.push_back(operations.top());
            operations.pop();
        }
        return postfix;
    }
    int evalpfix(string postfix) {
        for (int i = 0; i < postfix.length(); i++) {
            if (postfix[i] == '+' || postfix[i] == '-') {
                int lelement = result.top();
                result.pop();
                int pelement = result.top();
                result.pop();
                if (postfix[i] == '+') {
                    result.push(pelement + lelement);
                }
                else if (postfix[i] == '-') {
                    result.push(pelement - lelement);
                }
            }
            else {
                result.push(postfix[i] - '0');
            }
        }
        return result.top();
    }
};
int main()
{
    string input;
    getline(cin, input);
    stackproblems problem = stackproblems(input);
    string postfix = problem.infixtopostfix();
    int result = problem.evalpfix(postfix);
    cout << result << endl;
}


