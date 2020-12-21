#pragma once
#include <memory>

class FunnyObject;
class SadObject;

class Visitor
{
public:
    using Ptr = std::shared_ptr<Visitor>;

    virtual void VisitFunny(const FunnyObject* pFunnyObject) = 0;
    virtual void VisitSad(const SadObject* pSadObject) = 0;

    virtual ~Visitor() = default;
};

namespace VisitorFactory
{
    Visitor::Ptr CreateCleverVisitor();
    Visitor::Ptr CreateDummyVisitor();
}