// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include "gtest/gtest.h"

#include "Darwin.h"
#include <iostream>

using namespace std;

// ----
// test
// ----

// Test begin() function
TEST(DarwinFixture, darwin_begin) {
    Darwin d(4, 4);
    Darwin_It b =  d.begin();
    Darwin_It it = Darwin_It(d);
    ASSERT_FALSE(b != it);
}

TEST(DarwinFixture, darwin_begin2) {
    Darwin d(3, 3);
    Darwin_It b = d.begin();
    Darwin_It it = Darwin_It(d);
    ++b;
    ASSERT_TRUE(b != it);
}

TEST(DarwinFixture, darwin_begin3) {
    Darwin d(3, 3);
    Darwin_It b = d.begin();
    Darwin_It it = Darwin_It(d);
    ++b;
    ++it;
    ASSERT_FALSE(b != it);
}

TEST(DarwinFixture, darwin_begin4) {
    Darwin d(2, 2);
    Species f('f');
    Creature c(f,Direction::N);
    d.add_creature(c, 1, 1);
    Darwin_It b = d.begin();
    Darwin_It i = Darwin_It(d);
    ASSERT_FALSE(b != i);   
}

TEST(DarwinFixture, darwin_end1) {
    Darwin d(2, 2);
    Darwin_It e = d.end();
    Darwin_It it = Darwin_It(d);
    ++it;
    ++it;
    ++it;
    ++it;
    //  ++it;
    ASSERT_TRUE(e == it);
}

TEST(DarwinFixture, darwin_end2) {
    Darwin d(2 ,2);
    Darwin_It e = d.end();
    Darwin_It it = Darwin_It(d);
    ++it;
    ++it;
    ++it;
    ASSERT_FALSE(e == it);
}

TEST(DarwinFixture, darwin_add_creature1) {
    Darwin d(2, 2);
    Species f('f');
    Creature c(f, Direction::N);
    d.add_creature(c, 0, 0);
    Darwin_It it = d.begin();
    ASSERT_FALSE(*it != d.valid_space(0,0) );
}

TEST(DarwinFixture, darwin_add_creature2) {
    Darwin d(2, 2);
    Species f('f');
    Creature c(f, Direction::N);
    d.add_creature(c, 0, 1);
    Darwin_It it = d.begin();
    ++it;
    ASSERT_FALSE(*it != d.valid_space(0,1) );
}

TEST(DarwinFixture, darwin_add_creature3) {
    Darwin d(2, 2);
    Species f('f');
    Creature c(f, Direction::N);
    d.add_creature(c, 0, 0);
    Darwin_It it = d.begin();
    ++it;
    ASSERT_TRUE(*it != d.valid_space(0,0) );
}

TEST(DarwinFixture, species_add_instructions1) {
    Species f('f');
    f.add_instructions(Action_Control::HOP);
    ASSERT_EQ(f.instructions[0].first, Action_Control::HOP);
}

TEST(DarwinFixture, species_add_instructions2) {
    Species f('f');
    f.add_instructions(Action_Control::HOP);
    f.add_instructions(Action_Control::INFECT);
    ASSERT_EQ(f.instructions[1].first, Action_Control::INFECT);
}

TEST(DarwinFixture, species_add_instructions3) {
    Species f('f');
    f.add_instructions(Action_Control::HOP);
    f.add_instructions(Action_Control::GO, 0);
    ASSERT_EQ(f.instructions[1].second, 0);
}


// << operator for darwin board
TEST(DarwinFixture, darwin_const) {
    Darwin x(2 , 2);
    ostringstream w;
    w << x;
    ASSERT_EQ("Turn = 0\n  01\n0 ..\n1 ..\n\n", w.str());}   

TEST(DarwinFixture, darwin_const1) {
    Darwin x(3 , 3);
    ostringstream w;
    w << x;
    ASSERT_EQ("Turn = 0\n  012\n0 ...\n1 ...\n2 ...\n\n", w.str());}

TEST(DarwinFixture, darwin_const2) {
    Darwin x(4, 4);
    ostringstream w;
    w << x;
    ASSERT_EQ("Turn = 0\n  0123\n0 ....\n1 ....\n2 ....\n3 ....\n\n", w.str());}

