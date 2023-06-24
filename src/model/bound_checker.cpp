#include "bound_checker.h"

BoundResult BoundChecker::intoTop(
        const Model &actor,
        double actorX,
        double actorY,
        const Model &receiver,
        double receiverX,
        double receiverY
) {
    BoundResult result;

    // o(n^2) implementation, maybe change in the future...
    for (auto & actorBox : actor.getBoundingBoxes()) {
        for (auto & receiverBox : receiver.getBoundingBoxes()) {
            // Check if bounding boxes overlap on the x-axis
            if (actorBox.left + actorX >= receiverBox.right + receiverX ||
                actorBox.right + actorX <= receiverBox.left + receiverX) {
                continue;
            }
            double actorBotAbs    = actorBox.bottom + actorY;
            double receiverTopAbs = receiverBox.top + receiverY;
            if (actorBotAbs < receiverTopAbs) {
                if (!result.boundFound) {
                    result.boundFound = true;
                    result.newActorPos = receiverTopAbs;
                    continue;
                }
                if (receiverTopAbs > result.newActorPos) {
                    result.newActorPos = receiverTopAbs;
                }
            }
        }
    }

    return result;
}

BoundResult BoundChecker::intoLeft(
        const Model &actor,
        double actorX,
        double actorY,
        const Model &receiver,
        double receiverX,
        double receiverY
) {
    BoundResult result;

    for (auto & actorBox : actor.getBoundingBoxes()) {
        for (auto & receiverBox : receiver.getBoundingBoxes()) {
            // Check if bounding boxes overlap on the y-axis
            if (actorBox.bottom + actorY >= receiverBox.top + receiverY ||
                actorBox.top + actorY <= receiverBox.bottom + receiverY) {
                continue;
            }
            double actorLeftAbs     = actorBox.left + actorX;
            double receiverRightAbs = receiverBox.right + receiverX;
            if (actorLeftAbs < receiverRightAbs) {
                if (!result.boundFound) {
                    result.boundFound = true;
                    result.newActorPos = receiverRightAbs;
                    continue;
                }
                if (receiverRightAbs > result.newActorPos) {
                    result.newActorPos = receiverRightAbs;
                }
            }
        }
    }

    return result;
}

BoundResult BoundChecker::intoRight(
        const Model &actor,
        double actorX,
        double actorY,
        const Model &receiver,
        double receiverX,
        double receiverY
) {
    BoundResult result;

    for (auto & actorBox : actor.getBoundingBoxes()) {
        for (auto & receiverBox : receiver.getBoundingBoxes()) {
            // Check if bounding boxes overlap on the y-axis
            if (actorBox.bottom + actorY >= receiverBox.top + receiverY ||
                actorBox.top + actorY <= receiverBox.bottom + receiverY) {
                continue;
            }
            double actorRightAbs   = actorBox.right + actorX;
            double receiverLeftAbs = receiverBox.left + receiverX;
            if (actorRightAbs > receiverLeftAbs) {
                if (!result.boundFound) {
                    result.boundFound = true;
                    result.newActorPos = receiverLeftAbs;
                    continue;
                }
                if (receiverLeftAbs < result.newActorPos) {
                    result.newActorPos = receiverLeftAbs;
                }
            }
        }
    }

    return result;
}

