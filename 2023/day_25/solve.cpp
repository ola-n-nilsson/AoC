// from https://stackoverflow.com/questions/46753785/bgl-geting-edge-indices-from-stoer-wagner-min-cut

// g++ -std=c++14 -O2 -Wall -pedantic -pthread -o solve solve.cpp

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/stoer_wagner_min_cut.hpp>

#if 0
typedef enum  {
#include "datar.txt"
} node_t;

typedef struct
{
  node_t node;
  const char* name;
} name_t;

const name_t names[] = {
#include "datastr.txt"
};

const node_t data[][20] = {
#include "data.txt"
};
#else
typedef enum  {
#include "datar2.txt"
} node_t;

typedef struct
{
  node_t node;
  const char* name;
} name_t;

const name_t names[] = {
#include "datastr2.txt"
};

const node_t data[][20] = {
#include "data2.txt"
};

#endif


int main(void) {
  typedef boost::property<boost::edge_weight_t, int> EdgeWeightProp;
  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProp> Graph;
  node_t guard = (node_t)-1;

  Graph conn(end);

  for(int i=0;i<(int)(sizeof(data)/sizeof(data[0]));i++) {
    int j = 1;
      
    while(data[i][j]!=guard) {
      add_edge(data[i][j], data[i][0], 1, conn);
      j++;
    }
  }

  auto parity = boost::make_one_bit_color_map(num_vertices(conn), get(boost::vertex_index, conn));
  auto weights = get(boost::edge_weight, conn);
  int w = boost::stoer_wagner_min_cut(conn, weights, boost::parity_map(parity));

  for (auto ed : boost::make_iterator_range(edges(conn))) {
    auto s = source(ed, conn), t = target(ed, conn);
    if (get(parity, s)!=get(parity, t))
      std::cout << "{" << names[s].name << "," << names[t].name << "; weight " << get(weights, ed) << "}\n";
  }

  std::cout << "Mincut weight is " << w << std::endl;
}
