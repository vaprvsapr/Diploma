#pragma once

#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

class LogDuration
{
private:
	string message;
	steady_clock::time_point start;
public:
	explicit LogDuration(const string& msg = "")
		: message(msg + ": ")
		, start(steady_clock::now())
	{
	}

	~LogDuration()
	{
		auto finish = steady_clock::now();
		auto duration = finish - start;
		cerr << message
			<< duration_cast<milliseconds>(duration).count()
			<< endl;
	}
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_$$lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
LogDuration UNIQ_ID(__LINE__){message};