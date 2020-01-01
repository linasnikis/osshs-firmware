/*
 * MIT License
 *
 * Copyright (c) 2019 Linas Nikiperavicius
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef OSSHS_TIME_HPP
#define OSSHS_TIME_HPP

#include <cstdint>

namespace osshs
{
	class Time
	{
	public:
		enum class
		Precision
		{
			Milliseconds,
			Seconds
		};

		/**
		 * @brief Initialize system time.
		 * 
		 */
		static void
		initialize();

		/**
		 * @brief System time getter.
		 * 
		 * @tparam T return type.
		 * @tparam precision Either Precision::Milliseconds or Precision::Seconds.
		 * @return T system time.
		 */
		template<typename T, Precision precision>
		static T
		getSystemTime();
	private:
		static uint64_t systemTime;

		/**
		 * @brief Increment system time. Called from interrupt.
		 * 
		 */
		static void
		tick();
	};
}

#include <osshs/time_impl.hpp>

#endif  // OSSHS_TIME_HPP
