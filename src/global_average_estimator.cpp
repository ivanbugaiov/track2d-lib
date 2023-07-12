#include "include/global_average_estimator.hpp"
#include <cmath>

namespace track2d {

static bool check_double_equal(double first, double second) {
    constexpr static double eps = 1.0 / 1000000.0;
    return std::abs(first - second) <= std::abs(eps * std::max(first, second));
}

GlobalAverageEstimator::GlobalAverageEstimator(std::shared_ptr<IPlotSource> plot_source, 
                                               TrackDisplayCallback display_cb) {
    m_plot_source = plot_source;
    m_display_cb = display_cb;
} // GlobalAverageEstimator
    
GlobalAverageEstimator::~GlobalAverageEstimator() {
} // ~GlobalAverageEstimator

std::optional<ITrackEstimator::Result> GlobalAverageEstimator::get_expected_crossing(std::shared_ptr<IPerimeter> perimeter) {
    if (m_state.consumed_plot_count < 2) {
        // estimation not possible
        return std::nullopt;
    }

    custom_time_t look_ahead_time_max = m_state.tick_statistics.get_avg() * 16;
    custom_time_t time_step = m_state.tick_statistics.get_avg();

    double speed_value = m_state.speed_statistics.get_avg();
    double orientation = m_state.prev_angle.value();
    double turn_rate = m_state.turn_statistics.get_avg();
    Vector2D speed_vector = Vector2D(speed_value * time_step, orientation).polar2cartesian();

    Vector2D approach_point = m_state.prev_plot->loc;
    Vector2D unknown_point = approach_point;

    for (custom_time_t look_ahead_time = 0.0; look_ahead_time < look_ahead_time_max; look_ahead_time += time_step) {
        speed_vector = speed_vector.rotate(turn_rate * time_step);
        unknown_point += speed_vector;

        auto maybe_crossing_point = perimeter->get_crossing_point(approach_point, unknown_point);
        if (maybe_crossing_point.has_value()) {
            Result res;
            res.plot.loc = maybe_crossing_point.value();
            res.plot.time = m_state.prev_plot->time + look_ahead_time;
            res.speed = speed_value;
            res.angle = orientation;

            { // report collision
                TrackDisplayMessage msg;
                msg.plot_type = TrackDisplayMessage::PlotType::collision;
                msg.plot = res.plot;
                m_display_cb(msg);
            }

            return res;
        }


        { // report expected position without collision
            TrackDisplayMessage msg;
            msg.plot_type = TrackDisplayMessage::PlotType::estimate;
            msg.plot = {m_state.prev_plot->time + look_ahead_time, unknown_point};
            m_display_cb(msg);
        }

        approach_point = unknown_point;
    }

    return std::nullopt;
} // get_expected_crossing
    
bool GlobalAverageEstimator::advance() {
    auto maybe_next_plot = m_plot_source->get();
    if (!maybe_next_plot) { return false; }

    { // report consumed plot
        TrackDisplayMessage msg;
        msg.plot_type = TrackDisplayMessage::PlotType::source;
        msg.plot = maybe_next_plot.value();
        m_display_cb(msg);
    }
    
    m_state.consumed_plot_count += 1;

    if (!m_state.prev_plot) {
        m_state.prev_plot = maybe_next_plot.value();
        return true;
    }

    Plot next_plot = maybe_next_plot.value();
    Plot prev_plot = m_state.prev_plot.value();

    double dt = next_plot.time - prev_plot.time;
    m_state.tick_statistics.put(dt);

    if (check_double_equal(dt, 0.0)) {
        // skip state updates if time delta is near zero
        return true;
    }

    Vector2D offset = next_plot.loc - prev_plot.loc;

    double current_speed = offset.length() / dt;
    m_state.speed_statistics.put(current_speed);

    if (!m_state.prev_angle) {
        m_state.prev_angle = offset.angle();
    } else {
        double current_angle = offset.angle();
        double current_turn = (current_angle - m_state.prev_angle.value()) / dt;
        m_state.turn_statistics.put(current_turn);
        m_state.prev_angle = current_angle;
    }

    m_state.prev_plot = next_plot;
    return true;
} // advance

} // namespace track2d

