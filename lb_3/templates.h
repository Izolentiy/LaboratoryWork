template <typename T>
class Interval {
public:
    // Interval(T inStart, T inEnd) : start(inStart), end(inEnd) {}
    Interval(T start, T end) {
        this -> start = start;
        this -> end = end;
    };

    T get_start() const; // Модификатор const означает "Только для чтения"
    T get_end() const; // Метод не изменяет ничего в своем теле
    T get_size() const;
    void set_end(T end);
    void get_end_nonconst();

    Interval<T> intersection(const Interval<T>& other);

private:
    T start;
    T end;
};

// #include "templates.hpp"