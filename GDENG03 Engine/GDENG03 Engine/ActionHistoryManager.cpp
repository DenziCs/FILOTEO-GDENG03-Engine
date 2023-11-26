#include"ActionHistoryManager.h"
#include<iostream>

ActionHistoryManager* ActionHistoryManager::instance = nullptr;

ActionHistoryManager* ActionHistoryManager::getInstance() {
	return instance;
}

void ActionHistoryManager::initialize() {
	instance = new ActionHistoryManager();
}

void ActionHistoryManager::destroy() {
	instance->clearUndo();
	instance->clearRedo();
}

void ActionHistoryManager::startAction(AGameObject* game_object) {
	mCurrentObject = game_object;
	StateSnapshot* beforeState = new StateSnapshot(mCurrentObject);
	mBeforeState = beforeState;
}

void ActionHistoryManager::endAction() {
	StateSnapshot* afterState = new StateSnapshot(mCurrentObject);
	ActionMemento* memento = new ActionMemento(mBeforeState, afterState);
	mUndoStack.push(memento);
	clearRedo();

	mCurrentObject = nullptr;
	mBeforeState = nullptr;
}

bool ActionHistoryManager::canUndo() {
	return !mUndoStack.empty();
}

bool ActionHistoryManager::canRedo()
{
	return !mRedoStack.empty();
}

void ActionHistoryManager::applyState(StateSnapshot* state) {
	AGameObject* object = state->getObject();
	object->setActive(state->getEnabledState());
	object->setScale(state->getStoredScale());
	object->setRotation(state->getStoredRotation());
	object->setPosition(state->getStoredPosition());
}

void ActionHistoryManager::undoAction() {
	ActionMemento* action = mUndoStack.top();
	mUndoStack.pop();
	mRedoStack.push(action);

	applyState(action->getBeforeState());
}

void ActionHistoryManager::redoAction() {
	ActionMemento* action = mRedoStack.top();
	mRedoStack.pop();
	mUndoStack.push(action);

	applyState(action->getAfterState());
}

void ActionHistoryManager::clearUndo() {
	while (!mUndoStack.empty()) {
		ActionMemento* action = mUndoStack.top();
		mUndoStack.pop();
		delete action;
	}
}

void ActionHistoryManager::clearRedo() {
	while (!mRedoStack.empty()) {
		ActionMemento* action = mRedoStack.top();
		mRedoStack.pop();
		delete action;
	}
}

ActionHistoryManager::ActionHistoryManager() {
	mCurrentObject = nullptr;
	mBeforeState = nullptr;
}

ActionHistoryManager::~ActionHistoryManager() {
	delete instance;
}