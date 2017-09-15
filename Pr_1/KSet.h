#pragma once

#include <initializer_list>

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
class KSet
{
	Node<T>* tail;
	unsigned size = 0;
public:
	typedef iter_class<T> _iter;
	KSet()
	{
		tail = NULL;
		size = 0;
	}
	KSet(const KSet<T>&& other) : KSet()
	{
		*this = other;
		other.Clear();
	}
	KSet(const KSet<T>& other) : KSet()
	{
		Node<T> *s;
		s = other.tail;
		for (auto i = 0; i < other.Size(); i++)
		{
			Insert(s->info);
			s = s->next;
		}
	}
	KSet(std::initializer_list<T> list)
	{
		for (auto& item : list)
		{
			if(!(this->Search(item)) || size == 0)
				this->Insert(item);
		}
		this->Sort();
	}
	Node<T>* create_Node(T);
	void Insert(T);
	void insert_pos(T, unsigned);
	void push_front(T);
	T pop_back();
	T& get_first() const;
	T& Get_Pos(unsigned) const;
	unsigned Size() const;
	void Erase(unsigned);
	void Sort();
	bool Search(T) const;
	void update(T, unsigned);
	void reverse();
	void Display();
	void Clear();
	_iter begin();
	_iter end();
	KSet<T>& operator = (KSet<T>&&);
	KSet<T>& operator = (KSet<T>&);
	void operator+=(const KSet<T>&);
	KSet<T>& operator+(const KSet<T>&);
	void operator*=(const KSet<T>&);
	KSet<T>& operator*(const KSet<T>&);
	void operator/=(const KSet<T>&);
	KSet<T>& operator/(const KSet<T>&);
	void operator-=(const KSet<T>&);
	KSet<T>& operator-(const KSet<T>&);
	bool operator==(const KSet<T>&);
	bool operator<=(const KSet<T>&);
	KSet<T>& operator[](const KSet<T>&);
	void Swap(KSet<T>&);
	~KSet()
	{
		Clear();
	}
};

template<typename T>
Node<T> *KSet<T>::create_Node(T value)
{
	Node<T> *temp;
	temp = new(Node<T>);
	if (temp == NULL)
	{
		cout << "Memory not allocated " << endl;
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
void KSet<T>::Insert(T value)
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
void KSet<T>::push_front(T value)
{
	size++;
	Node<T> *temp, *s;
	temp = create_Node(value);
	s = tail;
	while (s->next != NULL)
		s = s->next;
	temp->next = NULL;
	s->next = temp;

}
template<typename T>
T KSet<T>::pop_back()
{
	Erase(0);
	return this->get_first();
}
template<typename T>
T& KSet<T>::get_first() const
{
	return Get_Pos(0);
}
template<typename T>
T& KSet<T>::Get_Pos(unsigned pos) const
{
	T null = T();
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
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
		cout << "\nPosition out of range" << endl;
		return null;
	}
}
template<typename T>
unsigned KSet<T>::Size() const
{
	return size;
}
template<typename T>
void KSet<T>::insert_pos(T value, unsigned pos)
{
	Node<T> *temp, *s, *ptr;
	temp = create_Node(value);
	if (pos == 0)
	{
		if (tail == NULL)
		{
			tail = temp;
			tail->next = NULL;
		}
		else
		{
			ptr = tail;
			tail = temp;
			tail->next = ptr;
		}
		size++;
	}
	else if (pos > 0 && pos < size)
	{
		s = tail;
		for (auto i = 0; i < pos - 1; i++)
		{
			s = s->next;
		}
		ptr = s->next;
		s->next = temp;
		temp->next = ptr;
		size++;
	}
	else
	{
		cout << "\nPositon out of range" << endl;
	}
}
template<typename T>
void KSet<T>::Sort()
{
	Node<T> *ptr, *s;
	int value;
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
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
void KSet<T>::Erase(unsigned pos)
{
	if (tail == NULL)
		return;
	size--;
	Node<T> *s = tail, *ptr = new Node<T>;
	if (pos == 1)
		tail = s->next;
	else
	{
		if (pos > 0 && pos <= size)
		{
			for (auto i = 1; i < pos; i++)
			{
				ptr = s;
				s = s->next;
			}
			ptr->next = s->next;
		}
		else
		{
			cout << "\nPosition out of range" << endl;
			size++;
		}
	}
	free(s);
}
template<typename T>
void KSet<T>::update(T value, unsigned pos)
{
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
		return;
	}
	Node<T> *s, *ptr;
	s = tail;
	if (pos == 1)
		tail->info = value;
	else
	{
		for (auto i = 0; i < pos - 1; i++)
		{
			if (s == NULL)
			{
				cout << "\nThere are less than " << pos << " elements";
				return;
			}
			s = s->next;
		}
		s->info = value;
	}
}
template<typename T>
bool KSet<T>::Search(T value) const
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
void KSet<T>::reverse()
{
	Node<T> *ptr1, *ptr2, *ptr3;
	if (tail == NULL)
		return;
	if (tail->next == NULL)
		return;
	ptr1 = tail;
	ptr2 = ptr1->next;
	ptr3 = ptr2->next;
	ptr1->next = NULL;
	ptr2->next = ptr1;
	while (ptr3 != NULL)
	{
		ptr1 = ptr2;
		ptr2 = ptr3;
		ptr3 = ptr3->next;
		ptr2->next = ptr1;
	}
	tail = ptr2;
}
template<typename T>
void KSet<T>::Display()
{
	Node<T> *temp;
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
		return;
	}
	temp = tail;
	cout << "\nElements of list are: " << endl;
	while (temp != NULL)
	{
		cout << temp->info << " ";
		temp = temp->next;
	}
}
template<typename T>
void KSet<T>::Clear()
{
	while (tail != NULL)
		Erase(1);
}
template<typename T>
iter_class<T> KSet<T>::end()
{
	Node<T>* s = tail;
	for (auto i = 0; i < Size(); i++)
		s = s->next;
	return iter_class<T>(s);
}
template<typename T>
iter_class<T> KSet<T>::begin()
{
	return iter_class<T>(tail);
}
template<typename T>
KSet<T>& KSet<T>::operator = (KSet<T>&& o)
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
KSet<T>& KSet<T>::operator = (KSet<T>& o)
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
void KSet<T>::operator+=(const KSet<T>& a)
{
	for (int i = 0; i < a.Size(); i++)
	{
		this->Insert(a.Get_Pos(i));
	}
	this->Sort();
}

