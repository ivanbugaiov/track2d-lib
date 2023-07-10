#ifndef LINEAR_ESTIMATOR_HPP
#define LINEAR_ESTIMATOR_HPP

#include "../../include/track2d.hpp"
#include <list>

namespace track2d {

class LinearEstimator : public ITrackEstimator {
public:
    LinearEstimator(std::shared_ptr<IPlotSource> plot_source);
    ~LinearEstimator() final override;
    std::optional<ITrackEstimator::Result> get_expected_crossing(std::shared_ptr<IPerimeter> perimeter,
                                                                 custom_time_t look_ahead_interval) final override;
    bool advance() final override;
private:
    std::shared_ptr<IPlotSource> m_plot_source;
    Plot last_plot;
}; // LinearEstimator

} // namespace track2d

#endif // LINEAR_ESTIMATOR_HPP
