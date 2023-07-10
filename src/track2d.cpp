#include "../include/track2d.hpp"
#include "include/instant_linear_estimator.hpp"

#include <list>

namespace track2d {

TrackEstimator::TrackEstimator(std::shared_ptr<IPlotSource> track_provider, EstimationModel estimation_model) {
    switch (estimation_model) {
        case EstimationModel::linear:
            m_impl = std::unique_ptr<ITrackEstimator>(new InstantLinearEstimator(track_provider));
    }
    
} // TrackEstimator
    
TrackEstimator::~TrackEstimator() {
} // ~TrackEstimator

std::optional<EstimationResult> TrackEstimator::get_expected_crossing(std::shared_ptr<IPerimeter> perimeter) {
    return m_impl->get_expected_crossing(perimeter);
} // get_expected_crossing

bool TrackEstimator::advance() {
    return  m_impl->advance();
} // advance

} // namespace track2d
