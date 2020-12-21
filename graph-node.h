#pragma once

#include "common.h"
#include "visitors.h"

#include <sstream>
#include <memory>

class GraphVertex : public Chainable
{
public:
	using Ptr = std::shared_ptr<GraphVertex>;
	virtual ~GraphVertex() = default;
	virtual int GetId() const = 0;
	virtual void Accept(Visitor::Ptr shVisitor) = 0;
	virtual void Execute() = 0;
};

template<typename TConcrete, typename TBase>
class ConcreteGraphVertex : public GraphVertex
{
public:
	virtual ~ConcreteGraphVertex() = default;

	int GetId() const override
	{
		return m_nId;
	}

	static std::shared_ptr<GraphVertex> Create(TConcrete* pContent, int nId) 
	{
		struct make_shared_enabler : public ConcreteGraphVertex<TConcrete, TBase> 
		{
			make_shared_enabler(TConcrete* pC, int nI) : ConcreteGraphVertex<TConcrete, TBase>(pC, nI) {};
		};
		return std::make_shared<make_shared_enabler>(pContent, nId);
	};

	void Accept(Visitor::Ptr shVisitor) override
	{
		return m_fAcceptFunction(shVisitor);
	}

	void Execute() override
	{
		return m_shContent->Execute();
	}
	
	void SetNext(Chainable::Ptr shNextHandler) override
	{
		m_shNextInChain = shNextHandler;
	}

	void Handle(const std::function<void(Chainable*)>& fnOperation) override
	{
		if(m_shNextInChain == nullptr)
		{
			return m_shNextInChain->Handle(fnOperation);
		}

		return fnOperation(this);
	}


private:
	ConcreteGraphVertex(TConcrete* pContent, int nId)
		: m_nId(nId)
	{

		auto m_shConcreteContent = std::make_shared<TConcrete>(*pContent);
		m_shContent = m_shConcreteContent;
		m_fAcceptFunction = std::bind(&TConcrete::Accept, *m_shConcreteContent, std::placeholders::_1);	
	}

	int m_nId;
	std::function<void(Visitor::Ptr)> m_fAcceptFunction;
	std::shared_ptr<TBase> m_shContent;
	Chainable::Ptr m_shNextInChain;
};


struct GraphEdge
{
public:
	GraphEdge(int nSource, int nDest, ComplexObject::Ptr shWeight = nullptr)
		: m_nSource(nSource)
		, m_nDest(nDest)
		, m_shWeight(shWeight)
	{}

	GraphEdge(GraphVertex::Ptr shSource, GraphVertex::Ptr shDest, ComplexObject::Ptr shWeight = nullptr)
		: GraphEdge(shSource->GetId(), shDest->GetId(), shWeight)
	{}

	int m_nSource;
	int m_nDest;
	ComplexObject::Ptr m_shWeight;
};


template<typename T>
class SimpleObjectWrapper : public ComplexObject
{
public:
	SimpleObjectWrapper(T* v)
	{
		if(v != nullptr)
		{
			auto temp = *v;
			val = std::make_shared<T>(temp);
		}
	}
	void Execute() override {};
	void Accept(Visitor::Ptr shVisitor) const override {};
	std::shared_ptr<T> GetValue() const {return val;};
	std::shared_ptr<T> val;
	void SetNext(Chainable::Ptr shNextHandler) {}
	void Handle(const std::function<void(Chainable*)>& fnOperation) {}
};


template<typename T>
struct WrappedConcreteGraphVertex
{
	static std::shared_ptr<GraphVertex> Create(T* pContent, int nId)
	{
		SimpleObjectWrapper<T> wrappedContent(pContent);
		return ConcreteGraphVertex<SimpleObjectWrapper<T>, SimpleObjectWrapper<T>>::Create(&wrappedContent, nId);
	}
};

template <typename T>
using SimpleObjVertex = WrappedConcreteGraphVertex<T>;

template <class T>
using ComplexObjVertex = ConcreteGraphVertex<T, ComplexObject>;