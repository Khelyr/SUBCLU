#pragma once
#include "dataanalysis.h"
#include "node.h"

using namespace alglib;

#define MAX_FILENAME 128

// Structure that contain config info
typedef struct arguments_struct {

    int dimension;
    int k; // minimum cluster amount

    char input_filename[MAX_FILENAME];  // Name of the output file
    char output_filename[MAX_FILENAME]; // Name of the input file

} arguments_t;

class SubClustering{
private:

public:


    //Runs the SubClustering Algorithm
    void run(real_2d_array &data, int lim, const char *filename);

    //Subclusters the 2d array result into a Node tree
    void subcluster(integer_2d_array &arr, int currIndex, Node *headNode);


    //Recursive Subclustering
    //DOESN'T WORK
    void recursiveSubclustering(integer_2d_array &arr, int currIndex, Node *currNode);

    //Calculate all node's number of leaf chlidren
    //Fills each node with data
    int calcLeafNodesNum(Node *node);

    //Find Nodes that have lower num of leaf children than the limit
    //These nodes will be the head of different subclusters
    void FillClusterNodes(Node *root, std::vector<Node *> &clusteredNodes, int limit);

    //Find all the leaf nodes under this node and add them to the cluster
    void findLeafNodes(Node *node, std::vector<int> &cluster, int limit);

    //Turn the node trees into a List of Lists to subcluster them properly
    void nodesIntoClusters(std::vector<Node *> &clusteredNodes, std::vector<std::vector<int>> &clusters, int limit);

    //Deletes the tree
    void deleteTree(Node *node);

    //In order traversal showing the labels of each node in the graph
    void inorderTraversal(Node *node);

    //In order traversal showing the labels and the number of leaf child nodes of each node
    void inordernumofLeafChilds(Node *node);

    //Print the results of the clusters
    void print2dvector(std::vector<std::vector<int>> &vectors);

    //Compares two clusters
    //Returns true if clusters are the same
    bool compareClusters(std::vector<std::vector<int>> &vec1, std::vector<std::vector<int>> &vec2);
};
