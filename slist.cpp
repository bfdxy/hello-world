#include <iostream>
#include<string>
using namespace std;
template <class T>
class AStack
{
private:
	int size;
	T *stackArray;
	int top;
public:
	AStack(int MaxStackSize)
	{
		size = MaxStackSize;
		stackArray = new T[MaxStackSize];
		top = -1;
	}
	~AStack() { delete[] stackArray; }
	bool Push(const T &item)
	{
		if (IsFull())
		{
			cout << "Pushing into a full stack!" << endl;
			return false;
		}
		stackArray[++top] = item;
		return true;
	}
	bool Pop(T &item)
	{
		if (IsEmpty())
		{
			//cout<<"Poping from an empty stack!"<<endl;
			return false;
		}
		item = stackArray[top--];
		//cout<<item<<endl;
		return true;
	}
	bool Peek(T &item)const
	{
		if (IsEmpty())
		{
			cout << "Peeking from an empty stack!" << endl;
		}
		item = stackArray[top];
		return true;
	}
	int IsEmpty()const { return top == -1; }
	int IsFull()const { return top == size - 1; }
	void clear() { top = -1; }
};

template<class T>
class SLNode
{
public:
	T data;
	SLNode<T> *next;
	SLNode(SLNode *nextNode = NULL) { next = nextNode; }
	SLNode(const T &item, SLNode *nextNode = NULL) { data = item; next = nextNode; }
};
template<class T>
class SLList
{
private:
	SLNode<T> *head;
	SLNode<T> *tail;
	SLNode<T> *currptr;
	int size;
public:
	SLList();
	SLList(T &item);
	~SLList(void);
	bool IsEmpty(void)const { return head->next == head; };
	int length(void)const { return size; }
	bool Find(int k, T &item)const;
	int Search(const T &item)const;
	void Insert(const T &item);
	void InsertFromTail(const T &item);
};

template<class T>
SLList<T>::SLList() //生成空表
{
	head = tail = currptr = new SLNode<T>(head);
	size = 0;
}
template<class T>
SLList<T>::SLList(T &item)   //生成含一节点表
{
	tail = currptr = new SLNode<T>(item, head);
	head = new SLNode<T>(currptr);
	size = 1;
}
template<class T>
SLList<T>::~SLList()     //析构
{
	while (!IsEmpty())
	{
		currptr = head->next;
		head->next = currptr->next;
		delete currptr;
	}
	delete head;
}
template<class T>
bool SLList<T>::Find(int k, T &item)const
{
	if (k<1 || k>size)
	{
		cout << "存取位置不合法" << endl;
		return false;
	}
	SLNode<T> *p;
	p = head->next;
	int i;
	for (i = 1; i<k; i++)
		p = p->next;
	item = p->data;
	//cout<<"第"<<k<<"项值为"<<item<<endl;
	return true;
}

template<class T>
int SLList<T>::Search(const T &item)const
{
	int k;
	SLNode<T> *p;
	p = head->next;
	for (k = 1; k <= size; k++)
	{
		if (p->data == item)
		{
			cout << item << "位于链表中的第" << k << "项" << endl;
			return k;
		}
		p = p->next;
	}
	cout << "链表中无值为" << item << "的项" << endl;
	return -1;
}
template<class T>
void SLList<T>::Insert(const T &item)      //在当前节点后插入
{
	currptr->next = new SLNode<T>(item, currptr->next);
	if (tail == currptr)
		tail = currptr->next;
	size++;
}
template<class T>
void SLList<T>::InsertFromTail(const T &item)    //在表尾插入
{
	tail->next = new SLNode<T>(item, head);
	tail = tail->next;
	size++;
}


void InPut(string &s, SLList<char> &sl)
{

	int i;
	for (i = 0; i<s.size(); i++)
		sl.InsertFromTail(s[i]);
}
bool Check(SLList<char> &sl)
{
	AStack<char> stack(100);
	char c, d;
	int i;
	for (i = 1; i <= sl.length(); i++)
	{
		sl.Find(i, c);
		if (c == '(' || c == '[' || c == '{')
			stack.Push(c);
		if (c == ')' || c == ']' || c == '}')
		{
			if (!stack.Pop(d))
			{
				cout << "括号不匹配！" << endl;
				cout << "右括号多余" << endl;
				return false;
			}
			if (c != d + 1 && c != d + 2)
			{
				cout << "括号不匹配！" << endl;
				cout << "位置：" << i << endl;
				return false;
			}
		}

	}
	if (!stack.IsEmpty())
	{
		//cout << "括号不匹配！" << endl;
		//cout << "左括号多余" << endl;
		return false;
	}
	cout << "括号匹配!" << endl;
	return true;
}

int main()
{
	SLList<char> list;
	string s;
	//cout << "请输入算术表达式s：" << endl;
	cin >>s;
	InPut(s, list);
	Check(list);
	return 0;
}
