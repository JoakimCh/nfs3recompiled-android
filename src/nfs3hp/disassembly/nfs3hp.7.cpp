#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* sub_42c7f0: native, nfs3hp::raceload::setTimeStep */

/* sub_42c830: native, nfs3hp::raceload::addCarTasks */

/* sub_42c950: native, nfs3hp::raceload::openCarViv */

/* sub_42ca80: native, nfs3hp::raceload::closeCarViv */

/* sub_42cab0: native, nfs3hp::raceload::removeCarTasks */

/* sub_42cc20: native, nfs3hp::raceload::countLaps */

/* sub_42cd00: native, nfs3hp::raceload::carAxesSpeed */

/* sub_42cdd0: native, nfs3hp::raceload::carForwardSpeed */

/* sub_42ce10: native, nfs3hp::raceload::carRaceDistance */

/* sub_42ce70: native, nfs3hp::raceload::updateRaceCars */

/* sub_42cff0: native, nfs3hp::raceload::frameFraction */

/* sub_42d020: native, nfs3hp::raceload::placeHeadlights */

/* sub_42d160: native, nfs3hp::raceload::placeCarShadow */

/* sub_42d3e0: native, nfs3hp::raceload::sortRaceCars */

/* sub_42d4f0: native, nfs3hp::dead::stub_0x42d4f0 */

/* sub_42d500: native, nfs3hp::raceload::emptyHook */

/* sub_42d510: native, nfs3hp::ea::gameTrace */

/* sub_42d520: native, nfs3hp::raceload::emptyHook2 */

/* sub_42d530: native, nfs3hp::dead::stub_0x42d530 */

/* sub_42d540: native, nfs3hp::dead::stub_0x42d540 */

/* sub_42d620: native, nfs3hp::raceload::showMessage */

/* sub_42d710: native, nfs3hp::raceload::sendMessage */

/* sub_42d790: native, nfs3hp::raceload::openMessages */

/* sub_42d7f0: native, nfs3hp::raceload::closeMessages */

/* sub_42d800: native, nfs3hp::raceload::clearMessages */

/* sub_42d810: native, nfs3hp::raceload::sendTypedMessage */

/* sub_42d860: native, nfs3hp::raceload::newMessageLine */

/* sub_42d8a0: native, nfs3hp::raceload::freeMessageLine */

/* sub_42d8b0: native, nfs3hp::raceload::insertMessageLine */

/* sub_42d910: native, nfs3hp::raceload::freeMessageLines */

/* sub_42d940: native, nfs3hp::raceload::clearMessageLines */

/* sub_42d9b0: native, nfs3hp::raceload::showMessageLines */

/* sub_42da30: native, nfs3hp::raceload::appendMessageLine */

/* sub_42daa0: native, nfs3hp::dead::stub_0x42daa0 */

/* sub_42daf0: native, nfs3hp::raceload::closeMessageLines */

/* sub_42db70: native, nfs3hp::raceload::openMessageLines */

/* sub_42dc20: native, nfs3hp::raceload::raceControlsThread */

/* sub_42dc3e: native, nfs3hp::dead::stub_0x42dc3e */

/* sub_42dc40: native, nfs3hp::raceload::wakeRaceControls */

/* sub_42dc60: native, nfs3hp::raceload::raceControlsTick */

/* sub_42dcb0: native, nfs3hp::raceload::startRaceControlsTick */

/* sub_42dd00: native, nfs3hp::raceload::stopRaceControlsTick */

/* sub_42dd60: native, nfs3hp::raceload::cornerInBox */

/* sub_42e010: native, nfs3hp::raceload::cornerInBoxBack */

/* sub_42e2c0: native, nfs3hp::raceload::cornerInBox2 */

/* sub_42e4f0: native, nfs3hp::raceload::cornerInBoxBack2 */

/* sub_42e720: native, nfs3hp::raceload::clampSpin */