// Basic darwin constructor 
TEST(DarwinFixture, darwin_const3) {
    Darwin dar(5, 10);
    ASSERT_EQ(5, dar.rows);
    ASSERT_EQ(10, dar.cols);
}

// Darwin constructor with big board
TEST(DarwinFixture, darwin_const5) {
    Darwin dar(100, 100);
    ASSERT_EQ(100, dar.rows);
    ASSERT_EQ(100, dar.cols);
}

// valid space
TEST(DarwinFixture, darwin_valid1) {
    Darwin d(3, 3);
    ASSERT_TRUE(d.valid_space(1, 2));
}

// invalid space with positive numbers
TEST(DarwinFixture, darwin_valid2) {
    Darwin d(3, 3);
    ASSERT_FALSE(d.valid_space(4, 4));
}

// invalid space with negative numbers
TEST(DarwinFixture, darwin_valid3) {
    Darwin d(3, 3);
    ASSERT_FALSE(d.valid_space(0, -1));
}

// species constructor with passed in label
TEST(DarwinFixture, species_const1) {
    Species food('f');
    ASSERT_EQ('f', food.rep);
}

// species print operator
TEST(DarwinFixture, spcies_print) {
    Species p('p');
    ostringstream w;
    w << p;
    ASSERT_EQ('p', *(w.str().c_str()));
}


// species print operator
TEST(DarwinFixture, spcies_print2) {
    Species p('b');
    ostringstream w;
    w << p;
    ASSERT_EQ('b', *(w.str().c_str()));
}  


// species print operator
TEST(DarwinFixture, species_print3) {
    Species p('p');
    ostringstream w;
    w << p;
    ASSERT_FALSE('g' == *(w.str().c_str()));
} 

// creature print operator 
TEST(DarwinFixture, creature_print2) {
    Species food('f');
    Creature c1(food, Direction::N);
    ostringstream w;
    w << c1;
    ASSERT_EQ('f', *(w.str().c_str()));
}


// creature print operator 
TEST(DarwinFixture, creature_print3) {
    Species food('b');
    Creature c1(food, Direction::N);
    ostringstream w;
    w << c1;
    ASSERT_EQ('b', *(w.str().c_str()));
}


// creature print operator 
TEST(DarwinFixture, creature_print4) {
    Species food('f');
    Creature c1(food, Direction::N);
    ostringstream w;
    w << c1;
    ASSERT_FALSE('g' == *(w.str().c_str()));
}

// Test the == operator 
TEST(DarwinFixture, it_equals) {
    Darwin dar(3, 3);
    Darwin_It d1(dar);
    Darwin_It d2 = dar.begin();
    ASSERT_TRUE(d1 == d2);
}


// Test the == operator  with bigger board
TEST(DarwinFixture, it_equals2) {
    Darwin dar(4, 4);
    Darwin_It d1(dar);
    Darwin_It d2 = dar.begin();
    ASSERT_TRUE(d1 == d2);
}

TEST(DarwinFixture, it_equals3) {
    Darwin dar(3, 3);
    Darwin_It d1(dar);
    Darwin_It d2 = ++d1;
    ++d1;
    ASSERT_FALSE(d1 == d2);
}
 
// Test the increment operator
TEST(DarwinFixture, it_increment2) {
    Darwin dar(3, 3);
    Darwin_It d1(dar);
    Darwin_It d2(dar);
    ++d1;
    ++d2;
    ASSERT_TRUE(d1 == d2);
}


// Test the increment operator
TEST(DarwinFixture, it_increment3) {
    Darwin dar(3, 3);
    Darwin_It d1(dar);
    Darwin_It d2(dar);
    ++d1;
    ASSERT_FALSE(d1 == d2);
}


// Test infect instruction
TEST(DarwinFixture, darwin_infect1) {
	Darwin dar(4, 4);

    Species food('f');
    food.add_instructions(Action_Control::LEFT);
    food.add_instructions(Action_Control::GO, 0);
    
    Species hopper('h');
    hopper.add_instructions(Action_Control::INFECT);
    hopper.add_instructions(Action_Control::GO, 0);
    
	Creature c(hopper, Direction::S);
	Creature f1(food, Direction::E);
	
	dar.add_creature(c, 2, 2);
	dar.add_creature(f1, 3, 2);
	
	dar.next_turn();
	
	ASSERT_TRUE((*dar.valid_space(2,2)).species == (*dar.valid_space(3,2)).species);
}

