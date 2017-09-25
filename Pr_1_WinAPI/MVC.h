#pragma once
#include "stdafx.h"
#include "Pr1WinAPI.h"
#include <string>
#include <initializer_list>
#include <iostream>
#include <sstream>
using namespace std;

template<class T>
class Model;

template<class T>
class View;

template<class T>
class Controller;


template<class T>
class View
{
	Model<T> model_1, model_2;
public:
	View() {};
	View(Model<T>& m1, Model<T>& m2)
	{
		model_1 = m1;
		model_2 = m2;
	}
	INT_PTR CALLBACK ButtonEvent(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case ID_ENTER1:
			{
				auto item = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, true);
				cnt.AddItem_1(item, hDlg);
				break;
			}
			case ID_ENTER2:
			{
				auto item = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, true);
				cnt.AddItem_2(item, hDlg);
				break;
			}
			case IDC_INTERSECTION:
			{
				cnt.Intersection(hDlg);
				break;
			}
			case IDC_UNION:
			{
				cnt.Union(hDlg);
				break;
			}
			case IDC_ELEMENTS:
			{
				cnt.Elements(hDlg);
				break;
			}
			case IDCANCEL:
				EndDialog(hDlg, LOWORD(wParam));
				DestroyWindow(GetParent(hDlg));
				return (INT_PTR)TRUE;
				break;
			}
			break;
		}
		return (INT_PTR)FALSE;
	}
	void Display(HWND h, Model<T> m, int IDC)
	{
		basic_stringstream<TCHAR> str;
		for (int i = 0; i < m.Size(); i++)
		{
			str << _T(' ') << m.Get_Pos(i);
		}
		SetDlgItemText(h, IDC, str.str().c_str());
	}
};

template<class T>
class Controller
{
	Model<T> model_1, model_2;
	View<T> view;
public:
	Controller(Model<T>& m1, Model<T>& m2, View<T>& v)
	{
		model_1 = m1;
		model_2 = m2;
		view = v;
	}
	void AddItem_1(T item, HWND h)
	{
		if (typeid(T) == typeid(item))
		{
			model_1.Insert(item);
			view.Display(h, model_1, IDC_STATIC_1);
		}
	}
	void AddItem_2(T item, HWND h)
	{
		if (typeid(T) == typeid(item))
		{
			model_2.Insert(item);
			view.Display(h, model_2, IDC_STATIC_2);
		}
	}
	void Intersection(HWND h)
	{
		view.Display(h, model_1 * model_2, IDC_STATIC_INTERSECTION);
	}
	void Union(HWND h)
	{
		view.Display(h, model_1 + model_2, IDC_STATIC_UNION);
	}
	void Elements(HWND h)
	{
		view.Display(h, model_1 + model_2, IDC_CONTROL_ELEMENTS);
	}
};

template<typename T>
struct Node
{
	T info;
	Node *next;
};

template<class T>
class iter_class
{
	Node<T>* ptr;
public:

	iter_class(Node<T>* p = NULL)
	{
		ptr = p;
	}
	iter_class<T>& operator = (const iter_class& i)
	{
		ptr = i.ptr;
		return this;
	}
	iter_class<T>& operator ++ (int)
	{
		iter_class<T>* p = new iter_class<T>(this->ptr);
		if (ptr != NULL)
			ptr = ptr->next;
		return *p;
	}
	iter_class<T>& operator ++ ()
	{
		if (ptr != NULL)
			ptr = ptr->next;
		return *this;
	}
	T& operator * (void)
	{
		if (ptr != NULL)
			return ptr->info;
		else
			cerr << "NULL iterator";
	}
};

