# Assignment 5: Treebook

Due Friday, November 8th at 11:59PM

## Overview

The newest Stanford social media startup is Treebook, and you’re a founding member
of the team! To get the product off the ground and compete with an unnamed,
completely legally unaffiliated app from Harvard, you’ve been assigned the task of
implementing user profiles.

For this assignment, you will be implementing parts of a class to allow for operator
overloads, as well as to remove some aspects of the special member functions.

There are three files you'll work with for this assignment:

* `user.h` - Contains the declaration for the `User` class that you will extend with special member functions and operators.
* `user.cpp` - Contains the definition of the `User` class.

To download the starter code for this assignment, please see the instructions for [**Getting Started**](../README.md#getting-started) on the course assignments repository.

## Part 1: Viewing Profiles

Take a look at the `user.h` header file. Your coworkers have begun to write a `User` class that will store the name and friends list of each user who joins your social media platform! In order to keep this class super efficient, they have chosen to represent the list of friends as a raw pointer array of `std::string` (kind of like how a `std::vector` stores its elements behind the scenes). Thankfully, they have already written logic for creating a new `User` and for adding friends to an existing `User`'s friend list (`add_friend`), but they've begun to experience some strange issues when working with `User` objects.    

To begin with, there's no easy way to print information about each `User` object to the console, which has made debugging at Treebook difficult. To help your coworkers out, write an `operator<<` method that prints a `User` to a `std::ostream`. **This operator should be declared as a non-member function in `user.h` and implemented in `user.cpp`.** For example, a user named `"Alice"` with friends `"Bob"` and `"Charlie"` should give the following output when printed to the console:

```
User(name=Alice, friends=[Bob, Charlie])
```

## Part 2: Unfriendly Behaviour

With the help of your `operator<<`, your coworkers have been able to make good progress on the social media app. However, they can't quite wrap their head around some seemingly bizzare issues that occur when they try to make copies of `User` objects in memory. Having recently taken CS106L, you suspect that it might have something to do with the special member functions (or the lack thereof) on the `User` class.