#include <map>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
		if (keyBegin >= keyEnd) return;

		auto lowerBound = m_map.lower_bound(keyBegin);
		auto upperBound = m_map.lower_bound(keyEnd);

		bool isLowerBoundMatching = (lowerBound == m_map.begin()) ? (m_valBegin == val) : (std::prev(lowerBound)->second == val);
		bool isUpperBoundMatching = (upperBound == m_map.begin()) ? (m_valBegin == val) : (std::prev(upperBound)->second == val);

		if (isLowerBoundMatching && (upperBound == m_map.end() || upperBound->first != keyEnd || upperBound->second == val)) {
			return;
		}

		if (!isLowerBoundMatching) {
			lowerBound = m_map.insert_or_assign(keyBegin, val).first;
		}

		if (upperBound == m_map.end() || upperBound->first != keyEnd) {
			if (!isUpperBoundMatching) {
				m_map[keyEnd] = (upperBound == m_map.end()) ? m_valBegin : upperBound->second;
			}
		}

		if (lowerBound != m_map.end()) {
			m_map.erase(std::next(lowerBound), upperBound);
		}

		if (lowerBound != m_map.begin() && std::prev(lowerBound)->second == val) {
			m_map.erase(lowerBound);
		}

		if (upperBound != m_map.end() && upperBound->second == m_map[keyEnd]) {
			m_map.erase(keyEnd);
		}
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.