template<typename T>
class Model
{
	Node<T>* tail;
	unsigned size = 0;
public:
	typedef iter_class<T> _iter;
	Model()
	{
		tail = NULL;
		size = 0;
	}
	Model(Model<T>&& other)
	{
		Node<T> *s;
		s = other.tail;
		for(auto i = 0; i < other.Size(); i++)
		{
			Insert(s->info);
			s = s->next;
		}
		other.Clear();
	}
	Model(const Model<T>& other) : Model()
	{
		Node<T> *s;
		s = other.tail;
		for(auto i = 0; i < other.Size(); i++)
		{
			Insert(s->info);
			s = s->next;
		}
	}
	Model(initializer_list<T> list)
	{
		for (auto& item : list)
		{
			if (!(this->Search(item)) || size == 0)
				this->Insert(item);
		}
		this->Sort();
	}
	Node<T>* create_Node(T);
	void Insert(T);
	T pop_back();
	T& Get_Pos(unsigned) const;
	unsigned Size() const;
	void Erase(unsigned);
	void Sort();
	bool Search(T) const;
	void Display();
	void Clear();
	_iter begin();
	_iter end();
	Model<T>& operator = (Model<T>&&);
	Model<T>& operator = (const Model<T>&);
	void operator+=(const Model<T>&);
	friend Model<T> operator+(const Model<T>& a, const Model<T>& b)
	{
		Model<T> buff(a);
		buff += b;
		buff.Sort();
		return buff;
	}
	void operator*=(const Model<T>&);
	Model<T>& operator-(const Model<T>&);
	void operator/=(const Model<T>&);
	Model<T>& operator/(const Model<T>&);
	void operator-=(const Model<T>&);
	friend Model<T> operator*(const Model<T>& a, const Model<T>& b)
	{
		Model<T> buff(a);
		buff *= b;
		buff.Sort();
		return buff;
	}
	bool operator==(const Model<T>&);
	void Swap(Model<T>&);
	~Model()
	{
		Clear();
	}
};

template<typename T>
Node<T> *Model<T>::create_Node(T value)
{
	Node<T> *temp;
	temp = new(Node<T>);
	if (temp == NULL)
	{
		return 0;
	}
	else
	{
		temp->info = value;
		temp->next = NULL;
		return temp;
	}
}
template<typename T>
void Model<T>::Insert(T value)
{
	if (!(this->Search(value)))
	{
		size++;
		Node<T> *temp, *p;
		temp = create_Node(value);
		if (tail == NULL)
		{
			tail = temp;
			tail->next = NULL;
		}
		else
		{
			p = tail;
			tail = temp;
			tail->next = p;
		}
		this->Sort();
	}
}
template<typename T>
T Model<T>::pop_back()
{
	Erase(0);
	return this->get_first();
}
template<typename T>
T& Model<T>::Get_Pos(unsigned pos) const
{
	T null = T();
	if (tail == NULL)
	{
		return null;
	}

	Node<T> *ptr;
	ptr = tail;
	if (pos >= 0 && pos < size)
	{
		for (int i = 0; i < pos; i++)
		{
			ptr = ptr->next;
		}
		return ptr->info;
	}
	else
	{
		return null;
	}
}
template<typename T>
unsigned Model<T>::Size() const
{
	return size;
}
template<typename T>
void Model<T>::Sort()
{
	Node<T> *ptr, *s;
	int value;
	if (tail == NULL)
	{
		return;
	}
	ptr = tail;
	while (ptr != NULL)
	{
		for (s = ptr->next; s != NULL; s = s->next)
			if (ptr->info > s->info)
			{
				value = ptr->info;
				ptr->info = s->info;
				s->info = value;
			}
		ptr = ptr->next;
	}
}
template<typename T>
void Model<T>::Erase(unsigned pos)
{
	if(tail == NULL)
		return;
	size--;
	Node<T> *s = tail, *ptr = new Node<T>;
	if(pos == 0)
		tail = s->next;
	else
	{
		if(pos > 0 && pos <= size)
		{
			for(auto i = 1; i < pos; i++)
			{
				ptr = s;
				s = s->next;
			}
			ptr->next = s->next;
		}
		else
		{
			size++;
		}
	}
	free(s);
}

