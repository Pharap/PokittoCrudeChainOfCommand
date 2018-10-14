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

#include <ButtonEvent.h>
#include <ButtonHandler.h>
#include <Pokitto.h>

class SoundControlHandler : public ButtonHandler
{
private:
	bool active = false;

public:
	bool isActive(void) const
	{
		return this->active;
	}
	
	void toggleActive(void)
	{
		this->active = !this->active;
	}

	void activate(void)
	{
		this->active = true;
	}
	
	void deactivate(void)
	{
		this->active = false;
	}

	// Only attempts to handle volume while active
	bool handleButtonsPressed(ButtonEvent & event) override
	{
		// If not active, don't handle anything
		if(!this->isActive())
			return false;
	
		auto buttons = event.getButtons();
		if(buttons.hasAny(Buttons::Up))
		{
			Pokitto::Sound::volumeUp();
			return true;
		}
		else if(buttons.hasAny(Buttons::Down)
		{
			Pokitto::Sound::volumeDown();
			return true;
		}
		return false;
	}
	
	bool handleButtonsReleased(ButtonEvent & event) override
	{
		// Does nothing
		// Must be defined because parent marked this function as pure virtual
	}
};