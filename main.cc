#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <atomic>
#include <cstdint>
#include <chrono>

#include "wave.h"
#include "symbol_queue.hh"
#include "output.hh"

// Enhancement try_push to avoid huge memory usage
namespace {
void push(symbol_queue &q, symbol value)
{
	constexpr std::chrono::milliseconds SleepTime(10);
	while (1) {
		auto res = q.try_push(value);
		if (res == 1) {
			std::this_thread::sleep_for(SleepTime);
		} else {
			break;
		}
	}
}
}

int main()
{
	symbol_queue q;
	std::atomic_bool continue_output(true);
	std::atomic<std::uint64_t> symbols_queued(0);
	std::uint64_t symbols_queued_temp = 0;
	std::thread output_thread(run_output_thread,
	                          std::ref(q), std::ref(continue_output), std::ref(symbols_queued));
	for (std::string line; std::getline(std::cin, line); ) {
		for (auto i = decltype(line.size()){0}; i != line.size(); ++i) {
			int ival;
			char ch = line[i];
			if (ch >= 'a' && ch <= 'z') {
				ival = ch - 'a';
			} else if (ch >= 'A' && ch <= 'Z') {
				ival = ch - 'A';
			} else if (ch >= '1' && ch <= '9') {
				ival = (ch - '1') + 26;
			} else if (ch == '0') {
				ival = static_cast<int>(symbol::ZERO);
			} else if (ch == ' ') {
				ival = static_cast<int>(symbol::SPACE);
			} else if (ch == '.') {
				ival = static_cast<int>(symbol::PERIOD);
			} else if (ch == ',') {
				ival = static_cast<int>(symbol::COMMA);
			} else if (ch == '?') {
				ival = static_cast<int>(symbol::QUESTION_MARK);
			} else if (ch == '\'') {
				ival = static_cast<int>(symbol::APOSTROPHE);
			} else if (ch == '/') {
				ival = static_cast<int>(symbol::SLASH);
			} else {
				ival = -1; // Like it never happened
			}
			if (ival >= 0) {
				push(q, static_cast<symbol>(ival));
				++symbols_queued_temp;
			}
			if (i + 1 == line.size()) {
				push(q, symbol::SPACE);
				++symbols_queued_temp;
			}
		}
	}
	symbols_queued.store(symbols_queued_temp);
	continue_output.store(false);
	output_thread.join();
}
