#include <map>
#include <vector>
#include <SDL.h>

#include "System.h"
#include "Entity.h"


enum InputType
{
	ACTION,
	STATE,
	RANGE
};

enum Action
{
	EXECUTE = true,
	STOP = false
};

enum inputState
{
	PRESSED = true,
	RELEASED = false
};

class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
	virtual InputType type() = 0;
};

class InputHandler : public System
{
private:
	InputHandler()
	{
		//creates pointers to all the commands eg. Walking = new Walk();
		//commands[SDLK_1] = Walking;
		//commands[SDLK_w] = 
	}

	~InputHandler()
	{
		//Delete all command pointers
		std::map<int, Command*>::iterator iter;
		for (iter = commands.begin(); iter != commands.end(); iter++)
			delete iter->second;
	}

	//pointers to commands eg. Command* Walking;



	std::map<int, Command*> commands;

	std::map<int, inputState> state_map;
	std::map<int, Action> action_map;

	// converts the input into an action
	bool inputToAction()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT) // 
			{
				return true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					return true;
				}
				keydown(event);
			}
			else if (event.type == SDL_KEYUP)
			{
				keyup(event);
			}

		return false;
	}

	// fills the commands queue
	void fillCommands(std::vector<Command*>& command_queue)
	{
		std::map<int, Command*>::iterator iter; // creates the iterator for the commands list
		for (iter = commands.begin(); iter != commands.end(); iter++)
		{
			if (is_held(iter->first) && iter->second->type() == STATE)
			{
				command_queue.push_back(iter->second); //adds to the queue
			}
			else if (was_pressed(iter->first) && iter->second->type() == ACTION)
			{
				command_queue.push_back(iter->second); // adds to the queue
			}
		}
	}

	// checks to see if the key is pressed
	void keydown(SDL_Event& event)
	{
		if (state_map[event.key.keysym.sym] == RELEASED)
		{
			action_map[event.key.keysym.sym] = EXECUTE;
			state_map[event.key.keysym.sym] = PRESSED;
		}
	}

	//checks to see if key is released
	void keyup(SDL_Event& event)
	{
		state_map[event.key.keysym.sym] = RELEASED; // if the key has been released
	}

	bool was_pressed(int key)
	{
		return action_map[key]; //returns last key pressed
	}

	//creates the input commands
	bool generateInputs(std::vector<Command*>& command_queue)
	{
		bool exit = inputToAction();    // converts raw input datum to an action and/or state

		if (exit)
		{
			return true;
		}
		else
		{
			fillCommands(command_queue);  // fills command queue
			action_map.clear();         // clears key presses
			return false;
		}
	}

	//binds the keys to a command
	void bindings(int key, Command* command)
	{
		commands[key] = command; // key pressed is pointed to the command
	}

	//if button is being held
	bool is_held(int key)
	{
		return state_map[key]; // returns the current button pressed
	}




	//classes to call the function body
	//execution of states changing

	//eg.
	//class Walk : public Command
	//{
	//public:
	//void execute() {walking();}
	//InputType type() {return STATE;}
	//};
};