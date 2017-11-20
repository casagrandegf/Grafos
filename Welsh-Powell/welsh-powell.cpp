// Gabriel Fernando Casagrande
// Use -std=c++11

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

typedef pair< int, int > ii;

// Testa se algum dos vizinhos ja foi colorido com a cor atual
bool cNeighbors(vector<int> listAdj, set<ii> vColors, int color) {
  for (auto i : listAdj)
    if (vColors.count(ii(i, color))) 
      return false;
  return true;
}

void welshPowell(vector< vector<int> > listAdj, list<ii> dg, set<ii> &vColors) {
  int color = 1;
  list<ii> vDel;

  while(!dg.empty()) {
    // Encontra vertices para colorir
    for (auto i : dg) {
      if (cNeighbors(listAdj[i.second], vColors, color)) {
        vColors.insert(ii(i.second, color));
        vDel.push_back(i);
      }     
    }
    // Remove os vertices ja coloridos da lista
    for(auto j : vDel) 
      dg.remove(j);
    color++;
  }
}

int main () {
  int u, v, nV;
  
  cin >> nV;
  
  vector<int> dg(nV);
  vector< vector<int> > listAdj(nV);

  // Constroi o grafo
  while (cin >> u >> v) {
    dg[u]++; dg[v]++;
    listAdj[u].push_back(v); listAdj[v].push_back(u);
  }

  // Ordena os vertices pelo grau, first = grau, second = vertice 
  list<ii> dgl;
  for (int i = 0; i < nV; i++)
    dgl.push_back(ii(dg[i], i));
  dgl.sort(greater<ii>());
  
  // Colore os vertices
  set<ii> vColors;
  welshPowell(listAdj, dgl, vColors);
  
  for(auto i:vColors)
    cout << "Verice: " << (char)(i.first + 'A') << "  Cor: " << i.second << "  Grau: " << dg[i.first] << "\n";
  
  return 0;
}