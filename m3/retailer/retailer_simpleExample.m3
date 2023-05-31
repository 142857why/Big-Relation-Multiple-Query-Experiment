CREATE TYPE RingSum FROM FILE 'ring/ring_sum.hpp';

CREATE STREAM R(
    locn int,
    ksn int,
    dateid int,
    zip int,
    households int,
    rain byte,
    prize double,
    inventoryunits int)
FROM FILE 'R.tbl' LINE DELIMITED CSV (delimiter := ',');

DECLARE MAP V1_R(RingSum)[][locn: int];

DECLARE QUERY V1_R := V1_R(RingSum)[][locn]<local>;

ON BATCH UPDATE OF R {
    V1_R(RingSum)[][locn]<local> += AggSum(
        [locn],
        ((DELTA R)(locn,ksn,dateid,zip,households,rain,prize,inventoryunits) * [lift:RingSum](inventoryunits))
    );
}

ON SYSTEM READY {

}
