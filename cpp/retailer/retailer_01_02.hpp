#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"

#include "ring/ring_sum.hpp"
#include <chrono>
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
    RingSum __av;
    V1_R_entry* nxt;
    V1_R_entry* prv;

    explicit V1_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V1_R_entry(const int c0, const int c1, const int c2, const RingSum& c3) {
        locn = c0;
        dateid = c1;
        ksn = c2;
        __av = c3;
    }
    V1_R_entry(const V1_R_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V1_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 3) return; */
        locn = std::stoi(f[0]);
        dateid = std::stoi(f[1]);
        ksn = std::stoi(f[2]);
        __av = v;
        nxt = nullptr;
        prv = nullptr;
    }

    FORCE_INLINE V1_R_entry& modify(const int c0, const int c1, const int c2) {
        locn = c0;
        dateid = c1;
        ksn = c2;
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
        DBT_SERIALIZATION_NVP(ar, __av);
    }
};

struct V1_R_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const V1_R_entry& e) {
        size_t h = 0;
        hash_combine(h, e.locn);
        hash_combine(h, e.dateid);
        hash_combine(h, e.ksn);
        return h;
    }

    FORCE_INLINE static bool equals(const V1_R_entry& x, const V1_R_entry& y) {
        return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn;
    }
};

typedef MultiHashMap<V1_R_entry, RingSum,
        PrimaryHashIndex<V1_R_entry, V1_R_mapkey012_idxfn>
        > V1_R_map;


struct dV2_R_entry {
    int locn;
    int dateid;
    int ksn;
    int8_t rain;
    int households;
    RingSum __av;
    dV2_R_entry* nxt;
    dV2_R_entry* prv;

    explicit dV2_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit dV2_R_entry(const int c0, const int c1, const int c2, const int8_t c3, const int c4, const RingSum& c5) {
        locn = c0;
        dateid = c1;
        ksn = c2;
        rain = c3;
        households = c4;
        __av = c5;
    }
    dV2_R_entry(const dV2_R_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), rain(other.rain), households(other.households), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    dV2_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 5) return; */
        locn = std::stoi(f[0]);
        dateid = std::stoi(f[1]);
        ksn = std::stoi(f[2]);
        rain = (int8_t) std::stoi(f[3]);
        households = std::stoi(f[4]);
        __av = v;
        nxt = nullptr;
        prv = nullptr;
    }

    FORCE_INLINE dV2_R_entry& modify(const int c0, const int c1, const int c2, const int8_t c3, const int c4) {
        locn = c0;
        dateid = c1;
        ksn = c2;
        rain = c3;
        households = c4;
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
        DBT_SERIALIZATION_NVP(ar, households);
        ar << ELEM_SEPARATOR;
        DBT_SERIALIZATION_NVP(ar, __av);
    }
};

struct dV2_R_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const dV2_R_entry& e) {
        size_t h = 0;
        hash_combine(h, e.locn);
        hash_combine(h, e.dateid);
        hash_combine(h, e.ksn);
        hash_combine(h, e.rain);
        hash_combine(h, e.households);
        return h;
    }

    FORCE_INLINE static bool equals(const dV2_R_entry& x, const dV2_R_entry& y) {
        return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn && x.rain == y.rain && x.households == y.households;
    }
};

typedef MultiHashMap<dV2_R_entry, RingSum,
        PrimaryHashIndex<dV2_R_entry, dV2_R_mapkey01234_idxfn>
        > dV2_R_map;


struct V2_R_entry {
    int locn;
    int dateid;
    int ksn;
    int8_t rain;
    int households;
    RingSum __av;
    V2_R_entry* nxt;
    V2_R_entry* prv;

    explicit V2_R_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V2_R_entry(const int c0, const int c1, const int c2, const int8_t c3, const int c4, const RingSum& c5) {
        locn = c0;
        dateid = c1;
        ksn = c2;
        rain = c3;
        households = c4;
        __av = c5;
    }
    V2_R_entry(const V2_R_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), rain(other.rain), households(other.households), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V2_R_entry(const std::vector<std::string>& f, const RingSum& v) {
        /* if (f.size() < 5) return; */
        locn = std::stoi(f[0]);
        dateid = std::stoi(f[1]);
        ksn = std::stoi(f[2]);
        rain = (int8_t) std::stoi(f[3]);
        households = std::stoi(f[4]);
        __av = v;
        nxt = nullptr;
        prv = nullptr;
    }

    FORCE_INLINE V2_R_entry& modify(const int c0, const int c1, const int c2, const int8_t c3, const int c4) {
        locn = c0;
        dateid = c1;
        ksn = c2;
        rain = c3;
        households = c4;
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
        DBT_SERIALIZATION_NVP(ar, households);
        ar << ELEM_SEPARATOR;
        DBT_SERIALIZATION_NVP(ar, __av);
    }
};

struct V2_R_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const V2_R_entry& e) {
        size_t h = 0;
        hash_combine(h, e.locn);
        hash_combine(h, e.dateid);
        hash_combine(h, e.ksn);
        hash_combine(h, e.rain);
        hash_combine(h, e.households);
        return h;
    }

    FORCE_INLINE static bool equals(const V2_R_entry& x, const V2_R_entry& y) {
        return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn && x.rain == y.rain && x.households == y.households;
    }
};

