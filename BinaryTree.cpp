#include <iostream>
#include <cstring>

using namespace std; 
using namespace std;

typedef struct tagDate {
	char name[100];
}DATA;

typedef struct tagTree {
	DATA* date;
	struct tagTree* left, *right;
}TREE;

TREE* root = NULL;
TREE* newRoot = NULL;

typedef enum tagType { LEFT, RIGHT } TYPE;

TREE* addNode(TREE* node,const char* name, TYPE type = LEFT) {
	TREE* newNode = (TREE*)malloc(sizeof(TREE));
	newNode->date = (DATA*)malloc(sizeof(DATA));
	if (type == LEFT && node != NULL) {
		node->left = newNode;
	}
	else if (node != NULL) {
		node->right = newNode;
	}
	strcpy_s(newNode->date->name, name);
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}
void showNext(TREE* node, int off) {
	if (node != NULL) {
		for (int i = 0; i < off; i++) {
			putchar(' ');
		}
		std::cout << node->date->name << '\n';
		showNext(node->left, off);
		showNext(node->right, off+1);
	}
}

void showTREE(TREE* root) {
	if (root != NULL) {
		cout << root->date->name << endl;
		showNext(root->left, 0);
		showNext(root->right, 1);
	}
}

void delNext(TREE* node) {
	if (node != NULL) {
		delNext(node->left);
		delNext(node->right);
		std::cout << "DELETE node = " << node->date->name << '\n';
		free(node->date);
		free(node);
	}
}

void delTree(TREE* rt) {
	if (rt != NULL) {
		delNext(rt->left);
		delNext(rt->right);
		std::cout << "DELETE root = " << rt->date->name << '\n';
		free(rt->date);
		free(rt);
	}
}

void replaceNext(TREE* node, TREE* newNode) {
	if (node != NULL && newNode != NULL) {
		replaceNext(node->left, newNode->left);
		replaceNext(node->right, newNode->right);
		std::cout << "REPLACE root = " << node->date->name << "REPLACE newRoot = " << newNode->date->name << '\n';
		strcpy_s(node->date->name, newNode->date->name);
		node = newNode;
		free(newNode->date);
		free(newNode);
		newNode = NULL;
	}
	else if (node != NULL && newNode == NULL) {
		replaceNext(node->left, NULL);
		replaceNext(node->right, NULL);
		std::cout << "NOT RAPLCE node = " << node->date->name << '\n';
		free(node->date->name);
		free(node->date);
		node = NULL;
	}
	else if (node == NULL && newNode != NULL) {
		replaceNext(NULL, newNode->left);
		replaceNext(NULL, newNode->right);
		std::cout << "ADD root to newNode = " << newNode->date->name << '\n';
		strcpy_s(node->date->name, newNode->date->name);
		node = newNode;
		free(newNode->date);
		free(newNode);
		newNode = NULL;
	}
}

void replaceTree() {
	if (root != NULL && newRoot != NULL) {
		replaceNext(root->left, newRoot->left);
		replaceNext(root->right, newRoot->right);
		std::cout << "REPLACE root = " << root->date->name << "REPLACE newRoot = " << newRoot->date->name << '\n';
		newRoot = NULL;
	}
}

int main()//cin.getline(nodeName,sizeof(nodeName))
{
	setlocale(LC_ALL, "Russian");
	char rootName[100], nodeName[100];
	int vybor = 1;
	cout << "Введите название первого дерева\n";
	if (!cin.getline(rootName, sizeof(rootName))) {
		cout << "Введенные данные неверны";
		return -1;
	}
	cin.clear();
	root = addNode(NULL, rootName);
	cout << "Введите название первого узла\n";
	cin.getline(nodeName, sizeof(nodeName));
	TREE* current = addNode(root,nodeName,LEFT);
	while (vybor != 0)
	{
		cout << "1 - Вставка узла от корня влево\n2 - Вставка узла от корня вправо\n3 - Вставка узла от текущего влево\n4 - Вставка узла от текущего вправо\n0 - Завершить вставку в дерево\n";
		cin >> vybor;
		cin.ignore();
		switch (vybor)
		{
			case 1:{
				cout << "Введите название узла: ";
				if (cin.getline(nodeName, sizeof(nodeName))) {
					current = addNode(root->left, nodeName, LEFT);
				}
				break;
			}
			case 2: {
				cout << "Введите название узла: ";
				if (cin.getline(nodeName, sizeof(nodeName))) {
					current = addNode(root->right, nodeName, LEFT);
				}
	
				break;
			}
			case 3: {
				cout << "Введите название узла: ";
				cin.getline(nodeName, sizeof(nodeName));
				current = addNode(current, nodeName, LEFT);
				break;
			}
			case 4: {
				cout << "Введите название узла: ";
				cin.getline(nodeName, sizeof(nodeName));
				current = addNode(current, nodeName, RIGHT);
				break;
			}
			case 0: break;
			default: cout << "Введенные данные неверны!\n";
		}
	}
	vybor = 1;
	cout << "Введите название второго дерева\n";
	if (!cin.getline(rootName, sizeof(rootName))) {
		cout << "Введенные данные неверны";
		return -1;
	}
	newRoot = addNode(NULL, rootName);
	cout << "Введите название первого узла\n";
	cin.getline(nodeName, sizeof(nodeName));
	TREE* newCurrent = addNode(newRoot, nodeName, LEFT);
	while (vybor != 0)
	{
		cout << "1 - Вставка узла от корня влево\n2 - Вставка узла от корня вправо\n3 - Вставка узла от текущего влево\n4 - Вставка узла от текущего вправо\n0 - Завершить вставку в дерево\n";
		cin >> vybor;
		cin.ignore();
		switch (vybor)
		{
		case 1: {
			cout << "Введите название узла: ";
			cin.getline(nodeName, sizeof(nodeName));
			newCurrent = addNode(newRoot->left, nodeName, LEFT);
			break;
		}
		case 2: {
			cout << "Введите название узла: ";
			cin.getline(nodeName, sizeof(nodeName));
			newCurrent = addNode(newRoot->right, nodeName, LEFT);
			break;
		}
		case 3: {
			cout << "Введите название узла: ";
			cin.getline(nodeName, sizeof(nodeName));
			newCurrent = addNode(newCurrent, nodeName, LEFT);
			break;
		}
		case 4: {
			cout << "Введите название узла: ";
			cin.getline(nodeName, sizeof(nodeName));
			newCurrent = addNode(newCurrent, nodeName, RIGHT);
			break;
		}
		case 0: break;
		default: cout << "Введенные данные неверны!\n";
		}
	}
	cout << "Вывод первого дерева\n";
	showTREE(root);
	cout << "Вывод второго дерева\n";
	showTREE(newRoot);
	cout << "Замена второго дерева на первое\n";
	replaceTree();
	cout << "Вывод замсененого дерева\n";
	showTREE(root);
	cout << "Удаление дерева\n";
	delTree(root);
	root = NULL;
	return 0;
}

