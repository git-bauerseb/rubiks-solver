# Searching

## Dijkstra

Idea:
    - dist: array from source to each node
    - Q: queue of all nodes (priority queue according to distance)
    - S: empty set to indicate visited

Algorithm:
    - While !Q.empty() and not in S, extract node v s.t. dist(v) is minimum
    - add v to S
    - for all neighbours u: If dist(v) + w(v,u) < dist(u), update dist(u)


## A star

- introduce heuristic into regular graph-searching algorithm
