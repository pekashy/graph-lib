# Graph Library

Hometask for MIPT metaprogramming course
## Features
- Construct Different representations of graph
- Store any copyable objects in edges or vertices
- Iterators for graphs provided by this lib
- Objects and interfaces to apply `Visitor`, `Composite`, `Chain of responsibility` patterns on graph

## Usage
Usage examples can be found in tests (`graph-lib-test.cpp`), which are written using Google Test framework, but here are overall recommendations:

### Graph initialisation

1. Firstly you must create or get objects, that will be stored in graph.
Classes of any data in graph must inheirt `ComplexObject` interface. If you want to perform any operations on your data, it is recommended to implement your custom wrappings, you can take `FunnyObject` and `SadObject` as the examples. If you wish to just store data in graph, you can use `SimpleObjectWrapper<T>` class. During the next step those objects will be copied, so they have to be copyable and have public constructor (for now).

        FunnyObject* oF = new FunnyObject();

2. Then you can create graph entities. `ConcreteGraphVertex<TConcrete, TBase>` class takses object type and base object type as parameters, but if you used `ComplexObject` as a base class, you may want to use `ComplexObjVertex<T>` macro. If you use `SimpleObjVertex<T>` for primitive type, it will be automaticly wrapped with `SimpleObjectWrapper<T>`. You also must specify an index for vertex that will be used to locate it in graph later.

        FunnyObject v1 = ComplexObjVertex<FunnyObject>::Create(oF, 1);
        std::shared_ptr<GraphVertex> e = SimpleObjVertex<int>::Create(&content, 0);

3. After you created som vertixes, you can create edges, connecting them. You can also attach some payload to edges.

4. To create graph instance, you can use `GraphFactory` methods

        auto g = GraphFactory::CreateAdjListGraph();

5. Then you should add all created vertexes and edges to graph instance

            g->AddVertex(v1);
            g->AddVertex(v2);
            g->AddVertex(v3);
            g->AddVertex(v4);

            g->AddEdge(e12);
            g->AddEdge(e23);
            g->AddEdge(e34);

### Graph iteration
To iterate over graph you can create an iterator using `GraphIteratorFactory`

Iterator takes as argument the graph and index of starting vertex, then traverses it, returning pointers to graph's vertexes. When traverse is over, iterator returns nullptr.

        	std::shared_ptr<GraphIterator> graphIt = GraphIteratorFactory::CreateGraphIterator(g, 1);
	        std::shared_ptr<GraphVertex> v1_recieved = graphIt->Next();


### Visitor pattern
Example of visitor for graph - `Visitor` class

	    std::shared_ptr<Visitor> cleverVisitor = VisitorFactory::CreateCleverVisitor();
	    v1_recieved->Accept(cleverVisitor);


### Composite pattern
`ComplexObject` and `GraphVertex` have an Execute method in interface, you can create implementation in concrete payload classes


### Chain of responsibility pattern
`ComplexObject` and `GraphVertex` inheirt `Chainable` interface, you can create operation functor and set next objct in chain for graph vertixes or payload objects.
