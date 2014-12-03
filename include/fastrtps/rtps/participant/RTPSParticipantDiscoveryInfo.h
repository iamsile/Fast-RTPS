/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * fastrtps_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file RTPSParticipantDiscoveryInfo.h
 *
 */

#ifndef RTPSPARTICIPANTDISCOVERYINFO_H_
#define RTPSPARTICIPANTDISCOVERYINFO_H_

#include <vector>
#include "fastrtps/rtps/common/Types.h"

namespace eprosima{
namespace fastrtps{
namespace rtps{

//!Discovery status
enum RTPS_DllAPI DISCOVERY_STATUS
{
	DISCOVERED_RTPSPARTICIPANT,
	CHANGED_QOS_RTPSPARTICIPANT,
	REMOVED_RTPSPARTICIPANT
};

typedef std::vector<std::pair<std::string,std::string>> PropertyList;
typedef std::vector<octet> UserData;

/**
* Discovery information of the RTPS Participant.
*/
class RTPSParticipantDiscoveryInfo{
public:
	RTPSParticipantDiscoveryInfo():m_status(DISCOVERED_RTPSPARTICIPANT){};
	virtual ~RTPSParticipantDiscoveryInfo(){};
	//!Status
	DISCOVERY_STATUS m_status;
	//!Associated GUID
	GUID_t m_guid;
	//!Property list
	PropertyList m_propertyList;
	//!User data
	UserData m_userData;
	//!Participant name
	std::string m_RTPSParticipantName;
};
}
}
}



#endif /* RTPSPARTICIPANTDISCOVERYINFO_H_ */
