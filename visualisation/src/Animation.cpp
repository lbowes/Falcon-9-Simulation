#include "Animation.h"
#include "../3rd_party/imgui/imgui.h"

#include <algorithm>
#include <iostream>


namespace F9Sim {
namespace Graphics {


Animation::Animation(const nlohmann::json& data, float snapshotInterval_s) :
    m_duration_s(0.0),
    m_snapshotInterval_s(snapshotInterval_s) {

    // This initialisation assumes that:
    // 1. the first snapshot is at time 0
    // 2. the snapshots are spaced equally

    for(auto& state : data)
        m_snapshots.push_back(StateSnapshot(state));

    if(!m_snapshots.empty())
        m_duration_s = m_snapshots.back().m_time_s;
}


StateSnapshot Animation::stateAt(float time_s) const {
    if(m_snapshots.empty())
        return StateSnapshot();

    time_s = std::clamp(time_s, 0.0f, m_duration_s);

    // TODO: This is not perfect, at certain individual frames the state is not interpolated, and jumps/flickers
    const float s = floor(time_s / m_snapshotInterval_s);
    const float between = fmod(time_s, m_snapshotInterval_s) / m_snapshotInterval_s;

    const unsigned int lastSnapshotIdx = m_snapshots.size() - 1;
    const unsigned int previousSnapshotIdx = std::clamp(static_cast<unsigned int>(s), 0U, lastSnapshotIdx);

    const StateSnapshot previous = m_snapshots.at(previousSnapshotIdx);
    const StateSnapshot next = m_snapshots.at(std::clamp(previousSnapshotIdx + 1, 0U, lastSnapshotIdx));
    const StateSnapshot output = StateSnapshot::lerp(previous, next, between);

    return output;
}


} // namespace Graphics
} // namespace F9Sim
