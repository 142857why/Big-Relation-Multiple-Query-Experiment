#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"

#include "ring/ring_sum.hpp"

#define RELATION_R_DYNAMIC

namespace dbtoaster {

  /* Definitions of maps used for storing materialized views. */
  struct R_entry {
    int locn; int ksn; int dateid; int zip; int population; int white; int asian; int pacific; int black; DOUBLE_TYPE medianage; int occupiedhouseunits; int houseunits; int families; int households; int husbwife; int males; int females; int householdschildren; int hispanic; int8_t subcategory; int8_t category; int8_t categorycluster; DOUBLE_TYPE prize; int rgn_cd; int clim_zn_nbr; int tot_area_sq_ft; int sell_area_sq_ft; int avghhi; DOUBLE_TYPE supertargetdistance; DOUBLE_TYPE supertargetdrivetime; DOUBLE_TYPE targetdistance; DOUBLE_TYPE targetdrivetime; DOUBLE_TYPE walmartdistance; DOUBLE_TYPE walmartdrivetime; DOUBLE_TYPE walmartsupercenterdistance; DOUBLE_TYPE walmartsupercenterdrivetime; int8_t rain; int8_t snow; int maxtemp; int mintemp; DOUBLE_TYPE meanwind; int8_t thunder; int inventoryunits; long __av; R_entry* nxt; R_entry* prv;
  
