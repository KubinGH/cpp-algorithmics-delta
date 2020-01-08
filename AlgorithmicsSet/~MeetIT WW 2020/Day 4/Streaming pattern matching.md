# Streaming pattern matching

## Streaming model

- Space is very limited
- Created to handle large amounts of data (big data)

## Example problems

- One missing number in stream of permutation $\{1, 2, ..., n\}$
    - Trivial (sum or xor)
- Two missing numbers
    - Sum of powers trick (like recoverable hash)

## Pattern matching in streaming model

```
[pattern, length m] $ [text, length n]
```

*Aim*: $O(\log m)$ space and processing of one letter.

**This is possible if we allow for a nondeterministic approach.**

### Randomized approach – string hashing

- *Rabin-Karp* hash function (polynomial hash, rolling hash): denote moudlo $q$ and base $r$
    - *Schwartz-Zippel lemma*: probability of collision of two words of length $m$ is on the order of $O \left( \frac{m}{q} \right)$
    - *Rolling property*: hash of substring (window) can be moved in constant time (or logarithmically if powers of $r$ are not known)

Algorithm:
- Compute hash of pattern.
- Compute hash of windows of length $m$ – report occurence if hashes all equal.

**Problem**: $O(m)$ characters have to be kept, breaking the space limit.

#### Second try

*Key property*: given $u$, $v$ and $w = uv$ we can easily compute hash of each one from the other two.

New algorithm:
- Compute hash of pattern and each prefix such that its length is a power of two.
- Consider occurences of those prefixes in the text.
    - Useful property. *Combinatorics on words*: (\*) given $p$ and $t$ with $|t| \le 2|p|$, and $p$ occuring in $t$ at least three times, the indices of those occurences form an arithmetic sequence.
    - For every $p_j$ (prefix of $p$ of length $2^j$) we want to keep occurences in the last $2^{j+1}$ characters of $t$ – call this $Occ(j)$.
        - If there are at most two: store explicitly. Space is constant.
        - In the opposite case: (\*) is true, so we can store the beginning and the difference of the arithmetic progression. Space is constant too.
        - New problem: **updating** $Occ$.
            - Update $Occ(0)$, then greater $j$.
            - *This can be done with multiple rolling hash operations.*
                1. Remove the first element of $Occ(j)$ if it is equal to $i' = i - 2^j$ *(out of window)*.
                2. If the first element of $Occ(j)$ is $i' + 1$, check if it can be extended into an occurence of $p_{j+1}$ and, if so, add it to $Occ(j + 1)$ *(extend occurence at beginning of window)*.
            - Checking if occurence $p_j$ can be extended to $p_{j+1}$.
                - Keep hash of text up until beginning of first occurence and until this point and do some operations.
            - **A lot of corner cases are here, but it can be done.**

Note that if $m$ is not a power of two, then another prefix is added which is the whole string (needed properties are still kept).

#### Summary

Stored:
- Hash of text up until this point
- For each prefix of length $2^j$:
    - Hash of prefix
    - Arithmetic progression data
    - Hash until first occurence
    - Hash of period of $p_j$

### Mismatches

$k$ mismatches: Can be done in terms of polynomial of $k$ and $\log n$.

### Various

- Two-pass shortest cover
