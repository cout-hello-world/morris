#ifndef OUTPUT_HH
#define OUTPUT_HH
#include "symbol_queue.hh"
#include <atomic>
#include <cstdint>
void run_output_thread(symbol_queue &q,
                       std::atomic_bool &continue_output,
                       std::atomic<std::uint64_t> &symbols_queued);
#endif
