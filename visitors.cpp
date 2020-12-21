#include "visitors.h"
#include "common.h"
#include <iostream>

namespace
{
    class CleverVisitor : public Visitor
    {
    public:
        void VisitSad(const SadObject* pSadObject) override;
        void VisitFunny(const FunnyObject* pFunnyObject) override;
    };

    class DummyVisitor : public Visitor
    {
    public:
        void VisitSad(const SadObject* pSadObject) override;
        void VisitFunny(const FunnyObject* pFunnyObject) override;
    };
}

void CleverVisitor::VisitFunny(const FunnyObject* pFunnyObject)
{
    std::cout << "Visiting funny smartly" << std::endl;
    pFunnyObject->DoFunnyAction();
}

void CleverVisitor::VisitSad(const SadObject* pSadObject)
{
    std::cout << "Visiting sad smartly" << std::endl;
    pSadObject->DoSadAction();
}


void DummyVisitor::VisitFunny(const FunnyObject* pFunnyObject)
{
    std::cout << "Visiting funny dummy" << std::endl;
    pFunnyObject->DoFunnyAction();
}

void DummyVisitor::VisitSad(const SadObject* pSadObject)
{
    std::cout << "Visiting sad dummy" << std::endl;
    pSadObject->DoSadAction();
}


Visitor::Ptr VisitorFactory::CreateCleverVisitor()
{
    return std::make_shared<CleverVisitor>();
}

Visitor::Ptr VisitorFactory::CreateDummyVisitor()
{
    return std::make_shared<DummyVisitor>();
}
