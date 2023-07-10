#ifndef TRACK2D_HPP
#define TRACK2D_HPP

#include <cstdint>
#include <memory>
#include <optional>

namespace track2d {
    
// sample data from task description hints at floating point time
using custom_time_t = double;
    
struct point2d_t { 
    double x = 0.0;
    double y = 0.0;
}; // point2d_t

using vector2d_t = point2d_t;

struct Plot {
    custom_time_t time = 0;
    point2d_t loc;
}; // Plot
    
class IPlotSource {
public:
    virtual ~IPlotSource() {}
    virtual std::optional<Plot> get() = 0;
    virtual bool advance() = 0;
}; // IPlotSource
    
class IPerimeter {
public:
    virtual bool is_point_inside(const point2d_t& pt) = 0;
}; // IPerimeter

struct Target {
    point2d_t current_location;
    vector2d_t current_speed;
}; // Traget

double get_target_speed(const Target& target);
double get_target_angle(const Target& target);

class ITrackEstimator {   
public:
    struct Result {
        Plot plot;
        vector2d_t speed;
        double accuracy;
    }; // Result

public:
    virtual ~ITrackEstimator() {}
    virtual std::optional<Result> get_expected_crossing(std::shared_ptr<IPerimeter> perimeter,
                                                        custom_time_t look_ahead_interval) = 0;
    virtual bool advance() = 0;
}; // ITrackEstimator


class TrackEstimator : public ITrackEstimator {
public:
    enum class Model {
        linear
    }; // Model

public:
    TrackEstimator(std::shared_ptr<IPlotSource> track_provider, Model estimation_model);
    ~TrackEstimator() final override;
    std::optional<Result> get_expected_crossing(std::shared_ptr<IPerimeter> perimeter,
                                                custom_time_t look_ahead_interval) final override;
    bool advance() final override;
protected:
    TrackEstimator(std::shared_ptr<IPlotSource> track_provider);
    
private: 
    std::unique_ptr<ITrackEstimator> m_impl;
}; // TrackEstimator

} // namespace track2d 

#endif // TRACK2D_HPP