// Test infect instruction 2
TEST(DarwinFixture, darwin_infect2) {
	Darwin dar(5, 5);

    Species food('f');
    food.add_instructions(Action_Control::RIGHT);
    food.add_instructions(Action_Control::GO, 0);
    
    Species hopper('h');
    hopper.add_instructions(Action_Control::INFECT);
    hopper.add_instructions(Action_Control::GO, 0);
    
	Creature h(hopper, Direction::E);
	Creature f(food, Direction::E);
	
	dar.add_creature(h, 0, 2);
	dar.add_creature(f, 0, 3);
	
	dar.next_turn();

	ASSERT_TRUE((*dar.valid_space(0,2)).species == (*dar.valid_space(0,3)).species);
}

// Test infect instruction 3
TEST(DarwinFixture, darwin_infect3) {
	Darwin dar(4, 4);

    Species food('f');
    food.add_instructions(Action_Control::LEFT);
    food.add_instructions(Action_Control::GO, 0);
    
    Species hopper('h');
    hopper.add_instructions(Action_Control::INFECT);
    hopper.add_instructions(Action_Control::GO, 0);
    
	Creature c(hopper, Direction::N);
	Creature f(food, Direction::E);
	
	dar.add_creature(c, 3, 3);
	dar.add_creature(f, 2, 3);
	
	dar.next_turn();

	ASSERT_TRUE((*dar.valid_space(3,3)).species == (*dar.valid_space(2,3)).species);
}

// Test face_left
TEST(DarwinFixture, creature_face_left1) {
	Darwin dar(1, 1);
	Species food('f');
	food.add_instructions(Action_Control::LEFT);
    food.add_instructions(Action_Control::GO, 0);
    Creature f(food, Direction::N);
	dar.add_creature(f, 0, 0);
	dar.next_turn();
	ASSERT_TRUE(static_cast<Direction>((*dar.valid_space(0,0)).dir) == Direction::W);
}

// Test face_left
TEST(DarwinFixture, creature_face_left2) {
	Darwin dar(3, 3);
	Species food('f');
	food.add_instructions(Action_Control::LEFT);
    food.add_instructions(Action_Control::GO, 0);
    Creature f(food, Direction::E);
	dar.add_creature(f, 2, 2);
	dar.next_turn();
	ASSERT_TRUE(static_cast<Direction>((*dar.valid_space(0,0)).dir) == Direction::N);
}

// Test face_left
TEST(DarwinFixture, creature_face_left3) {
	Darwin dar(1, 1);
	Species food('f');
	food.add_instructions(Action_Control::LEFT);
    food.add_instructions(Action_Control::GO, 0);
    Creature f(food, Direction::S);
	dar.add_creature(f, 0, 0);
	dar.next_turn();
	ASSERT_TRUE(static_cast<Direction>((*dar.valid_space(0,0)).dir) == Direction::E);
}

// Test face_left
TEST(DarwinFixture, creature_face_left4) {
	Darwin dar(1, 1);
	Species food('f');
	food.add_instructions(Action_Control::LEFT);
    food.add_instructions(Action_Control::GO, 0);
    Creature f(food, Direction::W);
	dar.add_creature(f, 0, 0);
	dar.next_turn();
	ASSERT_TRUE(static_cast<Direction>((*dar.valid_space(0,0)).dir) == Direction::S);
}

// Test face_right
TEST(DarwinFixture, creature_face_right1) {
	Darwin dar(1, 1);	
	Species food('f');
	food.add_instructions(Action_Control::RIGHT);
    food.add_instructions(Action_Control::GO, 0);
    Creature f(food, Direction::N);
	dar.add_creature(f, 0, 0);
	dar.next_turn();
	ASSERT_TRUE(static_cast<Direction>((*dar.valid_space(0,0)).dir) == Direction::E);
}

