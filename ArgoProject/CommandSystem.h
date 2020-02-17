#include <map>
#include <vector>
#include <SDL.h>
#include "FSM.h"
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
public:
	virtual ~Command() {}
	virtual void execute(FSM* fsm) = 0;
	virtual InputType type() = 0;
};

//classes to call the function body
//execution of states changing

class AttackOne : public Command
{
public:
	void execute(FSM* fsm) { fsm->skillone(); }
	InputType type() { return STATE; }
};

class AttackTwo : public Command
{
public:
	void execute(FSM* fsm) { fsm->skilltwo(); }
	InputType type() { return STATE; }
};

class AttackThree : public Command
{
public:
	void execute(FSM* fsm) { fsm->skillthree(); }
	InputType type() { return STATE; }
};

class AttackFour : public Command
{
public:
	void execute(FSM* fsm) { fsm->skillfour(); }
	InputType type() { return STATE; }
};

class InputHandler : public System
{
public:
	// Pointers to all commands
	Command* pressAttackOne;
	Command* pressAttackTwo;
	Command* pressAttackThree;
	Command* pressAttackFour;

	std::map <int, Command*> commands;

	std::map <int, inputState> state_map;
	std::map <int, Action> action_map;


	//Vector2 mouseRelativePosition = Vector2(0, 0);
	Vector2 mousePosition = Vector2(0, 0);
	Vector2 mouseRelativePosition = Vector2(0, 0);

	bool move = false;
	bool updateMouse = false;

	InputHandler()
	{
		//Creates pointers to all the commands
		pressAttackOne = new AttackOne();
		pressAttackTwo = new AttackTwo();
		pressAttackThree = new AttackThree();
		pressAttackFour = new AttackFour();

		commands[SDLK_q] = pressAttackOne;
		commands[SDLK_w] = pressAttackTwo;
		commands[SDLK_e] = pressAttackThree;
		commands[SDLK_r] = pressAttackFour;


	}

	~InputHandler()
	{
		// Delete all command pointers    
		std::map<int, Command*>::iterator iter;
		for (iter = commands.begin(); iter != commands.end(); iter++)
			delete iter->second;
	}

	bool generateInputs(std::vector<Command*>& command_queue, SDL_Rect* t_camera)
	{
		bool exit = inputToAction(t_camera);    // converts raw input datum to an action and/or state

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

	void bindings(int key, Command* command)
	{
		commands[key] = command; // key pressed is pointed to the command
	}


	bool inputToAction(SDL_Rect* t_camera)
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
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_RIGHT)
				{

				}
				else if (event.button.button == SDL_BUTTON_LEFT)
				{

					mouseRelativePosition.x = event.button.x;
					mouseRelativePosition.y = event.button.y;

					mousePosition.x = event.button.x + t_camera->x;
					mousePosition.y = event.button.y + t_camera->y;
					move = true;
					updateMouse = true;
				}
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (move)
					{
						mouseRelativePosition.x = event.button.x;
						mouseRelativePosition.y = event.button.y;

						mousePosition.x = event.button.x + t_camera->x;
						mousePosition.y = event.button.y + t_camera->y;
					}
					break;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					updateMouse = false;
					break;
				}
			}
		return false;
	}

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

	void keydown(SDL_Event& event)
	{
		if (state_map[event.key.keysym.sym] == RELEASED)
		{
			action_map[event.key.keysym.sym] = EXECUTE;
			state_map[event.key.keysym.sym] = PRESSED;
		}
	}

	void keyup(SDL_Event& event)
	{
		state_map[event.key.keysym.sym] = RELEASED; // if the key has been released
	}

	bool is_held(int key)
	{
		return state_map[key]; // returns the current button pressed
	}

	bool was_pressed(int key)
	{
		return action_map[key];
	}

	bool leftKeyPressed()
	{
		SDL_Event _event;
		while (SDL_PollEvent(&_event))
			if (_event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (_event.button.button == SDL_BUTTON_LEFT)
				{
					return true;
				}
				else
				{

				}
			}

			return false;
	}
};

