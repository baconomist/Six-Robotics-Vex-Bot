//
// Created by Lucas on 11/15/2019.
//

#include <cstdio>
#include "action_queue.h"


QueueableAction::QueueableAction() = default;


void QueueableAction::execute()
{

}

bool QueueableAction::finished()
{ return true; }


DefaultQueueableAction::DefaultQueueableAction(void (*action)(), bool (*finished_func)())
{
    this->action_func = action;
    this->finished_func = finished_func;
}

void DefaultQueueableAction::execute()
{
    return action_func();
}

bool DefaultQueueableAction::finished()
{
    return finished_func();
}

ActionQueue::ActionQueue() = default;

void ActionQueue::update()
{
    if (currentAction != nullptr && currentAction->finished())
    {
        if (currentAction->next != nullptr)
        {
            currentAction->next->execute();
            currentAction = currentAction->next;
        }
    }
}

void ActionQueue::queue_action(QueueableAction *action)
{
    if (currentAction == nullptr)
    {
        currentAction = action;
        currentAction->execute();
    } else
    {
        QueueableAction *childAction = currentAction;
        while (childAction->next != nullptr)
            childAction = childAction->next;
        childAction->next = action;
    }
}

