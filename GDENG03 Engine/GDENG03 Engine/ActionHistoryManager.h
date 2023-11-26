#pragma once
#include<stack>
#include"ActionMemento.h"
#include"AGameObject.h"

class ActionHistoryManager
{
public:
	static ActionHistoryManager* getInstance();
	static void initialize();
	static void destroy();

	void startAction(AGameObject* game_object);
	void endAction();
	bool canUndo();
	bool canRedo();
	void applyState(StateSnapshot* state);
	void undoAction();
	void redoAction();
	void clearUndo();
	void clearRedo();

private:
	ActionHistoryManager();
	~ActionHistoryManager();
	ActionHistoryManager(ActionHistoryManager const&) {};
	ActionHistoryManager& operator =(ActionHistoryManager const&) {};

	static ActionHistoryManager* instance;

	AGameObject* mCurrentObject;
	StateSnapshot* mBeforeState;

	std::stack<ActionMemento*> mUndoStack;
	std::stack<ActionMemento*> mRedoStack;
};