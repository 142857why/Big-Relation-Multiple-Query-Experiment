# Multiple Query Optimization under a Big Table

## Goal:

## Experiment

### Experiment 1:
Consider the following 2 queries($Q_1$, $Q_2$):
```sql
SELECT locn, dateid, ksn, sum(inventoryunits)
FROM R
GROUP BY locn, dateid, ksn;

SELECT locn, dateid, ksn, rain, householdunits, sum(inventoryunits)
FROM R
GROUP BY locn, dateid, ksn, rain, householdunits;
```

There are clearly two plans for the two queries. The 1st(Plan 01) is to maintain both queries from the scratch and the
2nd(Plan 02) is to maintain $Q_2$ and then use it to compute $Q_1$. Note that
both queries shall have same number of final results as (locn, dateid, ksn) is the primary key of the table.

#### TODO:
- [x] Implement the first plan as 01_01.

- [x] Implement the second plan as 01_02.

- [x] Compare the performance of the two plans.(Interestingly to notice that with the simplified table of retailer, plan
02 is much faster than 01. But with the full table, plan 01 is slightly faster than 02.)

- [ ] Give reasoning for the performance difference.

### Experiment 2:

Consider the following 3 queries($Q_1$, $Q_2$, $Q_3$):

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
There might be 3 query plans to maintain all the queries. The 1st one(02_01) is to maintain all the queries like a chain.
It borrows the delta view from the previous group by query to compute the next group by query. The 2nd one(02_02) is only 
borrowing the delta view from $Q_1$ to compute $Q_2$ and $Q_3$. The 3rd one(02_03) is to maintain all
the queries from the scratch. Note that (locn, dateid, ksn) is the primary key of the table. And thus the number of 
results returned shall decrease from the first query to the third query. Also note that (locn, dateid) -> rain as
(locn, dateid) functions as a primary key in table Weather. 

#### TODO:
- [x] Implement the first plan as 02_01.

- [x] Implement the second plan as 02_02.

- [x] Implement the third plan as 02_03.

- [ ] Compare the performance of the three plans.

- [ ] Give reasoning for the performance difference.

### Experiment 3:

Consider 3 another queries below($Q_1$, $Q_2$, $Q_3$):

```sql
SELECT zip, rain, prize, sum(inventoryunits) FROM R GROUP BY zip, rain, prize;

SELECT zip, rain, sum(inventoryunits) FROM R GROUP BY zip, rain;

SELECT zip, sum(inventoryunits) FROM R GROUP BY zip;
```
Like what we did in Experiment 02, there are 3 query plans that can maintain all the queries. The difference is that the
size of each view shrink very quickly! It's a good example to test whether our estimation during each batch is accurate
or not.

#### TODO:
- [ ] Implement the first plan as 03_01.
- [ ] Implement the second plan as 03_02.
- [ ] Implement the third plan as 03_03.
- [ ] Compare the performance of the three plans.
- [ ] Give reasoning for the performance difference.

### Experiment 3:

Consider 3 another queries below($Q_1$, $Q_2$, $Q_3$):

```sql
SELECT zip, rain, prize, sum(inventoryunits) FROM R GROUP BY zip, rain, prize;

SELECT zip, rain, sum(inventoryunits * prize) FROM R GROUP BY zip, rain;

SELECT zip, sum(inventoryunits) FROM R GROUP BY zip;
```
At first glance, it looks quite similar to Experiment 03! However, if we take a close look at the 1st plan(03_01), 
we see that the top view may not directly borrow the delta view from the previous one. Instead, we may need to carry on 
the sum(units) information along with the sum(units * price) result to the upper view. This requires us to 
make a "bigger" ring for the operation. However, this new ring operation might be time-consuming.

#### TODO:
- [ ] Implement the first plan as 04_01.
- [ ] Implement the second plan as 04_02.
- [ ] Implement the third plan as 04_03.
- [ ] Compare the performance of the three plans.
- [ ] Give reasoning for the performance difference.