//
// Created by reeckset on 31-03-2018.
//

#ifndef CAL_DIJKSTRABIDIR_H
#define CAL_DIJKSTRABIDIR_H

#include "Dijkstra.h"

typedef vector<Edge> EdgeList;

class DijkstraBiDir : public Dijkstra {
private:
    vector<EdgeList> reversedEdges;
    set<DNode> pQueueReversed;
    DNode topDNodeReversed;
    DNodeHashTable checkedDNodesReversed;
    NodeHashTable pois;
    double bestPOIWeight = DBL_MAX;
    u_int bestPOIId = UINT_MAX;
    u_int regularSearchPOICounter = 0;
    u_int reverseSearchPOICounter = 0;
    bool finishedSearch = false;


    // Clears the data structures for new calculation, populates DNodes pQueue and Reversed edges
    void initDataStructures();

    // Populates the reversed edges container
    void populateReversedEdges();

    // Populates the priority queue for the reversed Dijkstra Expansion
    void populateReversedQueue();

    // Updates the priority queue for the reversed Dijsktra Expansion
    void updateReversedQueue();

    // Check if the current node has been analised by the reversed Dijsktra Expansion
    // Iif it has, it will be in checkedDNodesReversed
    bool isReverseCheckedNode(u_int nodeId) const;

    // Verify if the node is in the POIs Hash Table
    bool isNodePOI(const Node & node) const;

    // Updates the topDNodeReversed
    void updateReversedTopNode();

    // Updates the current best point of interest
    void updateBestPoi(const DNode & commonNode);

    // Takes the finish node that should be on top of the queue and creates a path from recurrent previous nodes
    void buildPath();

    // Checks if the node on top of the queue is a dead end
    bool isReversedTopNodeDeadEnd() const;

    // Removes the topDNode from the pQueue
    void removeReversedTopNodeFromQueue();

    // Reversed Dijkstra Expansion 'main loop'
    void reverseSearch();

    // Regular Dijkstra Expansion 'main loop'
    void regularSearch();

public:
    DijkstraBiDir(const Graph &graph);

    // Calculates optimal path between two nodes, passing through all the points of interest
    vector<u_int> calcOptimalPath(u_int startNodeId, u_int finishNodeId, const NodeHashTable & pois);

    // Returns the Node chosen as the best POI
    Node getBestPOI();

    // Verifies if there is a solution at the present moment
    bool foundSolution() const;
};


#endif //CAL_DIJKSTRABIDIR_H
