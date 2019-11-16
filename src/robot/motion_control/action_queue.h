//
// Created by Lucas on 11/15/2019.
//

#ifndef VEXROBOT_QUEUE_H
#define VEXROBOT_QUEUE_H

class QueueableAction
{
public:
    QueueableAction();

    virtual void execute();
    virtual bool finished();

    QueueableAction *next = nullptr;
};

class DefaultQueueableAction : public QueueableAction
{
public:
    DefaultQueueableAction(void (*action)(), bool (*finished)());

    virtual void execute() override;
    virtual bool finished() override;

private:
    void (*action_func)();

    bool (*finished_func)();
};

class ActionQueue
{
public:
    ActionQueue();

    QueueableAction *currentAction = nullptr;

    void update();

    void queue_action(QueueableAction *action);
};

#endif //VEXROBOT_QUEUE_H
