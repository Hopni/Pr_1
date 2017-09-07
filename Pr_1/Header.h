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
	KSet(const KSet<T>&& o) : KSet()
	{
		*this = o;
	}
	KSet(std::initializer_list<T> list)
	{
		for (auto& item : list)
		{
			bool q = true;
			for (int i = 1; i < size; i++)
			{
				if (item == this->get_pos(i))
					q = false;
			}
			if(q)
				this->push_back(item);
		}
		this->sort();
	}
	Node<T>* create_Node(T);
	void push_back(T);
	void insert_pos(T, unsigned);
	void push_front(T);
	T pop_back();
	T& get_first() const;
	T& get_pos(unsigned) const;
	unsigned get_size() const;
	void delete_pos(unsigned);
	void sort();
	bool search(T) const;
	void update(T, unsigned);
	void reverse();
	void display();
	void erase();
	_iter begin();
	_iter end();
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
		erase();
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
void KSet<T>::push_back(T value)
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
	T val = get_first();
	delete_pos(1);
	return val;
}
template<typename T>
T& KSet<T>::get_first() const
{
	return get_pos(1);
}
template<typename T>
T& KSet<T>::get_pos(unsigned pos) const
{
	T def = T();
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
		return def;
	}
	Node<T> *s, *ptr;
	s = tail;
	if (pos > 0 && pos <= size)
	{
		for (int i = 1; i < pos; i++)
		{
			ptr = s;
			s = s->next;
		}
		return s->info;
	}
	else
	{
		cout << "\nPosition out of range" << endl;
		return def;
	}
}
template<typename T>
unsigned KSet<T>::get_size() const
{
	return size;
}
template<typename T>
void KSet<T>::insert_pos(T value, unsigned pos)
{
	size++;
	int counter = 0;
	Node<T> *temp, *s, *ptr;
	temp = create_Node(value);
	if (pos == 1)
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
	}
	else if (pos > 1 && pos <= size)
	{
		s = tail;
		for (auto i = 1; i < pos; i++)
		{
			ptr = s;
			s = s->next;
		}
		ptr->next = temp;
		temp->next = s;
	}
	else
	{
		cout << "\nPositon out of range" << endl;
		size--;
	}
}
template<typename T>
void KSet<T>::sort()
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
void KSet<T>::delete_pos(unsigned pos)
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
bool KSet<T>::search(T value) const
{
	int pos = 0;
	bool flag = false;
	if (tail == NULL)
	{
		cout << "\nList is empty" << endl;
		return 0;
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
void KSet<T>::display()
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
void KSet<T>::erase()
{
	while (tail != NULL)
		delete_pos(1);
}
template<typename T>
iter_class<T> KSet<T>::end()
{
	Node<T>* s = tail;
	for (auto i = 1; i < get_size(); i++)
		s = s->next;
	return iter_class<T>(s);
}
template<typename T>
iter_class<T> KSet<T>::begin()
{
	return iter_class<T>(tail);
}
template<typename T>
KSet<T>& KSet<T>::operator = (KSet<T>& o)
{
	erase();
	Node<T> *s;
	s = o.tail;
	for (auto i = 1; i <= o.get_size(); i++)
	{
		push_back(s->info);
		s = s->next;
	}
	o.erase();
	return *this;
}

template<typename T>
void KSet<T>::operator+=(const KSet<T>& a)
{
	for (int i = 1; i <= a.get_size(); i++)
	{
		if (!(this->search(a.get_pos(i))))
			this->push_back(a.get_pos(i));
	}
	this->sort();
}

template<typename T>
KSet<T>& KSet<T>::operator+(const KSet<T>& a)
{
	KSet<T> buff;
	for (int i = 1; i < size; i++)
	{
		buff.push_back(this->get_pos(i));
	}
	for (int i = 0; i < a.get_size(); i++)
	{
		if (!(this->search(a.get_pos(i))))
			buff.push_back(a.get_pos(i));
	}
	buff.sort();
	return buff;
}

template<typename T>
void KSet<T>::operator*=(const KSet<T>& a)
{
	KSet<T> buff;
	for (int i = 1; i <= size; i++)
	{
		bool q = false;
		for (int j = 1; j <= a.get_size(); j++)
		{
			if (this->get_pos(i) == a.get_pos(j))
			{
				buff.push_back(a.get_pos(j));
			}
		}
	}
	this->erase();
	for (int i = 0; i < buff.get_size(); i++)
		this->push_back(buff.get_pos(i + 1));
}

template<typename T>
KSet<T>& KSet<T>::operator*(const KSet<T>& a)
{
	KSet<T> buff;
	for (int i = 1; i <= size; i++)
	{
		bool q = false;
		for (int j = 0; j <= a.get_size(); j++)
		{
			if (this->get_pos(i) == a.get_pos(j))
				q = true;
		}
		if (q)
			buff.push_back(this->get_pos(i));
	}
	buff.sort();
	return buff;
}

template<typename T>
void KSet<T>::operator/=(const KSet<T>& a)
{
	KSet<T> buff;
	for (int i = 1; i <= size; i++)
	{
		bool q = false;
		for (int j = 1; j <= a.get_size(); j++)
		{
			if (this->get_pos(i) == a.get_pos(j))
			{
				q = true;
			}
		}
		if (!q)
			buff.push_back(this->get_pos(i));
	}
	this->erase();
	for (int i = 0; i < buff.get_size(); i++)
		this->push_back(buff.get_pos(i + 1));
}

template<typename T>
KSet<T>& KSet<T>::operator/(const KSet<T>& a)
{
	KSet<T> buff;
	for (int i = 1; i < size; i++)
	{
		if (!(a.search(this->get_pos(i))))
			buff.push_back(this->get_pos(i));
	}
	buff.sort();
	return buff;
}

template<typename T>
void KSet<T>::operator-=(const KSet<T>& a)
{
	KSet<T> buff, buff1;
	for (int i = 1; i <= size; i++)
	{
		buff.push_back(this->get_pos(i));
	}
	for (int i = 1; i <= a.get_size(); i++)
	{
		buff1.push_back(a.get_pos(i));
	}
	*this /= a;
	buff1 /= buff;
	*this += buff1;
}

template<typename T>
KSet<T>& KSet<T>::operator-(const KSet<T>& a)
{
	KSet<T> buff, res;
	for (int i = 1; i < size; i++)
	{
		buff.push_back(this->get_pos(i));
	}
	for (int i = 1; i < size; i++)
	{
		res.push_back(this->get_pos(i));
	}
	res /= a;
	a /= buff;
	res += a;
	return res;
}

template<typename T>
bool KSet<T>::operator==(const KSet<T>& a)
{
	for (int i = 1; i < size; i++)
	{
		if (!(this->search(a.get_pos(i))))
			return false;
	}
	return true;
}

template<typename T>
bool KSet<T>::operator<=(const KSet<T>& a)
{
	int n = size < a.get_size() ? size : a.get_size();
	for (int i = 1; i < n; i++)
	{
		if (this->get_pos(i) > a.get_pos(i))
			return false;
	}
	return true;
}

template<typename T>
KSet<T>& KSet<T>::operator[](const KSet<T>& a)
{
	KSet<T> res;
	for (int j = 1, i = 1; j < a.get_size(); j++)
	{

	}
	res.sort();
	return res;
}

template<typename T>
void KSet<T>::Swap(KSet<T>& a)
{
	KSet<T> buff;
	for (int i = 1; i < size; i++)
	{
		buff.push_back(this->get_pos(i));
	}
	
	this->erase();
	for (int i = 1; i < a.get_size(); i++)
	{
		this->push_back(a.get_pos(i));
	}
	this->sort();
	a = buff;
}
