#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Map {
private:
	Map* iterator(int first) {
		Map* temp = root;

		while (temp != nullptr && temp->first != first) {
			if (first < temp->first) {
				temp = temp->left;
			}
			else {
				temp = temp->right;
			}
		}
		return temp;
	}

	const Map* iterator(int first) const {
		Map* temp = root;
		while (temp != nullptr && temp->first != first) {
			if (first < temp->first) {
				temp = temp->left;
			}
			else {
				temp = temp->right;
			}
		}
		return temp;
	}

	const int search(int first) const {
		const Map* temp = iterator(first);
		if (temp != nullptr) {
			return temp->second;
		}
		return 0;
	}

	Map* create(int first) {
		Map* newnode = (Map*)malloc(sizeof(Map));
		newnode->first = first;
		newnode->second = 0;
		newnode->left = nullptr;
		newnode->right = nullptr;
		newnode->par = nullptr;

		newnode->depth = 1;
		return newnode;
	}

	void right_rotation(Map* x) {
		Map* y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->par = x;
		}
		if (x->par != nullptr && x->par->right == x) {
			x->par->right = y;
		}
		else if (x->par != nullptr && x->par->left == x) {
			x->par->left = y;
		}
		y->par = x->par;
		y->right = x;
		x->par = y;
	}

	void left_rotation(Map* x) {
		Map* y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->par = x;
		}
		if (x->par != nullptr && x->par->left == x) {
			x->par->left = y;
		}
		else if (x->par != nullptr && x->par->right == x) {
			x->par->right = y;
		}
		y->par = x->par;
		y->left = x;
		x->par = y;
	}

	void helper(Map* node) {
		if (depthf(node->left) - depthf(node->right) > 1) {

			if (depthf(node->left->left) > depthf(node->left->right)) {
				node->depth = max(depthf(node->right) + 1, depthf(node->left->right) + 1);
				node->left->depth = max(depthf(node->left->left) + 1, depthf(node) + 1);
				right_rotation(node);
			}

			else {
				node->left->depth = max(depthf(node->left->left) + 1, depthf(node->left->right->left) + 1);
				node->depth = max(depthf(node->right) + 1, depthf(node->left->right->right) + 1);
				node->left->right->depth = max(depthf(node) + 1, depthf(node->left) + 1);
				left_rotation(node->left);
				right_rotation(node);
			}
		}

		else if (depthf(node->left) - depthf(node->right) < -1) {

			if (depthf(node->right->right) > depthf(node->right->left)) {
				node->depth = max(depthf(node->left) + 1, depthf(node->right->left) + 1);
				node->right->depth = max(depthf(node->right->right) + 1, depthf(node) + 1);
				left_rotation(node);
			}

			else {
				node->right->depth = max(depthf(node->right->right) + 1, depthf(node->right->left->right) + 1);
				node->depth = max(depthf(node->left) + 1, depthf(node->right->left->left) + 1);
				node->right->left->depth = max(depthf(node) + 1, depthf(node->right) + 1);
				right_rotation(node->right);
				left_rotation(node);
			}
		}
	}

	void balance(Map* node) {
		while (node != root) {
			int d = node->depth;
			node = node->par;
			if (node->depth < d + 1) {
				node->depth = d + 1;
			}
			if (node == root && depthf(node->left) - depthf(node->right) > 1) {
				if (depthf(node->left->left) > depthf(node->left->right)) {
					root = node->left;
				}
				else {
					root = node->left->right;
				}
				helper(node);
				break;
			}
			else if (node == root && depthf(node->left) - depthf(node->right) < -1) {
				if (depthf(node->right->right) > depthf(node->right->left)) {
					root = node->right;
				}
				else {
					root = node->right->left;
				}
				helper(node);
				break;
			}
			helper(node);
		}
	}

	int depthf(Map* node) {
		if (node == nullptr) return 0;
		return node->depth;
	}

	Map* insert(int first) {
		cnt++;
		Map* newnode = create(first);
		if (root == nullptr) {
			root = newnode;
			return root;
		}
		Map* temp = root, * prev = nullptr;
		while (temp != nullptr) {
			prev = temp;
			if (first < temp->first) {
				temp = temp->left;
			}
			else if (first > temp->first) {
				temp = temp->right;
			}
			else {
				free(newnode);
				cnt--;
				return temp;
			}
		}
		if (first < prev->first) {
			prev->left = newnode;
		}
		else {
			prev->right = newnode;
		}
		newnode->par = prev;
		balance(newnode);
		return newnode;
	}

	Map* inorderPredecessor(Map* head) {
		if (head == nullptr) return head;
		while (head->right != nullptr) {
			head = head->right;
		}
		return head;
	}

	Map* inorderSuccessor(Map* head) {
		if (head == nullptr) return head;
		while (head->left != nullptr) {
			head = head->left;
		}
		return head;
	}

