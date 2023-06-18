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

DECLARE MAP V1_R(RingSum)[][locn: int, dateid: int, ksn: int, rain:byte];
DECLARE MAP V2_R(RingSum)[][locn: int, dateid: int];
DECLARE MAP V3_R(RingSum)[][locn: int];

--- Declare Queries
-- DECLARE QUERY V1_R := V1_R(RingSum)[][locn,dateid,ksn,rain]<local>;
-- DECLARE QUERY V2_R := V2_R(RingSum)[][locn,dateid]<local>;
-- DECLARE QUERY V3_R := V3_R(RingSum)[][locn]<local>;

ON BATCH UPDATE OF R {
    V1_R(RingSum)[][locn,dateid,ksn,rain]<local> += AggSum(
        [locn, dateid, ksn, rain],
        ((DELTA R)(locn,ksn,dateid,zip,households,rain,prize,inventoryunits) * [lift:RingSum](inventoryunits))
    );

    V2_R(RingSum)[][locn,dateid]<local> += AggSum(
        [locn, dateid],
        ((DELTA R)(locn,ksn,dateid,zip,households,rain,prize,inventoryunits) * [lift:RingSum](inventoryunits))
    );

    V3_R(RingSum)[][locn]<local> += AggSum(
        [locn],
        ((DELTA R)(locn,ksn,dateid,zip,households,rain,prize,inventoryunits) * [lift:RingSum](inventoryunits))
    );
}

ON SYSTEM READY {

}