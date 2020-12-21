#pragma once
#include <memory>
#include "visitors.h"
#include "dispatcher.h"

class ComplexObject
{
public:
	using Ptr = std::shared_ptr<ComplexObject>;
	virtual ~ComplexObject() = default;
	virtual void DoObjectAction() = 0;
	virtual void Accept(Visitor::Ptr shVisitor) const = 0;
};

class FunnyObject : public ComplexObject
{
public:
	using Ptr = std::shared_ptr<FunnyObject>;
	void DoObjectAction() override;
	void DoFunnyAction() const;
	void Accept(Visitor::Ptr shVisitor) const override;
};

class SadObject : public ComplexObject
{
public:
	using Ptr = std::shared_ptr<SadObject>;
	void DoObjectAction() override;
	void DoSadAction() const ;
	void Accept(Visitor::Ptr shVisitor) const override;
};

using ComplexDispatcher = VisitorDispatcher<ComplexObject, ComplexObject>;
