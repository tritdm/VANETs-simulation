//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
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

#include "TraCI.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::TraCI);

/*void TraCI::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        // Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;
    }
    else if (stage == 1) {
        VMessage = new cMessage("VMessage");
        scheduleAt(simTime() + 1.0, VMessage);
        // Initializing members that require initialized other modules goes here
    }
}

void TraCI::finish()
{
    DemoBaseApplLayer::finish();
    cancelAndDelete(VMessage);
    // statistics recording goes here
}*/

void TraCI::onBSM(DemoSafetyMessage* bsm)
{
    veins::Coord myPosition = mobility->getPositionAt(simTime());
            EV << myPosition << endl;
        std::map<std::string, cModule*> allNodes = mobility->getManager()->getManagedHosts();
        EV << "num: " <<  allNodes.size() << endl;
            // Iterate through collection and find distance,
            std::map<std::string, cModule*>::iterator it;

            for(it = allNodes.begin(); it != allNodes.end(); it++)
            {
                TraCIMobility* auxMobility = TraCIMobilityAccess().get(it->second);
                veins::Coord receiverPosition = auxMobility->getPositionAt(simTime());

                //returns distance in meters
                double dist = myPosition.distance(receiverPosition);
                EV << "Distance: " << dist << endl;
            }
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
}

void TraCI::onWSM(BaseFrame1609_4* frame)
{
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void TraCI::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void TraCI::handleSelfMsg(cMessage* msg)
{
    DemoBaseApplLayer::handleSelfMsg(msg);
    // this method is for self messages (mostly timers)
    // it is important to call the DemoBaseApplLayer function for BSM and WSM transmission
}

void TraCI::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);
    //EV << "speed of: " << obj->getFullPath() << " is: " << mobility->getHostSpeed().length() << " " << mobility->getCurrentDirection() << endl;
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class
}
