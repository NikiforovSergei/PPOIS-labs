#include "gtest/gtest.h"
#include "pch.h"
#include "../stack_machine/interpreter.h"
#include "../stack_machine//interpreter.cpp"
#include "../stack_machine/Exceptions.h"
#include "../stack_machine/Exceptions.cpp"
#include "../stack_machine/function_namespace.h"
#include "../stack_machine/function_namespace.cpp"


TEST(Test1, Factorial_11) 
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test1_factorial11.txt", debug_level);
	I.interpret();
    EXPECT_EQ(39916800, I.get_result());
}

TEST(Test2, Factorial_0)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test2_factorial0.txt", debug_level);
	I.interpret();
	EXPECT_EQ(1, I.get_result());
}

TEST(Test3, Functions)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test3_functions.txt", debug_level);
	I.interpret();
	EXPECT_EQ(518400, I.get_result());
}

TEST(Test4, Functions_In_Functions)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test4_functions_in_functions.txt", debug_level);
	I.interpret();
	EXPECT_EQ(20160, I.get_result());
}

TEST(Test5, interpreter_test)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test5_all_simple_commands.txt", debug_level);
	I.interpret();
	EXPECT_EQ(6, I.get_result());
}

TEST(Test6, interpreter_test)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test6_goto.txt", debug_level);
	I.interpret();
	EXPECT_EQ(1, I.get_result());
}


TEST(Test7, interpreter_test)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test7_goto_not_in_main.txt", debug_level);
	I.interpret();
	EXPECT_EQ(1, I.get_result());
}

TEST(Test8, interpreter_test)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test8_ifgr.txt", debug_level);
	I.interpret();
	EXPECT_EQ(1, I.get_result());
}

TEST(Test9, interpreter_test)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test9_ifgr_not_gr.txt", debug_level);
	I.interpret();
	EXPECT_EQ(0, I.get_result());
}

TEST(Test10, interpreter_test)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test10_if_combination.txt", debug_level);
	I.interpret();
	EXPECT_EQ(1, I.get_result());
}

TEST(Test11, SyntaxError)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test12_syntax_error.txt", debug_level);
	try
	{
		I.interpret();
		EXPECT_FALSE(true);
	}
	catch (Exceptions::SyntaxError& SynEr)
	{
		EXPECT_TRUE(true);
	}
}

TEST(Test12, NameError)
{
	bool debug_level = false;
	interpreter I("E:\\work\\c++saves\\training_projects\\stack_machine\\Tests\\test13_name_error.txt", debug_level);
	try
	{
		I.interpret();
		EXPECT_FALSE(true);
	}
	catch (Exceptions::NameError& NameEr)
	{
		EXPECT_TRUE(true);
	}
}




int main(int argc, char** argv)
{
	//interpreter I("check.txt", false);
	//I.interpret();
	//I.get_result();
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
	//return 0;
}