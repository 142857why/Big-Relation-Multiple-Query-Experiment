CREATE TYPE RingSum FROM FILE 'ring/ring_sum.hpp';

CREATE STREAM R(locn int,
                ksn int,
                dateid int,
                zip int,
                population int,
                white int,
                asian int,
                pacific int,
                black int,
                medianage double,
                occupiedhouseunits int,
                houseunits int,
                families int,
                households int,
                husbwife int,
                males int,
                females int,
                householdschildren int,
                hispanic int,
                subcategory byte,
                category byte,
                categorycluster byte,
                prize double,
                rgn_cd int,
                clim_zn_nbr int,
                tot_area_sq_ft int,
                sell_area_sq_ft int,
                avghhi int,
                supertargetdistance double,
                supertargetdrivetime double,
                targetdistance double,
                targetdrivetime double,
                walmartdistance double,
                walmartdrivetime double,
                walmartsupercenterdistance double,
                walmartsupercenterdrivetime double,
                rain byte,
                snow byte,
                maxtemp int,
                mintemp int,
                meanwind double,
                thunder byte,
                inventoryunits int)
    FROM FILE 'R.tbl' LINE DELIMITED CSV (delimiter := ',');

DECLARE MAP V1_R(RingSum)[][locn: int, dateid: int, ksn: int, rain:byte];
DECLARE MAP dV1_R(RingSum)[][locn: int, dateid: int, ksn: int, rain: byte];
DECLARE MAP V2_R(RingSum)[][locn: int, dateid: int];
DECLARE MAP V3_R(RingSum)[][locn: int];

--- Declare Queries
-- DECLARE QUERY V1_R := V1_R(RingSum)[][locn,dateid,ksn,rain]<local>;
-- DECLARE QUERY V2_R := V2_R(RingSum)[][locn,dateid]<local>;
-- DECLARE QUERY V3_R := V3_R(RingSum)[][locn]<local>;

ON BATCH UPDATE OF R {
    dV1_R(RingSum)[][locn,dateid,ksn,rain]<local> := AggSum(
        [locn, dateid, ksn, rain],
        ((DELTA R)(locn,
             ksn,
             dateid,
             zip,
             population,
             white,
             asian,
             pacific,
             black,
             medianage,
             occupiedhouseunits,
             houseunits,
             families,
             households,
             husbwife,
             males,
             females,
             householdschildren,
             hispanic,
             subcategory,
             category,
             categorycluster,
             prize,
             rgn_cd,
             clim_zn_nbr,
             tot_area_sq_ft,
             sell_area_sq_ft,
             avghhi,
             supertargetdistance,
             supertargetdrivetime,
             targetdistance,
             targetdrivetime,
             walmartdistance,
             walmartdrivetime,
             walmartsupercenterdistance,
             walmartsupercenterdrivetime,
             rain,
             snow,
             maxtemp,
             mintemp,
             meanwind,
             thunder,
             inventoryunits) * [lift:RingSum](inventoryunits))
    );

    V1_R(RingSum)[][locn,dateid,ksn,rain]<local> += dV1_R(RingSum)[][locn,dateid,ksn,rain]<local>;
    V2_R(RingSum)[][locn,dateid]<local> += AggSum(
        [locn, dateid],
        dV1_R(RingSum)[][locn,dateid,ksn,rain]<local> * [lift:RingSum](1)
    );
    V3_R(RingSum)[][locn]<local> += AggSum(
        [locn],
        dV1_R(RingSum)[][locn,dateid,ksn,rain]<local> * [lift:RingSum](1)
    );
}

ON SYSTEM READY {

}