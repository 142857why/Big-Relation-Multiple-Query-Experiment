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

DECLARE MAP V1_R(RingSum)[][zip: int, rain: byte, prize: double];
DECLARE MAP dV1_R(RingSum)[][zip: int, rain: byte, prize: double];
DECLARE MAP V2_R(RingSum)[][zip: int, rain: byte];
DECLARE MAP V3_R(RingSum)[][zip: int];

--- Declare Queries
-- DECLARE QUERY V1_R := V1_R(RingSum)[][zip, rain, prize]<local>;
-- DECLARE QUERY V2_R := V2_R(RingSum)[][zip, rain]<local>;
-- DECLARE QUERY V3_R := V3_R(RingSum)[][zip]<local>;

ON BATCH UPDATE OF R {
    dV1_R(RingSum)[][zip,rain,prize]<local> := AggSum(
        [zip,rain,prize],
        ((DELTA R)(locn,ksn,dateid,zip,households,rain,prize,inventoryunits) * [lift:RingSum](inventoryunits))
    );

    V1_R(RingSum)[][zip,rain,prize]<local> += dV1_R(RingSum)[][zip,rain,prize]<local>;
    V2_R(RingSum)[][zip,rain]<local> += AggSum(
        [zip,rain],
        dV1_R(RingSum)[][zip,rain,prize]<local> * [lift:RingSum](1)
    );
    V3_R(RingSum)[][zip]<local> += AggSum(
        [zip],
        dV1_R(RingSum)[][zip,rain,prize]<local> * [lift:RingSum](1)
    );
}

ON SYSTEM READY {

}