public:
	static class Map* root;
	static int cnt;

	Map* left, * right, * par;
	int first, second, depth;

	int& operator[](int key) {
		return insert(key)->second;
	}

	const int operator[](int key) const {
		return search(key);
	}

	int count(int first) {
		Map* temp = iterator(first);
		if (temp != nullptr) {
			return 1;
		}
		return 0;
	}

	int size(void) {
		return cnt;
	}

	void erase(int first, Map* temp = root) {
		Map* prev = nullptr;
		cnt--;
		while (temp != nullptr && temp->first != first) {
			prev = temp;
			if (first < temp->first) {
				temp = temp->left;
			}
			else if (first > temp->first) {
				temp = temp->right;
			}
		}
		if (temp == nullptr) {
			cnt++;
			return;
		}
		if (cnt == 0 && temp == root) {
			free(temp);
			root = nullptr;
			return;
		}
		Map* l = inorderPredecessor(temp->left);
		Map* r = inorderSuccessor(temp->right);
		if (l == nullptr && r == nullptr) {
			if (prev == nullptr) {
				root = nullptr;
			}
			else {
				if (prev->left == temp) {
					prev->left = nullptr;
				}
				else {
					prev->right = nullptr;
				}
				free(temp);
				balance(prev);
			}
			return;
		}
		Map* start;
		if (l != nullptr) {
			if (l == temp->left) {
				l->right = temp->right;
				if (l->right != nullptr) {
					l->right->par = l;
				}
				start = l;
			}
			else {
				if (l->left != nullptr) {
					l->left->par = l->par;
				}
				start = l->par;
				l->par->right = l->left;
				l->right = temp->right;
				l->par = nullptr;
				if (l->right != nullptr) {
					l->right->par = l;
				}
				l->left = temp->left;
				temp->left->par = l;
			}
			if (prev == nullptr) {
				root = l;
			}
			else {
				if (prev->left == temp) {
					prev->left = l;
					l->par = prev;
				}
				else {
					prev->right = l;
					l->par = prev;
				}
				free(temp);
			}
			balance(start);
			return;
		}
		else {
			if (r == temp->right) {
				r->left = temp->left;
				if (r->left != nullptr) {
					r->left->par = r;
				}
				start = r;
			}
			else {
				if (r->right != nullptr) {
					r->right->par = r->par;
				}
				start = r->par;
				r->par->left = r->right;
				r->left = temp->left;
				r->par = nullptr;
				if (r->left != nullptr) {
					r->left->par = r;
				}
				r->right = temp->right;
				temp->right->par = r;
			}
			if (prev == nullptr) {
				root = r;
			}
			else {
				if (prev->right == temp) {
					prev->right = r;
					r->par = prev;
				}
				else {
					prev->left = r;
					r->par = prev;
				}
				free(temp);
			}
			balance(start);
			return;
		}
	}

	bool empty(void) {
		if (root == nullptr)
			return true;
		return false;
	}

	void update(int first, int second) {
		Map* temp = iterator(first);
		if (temp != nullptr) {
			temp->second = second;
		}
	}

	void clear(void) {
		while (root != nullptr) {
			erase(root->first);
		}
	}


	void iterate(void (*func)(int, int), Map* head = root) {
		if (root == nullptr)
			return;
		if (head->left != nullptr) {
			iterate(func, head->left);
		}
		func(head->first, head->second);
		if (head->right != nullptr) {
			iterate(func, head->right);
		}
	}


	Map* find(int first) {
		return iterator(first);
	}

	vector<int> keys;
	void insert(int first, int second) {
		Map* temp = iterator(first);
		if (temp == nullptr) {
			insert(first)->second = second;
			keys.push_back(first);
		}
		else {
			temp->second = second;
		}
	}
};