// Test face_right
TEST(DarwinFixture, creature_face_right2) {
	Darwin dar(1, 1);	
	Species food('f');
	food.add_instructions(Action_Control::RIGHT);
    food.add_instructions(Action_Control::GO, 0);
    Creature f(food, Direction::E);
	dar.add_creature(f, 0, 0);
	dar.next_turn();
	ASSERT_TRUE(static_cast<Direction>((*dar.valid_space(0,0)).dir) == Direction::S);
}

// Test face_right
TEST(DarwinFixture, creature_face_right3) {
	Darwin dar(1, 1);	
	Species food('f');
	food.add_instructions(Action_Control::RIGHT);
    food.add_instructions(Action_Control::GO, 0);
    Creature f(food, Direction::S);
	dar.add_creature(f, 0, 0);
	dar.next_turn();
	ASSERT_TRUE(static_cast<Direction>((*dar.valid_space(0,0)).dir) == Direction::W);
}

// Test face_right
TEST(DarwinFixture, creature_face_right4) {
	Darwin dar(1, 1);	
	Species food('f');
	food.add_instructions(Action_Control::RIGHT);
    food.add_instructions(Action_Control::GO, 0);
    Creature f(food, Direction::W);
	dar.add_creature(f, 0, 0);
	dar.next_turn();
	ASSERT_TRUE(static_cast<Direction>((*dar.valid_space(0,0)).dir) == Direction::N);
}

// Test is_space, empty board
TEST(DarwinFixture, creature_is_space1) {
	Darwin dar(4, 4);
	Darwin_It darIt = dar.begin();
	ASSERT_TRUE((*darIt)->is_space()); 
}

// Test is_space, non-empty board
TEST(DarwinFixture, creature_is_space2) {
	Darwin dar(4, 4);
	Species food('f');
	Creature f(food);
	dar.add_creature(f, 0, 0);
	Darwin_It darIt = dar.begin();
	ASSERT_FALSE((*darIt)->is_space()); 
}

// Test is_space, non-empty board, empty space
TEST(DarwinFixture, creature_is_space3) {
	Darwin dar(4, 4);
	Species food('f');
	Creature f(food);
	dar.add_creature(f, 1, 1);
	Darwin_It darIt = dar.begin();
	ASSERT_TRUE((*darIt)->is_space()); 
}

// Test check_if_enemy, when true
TEST(DarwinFixture, creature_check_if_enemy1) {
	Darwin dar(5,5);
	Species food('f');
	Species animal('a');
	Creature f(food);
	Creature a(animal);
	dar.add_creature(f, 0, 0);
	dar.add_creature(a, 0, 1);
	ASSERT_TRUE((*dar.valid_space(0,0)).check_if_enemy((*dar.valid_space(0,1))));
}

// Test check_if_enemy, when not an enemy
TEST(DarwinFixture, creature_check_if_enemy2) {
	Darwin dar(3,3);
	Species food('f');
	Creature f1(food);
	Creature f2(food);
	dar.add_creature(f1, 0, 0);
	dar.add_creature(f2, 0, 1);
	ASSERT_FALSE((*dar.valid_space(0,0)).check_if_enemy((*dar.valid_space(0,1))));
}

// Test check_if_enemy, when checking empty space
TEST(DarwinFixture, creature_check_if_enemy3) {
	Darwin dar(3,3);
	Species food('f');
	Creature f1(food);
	Creature f2(food);
	dar.add_creature(f1, 0, 0);
	ASSERT_FALSE((*dar.valid_space(0,0)).check_if_enemy((*dar.valid_space(0,1))));
}

// Test do_instr by checking the counter
TEST(DarwinFixture, creature_do_inst1) {
	Darwin dar(2,2);
	Species food('f');
	food.add_instructions(Action_Control::LEFT);
	food.add_instructions(Action_Control::INFECT);
	food.add_instructions(Action_Control::GO, 0);
	Creature f(food);
	dar.add_creature(f, 0, 0);
	Darwin_It darIt = dar.begin();
	int counter = f.counter;
	f.do_inst(dar, darIt);
	ASSERT_TRUE(f.counter == counter + 1);
}



