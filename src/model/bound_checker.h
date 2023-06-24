#pragma once

#include "model.h"
#include "bound_result.h"

namespace BoundChecker {

    enum Direction {INTO_TOP, INTO_BOTTOM, INTO_LEFT, INTO_RIGHT};

    BoundResult intoTop(
            const Model &actor,
            double actorX,
            double actorY,
            const Model &receiver,
            double receiverX,
            double receiverY
    );

    double intoBottom(
            const Model &actor,
            double actorX,
            double actorY,
            const Model &receiver,
            double receiverX,
            double receiverY
    );

    BoundResult intoLeft(
            const Model &actor,
            double actorX,
            double actorY,
            const Model &receiver,
            double receiverX,
            double receiverY
    );

    BoundResult intoRight(
            const Model &actor,
            double actorX,
            double actorY,
            const Model &receiver,
            double receiverX,
            double receiverY
    );

    BoundResult check(
            const Model &actor,
            double actorX,
            double actorY,
            const Model &receiver,
            double receiverX,
            double receiverY,
            BoundChecker::Direction dir
    );

    static bool secondaryAxisOverlaping(
            const BoundingBox &actorBox,
            double actorX,
            double actorY,
            const BoundingBox &receiverBox,
            double receiverX,
            double receiverY,
            Direction dir
    );

    static double primaryAxisOverlaping(
            const BoundingBox &actorBox,
            double actorX,
            double actorY,
            const BoundingBox &receiverBox,
            double receiverX,
            double receiverY,
            BoundChecker::Direction dir
    );
}