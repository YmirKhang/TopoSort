/*
Student Name: A. Emirhan Karagul
Student Number: 2013400057
Project Number: 3
Operating System: 250.ova
Compile Status: Compiled
Program Status: Working
Notes: Program is calculating the maximum path of all the jobs to be done, it uses some
 functions, which are explained in the inline comments.

*/

// A C++ program to print topological sorting of a DAG
#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <list>
#include <stack>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

//Class of a graph that holds the edges and vertices, and the durations and the adjacency list of the graph

class ProcessGraph
{
    int size;  //size of the graph

    list<int> *adjacency; // adjacency graph of vertices, that holds the adjacencies is the indexes respectively.

public:
    ProcessGraph(int V);

    vector<int> startVertices;

    void addProcess(int u, int v);

    double minTimeofGraph();

    double calcLongest(double *dist, int i);

     double *durations;

    void topoSort();
};

//Default constructor of the Graph, that takes the size as a parameter and initilazes
//the necessary lists.
ProcessGraph::ProcessGraph(int size)
{
    this->size= size;
    adjacency = new list<int>[size];
    durations = new double[size];
}
//Handles the dependancies, adds the vertices to the adj list.
void ProcessGraph::addProcess(int u, int v)
{
    adjacency[u].push_back(v);
}

// This function is used to find the minimum time of completion
// with a helper function
double ProcessGraph::minTimeofGraph() {
    //Initializes the distance array
    double distance[size];
    //Fills the array with -infinities
    // if the graph is cyclic this method returns - inf

    std::fill_n(distance,size,-INFINITY);

    double maxdist= -INFINITY;

    int n = 0;

    //This loop calculates every path starting with each of the starting vertices
    //and saves the maximum path

    for (int i = 0; i <startVertices.size() ; ++i) {
        if(distance[startVertices[i]]==-INFINITY){

            maxdist = std::max(maxdist, calcLongest(distance, startVertices[i]));
        }

    }

    return maxdist;

}

// This function just finds the vertices with indegree '0' and pushes them to the list.
//doesn't sort them.
void ProcessGraph::topoSort() {

    vector<int> in_degree(size, 0);

    for (int u = 0; u < size; u++) {
        list<int>::iterator ptr;
        for (ptr = adjacency[u].begin(); ptr != adjacency[u].end(); ptr++)
            in_degree[*ptr]++;
    }


    for (int i = 0; i < size; i++) {
        if (in_degree[i] == 0) {
            startVertices.push_back(i);
        }
    }


    }

//This function calculates the longest path with a given vertice.
//it takes the pointer to the distance array and traverses it

double ProcessGraph::calcLongest(double *dist, int i) {
    double max= 0;
    list<int>::iterator i1 = adjacency[i].begin();
    for(;i1!=adjacency[i].end();i1++){

        if(dist[*i1]==-INFINITY)

            calcLongest(dist, *i1);

        max=std::max(max,dist[*i1]);

    }

    dist[i]=max+durations[i];

    return dist[i];


}


int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Run the code with the following command: ./project3 [input_file] [output_file]" << endl;
        return 1;
    }
    ifstream infile(argv[1]);
    string line;
    vector<string> input;
    int size;
    int depends;

    // Takes the inputs as lines.

    while (getline(infile, line)) {
        input.push_back(line);
    }

    //parses the size and num of dependancies.

    vector<string> tokens;
    istringstream iss(input[0]);
    copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(tokens));
    size = stoi(tokens[0]);
    depends = stoi(tokens[1]);

    ProcessGraph processes = ProcessGraph(size);

    //saves the durations of the processes respectively.

    for (int i = 1; i <1+size ; ++i) {
        processes.durations[i-1]=stod(input[i]);
    }

    for (int j = size+1; j <size+depends+1 ; ++j) {
        tokens.clear();
        istringstream iss(input[j]);
        copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(tokens));
        processes.addProcess(stoi(tokens[0]),stoi(tokens[1]));

    }

    freopen(argv[2],"w",stdout);
    processes.topoSort();
    double result = processes.minTimeofGraph();
    if(result < 0){
        cout<<"-1"<<endl;
    }else{
        printf("%.6f", result);
        cout<<endl;
    }




}