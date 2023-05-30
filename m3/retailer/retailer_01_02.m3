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

DECLARE MAP V1_R(RingSum)[][locn: int, dateid: int, ksn: int];
DECLARE MAP dV2_R(RingSum)[][locn: int, dateid: int, ksn: int, rain: byte, houseunits: int];
DECLARE MAP V2_R(RingSum)[][locn: int, dateid: int, ksn: int, rain: byte, houseunits: int];

-- DECLARE QUERY V1_R := V1_R(RingSum)[][locn,dateid,ksn]<local>;
-- DECLARE QUERY V2_R := V2_R(RingSum)[][locnn,dateid,ksn,rain,houseunits]<local>;

ON BATCH UPDATE OF R {
    dV2_R(RingSum)[][locn,dateid,ksn,rain,houseunits]<local> := AggSum(
         [locn, dateid, ksn, rain, houseunits],
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
    V2_R(RingSum)[][locn,dateid,ksn,rain,houseunits]<local> += dV2_R(RingSum)[][locn,dateid,ksn,rain,houseunits]<local>;
    V1_R(RingSum)[][locn,dateid,ksn]<local> += AggSum(
        [locn,dateid, ksn],
        (dV2_R(RingSum)[][locn,dateid,ksn,rain,houseunits]<local> * [lift:RingSum](1))
    );
}

ON SYSTEM READY {

}