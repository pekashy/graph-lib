#include "common.h"
#include <iostream>

void FunnyObject::Execute()
{
	std::cout << "Making Generic Object Action (Ready for Composite Pattern)" << std::endl;
};

void SadObject::Execute()
{
	std::cout << "Making Generic Object Action (Ready for Composite Pattern)" << std::endl;
};


void FunnyObject::DoFunnyAction() const
{
	std::cout << "Making Funny Object Action" << std::endl;
};

void SadObject::DoSadAction() const
{
	std::cout << "Making Sad Object Action" << std::endl;
};


void FunnyObject::Accept(Visitor::Ptr shVisitor) const
{
	shVisitor->VisitFunny(this);
}

void SadObject::Accept(Visitor::Ptr shVisitor) const
{
	shVisitor->VisitSad(this);
}

void FunnyObject::SetNext(Chainable::Ptr shNextHandler)
{
	m_shNext = shNextHandler;
}

void FunnyObject::Handle(const std::function<void(void)>& fnOperation)
{
	if(m_shNext == nullptr)
	{
		return m_shNext->Handle(fnOperation);
	}
	return fnOperation();
}

void SadObject::SetNext(Chainable::Ptr shNextHandler) 
{
	m_shNext = shNextHandler;
}

void SadObject::Handle(const std::function<void(void)>& fnOperation)
{
	if(m_shNext == nullptr)
	{
		return m_shNext->Handle(fnOperation);
	}
	return fnOperation();
}
