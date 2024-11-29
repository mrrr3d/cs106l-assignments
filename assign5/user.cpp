#include "user.h"
#include <ostream>

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */

std::ostream&
operator << (std::ostream& out, const User& user)
{
  out << "User(name=" << user.get_name() << ", friends=[";
  for (int i = 0;i < user._size ; ++i)
  {
    if (i)
    {
      out << ", ";
    }
    out << user._friends[i];
  }
  out << "])";
  return out;
}

User::~User()
{
  delete [] _friends;
}

User::User(const User& user)
{
  this->_name = user._name;
  this->_capacity = user._capacity;
  this->_size = user._size;

  this->_friends = new std::string[this->_capacity];
  for (int i = 0; i < user._size; ++i)
  {
    this->_friends[i] = user._friends[i];
  }
}

User&
User::operator= (const User& user)
{
  this->_name = user._name;
  this->_capacity = user._capacity;
  this->_size = user._size;

  // don't forget this, free the old value
  delete[] this->_friends;
  this->_friends = new std::string[this->_capacity];
  for (int i = 0; i < user._size; ++i)
  {
    this->_friends[i] = user._friends[i];
  }
  // return what? doubao helped me.....
  return *this;
}

User&
User::operator+= (User& user)
{
  this->add_friend(user.get_name());
  user.add_friend(this->get_name());

  return *this;
}

bool
// add `const' at the end of the line, otherwise error
User::operator< (const User& user) const
{
  return this->get_name() < user.get_name();
}