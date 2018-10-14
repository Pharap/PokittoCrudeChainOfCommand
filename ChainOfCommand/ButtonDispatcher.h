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

#include <vector>
#include <ButtonEvent.h>
#include <ButtonHandler.h>

// This may itself be a ButtonHandler,
// to allow creation of a tree of handlers
class EventDispatcher // : public ButtonHandler
{
private:
	std::vector<ButtonHandler *> handlers;
	
public:
	// Cannot pass nullptr
	void registerHandler(const ButtonHandler & eventHandler)
	{
		this->handlers.push_back(&eventHandler);
	}
	
	// Goes through every handler and keeps trying until one handles the event
	bool handleButtonsPressed(ButtonEvent & event) override
	{
		for(auto & handler : this->handlers)
			if(handler.handleButtonsPressed(event))
				return true;

		return false;
	}
	
	bool handleButtonsReleased(ButtonEvent & event) override
	{
		for(auto & handler : this->handlers)
			if(handler.handleButtonsReleased(event))
				return true;

		return false;
	}
};