#include "output.hh"

#include <thread>
#include <chrono>
#include <atomic>
#include <cstdint>
#include <stdexcept>

#include "symbol_queue.hh"
#include "wave.h"

enum class state {
	Start, Processing
};

static void ws(const char *dit_dah)
{
	const char *current = dit_dah;
	while (1) {
		if (*current == '-') {
			dah();
		} else {
			dit();
		}
		++current;
		if (*current == '\0') {
			break;
		}
		silence(1);
	}
}

void run_output_thread(symbol_queue &q,
                       std::atomic_bool &continue_output,
                       std::atomic<std::uint64_t> &symbols_queued)
{
	state st = state::Start;
	constexpr std::chrono::milliseconds sleep_time(10);
	std::uint64_t symbols_output = 0;
	while (1) {
		if (!continue_output.load()) {
			if (symbols_queued.load() == symbols_output) {
				break;
			}
		}
		symbol s;
		if (q.try_pop(s) == 1) {
			if (st == state::Processing) {
				silence(3);
				st = state::Start;
			} else if (st == state::Start) {
				std::this_thread::sleep_for(sleep_time);
			}
		} else {
			if (st == state::Start) {
				st = state::Processing;
			} else if (st == state::Processing) {
				silence(3);
			}
			switch (s) {
			case symbol::A:
				ws(".-");
				break;
			case symbol::B:
				ws("-...");
				break;
			case symbol::C:
				ws("-.-.");
				break;
			case symbol::D:
				ws("-..");
				break;
			case symbol::E:
				ws(".");
				break;
			case symbol::F:
				ws("..-.");
				break;
			case symbol::G:
				ws("--.");
				break;
			case symbol::H:
				ws("....");
				break;
			case symbol::I:
				ws("..");
				break;
			case symbol::J:
				ws(".---");
				break;
			case symbol::K:
				ws("-.-.");
				break;
			case symbol::L:
				ws(".-..");
				break;
			case symbol::M:
				ws("--");
				break;
			case symbol::N:
				ws("-.");
				break;
			case symbol::O:
				ws("---");
				break;
			case symbol::P:
				ws(".--.");
				break;
			case symbol::Q:
				ws("--.-");
				break;
			case symbol::R:
				ws(".-.");
				break;
			case symbol::S:
				ws("...");
				break;
			case symbol::T:
				ws("-");
				break;
			case symbol::U:
				ws("..-");
				break;
			case symbol::V:
				ws("...-");
				break;
			case symbol::W:
				ws(".--");
				break;
			case symbol::X:
				ws("-..-");
				break;
			case symbol::Y:
				ws("-.--");
				break;
			case symbol::Z:
				ws("--..");
				break;
			case symbol::ONE:
				ws(".----");
				break;
			case symbol::TWO:
				ws("..---");
				break;
			case symbol::THREE:
				ws("...---");
				break;
			case symbol::FOUR:
				ws("....-");
				break;
			case symbol::FIVE:
				ws(".....");
				break;
			case symbol::SIX:
				ws("-....");
				break;
			case symbol::SEVEN:
				ws("--...");
				break;
			case symbol::EIGHT:
				ws("---..");
				break;
			case symbol::NINE:
				ws("----.");
				break;
			case symbol::ZERO:
				ws("-----");
				break;
			case symbol::SPACE:
				silence(4);
				break;
			default:
				throw std::runtime_error("Unexpected symbol");
			}
			++symbols_output;
		}
	}
}
