#ifndef TRACK2D_HPP
#define TRACK2D_HPP

#include <cstdint>
#include <memory>
#include <optional>

namespace track2d {
    
// time.h is not part of the standard library 
// custom type for storing time had to be made
using custom_time_t = uint64_t;
    
struct point2d_t { 
    double x; 
    double y; 
}; // point2d_t

using vector2d_t = point2d_t;

struct Plot {
    custom_time_t time;
    point2d_t loc;
}; // Plot
    
class IPlotSource {
public:
    IPlotSource() {}
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

struct EstimationResult {
    Plot expected_crossing_plot;
    vector2d_t expected_crossing_sped;
    double accuracy;
}; // EstimationResult

class ITrackEstimator {   
public:
    ITrackEstimator() {}
    virtual ~ITrackEstimator() {}
    virtual std::optional<EstimationResult> get_expected_crossing(std::shared_ptr<IPerimeter> perimeter) = 0;
    virtual bool advance() = 0;
}; // ITrackEstimator

enum class EstimationModel { 
    linear
}; // EstimationModel

class TrackEstimator : public ITrackEstimator {
public:
    TrackEstimator(std::shared_ptr<IPlotSource> track_provider, EstimationModel estimation_model);
    ~TrackEstimator() final override;
    std::optional<EstimationResult> get_expected_crossing(std::shared_ptr<IPerimeter> perimeter) final override;
    bool advance() final override;
protected:
    TrackEstimator(std::shared_ptr<IPlotSource> track_provider);
    
private: 
    std::unique_ptr<ITrackEstimator> m_impl;
}; // TrackEstimator

} // namespace track2d 

#endif // TRACK2D_HPP
