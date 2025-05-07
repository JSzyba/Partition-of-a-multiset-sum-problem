# Partition-of-a-multiset-sum-problem
A simple set of instructions to solve yet another generalization of a subset sum problem.

## Problem Description

We are given a multiset $M$ containing $n$ non-negative integer elements. This multiset has been arbitrarily divided into $m$ disjoint submultisets of equal size (assume that $n$ is a multiple of $m$).

We seek a multiset $S$ of elements that satisfies the following conditions:

- **Sum condition:**  
  The sum of the elements in multiset $S$ equals $s$.

- **Submultiset condition:**  
  The elements of multiset $S$ belong to at most $q$ different submultisets of the previously defined multiset $M$. This means there exists a family of submultisets $F$ to which all submultisets contributing elements to $S$ belong, and the cardinality of $F$ is at most $q$.

- **Range condition:**  
  The value of $s$ lies between:
  
  - the sum of elements of the submultiset with the minimal sum, and
  - the sum of the elements of the $q$ submultisets with the largest sums among all submultisets of $M$.

  This range is intended to avoid trivial cases where it would be impossible to find elements summing to $s$.

---

## Solution

The solution to the problem is to return a set $S$ that meets these conditions. If no such set $S$ exists, a message indicating that no solution can be found is returned.

By default, the parameter $q$ equals 2.

---

## Notes

This problem is a modification of the classical subset sum problem, which does not include the condition of selecting elements from at most $q$ fixed submultisets.
