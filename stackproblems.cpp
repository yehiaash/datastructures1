#include <iostream>
#include<string>
#include<stack>
#include <vector>
using namespace std;
class stackproblems {
    string input;
    string postfix="";
    stack<char> operations=stack<char>();
    stack<int>result;
    stack<int>circular;
public:
    stackproblems(string userinput="") {
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
    void nextgreater(vector<int> nums, int n) {
        vector<int> temp(n,0);
        for (int i = 0; i < n; i++) {
            bool check = false;
            for(int j=i-1;j>=0;j--){
                circular.push(nums[j]);
            }
            for (int k = n - 1; k > i; k--) {
                circular.push(nums[k]);
            }
            while (!circular.empty()) {
                if (circular.top() > nums[i]) {
                    temp[i] = circular.top();
                    check = true;
                    break;

                }
                else {
                    circular.pop();
                }
            }
            if (!check) {
                temp[i] = -1;
            }
            circular = stack<int>();
        }
        cout << "[";
        for (int i = 0; i < n; i++) {
            if (i == n - 1) {
                cout << temp[i] << "]";
            }
            else {
                cout << temp[i] << ",";
            }
        }
    }
};
int main()
{
    int choice = 0;
    cout << "Choose a problem(1,2) ";
    cin >> choice;
    cin.ignore();
    if (choice == 1) {
        string input;
        getline(cin, input);
        stackproblems problem = stackproblems(input);
        string postfix = problem.infixtopostfix();
        int result = problem.evalpfix(postfix);
        cout << result << endl;
    }
    else if (choice == 2) {
        int n;
        cin >> n;
        vector<int> input(n);
        for (int i = 0; i < n; i++) {
            cin >> input[i];
        }
        stackproblems problem = stackproblems();
        problem.nextgreater(input, n);
    }
  
    

}


