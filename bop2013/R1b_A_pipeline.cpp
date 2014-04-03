#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <cassert>
using namespace std;
namespace kingo
{

struct Vertex;

struct Edge
{
    int weight;
    int s;
    int vertex;
};

struct Vertex
{
    int number;
    int heapIndex;
    int state;
    int weight;
    int dist, pre;
    int dTime,fTime;
    list<Edge> edge; 
};

class Graph{
private:
	int time;
public:
	typedef pair<int,int> tPair;
    typedef vector<Vertex> tV;
    typedef list<Edge> tE;
    typedef tV::iterator tVIter;
    typedef tE::iterator tEIter;
	static const int MAXINT = 0x3ffffff;
    int numberOfVertex;
	int * shortest;
    int * flowMap;
	vector<Vertex> vertex;
	enum State{NOT_VISITED,VISITING,VISITED};

	Graph(int n):numberOfVertex(n),flowMap(NULL)
	{
		vertex.resize(n);
        for(int i=0;i<n;++i) vertex[i].number=i;
		shortest = NULL;
	}
	~Graph()
	{
		if(shortest) delete [] shortest;
        if(flowMap) delete [] flowMap;
	}
	
	
	void addDirectEdge(int s,int e,int weight)
	{
		Edge edge;
		edge.vertex = e;
		edge.weight = weight;
		vertex[s].edge.push_back(edge);
        if(flowMap)
        {
            flowMap[s*numberOfVertex+e] = weight;
        }
	}

	void addEdge(int s,int e,int weight)
	{
		Edge edge;
        edge.s = s;
		edge.vertex = e;
		edge.weight = weight;
		vertex[s].edge.push_back(edge);

        edge.s = e;
		edge.vertex = s;
		edge.weight = weight;
		vertex[e].edge.push_back(edge);
        if(flowMap)
        {
            flowMap[s*numberOfVertex+e] = weight;
            flowMap[e*numberOfVertex+s] = weight;
        }
	}
    bool MBFS(int s,int t)
    {
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->state = NOT_VISITED;
			it->dist = MAXINT;
			it->pre = -1;
		}
        queue<Vertex*> q;
        q.push(&vertex[s]);
        vertex[s].state = VISITED;
        vertex[s].dist = 0;
        Vertex* currentVertex;
        while(!q.empty())
        {
            currentVertex = q.front();
            q.pop();
            for(tEIter it = currentVertex->edge.begin();it != currentVertex->edge.end();++it)
            {
                Vertex &nextVertex = vertex[it->vertex];
                if(nextVertex.state == NOT_VISITED && flowMap[currentVertex->number * numberOfVertex + nextVertex.number] > 0)
                {
                    q.push(&nextVertex);
                    nextVertex.dist = currentVertex->dist+1;
                    nextVertex.state = VISITED;
                }
            }
        }
        return vertex[t].state == VISITED;
    }
    int MDFS(int x,int t, int flow)
    {
        if(x==t || !flow) return flow;
        int sum = 0,u;
        Vertex &currentVertex = vertex[x];
        for(tEIter it = currentVertex.edge.begin();it != currentVertex.edge.end();++it)
        {
            Vertex & nextVertex = vertex[it->vertex];
            if(nextVertex.dist == currentVertex.dist+1 
             && (u = MDFS(it->vertex,t,min(flow,flowMap[x*numberOfVertex+it->vertex]))) > 0)
             {
                flowMap[x*numberOfVertex+it->vertex] -= u;
                flowMap[it->vertex*numberOfVertex+x] += u;
                sum += u;
                flow -= u;
                if(!flow) break;
             }
        }
        return sum;
    }
    int getAugment(int s, int t)
    {
        int augment = MAXINT;
        int node = t,flow,pre;
        while((pre=vertex[node].pre) != -1)
        {
            flow = flowMap[pre*numberOfVertex+node];
            if(flow < augment) augment = flow;
            node = pre;
        }
        node = t;
        while((pre=vertex[node].pre) != -1)
        {
            flowMap[pre*numberOfVertex+node] -= augment;
            flowMap[node*numberOfVertex+pre] += augment;
            node = pre;
        }
        return augment;
    }
    int MaxFlowIncrment(int s,int t)
    {
        return MaxFlow(s,t,true);
    }
    int MaxFlow(int s, int t,bool increment=false)
    {
        int n = numberOfVertex;
        bool hasData = (flowMap!=NULL);
        if(flowMap==NULL)
        {
            flowMap = new int[n*n];
        }
        if(!increment || !hasData)
        {
            for(int i = 0; i < n; ++i)
            {
                for(int j=0; j < n; ++j)
                {
                    flowMap[i*n+j] = 0;
                }
            }
            for(int i=0;i < n;++i)
            {
                for(tEIter eit = vertex[i].edge.begin();eit != vertex[i].edge.end();++eit)
                {
                    flowMap[i * n + eit->vertex] = eit->weight;
                }
            }
        }
        int augment;
        int maxflow=0;
        while(MBFS(s,t))
        {
            maxflow += MDFS(s,t,MAXINT);
        }
        /*
        while((augment=getAugment(s,t))>0)
        {
            maxflow += augment;
        }
        */
        return maxflow;
    }
	void printVertex()
	{
		for(int i=0; i < vertex.size(); ++i)
		{
			cout << "Vertex:\t" << i << endl;
			cout << "state:\t" << vertex[i].state << endl;
			cout << "dist:\t" << vertex[i].dist << endl;
			cout << "dTime:\t" << vertex[i].dTime << endl;
			cout << "fTime:\t" << vertex[i].fTime << endl;
			cout << "pre:\t" << vertex[i].pre << endl;
			cout << endl;
		}
	}
};
}

void testMaxFlow()
{
    {
        kingo::Graph graph(2);
        graph.addEdge(0,1,100);
        assert(graph.MaxFlow(0,1)==100);
    }

    {
        kingo::Graph graph(4);
        graph.addDirectEdge(0,1,10000);
        graph.addDirectEdge(1,2,1);
        graph.addDirectEdge(0,2,10000);
        graph.addDirectEdge(2,3,10000);
        graph.addDirectEdge(1,3,10000);
        assert(graph.MaxFlow(0,3)==20000);
        graph.addDirectEdge(0,3,10);
        assert(graph.MaxFlowIncrment(0,3)==10);
    }
}
int main()
{
    //testMaxFlow();
    int T,n,m,x,y,c;
    int inc;
    cin >> T;
    for(int caseNumber=1;caseNumber<=T;++caseNumber)
    {
        cin >> n >> m;
        kingo::Graph graph(n);
        int i=0;
        cout << "Case #" << caseNumber << ":\n";
        while(m--)
        {
            i++;
            cin >> x >> y >> c;
            graph.addEdge(x-1,y-1,c);
            inc = graph.MaxFlowIncrment(0,n-1);
            if(inc>0) cout << i << ' ' << inc << '\n';
        }
    }
    return 0;
}