BoundResult BoundChecker::check(
        const Model &actor,
        double actorX,
        double actorY,
        const Model &receiver,
        double receiverX,
        double receiverY,
        BoundChecker::Direction dir
) {
    BoundResult result;

    for (auto &actorBox: actor.getBoundingBoxes()) {
        for (auto &receiverBox: receiver.getBoundingBoxes()) {
            if (!secondaryAxisOverlaping(actorBox, actorX, actorY, receiverBox, receiverX, receiverY, dir))
                continue;

            switch (dir) {
                case INTO_TOP: {
                    double actorBotAbs    = actorBox.bottom + actorY;
                    double receiverTopAbs = receiverBox.top + receiverY;
                    if (actorBotAbs < receiverTopAbs) {
                        if (!result.boundFound) {
                            result.boundFound = true;
                            result.newActorPos = receiverTopAbs;
                            continue;
                        }
                        if (receiverTopAbs > result.newActorPos) {
                            result.newActorPos = receiverTopAbs;
                        }
                    }
                    break;
                }

                case INTO_BOTTOM: {
                    double actorTopAbs       = actorBox.top + actorY;
                    double receiverBottomAbs = receiverBox.bottom + receiverY;
                    if (actorTopAbs > receiverBottomAbs) {
                        if (!result.boundFound) {
                            result.boundFound = true;
                            result.newActorPos = receiverBottomAbs;
                            continue;
                        }
                        if (actorTopAbs < result.newActorPos) {
                            result.newActorPos = receiverBottomAbs;
                        }
                    }
                    break;
                }

                case INTO_LEFT: {
                    double actorLeftAbs     = actorBox.left + actorX;
                    double receiverRightAbs = receiverBox.right + receiverX;
                    if (actorLeftAbs < receiverRightAbs) {
                        if (!result.boundFound) {
                            result.boundFound = true;
                            result.newActorPos = receiverRightAbs;
                            continue;
                        }
                        if (receiverRightAbs > result.newActorPos) {
                            result.newActorPos = receiverRightAbs;
                        }
                    }
                    break;
                }

                case INTO_RIGHT: {
                    double actorRightAbs   = actorBox.right + actorX;
                    double receiverLeftAbs = receiverBox.left + receiverX;
                    if (actorRightAbs > receiverLeftAbs) {
                        if (!result.boundFound) {
                            result.boundFound = true;
                            result.newActorPos = receiverLeftAbs;
                            continue;
                        }
                        if (receiverLeftAbs < result.newActorPos) {
                            result.newActorPos = receiverLeftAbs;
                        }
                    }
                    break;
                }
            }
        }
    }

    // Map bound values to absolute position of actor
    if (result.boundFound) {
        switch (dir) {
            case INTO_BOTTOM:
                result.newActorPos -= actor.getHeight();
                break;
            case INTO_RIGHT:
                result.newActorPos -= actor.getWidth();
                break;
            default:
                break;
        }
    }

    return result;
}

static bool BoundChecker::secondaryAxisOverlaping(
        const BoundingBox &actorBox,
        double actorX,
        double actorY,
        const BoundingBox &receiverBox,
        double receiverX,
        double receiverY,
        BoundChecker::Direction dir
) {
    switch (dir) {
        case BoundChecker::INTO_TOP:
        case BoundChecker::INTO_BOTTOM:
            return actorBox.left + actorX < receiverBox.right + receiverX &&
                   actorBox.right + actorX > receiverBox.left + receiverX;
        case BoundChecker::INTO_LEFT:
        case BoundChecker::INTO_RIGHT:
            return actorBox.bottom + actorY < receiverBox.top + receiverY &&
                   actorBox.top + actorY > receiverBox.bottom + receiverY;
    }

    return true;
}

/*static double BoundChecker::primaryAxisOverlaping(
        const BoundingBox &actorBox,
        double actorX,
        double actorY,
        const BoundingBox &receiverBox,
        double receiverX,
        double receiverY,
        BoundChecker::Direction dir
) {
    double actorBound, receiverBound;

    switch (dir) {
        case BoundChecker::INTO_TOP:
            actorBound = actorBox.bottom + actorY;
            receiverBound = receiverBox.top + receiverY;
            break;
        case BoundChecker::INTO_BOTTOM:
            actorBound = actorBox.top + actorY;
            receiverBound = receiverBox.bottom + receiverY;
            break;
        case BoundChecker::INTO_LEFT:
            actorBound = actorBox.left + actorX;
            receiverBound = receiverBox.right + receiverX;
            break;
        case BoundChecker::INTO_RIGHT:
            actorBound = actorBox.right + actorX;
            receiverBound = receiverBox.left + receiverX;
            break;
    }

    switch (dir) {
        case INTO_TOP:
        case INTO_LEFT:
            if (actorBound < receiverBound) {
                return receiverBound;
            }
            break;
        case INTO_BOTTOM:
        case INTO_RIGHT:
            if (actorBound > receiverBound) {
                return receiverBound;
            }
            break;
    }

    return actorBound;
}

// between left and right:
// aLA -> aRA
// rRA -> rLA
// flip all equalities*/