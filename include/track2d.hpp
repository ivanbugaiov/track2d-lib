#ifndef TRACK2D_HPP
#define TRACK2D_HPP

#include "vector2d.hpp"

#include <cstdint>
#include <memory>
#include <optional>
#include <functional>

namespace track2d {
    
// sample data from task description hints at floating point time
using custom_time_t = double;
using Vector2D = vector2d_t<double>;

struct Plot {
    custom_time_t time = 0;
    Vector2D loc;
}; // Plot
    
class IPlotSource {
public:
    virtual ~IPlotSource() {}
    virtual std::optional<Plot> get() = 0;
    virtual bool advance() = 0;
}; // IPlotSource
    
class IPerimeter {
public:
    virtual std::optional<track2d::Vector2D> get_crossing_point(const track2d::Vector2D& approach_point,
                                                                 const track2d::Vector2D& unknown_point) = 0;
}; // IPerimeter

struct Target {
    Vector2D location;
    double speed;
    double angle;
}; // Traget

class ITrackEstimator {   
public:
    struct Result {
        Plot plot;
        double speed;
        double angle;
    }; // Result

public:
    virtual ~ITrackEstimator() {}
    virtual std::optional<Result> get_expected_crossing(std::shared_ptr<IPerimeter> perimeter) = 0;
    virtual bool advance() = 0;
}; // ITrackEstimator

struct TrackDisplayMessage {
    enum class PlotType { source, estimate, collision };
    Plot plot;
    PlotType plot_type;
    double estimation_accuracy;
}; // TrackDisplayMessage

using TrackDisplayCallback = std::function<void(const TrackDisplayMessage&)>;

class TrackEstimator : public ITrackEstimator {
public:
    enum class Model {
        global_average
    }; // Model
    
public:
    TrackEstimator(std::shared_ptr<IPlotSource> track_provider, 
                   Model estimation_model, 
                   TrackDisplayCallback display_cb);
    ~TrackEstimator() final override;
    std::optional<Result> get_expected_crossing(std::shared_ptr<IPerimeter> perimeter) final override;
    bool advance() final override;
protected:
    TrackEstimator(std::shared_ptr<IPlotSource> track_provider);
    
private: 
    std::unique_ptr<ITrackEstimator> m_impl;
}; // TrackEstimator

} // namespace track2d 

#endif // TRACK2D_HPP
