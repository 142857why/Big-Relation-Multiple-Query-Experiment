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
    int locn;
    int ksn;
    int dateid;
    int zip;
    int households;
    int8_t rain;
    DOUBLE_TYPE prize;
    int inventoryunits;
    long __av;
    R_entry* nxt;
    R_entry* prv;

    explicit R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit R_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int8_t c5, const DOUBLE_TYPE c6, const int c7, const long c8) {
        locn = c0;
        ksn = c1;
        dateid = c2;
        zip = c3;
        households = c4;
        rain = c5;
        prize = c6;
        inventoryunits = c7;
        __av = c8;
    }
    R_entry(const R_entry& other) : locn(other.locn), ksn(other.ksn), dateid(other.dateid), zip(other.zip), households(other.households), rain(other.rain), prize(other.prize), inventoryunits(other.inventoryunits), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    R_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 8) return; */
        locn = std::stoi(f[0]);
        ksn = std::stoi(f[1]);
        dateid = std::stoi(f[2]);
        zip = std::stoi(f[3]);
        households = std::stoi(f[4]);
        rain = (int8_t) std::stoi(f[5]);
        prize = std::stod(f[6]);
        inventoryunits = std::stoi(f[7]);
        __av = v;
        nxt = nullptr;
        prv = nullptr;
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
    int locn;
    int dateid;
    int ksn;
    int8_t rain;
    RingSum __av;
    V1_R_entry* nxt;
    V1_R_entry* prv;

    explicit V1_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V1_R_entry(const int c0, const int c1, const int c2, const int8_t c3, const RingSum& c4) {
        locn = c0;
        dateid = c1;
        ksn = c2;
        rain = c3;
        __av = c4;
    }
    V1_R_entry(const V1_R_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), rain(other.rain), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V1_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 4) return; */
        locn = std::stoi(f[0]);
        dateid = std::stoi(f[1]);
        ksn = std::stoi(f[2]);
        rain = (int8_t) std::stoi(f[3]);
        __av = v;
        nxt = nullptr;
        prv = nullptr;
    }

    FORCE_INLINE V1_R_entry& modify(const int c0, const int c1, const int c2, const int8_t c3) {
        locn = c0;
        dateid = c1;
        ksn = c2;
        rain = c3;
        return *this;
    }
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


struct V2_R_entry {
    int locn;
    int dateid;
    RingSum __av;
    V2_R_entry* nxt;
    V2_R_entry* prv;

