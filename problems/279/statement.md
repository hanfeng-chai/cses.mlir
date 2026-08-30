Given an array of n integers, your task is to find the number of different subset xors.

# Input

The first line has an integer n: the size of the array.

The next line has n integers x\_1,x\_2,\dots,x\_n: the contents of the array.

# Output

Print one integer: the number of different subset xors.

# Constraints

- 1 \le n \le 2 \cdot 10^5
- 0 \le x\_i \le 10^9

# Example

Input:

```
3
3 6 5
```

Output:

```
4
```

Explanation: The following values can be the xor of a subset:

- 0 = \text{xor of the empty set}
- 3 = 3
- 5 = 3 \oplus 6
- 6 = 3 \oplus 5

In this case, no other values can be the xor of a subset.
