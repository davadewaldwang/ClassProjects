#include <initializer_list>
#include <iostream>

// Class declarations
class Set;
class Node;

// Function declarations
// Prints elements of the set (this code is given below)
std::ostream &operator<<(std::ostream &out, Set const &rhs);

// Class definitions
class Set
{
public:
	// This is new and will be clearly explained
	Set(std::initializer_list<int> initial_values); // done
	~Set();

	// The instructions will describe exactly what to do
	Set(Set const &orig);
	Set(Set &&orig);

	// The instructions will describe exactly what to do
	Set &operator=(Set const &orig);
	Set &operator=(Set &&orig);

	bool empty() const;		  // done
	std::size_t size() const; // done

	// Clear all items out of the set
	void clear();

	// Find the value item in the set
	//  - Return the address of the node if found,
	//    and nullptr otherwise.
	Node *find(int const &item) const;

	// Insert the item into the set if it
	// is not already in the set.
	//  - Return 1 if the item is new,
	//    and 0 otherwise.
	std::size_t insert(int const &item);

	// Insert all the items in the array
	// from array[begin] to array[end - 1]
	// that are not already in the set.
	//  - Return the number of items inserted
	//    into the set.
	std::size_t insert(int const array[], std::size_t const begin, std::size_t const end);

	// Remove the item from the set and
	// return the number of items removed.
	std::size_t erase(int const &item);

	// Move any items from 'other', whose values
	// do not appear in 'this', to 'this'.
	// Leave any items that already appear
	// in both sets, in both sets.
	std::size_t merge(Set &other);

	// Set operations (Automatic Assigment)
	Set &operator|=(Set const &other); // union
	Set &operator&=(Set const &other); // intersection
	Set &operator^=(Set const &other); // symmetric difference
	Set &operator-=(Set const &other); // minus

	// Set operations (Binary)
	Set operator|(Set const &other) const; // union
	Set operator&(Set const &other) const; // intersection
	Set operator^(Set const &other) const; // symmetric difference
	Set operator-(Set const &other) const; // minus

	// Returns 'true' if 'this' set is a
	// superset of 'other' set; that is,
	// all entries in the 'other' set are
	// also in this set.
	bool operator>=(Set const &other) const;

	// A superset but not equal to.
	bool operator>(Set const &other) const;

	// Is 'this' a subset of the other set?
	bool operator<=(Set const &other) const;

	// A subset but not equal to.
	bool operator<(Set const &other) const;

	bool operator==(Set const &other) const;
	bool operator!=(Set const &other) const;

private:
	Node *p_head_;
	std::size_t size_;

	friend std::ostream &operator<<(std::ostream &out, Set const &rhs);
};

class Node
{
public:
	Node(int new_value, Node *new_next);
	int value() const;
	Node *next() const;

private:
	int value_;
	Node *next_;

	// Allow any member function in the class
	// 'Set' to access or modify the member
	// variables of any instance of this class.
	friend class Set;
};

Node::Node(int new_value, Node *new_next) : value_{new_value}, next_{new_next}
{
}

int Node::value() const
{
	return value_;
}

Node *Node::next() const
{
	return next_;
}

// You are given this function that prints out
// a set to the output stream.
std::ostream &operator<<(std::ostream &out, Set const &rhs)
{
	out << "{";

	if (!rhs.empty())
	{
		out << rhs.p_head_->value();

		for (Node *ptr{rhs.p_head_->next()}; ptr != nullptr; ptr = ptr->next())
		{
			out << ", " << ptr->value();
		}
	}

	out << "}";

	return out;
}

Set::Set(std::initializer_list<int> initial_values) : p_head_{nullptr}, size_{0}
{
	for (int const &value : initial_values)
	{
		insert(value);
	}
}

Set::Set(Set const &orig) : p_head_{nullptr}, size_{0}
{
	for (Node *current{orig.p_head_}; current != nullptr; current = current->next())
	{
		insert(current->value_);
	}
}

Set::Set(Set &&orig) : p_head_{nullptr}, size_{0}
{
	std::swap(p_head_, orig.p_head_);
	std::swap(size_, orig.size_);
}

bool Set::empty() const
{
	if (p_head_ == nullptr)
		return true;
	else
		return false;
}

std::size_t Set::size() const
{
	return size_;
}

Node *Set::find(int const &item) const
{
	Node *current{p_head_}; // set pointer current to head node
	while (current != nullptr)
	{
		if (current->value_ == item)
			return current;
		current = current->next_; // move to next node
	}
	return nullptr; // return nullptr if not in set
}

std::size_t Set::insert(int const &item)
{
	if (find(item) != nullptr) // if item is already in set return 0
		return 0;
	Node *new_node{new Node(item, p_head_)}; // create new node with value item at head of list
	p_head_ = new_node;						 // set head to new node
	size_++;
	return 1;
}

