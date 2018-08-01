#ifndef SYMBOL_QUEUE_HH
#define SYMBOL_QUEUE_HH
#include <mutex>
#include <queue>
#include <cstdint>

enum class symbol : std::uint8_t {
	A = 0, B, C, D, E, F, G, H, I, J, K, L, M,
	N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, SPACE
};

class symbol_queue {
public:
	void push(symbol s)
	{
		std::lock_guard<std::mutex> lg(queue_mutex);
		queue.push(s);
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
	std::queue<symbol> queue;
	std::mutex queue_mutex;
};

#endif
