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

#include <Buttons.h>
#include <ButtonEvent.h>
#include <ButtonHandler.h>
#include <ButtonDispatcher.h>
#include <SoundControlHandler.h>

class DummyControlHandler : public ButtonHandler
{
public:
	bool handleButtonsPressed(ButtonEvent & event) override
	{
		Pokitto::Display::println("GameControlHandler handled button press");
	}
	
	bool handleButtonsReleased(ButtonEvent & event) override
	{
		Pokitto::Display::println("GameControlHandler handled button release");
	}
};

SoundControlHandler soundHandler;
DummyControlHandler dummyHandler;
ButtonDispatcher dispatcher;

int main(void)
{
	using Pokitto::Core;
	using Pokitto::Buttons;
	using Pokitto::Display;
	
	// Register handlers
	dispatcher.registerHandler(soundHandler);
	dispatcher.registerHandler(dummyHandler);

	Core::begin();
	while(Core::isRunning())
	{
		if(!Core::update())
			continue;
			
		Buttons buttons = Buttons::None;
		if(Buttons::pressed(UP_BTN))
			buttons |= Buttons::Up;
			
		if(Buttons::pressed(DOWN_BTN))
			buttons |= Buttons::Down;
			
		if(Buttons::pressed(C_BTN))
		{
			buttons |= Buttons::C;
			soundHandler.toggleActive();
		}
		
		if(buttons != Buttons::None)
		{
			ButtonEvent event = ButtonEvent(buttons)
			if(dispatcher.handleButtonsPressed(event))
				Display::println("ButtonsPressed event handled");
			else
				Display::println("ButtonsPressed event not handled");
		}
	}
}