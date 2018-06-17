#ifndef SKEL_CNTR_H
#define SKEL_CNTR_H
/************ TEMAT ************
W³amanie do grobowca w piramidzie Hejhopsa to ju¿ wiêksze wyzwanie. Mamy tam
jedn¹ komorê wejœciow¹ i sieæ korytarzy miêdzy komorami. Czas palenia pochodni pozwala dojœæ
do komory odleg³ej najwy¿ej o P komór od komory wejœciowej i nikt nigdy nie zapuœci³ siê dalej.
Sieæ korytarzy to prawdziwy labirynt, ilu¿ to ju¿ œmia³ków zagubi³o siê w nim i pozosta³o tam na
zawsze? No w³aœnie, ilu? Ka¿dy nad Nilem wie, ¿e w ka¿dym korytarzu bêd¹cym w zasiêgu
pochodni le¿y szkielet jednego œmia³ka. Czekaj¹c na skok z nudów wpatrzona w mapê piramidy
postanawiasz napisaæ algorytm, który zliczy ile szkieletów le¿y w korytarzach piramidy.
********************************/

/* skel_cntr.h -- Algorithm Header File */

/* User Includes */
#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
//#include <cstdlib>
//#include <windows.h>

using namespace std;

#define P_fire 3		//you can visit 'P' caves far apart from entrance on one burning torch

struct graph_edge{
	int start;
	int end;
	inline bool operator> (const graph_edge &e1) {
		if (start > e1.start) return true;
		if (start == e1.start && end > e1.end) return true;
		else return false;
	}
	inline bool operator< (const graph_edge &e1) {
		if (start < e1.start) return true;
		if (start == e1.start && end < e1.end) return true;
		else return false;
	}
};

/* Get graph data */
bool import_graph(vector<graph_edge> &m_edges, int &max, int &src);

/* Print edges data */
void print_data(vector <graph_edge> &m_edges);

/* Check if this edge is existing */
bool is_edge(vector<graph_edge> &m_edges, int p, int q);

/* Print adjacency matrix */
void print_adj_list(vector <vector <int>> adj_list, int max);

/* Reorganize data edges data */
void reorganize_edges(vector <graph_edge> &m_edges);

/* Delete edges that are duplicates */
void optim_edges(vector <graph_edge> &m_edges);

/* QuickSort graph data ascending */
void sort_vector(vector <graph_edge> &m_edges, int l, int r);

/* Create adjacency matrix */
template <unsigned R, unsigned C>
void adj_matrix(vector <graph_edge> m_edges, bool (&adj_m)[R][C]);

/* Return list of nodes adjacent */
void adj_list(vector<graph_edge> m_edges, vector<vector<int>> &m_nodes, int max);

/* Perform DLS - Depth Limited Search */
bool DLS(vector<graph_edge> m_edges, vector<vector<int>> &m_adj, int src, int dst, int limit, int maxV);

/* IDDFS to search if target is reachable from v. It uses recursive DFSUtil(). */
bool IDDFS(vector<graph_edge> m_edges, vector<vector<int>> &m_adj, int src, /*int target*/graph_edge m_edge, int max_depth, int maxV);

/* Count skeletons present in pyramide */
int count_skeletons(int entrance, int num_of_entr, vector<graph_edge> &pyr_schem, int max_fire_reach);
#endif