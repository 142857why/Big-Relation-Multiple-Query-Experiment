#ifndef RINGSUM_HPP
#define RINGSUM_HPP

#include "types.hpp"
#include "serialization.hpp"

using namespace dbtoaster;
extern int number_ring_x_ring;
extern int number_v_x_ring;
extern int number_ring_plus_ring;
extern int number_lifting;
struct RingSum {
    DOUBLE_TYPE sum;

    static RingSum zero;

    explicit RingSum() : sum(0.0) { }

    explicit RingSum(DOUBLE_TYPE s) : sum(s) { }

    inline bool isZero() const { return sum == 0; }

    RingSum& operator+=(const RingSum &r) {
        number_ring_plus_ring++;
        this->sum += r.sum;
        return *this;
    }

    RingSum operator*(const RingSum &other) {
        number_ring_x_ring++;
        return RingSum(this->sum * other.sum);
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
        ar << ELEM_SEPARATOR;
        DBT_SERIALIZATION_NVP(ar, sum);
    }
};

RingSum operator*(int alpha, const RingSum &r) {
    number_v_x_ring++;
    return RingSum(alpha * r.sum);
}

RingSum Ulift(DOUBLE_TYPE a) {
    number_lifting++;
    return RingSum(a);
}

#endif /* RINGSUM_HPP */