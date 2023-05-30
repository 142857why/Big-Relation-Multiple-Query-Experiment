# Multiple Query Optimization under a Big Table

## Goal:

## Experiment

### Experiment 1:
Consider the following 2 queries:
```sql
SELECT locn, dateid, ksn, sum(inventoryunits)
FROM R
GROUP BY locn, dateid, ksn;

SELECT locn, dateid, ksn, rain, householdunits, sum(inventoryunits)
FROM R
GROUP BY locn, dateid, ksn, rain, householdunits;
```

There are clearly two plans for the two queries. The first one is to maintain both queries from the scratch and the
second one is to maintain the second query and then use the first query to compute the second query. Note that
both queries shall have same number of final results as (locn, dateid, ksn) is the primary key of the table.


### Experiment 2:

Consider the following 3 queries($Q_1$, $Q_2$, $Q_3):

```sql
SELECT locn, dateid, ksn, rain, sum(inventoryunits)
FROM R
GROUP BY locn, dateid, ksn, rain;

SELECT locn, dateid, sum(inventoryunits)
FROM R
GROUP BY locn, dateid;

SELECT locn, sum(inventoryunits)
FROM R
GROUP BY locn;
```
There might be 3 query plans to maintain all of the queries. The first one is to maintain all the queries like a chain.
It borrows the delta view from the previous group by query to compute the next group by query. The second one is only 
borrowing the delta view from the first query to compute the second and third query. The third one is to maintain all
the queries from the scratch. Note that (locn, dateid, ksn) is the primary key of the table. And thus the number of 
results returned shall decrease from the first query to the third query. Also note that (locn, dateid) -> rain as
(locn, dateid) functions as a primary key in table Weather. 

### Experiment 3:
