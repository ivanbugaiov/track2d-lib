#ifndef LINEAR_ESTIMATOR_HPP
#define LINEAR_ESTIMATOR_HPP

#include "../../include/track2d.hpp"
#include "statistics.hpp"
#include <list>

namespace track2d {

class GlobalAverageEstimator : public ITrackEstimator {
public:
    GlobalAverageEstimator(std::shared_ptr<IPlotSource> plot_source, TrackDisplayCallback display_cb);
    ~GlobalAverageEstimator() final override;
    std::optional<ITrackEstimator::Result> get_expected_crossing(std::shared_ptr<IPerimeter> perimeter) final override;
    bool advance() final override;

private:
    struct State {
        std::optional<Plot> prev_plot;
        std::optional<double> prev_angle;
        Statistics speed_statistics;
        Statistics turn_statistics;
        Statistics tick_statistics;
        size_t consumed_plot_count = 0;
    }; // State

private:
    TrackDisplayCallback m_display_cb;
    std::shared_ptr<IPlotSource> m_plot_source;
    State m_state;
}; // GlobalAverageEstimator

} // namespace track2d

#endif // LINEAR_ESTIMATOR_HPP
