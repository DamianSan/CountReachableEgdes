
#include "skel_cntr.h"

bool import_graph(vector<graph_edge> &m_edges, int &max, int &src) {
	bool pos = false;
	max = 0;
	graph_edge edge = {0, 0};
	string file_name;
	char ch;
	ifstream graf1;
	cout << "Enter file name with graph coefficients:\n";
	cin >> file_name;
	graf1.open((file_name + ".txt"));
	if (!graf1.good()) {
		cout << "Can't find this file name!\n";
		return false;
	}
	else {
		cout << "File loaded successfully!\n";
		while (true) {
			if (!pos) {
				graf1 >> edge.start;
				for (static bool first = true; first; first = false) src = edge.start; //line to execute only once
				if (edge.start > max) max = edge.start;
				pos = !pos;
			}
			else {
				graf1 >> edge.end;
				if (edge.end > max) max = edge.end;
				m_edges.push_back(edge);
				pos = !pos;
			}
			if (graf1.eof()) break;
		}
		graf1.close();
		cout << "Default source is " << src << ". Would you like to change it?(Y/N) ";
		cin >> ch;
		if (ch == 'Y' || ch == 'y') {
			cout << "Specify new source: ";
			cin >> src;
			cout << "Source changed to: " << src << endl;
		}
		else if (ch == 'N' || ch == 'n')
			cout << "Source left as it is." << endl;
		else
			cout << "Wrong key --> Source left as it is." << endl;
		return true;
	}
}

/* Print edges data */
void print_data(vector <graph_edge> &m_edges) {
	cout << "Edges data: \n";
	for (size_t i = 0; i < m_edges.size(); i++)
		cout << m_edges[i].start << " -- " << m_edges[i].end << endl;
}

bool is_edge(vector<graph_edge> &m_edges, int p, int q) {
	for (size_t i = 0; i < m_edges.size(); i++) {
		if (m_edges[i].start == p && m_edges[i].end == q)
			return true;
		if (m_edges[i].start == q && m_edges[i].end == p)
			return true;
	}
	return false;
}

/* Print adjacency list */
void print_adj_list(vector <vector<int>> adj_list, int max) {
	for (size_t i = 0; i <= max; i++) {
		cout << "\n Adjacency list of vertex " << i << "\n head ";
		for (size_t j = 0; j < adj_list[i].size(); j++) 
				cout << "->"<< adj_list.at(i)[j] << ' ';
		printf("\n");
	}
}

/* Reorganize data edges data */
void reorganize_edges(vector <graph_edge> &m_edges) {
	int temp;
	for (size_t i = 0; i < m_edges.size(); i++) {
		if (m_edges[i].start > m_edges[i].end) {
			temp = m_edges[i].start;
			m_edges[i].start = m_edges[i].end;
			m_edges[i].end = temp;
		}	
	}
}

/* Delete edges that are duplicates */
void optim_edges(vector <graph_edge> &m_edges) {
	reorganize_edges(m_edges);
	sort_vector(m_edges, 0, m_edges.size() - 1);
	for (size_t i = 0; i < m_edges.size()-1; i++) {
		if (m_edges[i].start == m_edges[i + 1].start && m_edges[i].end == m_edges[i + 1].end)
			m_edges.erase(m_edges.begin()+i);
	}
}

/* Sort graph data ascending */
void sort_vector(vector <graph_edge> &m_edges, int l, int r) {
		int i = l;
		int j = r;
		graph_edge x = m_edges[(l+r)>>1];
		do {
			while (m_edges[i] < x) i++;
			while (m_edges[j] > x) j--;
			if (i <= j) {
				swap(m_edges[i], m_edges[j]);
				i++; j--;
			}
		} while (i <= j);
		if (l < j) sort_vector(m_edges, l, j);
		if (r > i) sort_vector(m_edges, i, r);
}

/* Create adjacency matrix */
template <unsigned R, unsigned C>
void adj_matrix(vector <graph_edge> m_edges, bool(&adj_m)[R][C]) {
	for (size_t i = 0; i < m_edges.size(); i++) {
		adj_m[m_edges[i].start][m_edges[i].end] = 1;
		adj_m[m_edges[i].end][m_edges[i].start] = 1;
	}
}

/* Return list of nodes adjacent */
void adj_list(vector<graph_edge> m_edges, vector<vector<int>> &m_nodes, int max) {
	vector<int> temp; temp.clear();
	m_nodes.clear();
	for (size_t j = 0; j <= max; j++) {
		for (size_t i = 0; i < m_edges.size(); i++) {
			if (m_edges[i].start == j)
				temp.push_back(m_edges[i].end);
			else if (m_edges[i].end == j)
				temp.push_back(m_edges[i].start);
		}
		m_nodes.push_back(temp); temp.clear();
	}
}

/* Perform DLS - Depth Limited Search */
bool DLS(vector<graph_edge> m_edges, vector<vector<int>> &m_adj, int src, int dst, int limit, int maxV) {
	vector<bool> visited; visited.assign(maxV, 0);
	if (limit <= 0)
		return false;
	//cout << "\nDla src=" << src << " m_adj= ";
	for (size_t j = 0; j < m_adj[src].size(); j++) {
		//cout << m_adj[src][j] << ' ';
		if ((m_adj[src][j] == dst && limit >= 1) || src == dst)
			return true;
	}

	for (size_t i = 0; i < m_adj[src].size(); i++) {
		//Recur for all the vertices adjacent to source vertex
		//cout << "\ni= " << i << " Szukanie dla src=" << m_adj[src][i] << endl;
		if (DLS(m_edges, m_adj, m_adj[src][i], dst, limit - 1, maxV) == true)
			return true;
	}
	return false;
}

/* IDDFS to search if target is reachable from src */
bool IDDFS(vector<graph_edge> m_edges, vector<vector<int>> &m_adj, int src, /*int target*/graph_edge m_edge, int max_depth, int maxV) {
	// Repeatedly depth-limit search till the maximum depth
	for (int i = 1; i <= max_depth; i++) {
		if (DLS(m_edges, m_adj, src, m_edge.start, i, maxV) == true && DLS(m_edges, m_adj, src, m_edge.end, i, maxV) == true)
			return true;
	}
	return false;
}

/* Count skeletons present in pyramide */
int count_skeletons(int entrance, int num_of_entr, vector<graph_edge> &pyr_schem, int max_fire_reach) {
	vector<graph_edge> corr_vect; corr_vect.clear();		//Vector to hold reachable corridors
	vector<vector<int>> adj_nodes; adj_nodes.clear();		//Vector to hold corridors adjacent to to present node
	optim_edges(pyr_schem);									//Reorganize vector holding edges data
	adj_list(pyr_schem, adj_nodes, num_of_entr);			//ADJACENT LIST NODES 
	print_data(pyr_schem);
	print_adj_list(adj_nodes, num_of_entr);
	for (size_t i = 0; i < pyr_schem.size(); i++) {
		if (IDDFS(pyr_schem, adj_nodes, entrance, pyr_schem[i], max_fire_reach, num_of_entr) == true ) {
			cout << "Target " << pyr_schem[i].start << "--" <<
				pyr_schem[i].end << " is reachable from source within max depth\n";
			corr_vect.push_back(pyr_schem[i]);
		}
		else
			cout << "Target " << pyr_schem[i].start << "--" <<
			pyr_schem[i].end << " is NOT reachable from source within max depth\n";
	}
	return corr_vect.size();
}