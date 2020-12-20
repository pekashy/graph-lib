#pragma once

class ComplexObject
{
public:
    virtual ~ComplexObject() = default;
    virtual void DoObjectAction() = 0;
};

class FunnyObject : public ComplexObject
{
public:
    void DoObjectAction() override;
    void DoFunnyAction();
};