    explicit R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit R_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const int c7, const int c8, const DOUBLE_TYPE c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15, const int c16, const int c17, const int c18, const int8_t c19, const int8_t c20, const int8_t c21, const DOUBLE_TYPE c22, const int c23, const int c24, const int c25, const int c26, const int c27, const DOUBLE_TYPE c28, const DOUBLE_TYPE c29, const DOUBLE_TYPE c30, const DOUBLE_TYPE c31, const DOUBLE_TYPE c32, const DOUBLE_TYPE c33, const DOUBLE_TYPE c34, const DOUBLE_TYPE c35, const int8_t c36, const int8_t c37, const int c38, const int c39, const DOUBLE_TYPE c40, const int8_t c41, const int c42, const long c43) { locn = c0; ksn = c1; dateid = c2; zip = c3; population = c4; white = c5; asian = c6; pacific = c7; black = c8; medianage = c9; occupiedhouseunits = c10; houseunits = c11; families = c12; households = c13; husbwife = c14; males = c15; females = c16; householdschildren = c17; hispanic = c18; subcategory = c19; category = c20; categorycluster = c21; prize = c22; rgn_cd = c23; clim_zn_nbr = c24; tot_area_sq_ft = c25; sell_area_sq_ft = c26; avghhi = c27; supertargetdistance = c28; supertargetdrivetime = c29; targetdistance = c30; targetdrivetime = c31; walmartdistance = c32; walmartdrivetime = c33; walmartsupercenterdistance = c34; walmartsupercenterdrivetime = c35; rain = c36; snow = c37; maxtemp = c38; mintemp = c39; meanwind = c40; thunder = c41; inventoryunits = c42; __av = c43;  }
    R_entry(const R_entry& other) : locn(other.locn), ksn(other.ksn), dateid(other.dateid), zip(other.zip), population(other.population), white(other.white), asian(other.asian), pacific(other.pacific), black(other.black), medianage(other.medianage), occupiedhouseunits(other.occupiedhouseunits), houseunits(other.houseunits), families(other.families), households(other.households), husbwife(other.husbwife), males(other.males), females(other.females), householdschildren(other.householdschildren), hispanic(other.hispanic), subcategory(other.subcategory), category(other.category), categorycluster(other.categorycluster), prize(other.prize), rgn_cd(other.rgn_cd), clim_zn_nbr(other.clim_zn_nbr), tot_area_sq_ft(other.tot_area_sq_ft), sell_area_sq_ft(other.sell_area_sq_ft), avghhi(other.avghhi), supertargetdistance(other.supertargetdistance), supertargetdrivetime(other.supertargetdrivetime), targetdistance(other.targetdistance), targetdrivetime(other.targetdrivetime), walmartdistance(other.walmartdistance), walmartdrivetime(other.walmartdrivetime), walmartsupercenterdistance(other.walmartsupercenterdistance), walmartsupercenterdrivetime(other.walmartsupercenterdrivetime), rain(other.rain), snow(other.snow), maxtemp(other.maxtemp), mintemp(other.mintemp), meanwind(other.meanwind), thunder(other.thunder), inventoryunits(other.inventoryunits), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    R_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 43) return; */
        locn = std::stoi(f[0]); ksn = std::stoi(f[1]); dateid = std::stoi(f[2]); zip = std::stoi(f[3]); population = std::stoi(f[4]); white = std::stoi(f[5]); asian = std::stoi(f[6]); pacific = std::stoi(f[7]); black = std::stoi(f[8]); medianage = std::stod(f[9]); occupiedhouseunits = std::stoi(f[10]); houseunits = std::stoi(f[11]); families = std::stoi(f[12]); households = std::stoi(f[13]); husbwife = std::stoi(f[14]); males = std::stoi(f[15]); females = std::stoi(f[16]); householdschildren = std::stoi(f[17]); hispanic = std::stoi(f[18]); subcategory = (int8_t) std::stoi(f[19]); category = (int8_t) std::stoi(f[20]); categorycluster = (int8_t) std::stoi(f[21]); prize = std::stod(f[22]); rgn_cd = std::stoi(f[23]); clim_zn_nbr = std::stoi(f[24]); tot_area_sq_ft = std::stoi(f[25]); sell_area_sq_ft = std::stoi(f[26]); avghhi = std::stoi(f[27]); supertargetdistance = std::stod(f[28]); supertargetdrivetime = std::stod(f[29]); targetdistance = std::stod(f[30]); targetdrivetime = std::stod(f[31]); walmartdistance = std::stod(f[32]); walmartdrivetime = std::stod(f[33]); walmartsupercenterdistance = std::stod(f[34]); walmartsupercenterdrivetime = std::stod(f[35]); rain = (int8_t) std::stoi(f[36]); snow = (int8_t) std::stoi(f[37]); maxtemp = std::stoi(f[38]); mintemp = std::stoi(f[39]); meanwind = std::stod(f[40]); thunder = (int8_t) std::stoi(f[41]); inventoryunits = std::stoi(f[42]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, population);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, white);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, asian);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, pacific);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, black);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, medianage);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, occupiedhouseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, houseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, families);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, households);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, husbwife);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, males);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, females);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, householdschildren);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, hispanic);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, subcategory);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, category);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, categorycluster);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rgn_cd);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, clim_zn_nbr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, tot_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, sell_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, avghhi);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supertargetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supertargetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, targetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, targetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartsupercenterdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartsupercenterdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, snow);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, maxtemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, mintemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, meanwind);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, thunder);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, inventoryunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct V1_R_entry {
    int locn; int dateid; int ksn; int8_t rain; RingSum __av; V1_R_entry* nxt; V1_R_entry* prv;
  
    explicit V1_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V1_R_entry(const int c0, const int c1, const int c2, const int8_t c3, const RingSum& c4) { locn = c0; dateid = c1; ksn = c2; rain = c3; __av = c4;  }
    V1_R_entry(const V1_R_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), rain(other.rain), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V1_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 4) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); rain = (int8_t) std::stoi(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V1_R_entry& modify(const int c0, const int c1, const int c2, const int8_t c3) { locn = c0; dateid = c1; ksn = c2; rain = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V1_R_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const V1_R_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      hash_combine(h, e.rain);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V1_R_entry& x, const V1_R_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn && x.rain == y.rain;
    }
  };
  
  typedef MultiHashMap<V1_R_entry, RingSum, 
    PrimaryHashIndex<V1_R_entry, V1_R_mapkey0123_idxfn>
  > V1_R_map;
  
  
  struct dV1_R_entry {
    int locn; int dateid; int ksn; int8_t rain; RingSum __av; dV1_R_entry* nxt; dV1_R_entry* prv;
  
    explicit dV1_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit dV1_R_entry(const int c0, const int c1, const int c2, const int8_t c3, const RingSum& c4) { locn = c0; dateid = c1; ksn = c2; rain = c3; __av = c4;  }
    dV1_R_entry(const dV1_R_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), rain(other.rain), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    dV1_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 4) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); rain = (int8_t) std::stoi(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE dV1_R_entry& modify(const int c0, const int c1, const int c2, const int8_t c3) { locn = c0; dateid = c1; ksn = c2; rain = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct dV1_R_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const dV1_R_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      hash_combine(h, e.rain);
      return h;
    }
    
    FORCE_INLINE static bool equals(const dV1_R_entry& x, const dV1_R_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn && x.rain == y.rain;
    }
  };
  
  typedef MultiHashMap<dV1_R_entry, RingSum, 
    PrimaryHashIndex<dV1_R_entry, dV1_R_mapkey0123_idxfn>
  > dV1_R_map;
  
  
  struct V2_R_entry {
    int locn; int dateid; RingSum __av; V2_R_entry* nxt; V2_R_entry* prv;
  
    explicit V2_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V2_R_entry(const int c0, const int c1, const RingSum& c2) { locn = c0; dateid = c1; __av = c2;  }
    V2_R_entry(const V2_R_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V2_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V2_R_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V2_R_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V2_R_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V2_R_entry& x, const V2_R_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<V2_R_entry, RingSum, 
    PrimaryHashIndex<V2_R_entry, V2_R_mapkey01_idxfn>
  > V2_R_map;
  
  
  struct V3_R_entry {
    int locn; RingSum __av; V3_R_entry* nxt; V3_R_entry* prv;
  
    explicit V3_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V3_R_entry(const int c0, const RingSum& c1) { locn = c0; __av = c1;  }
    V3_R_entry(const V3_R_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V3_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V3_R_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V3_R_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V3_R_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V3_R_entry& x, const V3_R_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<V3_R_entry, RingSum, 
    PrimaryHashIndex<V3_R_entry, V3_R_mapkey0_idxfn>
  > V3_R_map;
  
  
  struct DELTA_R_entry {
    int locn; int ksn; int dateid; int zip; int population; int white; int asian; int pacific; int black; DOUBLE_TYPE medianage; int occupiedhouseunits; int houseunits; int families; int households; int husbwife; int males; int females; int householdschildren; int hispanic; int8_t subcategory; int8_t category; int8_t categorycluster; DOUBLE_TYPE prize; int rgn_cd; int clim_zn_nbr; int tot_area_sq_ft; int sell_area_sq_ft; int avghhi; DOUBLE_TYPE supertargetdistance; DOUBLE_TYPE supertargetdrivetime; DOUBLE_TYPE targetdistance; DOUBLE_TYPE targetdrivetime; DOUBLE_TYPE walmartdistance; DOUBLE_TYPE walmartdrivetime; DOUBLE_TYPE walmartsupercenterdistance; DOUBLE_TYPE walmartsupercenterdrivetime; int8_t rain; int8_t snow; int maxtemp; int mintemp; DOUBLE_TYPE meanwind; int8_t thunder; int inventoryunits; long __av; DELTA_R_entry* nxt; DELTA_R_entry* prv;
  
    explicit DELTA_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_R_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const int c7, const int c8, const DOUBLE_TYPE c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15, const int c16, const int c17, const int c18, const int8_t c19, const int8_t c20, const int8_t c21, const DOUBLE_TYPE c22, const int c23, const int c24, const int c25, const int c26, const int c27, const DOUBLE_TYPE c28, const DOUBLE_TYPE c29, const DOUBLE_TYPE c30, const DOUBLE_TYPE c31, const DOUBLE_TYPE c32, const DOUBLE_TYPE c33, const DOUBLE_TYPE c34, const DOUBLE_TYPE c35, const int8_t c36, const int8_t c37, const int c38, const int c39, const DOUBLE_TYPE c40, const int8_t c41, const int c42, const long c43) { locn = c0; ksn = c1; dateid = c2; zip = c3; population = c4; white = c5; asian = c6; pacific = c7; black = c8; medianage = c9; occupiedhouseunits = c10; houseunits = c11; families = c12; households = c13; husbwife = c14; males = c15; females = c16; householdschildren = c17; hispanic = c18; subcategory = c19; category = c20; categorycluster = c21; prize = c22; rgn_cd = c23; clim_zn_nbr = c24; tot_area_sq_ft = c25; sell_area_sq_ft = c26; avghhi = c27; supertargetdistance = c28; supertargetdrivetime = c29; targetdistance = c30; targetdrivetime = c31; walmartdistance = c32; walmartdrivetime = c33; walmartsupercenterdistance = c34; walmartsupercenterdrivetime = c35; rain = c36; snow = c37; maxtemp = c38; mintemp = c39; meanwind = c40; thunder = c41; inventoryunits = c42; __av = c43;  }
    DELTA_R_entry(const DELTA_R_entry& other) : locn(other.locn), ksn(other.ksn), dateid(other.dateid), zip(other.zip), population(other.population), white(other.white), asian(other.asian), pacific(other.pacific), black(other.black), medianage(other.medianage), occupiedhouseunits(other.occupiedhouseunits), houseunits(other.houseunits), families(other.families), households(other.households), husbwife(other.husbwife), males(other.males), females(other.females), householdschildren(other.householdschildren), hispanic(other.hispanic), subcategory(other.subcategory), category(other.category), categorycluster(other.categorycluster), prize(other.prize), rgn_cd(other.rgn_cd), clim_zn_nbr(other.clim_zn_nbr), tot_area_sq_ft(other.tot_area_sq_ft), sell_area_sq_ft(other.sell_area_sq_ft), avghhi(other.avghhi), supertargetdistance(other.supertargetdistance), supertargetdrivetime(other.supertargetdrivetime), targetdistance(other.targetdistance), targetdrivetime(other.targetdrivetime), walmartdistance(other.walmartdistance), walmartdrivetime(other.walmartdrivetime), walmartsupercenterdistance(other.walmartsupercenterdistance), walmartsupercenterdrivetime(other.walmartsupercenterdrivetime), rain(other.rain), snow(other.snow), maxtemp(other.maxtemp), mintemp(other.mintemp), meanwind(other.meanwind), thunder(other.thunder), inventoryunits(other.inventoryunits), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_R_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 43) return; */
        locn = std::stoi(f[0]); ksn = std::stoi(f[1]); dateid = std::stoi(f[2]); zip = std::stoi(f[3]); population = std::stoi(f[4]); white = std::stoi(f[5]); asian = std::stoi(f[6]); pacific = std::stoi(f[7]); black = std::stoi(f[8]); medianage = std::stod(f[9]); occupiedhouseunits = std::stoi(f[10]); houseunits = std::stoi(f[11]); families = std::stoi(f[12]); households = std::stoi(f[13]); husbwife = std::stoi(f[14]); males = std::stoi(f[15]); females = std::stoi(f[16]); householdschildren = std::stoi(f[17]); hispanic = std::stoi(f[18]); subcategory = (int8_t) std::stoi(f[19]); category = (int8_t) std::stoi(f[20]); categorycluster = (int8_t) std::stoi(f[21]); prize = std::stod(f[22]); rgn_cd = std::stoi(f[23]); clim_zn_nbr = std::stoi(f[24]); tot_area_sq_ft = std::stoi(f[25]); sell_area_sq_ft = std::stoi(f[26]); avghhi = std::stoi(f[27]); supertargetdistance = std::stod(f[28]); supertargetdrivetime = std::stod(f[29]); targetdistance = std::stod(f[30]); targetdrivetime = std::stod(f[31]); walmartdistance = std::stod(f[32]); walmartdrivetime = std::stod(f[33]); walmartsupercenterdistance = std::stod(f[34]); walmartsupercenterdrivetime = std::stod(f[35]); rain = (int8_t) std::stoi(f[36]); snow = (int8_t) std::stoi(f[37]); maxtemp = std::stoi(f[38]); mintemp = std::stoi(f[39]); meanwind = std::stod(f[40]); thunder = (int8_t) std::stoi(f[41]); inventoryunits = std::stoi(f[42]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_R_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const int c7, const int c8, const DOUBLE_TYPE c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15, const int c16, const int c17, const int c18, const int8_t c19, const int8_t c20, const int8_t c21, const DOUBLE_TYPE c22, const int c23, const int c24, const int c25, const int c26, const int c27, const DOUBLE_TYPE c28, const DOUBLE_TYPE c29, const DOUBLE_TYPE c30, const DOUBLE_TYPE c31, const DOUBLE_TYPE c32, const DOUBLE_TYPE c33, const DOUBLE_TYPE c34, const DOUBLE_TYPE c35, const int8_t c36, const int8_t c37, const int c38, const int c39, const DOUBLE_TYPE c40, const int8_t c41, const int c42) { locn = c0; ksn = c1; dateid = c2; zip = c3; population = c4; white = c5; asian = c6; pacific = c7; black = c8; medianage = c9; occupiedhouseunits = c10; houseunits = c11; families = c12; households = c13; husbwife = c14; males = c15; females = c16; householdschildren = c17; hispanic = c18; subcategory = c19; category = c20; categorycluster = c21; prize = c22; rgn_cd = c23; clim_zn_nbr = c24; tot_area_sq_ft = c25; sell_area_sq_ft = c26; avghhi = c27; supertargetdistance = c28; supertargetdrivetime = c29; targetdistance = c30; targetdrivetime = c31; walmartdistance = c32; walmartdrivetime = c33; walmartsupercenterdistance = c34; walmartsupercenterdrivetime = c35; rain = c36; snow = c37; maxtemp = c38; mintemp = c39; meanwind = c40; thunder = c41; inventoryunits = c42;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, population);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, white);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, asian);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, pacific);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, black);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, medianage);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, occupiedhouseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, houseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, families);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, households);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, husbwife);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, males);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, females);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, householdschildren);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, hispanic);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, subcategory);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, category);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, categorycluster);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rgn_cd);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, clim_zn_nbr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, tot_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, sell_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, avghhi);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supertargetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supertargetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, targetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, targetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartsupercenterdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartsupercenterdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, snow);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, maxtemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, mintemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, meanwind);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, thunder);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, inventoryunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_R_mapkey0123456789101112131415161718192021222324252627282930313233343536373839404142_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_R_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.ksn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.zip);
      hash_combine(h, e.population);
      hash_combine(h, e.white);
      hash_combine(h, e.asian);
      hash_combine(h, e.pacific);
      hash_combine(h, e.black);
      hash_combine(h, e.medianage);
      hash_combine(h, e.occupiedhouseunits);
      hash_combine(h, e.houseunits);
      hash_combine(h, e.families);
      hash_combine(h, e.households);
      hash_combine(h, e.husbwife);
      hash_combine(h, e.males);
      hash_combine(h, e.females);
      hash_combine(h, e.householdschildren);
      hash_combine(h, e.hispanic);
      hash_combine(h, e.subcategory);
      hash_combine(h, e.category);
      hash_combine(h, e.categorycluster);
      hash_combine(h, e.prize);
      hash_combine(h, e.rgn_cd);
      hash_combine(h, e.clim_zn_nbr);
      hash_combine(h, e.tot_area_sq_ft);
      hash_combine(h, e.sell_area_sq_ft);
      hash_combine(h, e.avghhi);
      hash_combine(h, e.supertargetdistance);
      hash_combine(h, e.supertargetdrivetime);
      hash_combine(h, e.targetdistance);
      hash_combine(h, e.targetdrivetime);
      hash_combine(h, e.walmartdistance);
      hash_combine(h, e.walmartdrivetime);
      hash_combine(h, e.walmartsupercenterdistance);
      hash_combine(h, e.walmartsupercenterdrivetime);
      hash_combine(h, e.rain);
      hash_combine(h, e.snow);
      hash_combine(h, e.maxtemp);
      hash_combine(h, e.mintemp);
      hash_combine(h, e.meanwind);
      hash_combine(h, e.thunder);
      hash_combine(h, e.inventoryunits);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_R_entry& x, const DELTA_R_entry& y) {
      return x.locn == y.locn && x.ksn == y.ksn && x.dateid == y.dateid && x.zip == y.zip && x.population == y.population && x.white == y.white && x.asian == y.asian && x.pacific == y.pacific && x.black == y.black && x.medianage == y.medianage && x.occupiedhouseunits == y.occupiedhouseunits && x.houseunits == y.houseunits && x.families == y.families && x.households == y.households && x.husbwife == y.husbwife && x.males == y.males && x.females == y.females && x.householdschildren == y.householdschildren && x.hispanic == y.hispanic && x.subcategory == y.subcategory && x.category == y.category && x.categorycluster == y.categorycluster && x.prize == y.prize && x.rgn_cd == y.rgn_cd && x.clim_zn_nbr == y.clim_zn_nbr && x.tot_area_sq_ft == y.tot_area_sq_ft && x.sell_area_sq_ft == y.sell_area_sq_ft && x.avghhi == y.avghhi && x.supertargetdistance == y.supertargetdistance && x.supertargetdrivetime == y.supertargetdrivetime && x.targetdistance == y.targetdistance && x.targetdrivetime == y.targetdrivetime && x.walmartdistance == y.walmartdistance && x.walmartdrivetime == y.walmartdrivetime && x.walmartsupercenterdistance == y.walmartsupercenterdistance && x.walmartsupercenterdrivetime == y.walmartsupercenterdrivetime && x.rain == y.rain && x.snow == y.snow && x.maxtemp == y.maxtemp && x.mintemp == y.mintemp && x.meanwind == y.meanwind && x.thunder == y.thunder && x.inventoryunits == y.inventoryunits;
    }
  };
  
  typedef MultiHashMap<DELTA_R_entry, long, 
    PrimaryHashIndex<DELTA_R_entry, DELTA_R_mapkey0123456789101112131415161718192021222324252627282930313233343536373839404142_idxfn>
  > DELTA_R_map;

  

  /* Defines top-level materialized views */
  struct tlq_t {
    struct timeval t0, t; long tT, tN, tS;
    tlq_t(): tN(0), tS(0)  { 
      gettimeofday(&t0, NULL); 
    }
  
    /* Serialization code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      
    }
  
    
  
  protected:
    
    
  };

  /* Contains materialized views and processing (IVM) logic */
  struct data_t : tlq_t {
  
    data_t(): tlq_t() {
      
      
    }
  
    
  
    
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_batch_update_R(const std::vector<DELTA_R_entry>::iterator &begin, const std::vector<DELTA_R_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_R_entry>::iterator e1 = begin; e1 != end; e1++) {
          int locn = e1->locn;
          int ksn = e1->ksn;
          int dateid = e1->dateid;
          int zip = e1->zip;
          int population = e1->population;
          int white = e1->white;
          int asian = e1->asian;
          int pacific = e1->pacific;
          int black = e1->black;
          DOUBLE_TYPE medianage = e1->medianage;
          int occupiedhouseunits = e1->occupiedhouseunits;
          int houseunits = e1->houseunits;
          int families = e1->families;
          int households = e1->households;
          int husbwife = e1->husbwife;
          int males = e1->males;
          int females = e1->females;
          int householdschildren = e1->householdschildren;
          int hispanic = e1->hispanic;
          int8_t subcategory = e1->subcategory;
          int8_t category = e1->category;
          int8_t categorycluster = e1->categorycluster;
          DOUBLE_TYPE prize = e1->prize;
          int rgn_cd = e1->rgn_cd;
          int clim_zn_nbr = e1->clim_zn_nbr;
          int tot_area_sq_ft = e1->tot_area_sq_ft;
          int sell_area_sq_ft = e1->sell_area_sq_ft;
          int avghhi = e1->avghhi;
          DOUBLE_TYPE supertargetdistance = e1->supertargetdistance;
          DOUBLE_TYPE supertargetdrivetime = e1->supertargetdrivetime;
          DOUBLE_TYPE targetdistance = e1->targetdistance;
          DOUBLE_TYPE targetdrivetime = e1->targetdrivetime;
          DOUBLE_TYPE walmartdistance = e1->walmartdistance;
          DOUBLE_TYPE walmartdrivetime = e1->walmartdrivetime;
          DOUBLE_TYPE walmartsupercenterdistance = e1->walmartsupercenterdistance;
          DOUBLE_TYPE walmartsupercenterdrivetime = e1->walmartsupercenterdrivetime;
          int8_t rain = e1->rain;
          int8_t snow = e1->snow;
          int maxtemp = e1->maxtemp;
          int mintemp = e1->mintemp;
          DOUBLE_TYPE meanwind = e1->meanwind;
          int8_t thunder = e1->thunder;
          int inventoryunits = e1->inventoryunits;
          long v1 = e1->__av;
          V1_R.addOrDelOnZero(se1.modify(locn, dateid, ksn, rain), (v1 * Ulift(inventoryunits)));
        }
      }
      
      { //foreach
        for (std::vector<DELTA_R_entry>::iterator e2 = begin; e2 != end; e2++) {
          int locn = e2->locn;
          int ksn = e2->ksn;
          int dateid = e2->dateid;
          int zip = e2->zip;
          int population = e2->population;
          int white = e2->white;
          int asian = e2->asian;
          int pacific = e2->pacific;
          int black = e2->black;
          DOUBLE_TYPE medianage = e2->medianage;
          int occupiedhouseunits = e2->occupiedhouseunits;
          int houseunits = e2->houseunits;
          int families = e2->families;
          int households = e2->households;
          int husbwife = e2->husbwife;
          int males = e2->males;
          int females = e2->females;
          int householdschildren = e2->householdschildren;
          int hispanic = e2->hispanic;
          int8_t subcategory = e2->subcategory;
          int8_t category = e2->category;
          int8_t categorycluster = e2->categorycluster;
          DOUBLE_TYPE prize = e2->prize;
          int rgn_cd = e2->rgn_cd;
          int clim_zn_nbr = e2->clim_zn_nbr;
          int tot_area_sq_ft = e2->tot_area_sq_ft;
          int sell_area_sq_ft = e2->sell_area_sq_ft;
          int avghhi = e2->avghhi;
          DOUBLE_TYPE supertargetdistance = e2->supertargetdistance;
          DOUBLE_TYPE supertargetdrivetime = e2->supertargetdrivetime;
          DOUBLE_TYPE targetdistance = e2->targetdistance;
          DOUBLE_TYPE targetdrivetime = e2->targetdrivetime;
          DOUBLE_TYPE walmartdistance = e2->walmartdistance;
          DOUBLE_TYPE walmartdrivetime = e2->walmartdrivetime;
          DOUBLE_TYPE walmartsupercenterdistance = e2->walmartsupercenterdistance;
          DOUBLE_TYPE walmartsupercenterdrivetime = e2->walmartsupercenterdrivetime;
          int8_t rain = e2->rain;
          int8_t snow = e2->snow;
          int maxtemp = e2->maxtemp;
          int mintemp = e2->mintemp;
          DOUBLE_TYPE meanwind = e2->meanwind;
          int8_t thunder = e2->thunder;
          int inventoryunits = e2->inventoryunits;
          long v2 = e2->__av;
          V2_R.addOrDelOnZero(se2.modify(locn, dateid), (v2 * Ulift(inventoryunits)));
        }
      }
      
      { //foreach
        for (std::vector<DELTA_R_entry>::iterator e3 = begin; e3 != end; e3++) {
          int locn = e3->locn;
          int ksn = e3->ksn;
          int dateid = e3->dateid;
          int zip = e3->zip;
          int population = e3->population;
          int white = e3->white;
          int asian = e3->asian;
          int pacific = e3->pacific;
          int black = e3->black;
          DOUBLE_TYPE medianage = e3->medianage;
          int occupiedhouseunits = e3->occupiedhouseunits;
          int houseunits = e3->houseunits;
          int families = e3->families;
          int households = e3->households;
          int husbwife = e3->husbwife;
          int males = e3->males;
          int females = e3->females;
          int householdschildren = e3->householdschildren;
          int hispanic = e3->hispanic;
          int8_t subcategory = e3->subcategory;
          int8_t category = e3->category;
          int8_t categorycluster = e3->categorycluster;
          DOUBLE_TYPE prize = e3->prize;
          int rgn_cd = e3->rgn_cd;
          int clim_zn_nbr = e3->clim_zn_nbr;
          int tot_area_sq_ft = e3->tot_area_sq_ft;
          int sell_area_sq_ft = e3->sell_area_sq_ft;
          int avghhi = e3->avghhi;
          DOUBLE_TYPE supertargetdistance = e3->supertargetdistance;
          DOUBLE_TYPE supertargetdrivetime = e3->supertargetdrivetime;
          DOUBLE_TYPE targetdistance = e3->targetdistance;
          DOUBLE_TYPE targetdrivetime = e3->targetdrivetime;
          DOUBLE_TYPE walmartdistance = e3->walmartdistance;
          DOUBLE_TYPE walmartdrivetime = e3->walmartdrivetime;
          DOUBLE_TYPE walmartsupercenterdistance = e3->walmartsupercenterdistance;
          DOUBLE_TYPE walmartsupercenterdrivetime = e3->walmartsupercenterdrivetime;
          int8_t rain = e3->rain;
          int8_t snow = e3->snow;
          int maxtemp = e3->maxtemp;
          int mintemp = e3->mintemp;
          DOUBLE_TYPE meanwind = e3->meanwind;
          int8_t thunder = e3->thunder;
          int inventoryunits = e3->inventoryunits;
          long v3 = e3->__av;
          V3_R.addOrDelOnZero(se3.modify(locn), (v3 * Ulift(inventoryunits)));
        }
      }
    }
    
    
    void on_system_ready_event() {
      
    }
  
  private:
    
      /* Preallocated map entries (to avoid recreation of temporary objects) */
      V1_R_entry se1;
      V2_R_entry se2;
      V3_R_entry se3;
    
      
    
      /* Data structures used for storing materialized views */
      V1_R_map V1_R;
      dV1_R_map dV1_R;
      V2_R_map V2_R;
      V3_R_map V3_R;
      DELTA_R_map DELTA_R;
    
      
    
  };

  

}