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

DECLARE MAP V1_R(RingSum)[][locn: int, dateid: int, ksn: int];
DECLARE MAP V2_R(RingSum)[][locn: int, dateid: int, ksn: int, rain: byte, households: int];

-- DECLARE QUERY V1_R := V1_R(RingSum)[][locn,dateid,ksn]<local>;
-- DECLARE QUERY V2_R := V2_R(RingSum)[][locnn,dateid,ksn,rain,households]<local>;

ON BATCH UPDATE OF R {
     V1_R(RingSum)[][locn, dateid, ksn]<local> += AggSum(
         [locn, dateid, ksn],
         ((DELTA R)(locn,ksn,dateid,zip,households,rain,prize,inventoryunits) * [lift:RingSum](inventoryunits))
     );

    V2_R(RingSum)[][locn,dateid,ksn,rain,households]<local> += AggSum(
        [locn, dateid, ksn, rain, households],
        ((DELTA R)(locn,ksn,dateid,zip,households,rain,prize,inventoryunits) * [lift:RingSum](inventoryunits))
    );
}

ON SYSTEM READY {

}