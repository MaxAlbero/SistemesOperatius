#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono> //time
#include <list>

#pragma region Functions Declaration Header

void PrintElapsedTime(
	std::chrono::system_clock::time_point start, 
	std::chrono::system_clock::time_point end,
	std::string threadName);
void Count(unsigned long long maxCounter, std::string threadName);

void Example01();
void Example02();
void Example03();
void Example04();
void Example05();
void Example06();
void Example07();

#pragma endregion

#pragma region Global Variables

std::chrono::system_clock::time_point startDate;

#pragma endregion

void ThreadTutorialTest() {

	startDate = std::chrono::system_clock::now();

	int exampleUsed = 7; //Change this variable for the use of different examples

	switch (exampleUsed) {
	case 1:
		Example01();
		break;
	case 2:
		Example02();
		break;
	case 3:
		Example03();
		break;
	case 4:
		Example04();
		break;
	case 5:
		Example05();
		break;
	case 6:
		Example06();
		break;
	case 7:
		Example07();
		break;
	default:
		break;
	}

	std::cout << "Example 0" << exampleUsed << " finished" << std::endl;
	std::string text = "";
	std::getline(std::cin, text);
}

void PrintElapsedTime(
	std::chrono::system_clock::time_point start,
	std::chrono::system_clock::time_point end,
	std::string threadName) {
	
	std::chrono::duration<double> elapsedTime = end - start;
	std::cout << "Thread: " << threadName << " - Elapsed time: " << elapsedTime.count() << " seconds" << std::endl;
}

void Count(unsigned long long maxCounter, std::string threadName) {
	for (unsigned long long i = 0; i < maxCounter; i++) {

	}
	std::chrono::system_clock::time_point endDate = std::chrono::system_clock::now();
	PrintElapsedTime(startDate, endDate, threadName);
}

void Example01() {
	unsigned long long totalCount = 1000000000ull;

	std::thread* Counter1 = new std::thread(Count, totalCount, "1");
	std::thread* Counter2 = new std::thread(Count, totalCount, "2");
	std::thread* Counter3 = new std::thread(Count, totalCount, "3");

	//join() ens serveix per a fer que els threads s'esperin als altres per executar-se
	Counter1->join();
	Counter2->join();
	Counter3->join();

	Count(totalCount, "0");
}
void Example02() {
	unsigned long long totalCount = 1000000000ull;

	//num threads creats: 1
	std::thread* Counter1 = new std::thread(Count, totalCount, "1");
	
	Counter1->join();
	//num threads executats: 1
	//num threads creats->join: 1

	//num threads creats: 3
	std::thread* Counter2 = new std::thread(Count, totalCount, "2");
	std::thread* Counter3 = new std::thread(Count, totalCount, "3");

	Counter2->join();
	Counter3->join();
	//num threads executats: 3
	//num threads creats->join: 3

	Count(totalCount, "0");
}
void Example03() {
	//en el moment d'executar el programa, el nostre thread principal 
	//perd el control sobre les dades
	unsigned long long totalCount = 1000000000ull;

	std::thread* Counter1 = new std::thread(Count, totalCount, "1");
	std::thread* Counter2 = new std::thread(Count, totalCount, "2");
	std::thread* Counter3 = new std::thread(Count, totalCount, "3");


	Counter1->detach();
	Counter2->detach();
	Counter3->detach();

	Count(totalCount, "0");
}
void Example04() {
	std::list<std::thread*>* threads = new std::list<std::thread*>();

	unsigned long long totalCount = 1000000000ull;

	for (int i = 0; i < 3; i++) {
		std::thread* counterThread = new std::thread(Count, totalCount, std::to_string(i + 1));
		threads->push_back(counterThread);
		counterThread->join();
	}

	Count(totalCount, "0");
}
void Example05() {
	std::list<std::thread*>* threads = new std::list<std::thread*>();

	unsigned long long totalCount = 1000000000ull;

	for (int i = 0; i < 3; i++) {
		std::thread* counterThread = new std::thread(Count, totalCount, std::to_string(i + 1));
		threads->push_back(counterThread);
		counterThread->detach();
	}

	Count(totalCount, "0");
}
void Example06() {
	unsigned int maxThreads = std::thread::hardware_concurrency();
	std::cout << maxThreads << " concurrent threads are supported" << std::endl;

	int extraThreads = 0;

	unsigned long long totalCount = 1000000000ull;

	unsigned int totalThreads = maxThreads + extraThreads;

	std::list<std::thread*>* threads = new std::list<std::thread*>();

	for (int i = 0; i < totalThreads; i++)
	{
		std::thread* counterThread = new std::thread(Count, totalCount, std::to_string(i + 1));
		threads->push_back(counterThread);
	}

	for (std::thread* t : *threads)
	{
		t->join();
	}

	Count(totalCount, "0");
}

class ThreadTester {
public:
	ThreadTester() {}
	~ThreadTester() {}

	void Example07();

private:
	void TestFunction(unsigned long long testInt);
};

void ThreadTester::Example07() {
	std::thread* testThread = new std::thread(&ThreadTester::TestFunction, this, 14ull);
	testThread->join();
}

void ThreadTester::TestFunction(unsigned long long testInt) {
	std::cout << "Number is: " << testInt << std::endl;
}

void Example07() {
	ThreadTester* threadTester = new ThreadTester();
	threadTester->Example07();
}