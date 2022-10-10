#pragma once
#include <chrono>

#define AGL_BENCHMARK(name, ...) \
{ \
	::agl::timer timer; \
	timer.start(); \
	__VA_ARGS__ \
	double time = timer.milliseconds(); \
	std::cout << name << ":  " << time << "ms\n\n"; \
}

namespace agl
{
	class timer
	{
	public:
		void start() {
			start_ = std::chrono::system_clock::now();
		}

		double seconds() const {
			return std::chrono::duration<double>(std::chrono::system_clock::now() - start_).count();
		}

		double milliseconds() const {
			return seconds() * 1000.f;
		}

	private:
		std::chrono::time_point<std::chrono::system_clock> start_;
		std::chrono::time_point<std::chrono::system_clock> stop_;
	};
}