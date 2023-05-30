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
