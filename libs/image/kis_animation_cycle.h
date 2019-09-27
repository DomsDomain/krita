/*
 *  Copyright (c) 2018 Jouni Pentikäinen <joupent@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KIS_ANIMATION_CYCLE_H
#define KIS_ANIMATION_CYCLE_H

#include "kis_keyframe.h"
#include "kis_time_range.h"

class KisTimeSpan;
class KisFrameSet;
class KisRepeatFrame;

class KRITAIMAGE_EXPORT KisRepeatFrame : public KisKeyframeBase
{
public:
    KisRepeatFrame(KisKeyframeChannel *channel, int time, KisTimeSpan sourceRange);
    KisRepeatFrame(const KisRepeatFrame &rhs, KisTimeSpan newRange);
    KisRepeatFrame(const KisRepeatFrame &rhs, KisKeyframeChannel *newChannel);

    QRect affectedRect() const override;

    KisTimeSpan sourceRange() const;

    int getOriginalTimeFor(int time) const;
    KisKeyframeSP getOriginalKeyframeFor(int time) const override;

    /// Returns the earliest time the original frame appears in this repeat, or -1 if it never does.
    int firstInstanceOf(int originalTime) const;

    /**
     * Finds the frames on which the given original keyframe is displayed by the repeat.
     * If a non-empty range is given, the result will contain only matching frames.
     * If an empty range is given, the result may also contain other frames between repeated ones,
     * such as when the repeat continues infinitely.
     */
    KisFrameSet instancesWithin(KisKeyframeSP original, KisTimeSpan range) const;

    /** Returns the time at which the previous frame within the repeat appears,
     * or -1 if time is at the first repeated frame.
     * NB: time should be at the start of a repeated frame
     */
    int previousVisibleFrame(int time) const;

    /** Returns the time at which the next frame within the repeat appears,
     * or -1 if time is at the last repeated frame.
     * NB: time should be at the start of a repeated frame
     */
    int nextVisibleFrame(int time) const;

    /**
     * Finds the time of the next keyframe if any.
     * Returns -1 if the cycle continues indefinitely.
     */
    int lastFrame() const;

private:
    KisTimeSpan m_range;
};

#endif