typedef MultiHashMap<V2_R_entry, RingSum,
        PrimaryHashIndex<V2_R_entry, V2_R_mapkey01234_idxfn>
        > V2_R_map;


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
        c1 = Ulift(1);

    }





    /* Trigger functions for table relations */


    /* Trigger functions for stream relations */
    void on_batch_update_R(const std::vector<DELTA_R_entry>::iterator &begin, const std::vector<DELTA_R_entry>::iterator &end) {
        long batchSize = std::distance(begin, end);

        tN += batchSize;
        dV2_R.clear();
        {
            //foreach
            std::chrono::duration<double, std::milli> t_getKV_total(0);
            std::chrono::duration<double, std::milli> t_update_total(0);
            std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
            for (std::vector<DELTA_R_entry>::iterator e1 = begin; e1 != end; e1++) {
                std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
                int locn = e1->locn;
                int zip = e1->ksn;
                int dateid = e1->dateid;
                int ksn = e1->zip;
                int households = e1->households;
                int8_t rain = e1->rain;
                DOUBLE_TYPE prize = e1->prize;
                int inventoryunits = e1->inventoryunits;
                long v1 = e1->__av;
                std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
                t_getKV_total += t4 - t3;
                std::chrono::high_resolution_clock::time_point t5 = std::chrono::high_resolution_clock::now();
                dV2_R.addOrDelOnZero(se1.modify(locn, dateid, ksn, rain, households), (v1 * Ulift(inventoryunits)));
                std::chrono::high_resolution_clock::time_point t6 = std::chrono::high_resolution_clock::now();
                t_update_total += t6 - t5;
            }
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> t_total_scan = t2 - t1;
            std::cout << "\n--------\n1. Total delta R scan time: " << t_total_scan.count() << " ms" << std::endl;
            std::cout << "1. Total getKV time in dR: " << t_getKV_total.count() << " ms" << std::endl;
            std::cout << "1. Total update time for creating dV: " << t_update_total.count() << " ms" << std::endl;

        }

        {
            //foreach
            dV2_R_entry* e2 = dV2_R.head;
            std::chrono::duration<double, std::milli> t_getKV_total(0);
            std::chrono::duration<double, std::milli> t_update_total(0);
            std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
            while (e2) {
                std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
                int locn = e2->locn;
                int dateid = e2->dateid;
                int ksn = e2->ksn;
                int8_t rain = e2->rain;
                int households = e2->households;
                RingSum& v2 = e2->__av;
                std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
                t_getKV_total += t4 - t3;
                std::chrono::high_resolution_clock::time_point t5 = std::chrono::high_resolution_clock::now();
                V2_R.addOrDelOnZero(se2.modify(locn, dateid, ksn, rain, households), v2);
                std::chrono::high_resolution_clock::time_point t6 = std::chrono::high_resolution_clock::now();
                t_update_total += t6 - t5;
                e2 = e2->nxt;
            }
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> t_total_scan = t2 - t1;
            std::cout << "2. Total dV scan time: " << t_total_scan.count() << " ms" << std::endl;
            std::cout << "2. Total getKV time in dV: " << t_getKV_total.count() << " ms" << std::endl;
            std::cout << "2. Total moving time from dV--->V2: " << t_update_total.count() << " ms" << std::endl;
        }

        {
            //foreach
            dV2_R_entry* e3 = dV2_R.head;
            std::chrono::duration<double, std::milli> t_getKV_total(0);
            std::chrono::duration<double, std::milli> t_update_total(0);
            std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
            while (e3) {
                std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
                int locn = e3->locn;
                int dateid = e3->dateid;
                int ksn = e3->ksn;
                int8_t rain = e3->rain;
                int households = e3->households;
                RingSum& v3 = e3->__av;
                std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
                t_getKV_total += t4 - t3;
                std::chrono::high_resolution_clock::time_point t5 = std::chrono::high_resolution_clock::now();
                V1_R.addOrDelOnZero(se3.modify(locn, dateid, ksn), (v3 * c1));
                std::chrono::high_resolution_clock::time_point t6 = std::chrono::high_resolution_clock::now();
                t_update_total += t6 - t5;
                e3 = e3->nxt;
            }
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> t_total_scan = t2 - t1;
            std::cout << "3. Total dV scan time: " << t_total_scan.count() << " ms" << std::endl;
            std::cout << "3. Total getKV time in dV: " << t_getKV_total.count() << " ms" << std::endl;
            std::cout << "3. Total computation time from dV--->V1: " << t_update_total.count() << " ms" << std::endl;
            std::cout << "---------\n";
        }
    }


    void on_system_ready_event() {

    }

  private:

    /* Preallocated map entries (to avoid recreation of temporary objects) */
    dV2_R_entry se1;
    V2_R_entry se2;
    V1_R_entry se3;



    /* Data structures used for storing materialized views */
    V1_R_map V1_R;
    dV2_R_map dV2_R;
    V2_R_map V2_R;
    DELTA_R_map DELTA_R;



    /* Constant definitions */
    /* const static */ RingSum c1;
};



}