A *tournament graph* is a directed graph where a single directed edge exists between every pair of nodes.

Given n, your task is to calculate for each k = 1 \dots n the number of tournament graphs that have n nodes and k strongly connected components.

# Input

The only line has an integer n: the number of nodes.

# Output

Print n lines: for each k=1 \dots n the number of graphs modulo 10^9+7.

# Constraints

- 1 \le n \le 500

# Example

Input:

```
3
```

Output:

```
2
0
6
```
