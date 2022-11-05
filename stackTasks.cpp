#include <string>
#include <vector>
#include <stack>
using namespace std;

int task1( int number ) {
  stack<int> s;
  s.push(1);

  while (number >= 2) {
    int temp = s.top();
    s.push(temp * number);
    number--;
  }

  return s.top();
}

bool isOpeningBracket(char br) {
    return ((br == '(') || (br == '[') || (br == '{'));
}

bool task2 (const string& list) {
    stack<char> stack1;
    int len = list.length();


    for (int i = 0; i < len; i++) {

        if (isOpeningBracket(list[i])) {
            stack1.push(list[i]);
        } else if (stack1.empty()) {
            return false;
        } else if (list[i] == ')') {
            char top = stack1.top();

            if (top != '(') {
                return false;
            }

            stack1.pop();
        } else if (list[i] == ']') {
            char top = stack1.top();

            if (top != '[') {
                return false;
            }

            stack1.pop();
        } else if (list[i] == '}') {

            char top = stack1.top();

            if (top != '{') {
                return false;
            }

            stack1.pop();
        }
    }
    
    return stack1.empty();
}

bool graphPath(const vector<vector<int>>& g, unsigned from, unsigned to, bool* visited) {
    if (visited[from]) {
        return false;
    }

    if (from == to) {
        return true;
    }

    visited[from] = true;

    bool isPath = false;

    for (int i = 0; i < g[from].size(); i++) {
        if (graphPath(g, g[from][i], to, visited)) {
            isPath = true;
            break;
        }
    }

    return isPath;
}

bool task3(const vector<vector<int>>& g, unsigned from, unsigned to) {
    int max = 0;

    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            if (g[i][j] > max) {
                max = g[i][j];
            }
        }
    }

    bool* visited = new bool[max + 1];
    
    for (int i = 0; i < max + 1; i++) {
        visited[i] = false;
    }

    bool isPath = graphPath(g, from, to, visited);

    delete[] visited;

    return isPath;
}

bool isNumber(const char& number) {
    return (number >= '0' && number <= '9');
}

string task4(const string& input) {
	stack<int> numbers;
	stack<string> words;

	int inputSize = input.size();
	int i = 0;

	while (i < inputSize) {
		if (isNumber(input[i])) {
			int number = input[i] - '0';
			i++;
			while (input[i] != '(') {
				number *= 10;
				number += (input[i] - '0');
				i++;
			}
			numbers.push(number);
		}
		else if (input[i] == '(') {
			i++;
			if (isNumber(input[i])) {
				int number = input[i] - '0';
				i++;
				while (input[i] != '(') {
					number *= 10;
					number += (input[i] - '0');
					i++;
				}
				numbers.push(number);
			}
			else {
				string combination;
				combination.push_back(input[i]);
				i++;
				while (input[i] != ')') {
					combination.push_back(input[i]);
					i++;
				}
				words.push(combination);
			}
		}
		else if (input[i] == ')') {
			if (numbers.size() == 0) {
				return nullptr;
			}
			if (numbers.size() == 1) {
				string word;
				while (!words.empty()) {
					string first = words.top();
					words.pop();
					string temp = first.append(word);
					word = temp;
				}
				words.push(word);
			} 
			int n = numbers.top();
			numbers.pop();
			string s = words.top();
			words.pop();
			string result = s;
			if (n == 0) {
				s = "";
			}
			else {
				while (n != 1) {
					result = result.append(s);
					n--;
				}
			}
			words.push(result);

			i++;
		}
	}

	return words.top();
}

bool task5(vector<vector<int>>g, unsigned from, unsigned to) {
	stack<int> nodes;
	int max = 0;

	for (int i = 0; i < g.size(); i++) {
		for (int j = 0; j < g[i].size(); j++) {
			if (g[i][j] > max) {
				max = g[i][j];
			}
		}
	}

	bool* visited = new bool[max + 1];

	for (int i = 0; i < max + 1; i++) {
		visited[i] = false;
	}

	visited[from] = true;

	for (int i = 0; i < g[from].size(); i++) {
		nodes.push(g[from][i]);
	}

	while (!nodes.empty()) {
		int node = nodes.top();
		nodes.pop();

		if (node == to) {
			delete[] visited;
			return true;
		}

		if (visited[node]) {
			continue;
		}

		visited[node] = true;

		for (int i = 0; i < g[node].size(); i++) {
			nodes.push(g[node][i]);
		}
	}

    delete[] visited;
	return false;
}

bool task6(const string& a, const string& b) {
	return false;
}