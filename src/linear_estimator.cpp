#include "include/linear_estimator.hpp"

namespace track2d {

LinearEstimator::LinearEstimator(std::shared_ptr<IPlotSource> plot_source) {
    m_plot_source = plot_source;
} // LinearEstimator
    
LinearEstimator::~LinearEstimator() {
    
} // ~TrackEstimatorImpl

std::optional<ITrackEstimator::Result> LinearEstimator::get_expected_crossing(std::shared_ptr<IPerimeter> perimeter,
                                                                              custom_time_t look_ahead_interval) {
    return std::nullopt;
} // get_expected_crossing
    
bool LinearEstimator::advance() {
    auto next_plot = m_plot_source->get();
    if (!next_plot) { return false; }

    // do something with new plot

    return true;
} // advance

} // namespace track2d
