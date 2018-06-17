// zad6_projekt.cpp : Defines the entry point for the console application.
/************ TEMAT ************
W�amanie do grobowca w piramidzie Hejhopsa to ju� wi�ksze wyzwanie. Mamy tam
jedn� komor� wej�ciow� i sie� korytarzy mi�dzy komorami. Czas palenia pochodni pozwala doj��
do komory odleg�ej najwy�ej o P kom�r od komory wej�ciowej i nikt nigdy nie zapu�ci� si� dalej.
Sie� korytarzy to prawdziwy labirynt, ilu� to ju� �mia�k�w zagubi�o si� w nim i pozosta�o tam na
zawsze? No w�a�nie, ilu? Ka�dy nad Nilem wie, �e w ka�dym korytarzu b�d�cym w zasi�gu
pochodni le�y szkielet jednego �mia�ka. Czekaj�c na skok z nud�w wpatrzona w map� piramidy
postanawiasz napisa� algorytm, kt�ry zliczy ile szkielet�w le�y w korytarzach piramidy.
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

