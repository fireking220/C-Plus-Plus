//Scott Patterson
//12/2/2016
//CS163
//Karla Fant
//.h file for defining the different aspects of what makes up a graph

struct vertex
{
	vertex();
	~vertex();
	void display();
	bool visit;
	int num_edges;
	char * m_goal;
	struct edge * head;
};

struct edge
{
	edge();
	~edge();
	vertex * adjacent;
	edge * next;
};

class graph
{
	public:
	graph(int size = 5);
	~graph();
	int insert_vertex(char * goal);
	int insert_edge(char * cur_vertex, char * to_attach);
	int display_all();
	int display_all_goal(char * key);
	int depth_first(char * key);

	private:
	vertex * adjacency_list;
	int find_location(char * key);
	void depth_first_rec(char * key);
	void display_all_goal_rec(edge * &head);
	int num_vertex;
	int graph_size;
};
