#ifndef INSTANT_LINEAR_ESTIMATOR_HPP
#define INSTANT_LINEAR_ESTIMATOR_HPP

#include "../../include/track2d.hpp"
#include <list>

namespace track2d {

class InstantLinearEstimator : public ITrackEstimator {
public:
    InstantLinearEstimator(std::shared_ptr<IPlotSource> plot_source);
    ~InstantLinearEstimator() final override;
    std::optional<EstimationResult> get_expected_crossing(std::shared_ptr<IPerimeter> perimeter) final override;
    bool advance() final override;
private:
    std::shared_ptr<IPlotSource> m_plot_source;
    Plot last_plot;
}; // InstantLinearEstimator 

} // namespace track2d

#endif // INSTANT_LINEAR_ESTIMATOR_HPP
