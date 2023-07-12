#include "../include/track2d.hpp"
#include "include/global_average_estimator.hpp"

#include <list>

namespace track2d {

TrackEstimator::TrackEstimator(std::shared_ptr<IPlotSource> track_provider, 
                               Model estimation_model, 
                               TrackDisplayCallback display_cb) {
    switch (estimation_model) {
        case Model::global_average:
            m_impl = std::unique_ptr<ITrackEstimator>(new GlobalAverageEstimator(track_provider,
                                                                                 display_cb));
    }
    
} // TrackEstimator
    
TrackEstimator::~TrackEstimator() {
} // ~TrackEstimator

std::optional<ITrackEstimator::Result> TrackEstimator::get_expected_crossing(std::shared_ptr<IPerimeter> perimeter) {
    return m_impl->get_expected_crossing(perimeter);
} // get_expected_crossing

bool TrackEstimator::advance() {
    return  m_impl->advance();
} // advance

} // namespace track2d
