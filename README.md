# DSA2-Project-BloomAndCuckooFilters-NAry-Trees

Vedanshi Shah <br/>
112003149 <br/>
DSA2 - Project <br/>
Divison - 2 <br/>

## Includes: <br/>
1. Application of Bloom Filters on nodes of N-Ary Trees
2. Application of Cuckoo Filters on nodes of N-Ary Trees

## Brief Idea: <br/>
1. Searching in N-Ary tree takes O(N) time by the Naive DFS/BFS algorithm. Application of filters on the tree nodes helps in searching the element better by only following the path that might have the probability of containing the element.
2. Bloom and Cuckoo Filters are probabilistic data-structures used for set membership.
3. Bloom Filters do not support deletion whereas Cuckoo Filters do.

## Results: <br/>
1. More than 80% increase in efficiency was seen by the application of both filters individually on the N-Ary Trees (Nearly 100000 Nodes).
2. Tree with Cuckoo Filter supports deletion of nodes (with respect to searching) (Nodes can be deleted in both trees, but efficient searching after deletion is facilitated by Cuckoo Filter Trees.)

## Graphs: <br/>

### Bloom Tree Search vs Naive Search
![image](https://user-images.githubusercontent.com/77985799/184061369-003835e1-b9f8-48ad-84d2-5388a8695105.png)
<br/>
![image](https://user-images.githubusercontent.com/77985799/184061396-63b24b56-d5b4-4ce5-b8bf-1478119db8ae.png)

### Cuckoo Tree search vs Naive Search
![image](https://user-images.githubusercontent.com/77985799/184061423-f7306c15-8aa4-4f04-818d-b5270fedf667.png)
<br/>
![image](https://user-images.githubusercontent.com/77985799/184061441-37c27efb-934f-404e-8bd3-356d4e4ee2ee.png)
<br/>

## Conclusion: <br/>
Efficient searching for data items in hierarchical data sets is facilitated by the application of bloom and cuckoo filters on the nodes of the N-Ary Tree.
Using these filters one can prune out subtrees that do not have the probability of containing the search element thereby reducing the search time greatly.

## References: <br/>
1. Research Paper on Bloom Filters on Trees[https://american-cse.org/csci2015/data/9795a018.pdf]