Map* Map::root = nullptr;
int Map::cnt = 0;

void log(int first, int second) {
	cout << first << ' ' << second << endl;
}


bool bfs(Map map, int startCity, int destination) {
	vector<pair<int, bool>> queue;
	queue.push_back(make_pair(startCity, true));

	vector<int> visited;
	visited.push_back(startCity);

	while (queue.size() > 0) {
		pair<int, bool> tmp = *queue.begin();
		queue.erase(queue.begin());

		vector<pair<int, bool>> neighbors;
		for (int i = 0; i < map.keys.size(); i++) {
			if (map.keys[i] == tmp.first) {
				if (find(visited.begin(), visited.end(), map[tmp.first]) != visited.end()) {
					neighbors.push_back(make_pair(map[tmp.first], true));
				}
				else {
					neighbors.push_back(make_pair(map[tmp.first], false));
				}
			}
			if (map[map.keys[i]] == tmp.first) {
				if (find(visited.begin(), visited.end(), map.keys[i]) != visited.end()) {
					neighbors.push_back(make_pair(map.keys[i], true));
				}
				else {
					neighbors.push_back(make_pair(map.keys[i], false));
				}
			}
		}


		for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
			if (!iter->second) {
				queue.push_back(make_pair(iter->first, true));
				visited.push_back(iter->first);
				if (iter->first == destination) {
					for (auto i = visited.begin(); i != visited.end(); i++) {
						cout << *i << ' ';
					}
					cout << endl;
					return true;
				} 
			}
		}
	}

	return false;
}

int n;
vector <vector<int> > g(1000);
vector < vector <int > > w;
vector <int> used(1000);
vector<int> comp;
vector<int> p;
vector <pair < int, int > > qwe;

void dfs(int v, int p = -1) {
	used[v] = 1;
	comp.push_back(v);
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)
			continue;
		if (!used[to])
			dfs(to, v);
		else if (v < g[v][i])
			qwe.push_back(make_pair(v + 1, g[v][i] + 1));
	}
}

void find_comps() {
	vector<int> ans;
	p.assign(n, -1);
	for (int i = 0; i < n; ++i)
		used[i] = 0;
	for (int i = 0; i < n; ++i)
		if (!used[i]) {
			comp.clear();
			dfs(i);
			for (size_t j = 0; j < comp.size(); ++j)
			{
				ans.push_back(comp[j]);
			}
			w.push_back(ans);
			ans.clear();
		}

}

int main() {
	Map map;

	map.insert(1, 2);
	map.insert(2, 3);
	map.insert(3, 1);
	map.insert(4, 8);
	map.insert(5, 6);
	map.insert(6, 7);
	map.insert(7, 5);
	n = map.size();

	vector <pair <int, int> > otv;
	for (auto iter = map.keys.begin(); iter != map.keys.end(); iter++) {
		g[*iter - 1].push_back(map[*iter] - 1);
		g[map[*iter] - 1].push_back(*iter - 1);
	}

	find_comps();

	cout << w.size() - 1 << endl;
	if (w.size() > 1) {
		for (size_t i = 0; i < w.size() - 1; i++) {
			otv.push_back(make_pair(w[i][0] + 1, w[i + 1][0] + 1));
		}
	}

	for (size_t i = 0; i < otv.size(); i++) {
		cout << qwe[i].first << " " << qwe[i].second << " ";
		cout << otv[i].first << " " << otv[i].second;
		cout << endl;
	}


	return 0;
}
//Система непересекающихся множеств — структура данных, которая позволяет администрировать множество элементов,
// разбитое на непересекающиеся подмножества.
//При этом каждому подмножеству назначается его представитель — элемент этого подмножества.