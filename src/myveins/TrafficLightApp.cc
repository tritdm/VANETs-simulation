//
// Copyright (C) 2018 Tobias Hardes <hardes@ccs-labs.org>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "TrafficLightApp.h"

#include "DemoSafetyMessage_m.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using veins::TrafficLightApp;

Define_Module(TrafficLightApp);

void TrafficLightApp::onBSM(DemoSafetyMessage* bsm)
{
    simtime_t currTime = simTime();
    avrSpeed += bsm->getSenderSpeedInDouble();
    vehNum ++;
    EV << currTime - lastTime << endl;
    EV << "Speed of " << "bsm->getSenderID()" << " is: " << bsm->getSenderSpeedInDouble() << endl;
    EV << "Position of " << bsm->getSenderPos().x << " " << bsm->getSenderPos().y << endl;
    EV << "Direction of " << bsm->getSenderSpeed().x << " " << bsm->getSenderSpeed().y << endl;
    if (currTime - lastTime >= 0.99)
    {
        avrSpeed /= vehNum;
        EV << "Average speed in last 1s: " << avrSpeed << endl;
        avrSpeed = 0;
        vehNum = 0;
        lastTime = currTime;
    }
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
}

void TrafficLightApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // if this RSU receives a WSA for service 42, it will tune to the chan
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}

void TrafficLightApp::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);
    // this rsu repeats the received traffic update in 2 seconds plus some random delay
    sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));
}

void TrafficLightApp::handleSelfMsg(cMessage* msg)
{
    DemoBaseApplLayer::handleSelfMsg(msg);
}

void TrafficLightApp::handleLowerMsg(cMessage *msg)
{

    DemoBaseApplLayer::handleLowerMsg(msg);
}