    explicit V2_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V2_R_entry(const int c0, const int c1, const RingSum& c2) {
        locn = c0;
        dateid = c1;
        __av = c2;
    }
    V2_R_entry(const V2_R_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V2_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]);
        dateid = std::stoi(f[1]);
        __av = v;
        nxt = nullptr;
        prv = nullptr;
    }

    FORCE_INLINE V2_R_entry& modify(const int c0, const int c1) {
        locn = c0;
        dateid = c1;
        return *this;
    }
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
    int locn;
    RingSum __av;
    V3_R_entry* nxt;
    V3_R_entry* prv;

    explicit V3_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V3_R_entry(const int c0, const RingSum& c1) {
        locn = c0;
        __av = c1;
    }
    V3_R_entry(const V3_R_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V3_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]);
        __av = v;
        nxt = nullptr;
        prv = nullptr;
    }

    FORCE_INLINE V3_R_entry& modify(const int c0) {
        locn = c0;
        return *this;
    }
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
    int locn;
    int ksn;
    int dateid;
    int zip;
    int households;
    int8_t rain;
    DOUBLE_TYPE prize;
    int inventoryunits;
    long __av;
    DELTA_R_entry* nxt;
    DELTA_R_entry* prv;

    explicit DELTA_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_R_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int8_t c5, const DOUBLE_TYPE c6, const int c7, const long c8) {
        locn = c0;
        ksn = c1;
        dateid = c2;
        zip = c3;
        households = c4;
        rain = c5;
        prize = c6;
        inventoryunits = c7;
        __av = c8;
    }
    DELTA_R_entry(const DELTA_R_entry& other) : locn(other.locn), ksn(other.ksn), dateid(other.dateid), zip(other.zip), households(other.households), rain(other.rain), prize(other.prize), inventoryunits(other.inventoryunits), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_R_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 8) return; */
        locn = std::stoi(f[0]);
        ksn = std::stoi(f[1]);
        dateid = std::stoi(f[2]);
        zip = std::stoi(f[3]);
        households = std::stoi(f[4]);
        rain = (int8_t) std::stoi(f[5]);
        prize = std::stod(f[6]);
        inventoryunits = std::stoi(f[7]);
        __av = v;
        nxt = nullptr;
        prv = nullptr;
    }

    FORCE_INLINE DELTA_R_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int8_t c5, const DOUBLE_TYPE c6, const int c7) {
        locn = c0;
        ksn = c1;
        dateid = c2;
        zip = c3;
        households = c4;
        rain = c5;
        prize = c6;
        inventoryunits = c7;
        return *this;
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
    struct timeval t0, t;
    long tT, tN, tS;
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
        int total_hash_hits = 0;
        {
            //foreach
            int hash_hits = 0;
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
                auto se1_pointer = se1.modify(locn, dateid, ksn, rain);
                if (V1_R.get(se1_pointer) != nullptr) {
                    hash_hits ++;
                }
                V1_R.addOrDelOnZero(se1_pointer, (v1 * Ulift(inventoryunits)));
            }
            total_hash_hits += hash_hits;
            std::cout << "\nHash hits for V1_R: " << hash_hits << std::endl;
            std::cout << "The size of V1_R now is: " << V1_R.count() << std::endl;
        }

        {
            //foreach
            int hash_hits = 0;
            for (std::vector<DELTA_R_entry>::iterator e2 = begin; e2 != end; e2++) {
                int locn = e2->locn;
                int ksn = e2->ksn;
                int dateid = e2->dateid;
                int zip = e2->zip;
                int households = e2->households;
                int8_t rain = e2->rain;
                DOUBLE_TYPE prize = e2->prize;
                int inventoryunits = e2->inventoryunits;
                long v2 = e2->__av;
                auto se2_pointer = se2.modify(locn, dateid);
                if (V2_R.get(se2_pointer) != nullptr) {
                    hash_hits ++;
                }
                V2_R.addOrDelOnZero(se2_pointer, (v2 * Ulift(inventoryunits)));
            }
            total_hash_hits += hash_hits;
            std::cout << "Hash hits for V2_R: " << hash_hits << std::endl;
            std::cout << "The size of V2_R now is: " << V2_R.count() << std::endl;
        }

        {
            //foreach
            int hash_hits = 0;
            for (std::vector<DELTA_R_entry>::iterator e3 = begin; e3 != end; e3++) {
                int locn = e3->locn;
                int ksn = e3->ksn;
                int dateid = e3->dateid;
                int zip = e3->zip;
                int households = e3->households;
                int8_t rain = e3->rain;
                DOUBLE_TYPE prize = e3->prize;
                int inventoryunits = e3->inventoryunits;
                long v3 = e3->__av;
                auto se3_pointer = se3.modify(locn);
                if (V3_R.get(se3_pointer) != nullptr) {
                    hash_hits ++;
                }
                V3_R.addOrDelOnZero(se3_pointer, (v3 * Ulift(inventoryunits)));
            }
            total_hash_hits += hash_hits;
            std::cout << "Hash hits for V3_R: " << hash_hits << std::endl;
            std::cout << "The size of V3_R now is: " << V3_R.count() << std::endl;
            std::cout << "----------\nTotal hash hits in this Round: " << total_hash_hits << "\n----------" << std::endl;
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
    V2_R_map V2_R;
    V3_R_map V3_R;
    DELTA_R_map DELTA_R;



};



}