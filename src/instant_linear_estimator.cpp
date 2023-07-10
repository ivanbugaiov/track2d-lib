#include "include/instant_linear_estimator.hpp"

namespace track2d {

InstantLinearEstimator::InstantLinearEstimator(std::shared_ptr<IPlotSource> plot_source) {
    m_plot_source = plot_source;
} // InstantLinearEstimator
    
InstantLinearEstimator::~InstantLinearEstimator() {
    
} // ~TrackEstimatorImpl

std::optional<EstimationResult> InstantLinearEstimator::get_expected_crossing(std::shared_ptr<IPerimeter> perimeter) {
    return std::nullopt;
} // get_expected_crossing
    
bool InstantLinearEstimator::advance() {
    auto next_plot = m_plot_source->get();
    if (!next_plot) { return false; }

    // do something with new plot

    return true;
} // advance

} // namespace track2d