std::size_t Set::insert(int const array[], std::size_t const begin, std::size_t const end)
{
	std::size_t count{0};
	for (std::size_t i = begin; i < end; i++)
	{
		if (find(array[i]) != nullptr) // if item is already in set return 0
			continue;
		Node *new_node{new Node(array[i], p_head_)}; // create new node with value item at head of list
		p_head_ = new_node;							 // set head to new node
		size_++;
		count++;
	}
	return count;
}

std::size_t Set::erase(int const &item)
{
	Node *erase{find(item)};
	if (erase == nullptr)
		return 0;
	if (erase == p_head_)
	{
		p_head_ = erase->next_;
	}
	else
	{
		Node *prev{p_head_};		 // find node before erase
		while (prev->next_ != erase) // check if the next node is erase
		{
			prev = prev->next_; // move to next node
		}
		prev->next_ = erase->next_;
	}
	delete erase;
	size_--;
	return 1;
}

std::size_t Set::merge(Set &other)
{
	std::size_t count{0};
	Node *current_other{other.p_head_};
	while (current_other != nullptr)
	{
		// std::cout << current_other->value_ << std::endl;
		if (find(current_other->value_) == nullptr) // if value in other is not in this
		{
			other.p_head_ = current_other->next_; // set other head to next from current
			current_other->next_ = p_head_;		  // point current's next to head of this
			p_head_ = current_other;			  // set this's head to current
			size_++;
			other.size_--;
			count++;
		}
		else
		{
			other.p_head_ = current_other->next_;
		}
		current_other = other.p_head_; // move current to next
	}
	return count;
}

void Set::clear()
{
	while (p_head_ != nullptr)
	{
		Node *current{p_head_->next_}; // create new pointer at head's next
		delete p_head_;				   // delete head and move to next
		p_head_ = current;
	}
	size_ = 0;
}

Set::~Set()
{
	clear();
}

Set &Set::operator=(Set const &orig)
{
	if (this == &orig)
		return *this;
	clear();
	for (Node *current{orig.p_head_}; current != nullptr; current = current->next())
	{
		insert(current->value_);
	}
	return *this;
}

Set &Set::operator=(Set &&orig)
{
	std::swap(p_head_, orig.p_head_);
	std::swap(size_, orig.size_);
	return *this;
}

// Set operations (Automatic Assigment)
Set &Set::operator|=(Set const &other) // union
{
	for (Node *current{other.p_head_}; current != nullptr; current = current->next_)
	{
		insert(current->value_);
	}
	return *this;
}

Set &Set::operator&=(Set const &other) // intersection
{
	for (Node *current{p_head_}; current != nullptr;)
	{
		Node *temp{current->next_};
		if (other.find(current->value_) == nullptr)
		{
			erase(current->value_);
		}
		current = temp;
	}
	return *this;
}

Set &Set::operator^=(Set const &other) // symmetric difference
{
	for (Node *current{other.p_head_}; current != nullptr; current = current->next_)
	{
		if (find(current->value_) != nullptr)
			erase(current->value_);
		else
			insert(current->value_);
	}
	return *this;
}

Set &Set::operator-=(Set const &other) // minus
{
	for (Node *current{other.p_head_}; current != nullptr; current = current->next_)
	{
		erase(current->value_);
	}
	return *this;
}

// Set operations (Binary)
Set Set::operator|(Set const &other) const // union
{
	Set temp{*this};
	temp |= other;
	return temp;
}

Set Set::operator&(Set const &other) const // intersection
{
	Set temp{*this};
	temp &= other;
	return temp;
}

Set Set::operator^(Set const &other) const // symmetric difference
{
	Set temp{*this};
	temp ^= other;
	return temp;
}

Set Set::operator-(Set const &other) const // minus
{
	Set temp{*this};
	temp -= other;
	return temp;
}

// // Returns 'true' if 'this' set is a
// // superset of 'other' set; that is,
// // all entries in the 'other' set are
// // also in this set.
bool Set::operator>=(Set const &other) const
{
	for (Node *current{other.p_head_}; current != nullptr; current = current->next_)
	{
		if (find(current->value_) == nullptr)
			return false;
	}
	return true;
}

// // A superset but not equal to.
bool Set::operator>(Set const &other) const
{
	if (*this >= other && size_ != other.size_)
		return true;
	return false;
}

// // Is 'this' a subset of the other set?
bool Set::operator<=(Set const &other) const
{
	return other >= *this;
}

// // A subset but not equal to.
bool Set::operator<(Set const &other) const
{
	return other > *this;
}

bool Set::operator==(Set const &other) const
{
	return (*this <= other && *this >= other);
}

bool Set::operator!=(Set const &other) const
{
	return !(*this == other);
}