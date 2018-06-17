// zad6_projekt.cpp : Defines the entry point for the console application.
/************ TEMAT ************
W³amanie do grobowca w piramidzie Hejhopsa to ju¿ wiêksze wyzwanie. Mamy tam
jedn¹ komorê wejœciow¹ i sieæ korytarzy miêdzy komorami. Czas palenia pochodni pozwala dojœæ
do komory odleg³ej najwy¿ej o P komór od komory wejœciowej i nikt nigdy nie zapuœci³ siê dalej.
Sieæ korytarzy to prawdziwy labirynt, ilu¿ to ju¿ œmia³ków zagubi³o siê w nim i pozosta³o tam na
zawsze? No w³aœnie, ilu? Ka¿dy nad Nilem wie, ¿e w ka¿dym korytarzu bêd¹cym w zasiêgu
pochodni le¿y szkielet jednego œmia³ka. Czekaj¹c na skok z nudów wpatrzona w mapê piramidy
postanawiasz napisaæ algorytm, który zliczy ile szkieletów le¿y w korytarzach piramidy.
********************************/

#include <stdio.h>
#include <tchar.h>
#include "skel_cntr.h"

#define FIRE_RANGE 3

using namespace std;

int main(int argc, _TCHAR* argv[]) {
	vector<graph_edge> edges; edges.clear();
	int max = 0, skel_cnt = 0, src = 2, range=3;
	while (!import_graph(edges, max, src));
	print_data(edges);
	skel_cnt = count_skeletons(src, max, edges, range);
	cout << "Number of edges in range: " << skel_cnt << endl;
	cout << "It WORKS!" << endl;
	getch();
	return 0;
}

