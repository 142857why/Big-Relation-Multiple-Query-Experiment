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
    int locn; int ksn; int dateid; int zip; int households; int8_t rain; DOUBLE_TYPE prize; int inventoryunits; long __av; R_entry* nxt; R_entry* prv;
  
    explicit R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit R_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int8_t c5, const DOUBLE_TYPE c6, const int c7, const long c8) { locn = c0; ksn = c1; dateid = c2; zip = c3; households = c4; rain = c5; prize = c6; inventoryunits = c7; __av = c8;  }
    R_entry(const R_entry& other) : locn(other.locn), ksn(other.ksn), dateid(other.dateid), zip(other.zip), households(other.households), rain(other.rain), prize(other.prize), inventoryunits(other.inventoryunits), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    R_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 8) return; */
        locn = std::stoi(f[0]); ksn = std::stoi(f[1]); dateid = std::stoi(f[2]); zip = std::stoi(f[3]); households = std::stoi(f[4]); rain = (int8_t) std::stoi(f[5]); prize = std::stod(f[6]); inventoryunits = std::stoi(f[7]); __av = v; nxt = nullptr; prv = nullptr;
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
      DBT_SERIALIZATION_NVP(ar, households);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, inventoryunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct V1_R_entry {
    int locn; RingSum __av; V1_R_entry* nxt; V1_R_entry* prv;
  
    explicit V1_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V1_R_entry(const int c0, const RingSum& c1) { locn = c0; __av = c1;  }
    V1_R_entry(const V1_R_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V1_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V1_R_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V1_R_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V1_R_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V1_R_entry& x, const V1_R_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<V1_R_entry, RingSum, 
    PrimaryHashIndex<V1_R_entry, V1_R_mapkey0_idxfn>
  > V1_R_map;
  
  
  struct DELTA_R_entry {
    int locn; int ksn; int dateid; int zip; int households; int8_t rain; DOUBLE_TYPE prize; int inventoryunits; long __av; DELTA_R_entry* nxt; DELTA_R_entry* prv;
  
    explicit DELTA_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_R_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int8_t c5, const DOUBLE_TYPE c6, const int c7, const long c8) { locn = c0; ksn = c1; dateid = c2; zip = c3; households = c4; rain = c5; prize = c6; inventoryunits = c7; __av = c8;  }
    DELTA_R_entry(const DELTA_R_entry& other) : locn(other.locn), ksn(other.ksn), dateid(other.dateid), zip(other.zip), households(other.households), rain(other.rain), prize(other.prize), inventoryunits(other.inventoryunits), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_R_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 8) return; */
        locn = std::stoi(f[0]); ksn = std::stoi(f[1]); dateid = std::stoi(f[2]); zip = std::stoi(f[3]); households = std::stoi(f[4]); rain = (int8_t) std::stoi(f[5]); prize = std::stod(f[6]); inventoryunits = std::stoi(f[7]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_R_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int8_t c5, const DOUBLE_TYPE c6, const int c7) { locn = c0; ksn = c1; dateid = c2; zip = c3; households = c4; rain = c5; prize = c6; inventoryunits = c7;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, households);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, inventoryunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_R_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_R_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.ksn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.zip);
      hash_combine(h, e.households);
      hash_combine(h, e.rain);
      hash_combine(h, e.prize);
      hash_combine(h, e.inventoryunits);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_R_entry& x, const DELTA_R_entry& y) {
      return x.locn == y.locn && x.ksn == y.ksn && x.dateid == y.dateid && x.zip == y.zip && x.households == y.households && x.rain == y.rain && x.prize == y.prize && x.inventoryunits == y.inventoryunits;
    }
  };
  
  typedef MultiHashMap<DELTA_R_entry, long, 
    PrimaryHashIndex<DELTA_R_entry, DELTA_R_mapkey01234567_idxfn>
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
      ar << "\n";
      const V1_R_map& _V1_R = get_V1_R();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V1_R), _V1_R, "\t");
    }
  
    /* Functions returning / computing the results of top level queries */
    const V1_R_map& get_V1_R() const {
      return V1_R;
    }
  
  protected:
    /* Data structures used for storing / computing top-level queries */
    V1_R_map V1_R;
    
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
          int households = e1->households;
          int8_t rain = e1->rain;
          DOUBLE_TYPE prize = e1->prize;
          int inventoryunits = e1->inventoryunits;
          long v1 = e1->__av;
          V1_R.addOrDelOnZero(se1.modify(locn), (v1 * Ulift(inventoryunits)));
        }
      }
    }
    
    
    void on_system_ready_event() {
      
    }
  
  private:
    
      /* Preallocated map entries (to avoid recreation of temporary objects) */
      V1_R_entry se1;
    
      
    
      /* Data structures used for storing materialized views */
      DELTA_R_map DELTA_R;
    
      
    
  };

  

}