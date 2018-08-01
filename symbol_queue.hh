#ifndef SYMBOL_QUEUE_HH
#define SYMBOL_QUEUE_HH
#include <mutex>
#include <queue>
#include <cstdint>
#include <cstdlib>

enum class symbol : std::uint8_t {
	A = 0, B, C, D, E, F, G, H, I, J, K, L, M,
	N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, SPACE
};

class symbol_queue {
public:
	int try_push(symbol s)
	{
		std::lock_guard<std::mutex> lg(queue_mutex);
		if (queue.size() >= MaxSize) {
			return 1;
		}
		queue.push(s);
		return 0;
	}
	int try_pop(symbol &s)
	{
		std::lock_guard<std::mutex> lg(queue_mutex);
		if (queue.empty()) {
			return 1;
		}
		s = queue.front();
		queue.pop();
		return 0;
	}
private:
	static constexpr std::size_t MaxSize = 8 * 1024;
	std::queue<symbol> queue;
	std::mutex queue_mutex;
};

#endif
