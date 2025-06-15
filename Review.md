# Review

- Simulation: `Queue Problem`, `Geometry`, `Date Calculation`, `String number add/multiply`, `Rank calculation`
- Datastructure: `Tree Traversal Order Transform`
- Graph: `Deepest nodes`
- DP: `Maximun SubSequence Sum`, `0/1 Package`, `Tree Dependency DP`

Some miscellanies: accurate up means round 
## Simulation

### Queue Problem

- 1014
- 1017
- 1026

```cpp
    q.push( max( minFinishTime, arriveTime ) + neededTime );            // The service time is the maximun of last finishtime and the arrival time of the customer.
    totalWaitedSeconds += max( minFinishTime, arriveTime ) - arriveTime;// Service time - arrvice time = waited time
```

### Num digits problem

- A1060 How to trim string number's zero-prefix and some dogshit boundary condition.
- A1065 climits

### Date Calculation

```cpp

```

## DataStructure

## Graph

- A1021 : Deepest node problem

## DP

- A1068: 0/1 DP + Greedy print package


# TODO List

## Thery Prof

- [ ] 1033 Prove the pesudo-dijkstra algorithm
- [x] 1067 Prove the reverse algorithm

## More Simplified Code

- [x] 1012, 1018 is too complex
- [ ] 1039, 1045 ~~why bit operator << is slower than multuply *~~(bitwise op is lower than plus), why ~~unordered_map is slower than vector and map~~(hash cost and confilct cost)?
- [ ] 1040 Change to DP.
- [x] 1010 Maybe some shitty overflow controll can be simplified.
