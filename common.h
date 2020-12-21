#pragma once
#include <memory>
#include "visitors.h"
#include "dispatcher.h"

#include <functional>

class Chainable
{
public:
	using Ptr = std::shared_ptr<Chainable>;
	virtual ~Chainable() = default;
	virtual void SetNext(Chainable::Ptr shNextHandler) = 0;
	virtual void Handle(const std::function<void(Chainable*)>& fnOperation) = 0;
};

class ComplexObject : public Chainable
{
public:
	using Ptr = std::shared_ptr<ComplexObject>;
	virtual ~ComplexObject() = default;
	virtual void Execute() = 0;
	virtual void Accept(Visitor::Ptr shVisitor) const = 0;
};

class FunnyObject : public ComplexObject
{
public:
	using Ptr = std::shared_ptr<FunnyObject>;
	void Execute() override;
	void DoFunnyAction() const;
	void Accept(Visitor::Ptr shVisitor) const override;
	void SetNext(Chainable::Ptr shNextHandler) override;
	void Handle(const std::function<void(Chainable*)>& fnOperation) override;
private:
	Chainable::Ptr m_shNext;
};

class SadObject : public ComplexObject
{
public:
	using Ptr = std::shared_ptr<SadObject>;
	void Execute() override;
	void DoSadAction() const ;
	void Accept(Visitor::Ptr shVisitor) const override;
	void SetNext(Chainable::Ptr shNextHandler) override;
	void Handle(const std::function<void(Chainable*)>& fnOperation) override;
private:
	Chainable::Ptr m_shNext;
};

using ComplexDispatcher = VisitorDispatcher<ComplexObject, ComplexObject>;
