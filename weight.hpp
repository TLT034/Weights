#pragma once

#include <cstdint>
#include <ratio>

namespace usu
{
    template <typename T, typename R = std::uint64_t>
    class weight
    {
      public:
        weight() { m_count = 0; }
        weight(R count) :
            m_count(count) {}

        R count() { return m_count; }

        weight operator+(const weight& rhs)
        {
            weight result;
            result.m_count = m_count + rhs.m_count;
            return result;
        }

        weight operator-(const weight& rhs)
        {
            weight result;
            result.m_count = m_count - rhs.m_count;
            return result;
        }

        using ratio = T;

      private:
        R m_count;
    };

    template <typename T, typename S>
    T operator*(T& lhs, S scalar)
    {
        T result(lhs.count() * scalar);
        return result;
    }

    template <typename T, typename S>
    T operator*(S scalar, T& rhs)
    {
        T result(scalar * rhs.count());
        return result;
    }

    template <typename T, typename R>
    T weight_cast(R& oldWeight)
    {
        auto oldScale = (R::ratio::num / static_cast<double>(R::ratio::den)) * oldWeight.count();
        auto newScale = (T::ratio::den / static_cast<double>(T::ratio::num));
        T result(newScale * oldScale);
        return result;
    }

    using microgram = weight<std::ratio<1, 1000000>>;
    using gram = weight<std::ratio<1, 1>>;
    using kilogram = weight<std::ratio<1000, 1>, double>;
    using ounce = weight<std::ratio<28349523125, 1000000000>, double>;
    using pound = weight<std::ratio<45359237, 100000>, double>;
    using ton = weight<std::ratio<90718474, 100>, double>;

} // namespace usu
