#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <atomic>
#include <cstdint>

#include "wave.h"
#include "symbol_queue.hh"
#include "output.hh"

// Enhancement try_push to avoid huge memory usage

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
			} else {
				ival = -1; // Like it never happened
			}
			if (ival >= 0) {
				q.push(static_cast<symbol>(ival));
				++symbols_queued_temp;
			}
			if (i + 1 == line.size()) {
				q.push(symbol::SPACE);
				++symbols_queued_temp;
			}
		}
	}
	symbols_queued.store(symbols_queued_temp);
	continue_output.store(false);
	output_thread.join();
}
