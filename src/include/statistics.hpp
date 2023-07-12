#ifndef STATISTICS_HPP
#define STATISTICS_HPP

class Statistics {
public:
    Statistics();
    ~Statistics();

    void reset();
    void put(double val);

    double get_min() const;
    double get_max() const;
    double get_avg() const;
    double get_var() const;
    double get_std() const;
    unsigned int get_count() const;

    void print() const;

private:
    double sum;
    double squares_sum;
    double min;
    double max;
    unsigned int count;
}; // Statistics

#endif // STATISTICS_HPP
