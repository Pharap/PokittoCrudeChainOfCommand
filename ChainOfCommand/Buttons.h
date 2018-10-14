#pragma once

// MIT License

// Copyright (c) 2018 Pharap

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdint>
#include <Pokitto.h>

enum class Buttons : std::uint8_t
{
	None = 0,
	Up = (1 << UPBIT),
	Down = (1 << DOWNBIT),
	Left = (1 << LEFTBIT),
	Right = (1 << RIGHTBIT),
	A = (1 << ABIT),
	B = (1 << BBIT),
	C = (1 << CBIT),
};

constexpr Buttons operator |(Buttons left, Buttons right)
{
	return static_cast<Buttons>(static_cast<std::uint8_t>(left) | static_cast<std::uint8_t>(right));
}

Buttons & operator |=(Buttons & left, Buttons right)
{
	left = left | right;
	return left;
}

constexpr Buttons operator &(Buttons left, Buttons right)
{
	return static_cast<Buttons>(static_cast<std::uint8_t>(left) & static_cast<std::uint8_t>(right));
}

Buttons & operator &=(Buttons & left, Buttons right)
{
	left = left & right;
	return left;
}

constexpr Buttons operator ^(Buttons left, Buttons right)
{
	return static_cast<Buttons>(static_cast<std::uint8_t>(left) ^ static_cast<std::uint8_t>(right));
}

Buttons & operator ^=(Buttons & left, Buttons right)
{
	left = left | right;
	return left;
}