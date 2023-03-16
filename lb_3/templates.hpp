template <typename T>
T max(T a, T b) {
    if (a > b) return a;
    else return b;
}

template <typename T>
T min(T a, T b) {
    if (a < b) return a;
    else return b;
}

template <typename T>
class Interval {
public:
    Interval(T start, T end) {
        this -> start = start;
        this -> end = end;
    }

    T get_start() const {
        return start;
    }

    T get_end() const {
        return end;
    }

    T get_size() const {
        return (end - start);
    }

    void set_end(T end) {
        this.end = end;
    }

    void get_end_nonconst() {}

    Interval<T> intersection(const Interval<T>& other) const {
        return Interval<T>(
            max(start, other.start),
            min(end, other.end)
        );
    }

private:
    T start;
    T end;
};