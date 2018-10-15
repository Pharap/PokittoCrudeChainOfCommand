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
#include <memory>
#include <ButtonEvent.h>
#include <ButtonHandler.h>

// This may itself be a ButtonHandler,
// to allow creation of a tree of handlers
class EventDispatcher // : public ButtonHandler
{
private:
	using Handler = ButtonHandler;
	using WeakPointer = std::weak_ptr<ButtonHandler>;
	using SharedPointer = std::shared_ptr<ButtonHandler>;

private:
	std::vector<std::weak_ptr<ButtonHandler>> handlers;
	
public:
	// Ignores nullptr
	void registerHandler(std::shared_ptr<ButtonHandler> handler)
	{
		if(handler != nullptr)
			this->handlers.emplace_back(handler);
	}
	
	// Goes through every handler and keeps trying until one handles the event
	bool handleButtonsPressed(ButtonEvent & event) override
	{
		for(auto & handler : this->handlers)
			if(!handler.expired())
			{
				auto activeHandler = handler.lock();
				if(handler->handleButtonsPressed(event))
					return true;
			}

		return false;
	}
	
	bool handleButtonsReleased(ButtonEvent & event) override
	{
		for(auto & handler : this->handlers)
			if(!handler.expired())
			{
				auto activeHandler = handler.lock();
				if(handler->handleButtonsReleased(event))
					return true;
			}

		return false;
	}
	
	void eraseExpiredHandlers(void)
	{
		auto iterator = std::remove_if(std::begin(this->handlers), std::end(this->handlers),
			[] (const std::weak_ptr<ButtonHandler> & handler) { return handler.expired(); }
		);
		this->handlers.erase(iterator, std::end(this->handlers));
	}
	
	bool deregisterHandler(std::shared_ptr<ButtonHandler> handler)
	{
		auto iterator = std::find_if(std::begin(this->handlers), std::end(this->handlers),
			[&handler] (const std::weak_ptr<ButtonHandler> & innerHandler)
			{
				if(innerHandler.expired())
					return false;
					
				auto pointer = innerHandler.lock();
				return (handler == pointer);
			}
		);
		this->handlers.erase(iterator, std::end(this->handlers));
	}
	
	bool deregisterAllHandlers(std::shared_ptr<ButtonHandler> handler)
	{
		auto iterator = std::remove_if(std::begin(this->handlers), std::end(this->handlers),
			[&handler] (const std::weak_ptr<ButtonHandler> & innerHandler)
			{
				if(innerHandler.expired())
					return false;
					
				auto pointer = innerHandler.lock();
				return (handler == pointer);
			}
		);
		this->handlers.erase(iterator, std::end(this->handlers));
	}
};