template<typename T>
KSet<T>& KSet<T>::operator+(const KSet<T>& a)
{
	KSet<T> buff(*this);
	buff += a;
	buff.Sort();
	return buff;
}

template<typename T>
void KSet<T>::operator*=(const KSet<T>& a)
{
	KSet<T> buff;
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
KSet<T>& KSet<T>::operator*(const KSet<T>& a)
{
	KSet<T> buff;
	for (int i = 0; i < size; i++)
	{
		bool q = false;
		for (int j = 0; j < a.Size(); j++)
		{
			if (this->Get_Pos(i) == a.Get_Pos(j))
				q = true;
		}
		if (q)
			buff.Insert(this->Get_Pos(i));
	}
	buff.Sort();
	return buff;
}

template<typename T>
void KSet<T>::operator/=(const KSet<T>& a)
{
	KSet<T> buff;
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
KSet<T>& KSet<T>::operator/(const KSet<T>& a)
{
	KSet<T> buff;
	for (int i = 0; i < size; i++)
	{
		if (!(a.Search(this->Get_Pos(i))))
			buff.Insert(this->Get_Pos(i));
	}
	buff.Sort();
	return buff;
}

template<typename T>
void KSet<T>::operator-=(const KSet<T>& a)
{
	KSet<T> buff, buff1;
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
KSet<T>& KSet<T>::operator-(const KSet<T>& a)
{
	KSet<T> buff, res;
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
bool KSet<T>::operator==(const KSet<T>& a)
{
	for (int i = 0; i < size; i++)
	{
		if (!(this->Search(a.Get_Pos(i))))
			return false;
	}
	return true;
}

template<typename T>
bool KSet<T>::operator<=(const KSet<T>& a)
{
	int n = size < a.Size() ? size : a.Size();
	for (int i = 0; i < n; i++)
	{
		if (this->Get_Pos(i) > a.Get_Pos(i))
			return false;
	}
	return true;
}

template<typename T>
KSet<T>& KSet<T>::operator[](const KSet<T>& a)
{
	KSet<T> res;
	for (int j = 0, i = 0; j < a.Size(); j++)
	{

	}
	res.Sort();
	return res;
}

template<typename T>
void KSet<T>::Swap(KSet<T>& a)
{
	KSet<T> buff;
	for (int i = 1; i < size; i++)
	{
		buff.Insert(this->Get_Pos(i));
	}
	
	this->Clear();
	*this = a;
	this->Sort();
	a = buff;
}