/* sub_42e820: native, nfs3hp::raceload::applyImpulse */

/* sub_42e9c0: native, nfs3hp::raceload::bounceOffWall */

/* sub_42ee10: native, nfs3hp::raceload::hitWall */

/* sub_42efe0: native, nfs3hp::raceload::boxHitsWall */

/* sub_42f280: native, nfs3hp::raceload::carsCollide */

/* sub_42f550: native, nfs3hp::collide::findContact */

/* sub_42f8c0: native, nfs3hp::collide::contactNormal */

/* sub_42fe10: native, nfs3hp::collide::pushCarsApart */

/* sub_42fee0: native, nfs3hp::collide::separateCars */

/* sub_430210: native, nfs3hp::collide::polygonEdgeNormal */

/* sub_430350: native, nfs3hp::collide::clearOfWall */

/* sub_4304b0: native, nfs3hp::collide::carAgainstWalls */

/* sub_430c80: native, nfs3hp::collide::collideCars */

/* sub_430cd0: native, nfs3hp::collide::clearCarList */

/* sub_430ce0: native, nfs3hp::collide::objectInReach */

/* sub_430da0: native, nfs3hp::collide::carAgainstObjects */

/* sub_4310c0: native, nfs3hp::collide::addCarToList */

/* sub_4311d0: native, nfs3hp::collide::carCollisions */

/* sub_431250: native, nfs3hp::collide::distanceSquared */

/* sub_431280: native, nfs3hp::collide::nearestPoint */

/* sub_431320: native, nfs3hp::collide::openCollFile */

/* sub_4313b0: native, nfs3hp::collide::closeCollFile */

/* sub_4313d0: native, nfs3hp::collide::collFileSize */

/* sub_4313e0: native, nfs3hp::collide::readCollFile */

/* sub_431410: native, nfs3hp::collide::collFileCount */

/* sub_431420: native, nfs3hp::collide::collChunk */

/* sub_431430: native, nfs3hp::collide::playerControls */

/* sub_431580: native, nfs3hp::controls::clearJoysticks */

/* sub_4315a0: native, nfs3hp::controls::readJoysticks */

/* sub_431690: native, nfs3hp::controls::pollJoystick */

/* sub_4316c0: native, nfs3hp::controls::buttonHeld */

/* sub_4316f0: native, nfs3hp::controls::hatPointing */

/* sub_431740: native, nfs3hp::controls::axisAmount */

/* sub_4317d0: native, nfs3hp::controls::keyHeld */

/* sub_431800: native, nfs3hp::controls::controlHeld */

/* sub_431880: native, nfs3hp::controls::controlHeldNo */

/* sub_431885: native, nfs3hp::controls::controlHeldYes */

/* sub_43188d: native, nfs3hp::controls::controlHeldByKind */

/* sub_4318b0: native, nfs3hp::controls::noControl */

/* sub_4318c0: native, nfs3hp::collide::forgetRenderStates */

/* sub_431900: native, nfs3hp::graphics::setRenderState */

/* sub_431aa0: native, nfs3hp::collide::statesForText */

/* sub_431af0: native, nfs3hp::collide::statesForPictures */

/* sub_431b40: native, nfs3hp::collide::statesForHud */

/* sub_431bc0: native, nfs3hp::collide::statesForScreens */

/* sub_431c20: native, nfs3hp::collide::passLayerNothing */

/* sub_431c30: native, nfs3hp::collide::passSecondLayer */

/* sub_431c40: native, nfs3hp::collide::passFirstLayer */

/* sub_431c50: native, nfs3hp::collide::makeBlendTables */

/* sub_431d50: native, nfs3hp::collide::blendSpan */

/* sub_431e80: native, nfs3hp::dead::stub_0x431e80 */

/* sub_431fa0: native, nfs3hp::dead::stub_0x431fa0 */

/* sub_432070: native, nfs3hp::dead::stub_0x432070 */

}
