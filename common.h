#pragma once

class ComplexGraphObject
{
public:
    virtual ~ComplexGraphObject() = default;
    virtual void DoObjectAction() = 0;
};

class FunnyGraphObject : public ComplexGraphObject
{
public:
    void DoObjectAction() override;
    void DoFunnyAction();
};