template<typename T>
bool Model<T>::Search(T value) const
{
	int pos = 0;
	bool flag = false;
	if (tail == NULL)
	{
		return false;
	}
	Node<T> *s;
	s = tail;
	while (s != NULL)
	{
		pos++;
		if (s->info == value)
		{
			flag = true;
			return true;
		}
		s = s->next;
	}
	if (!flag)
		return false;
}
template<typename T>
void Model<T>::Display()
{
	Node<T> *temp;
	if (tail == NULL)
	{
		return;
	}
	temp = tail;
	while (temp != NULL)
	{
		temp = temp->next;
	}
}
template<typename T>
void Model<T>::Clear()
{
	while (tail != NULL)
		Erase(0);
}
template<typename T>
iter_class<T> Model<T>::end()
{
	Node<T>* s = tail;
	for (auto i = 0; i < Size(); i++)
		s = s->next;
	return iter_class<T>(s);
}
template<typename T>
iter_class<T> Model<T>::begin()
{
	return iter_class<T>(tail);
}
template<typename T>
Model<T>& Model<T>::operator = (Model<T>&& o)
{
	if (*this == o)
		return *this;
	this->Clear();
	Node<T> *s;
	s = o.tail;
	for (auto i = 0; i < o.Size(); i++)
	{
		Insert(s->info);
		s = s->next;
	}
	o.Clear();
	return *this;
}

template<typename T>
Model<T>& Model<T>::operator = (const Model<T>& o)
{
	if (*this == o)
		return *this;
	this->Clear();
	Node<T> *s;
	s = o.tail;
	for (auto i = 0; i < o.Size(); i++)
	{
		Insert(s->info);
		s = s->next;
	}
	return *this;
}


template<typename T>
void Model<T>::operator+=(const Model<T>& a)
{
	for (int i = 0; i < a.Size(); i++)
	{
		if (!(this->Search(a.Get_Pos(i))))
			this->Insert(a.Get_Pos(i));
	}
	this->Sort();
}

template<typename T>
void Model<T>::operator*=(const Model<T>& a)
{
	Model<T> buff;
	for (int i = 0; i < size; i++)
	{
		bool q = false;
		for (int j = 0; j < a.Size(); j++)
		{
			if (this->Get_Pos(i) == a.Get_Pos(j))
			{
				buff.Insert(a.Get_Pos(j));
			}
		}
	}
	this->Clear();
	*this = buff;
}
template<typename T>
void Model<T>::operator/=(const Model<T>& a)
{
	Model<T> buff;
	for (int i = 0; i < size; i++)
	{
		bool q = false;
		for (int j = 0; j < a.Size(); j++)
		{
			if (this->Get_Pos(i) == a.Get_Pos(j))
			{
				q = true;
			}
		}
		if (!q)
			buff.Insert(this->Get_Pos(i));
	}
	this->Clear();
	*this = buff;
}

template<typename T>
Model<T>& Model<T>::operator/(const Model<T>& a)
{
	Model<T> buff;
	for (int i = 0; i < size; i++)
	{
		if (!(a.Search(this->Get_Pos(i))))
			buff.Insert(this->Get_Pos(i));
	}
	buff.Sort();
	return buff;
}
template<typename T>
void Model<T>::operator-=(const Model<T>& a)
{
	Model<T> buff, buff1;
	for (int i = 0; i <= size; i++)
	{
		buff.Insert(this->Get_Pos(i));
	}
	for (int i = 0; i <= a.Size(); i++)
	{
		buff1.Insert(a.Get_Pos(i));
	}
	*this /= a;
	buff1 /= buff;
	*this += buff1;
}
template<typename T>
Model<T>& Model<T>::operator-(const Model<T>& a)
{
	Model<T> buff, res;
	for (int i = 0; i < size; i++)
	{
		buff.Insert(this->Get_Pos(i));
	}
	for (int i = 0; i < size; i++)
	{
		res.Insert(this->Get_Pos(i));
	}
	res /= a;
	a /= buff;
	res += a;
	return res;
}

template<typename T>
bool Model<T>::operator==(const Model<T>& a)
{
	if (this->size != a.size)
		return false;
	for (int i = 0; i < size; i++)
	{
		if (!(this->Search(a.Get_Pos(i))))
			return false;
	}
	return true;
}
template<typename T>
void Model<T>::Swap(Model<T>& a)
{
	Model<T> buff;
	for (int i = 1; i < size; i++)
	{
		buff.Insert(this->Get_Pos(i));
	}

	this->Clear();
	*this = a;
	this->Sort();
	a = buff;
}

