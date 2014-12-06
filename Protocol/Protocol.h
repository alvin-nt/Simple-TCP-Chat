#ifndef _Protocol_H
#define _Protocol_H

/**
 * Communication Protocol
 *
 * Defines the communication protocol used by both the chat server and the chat client
 *
 * ofc, this is a much dumb(er) version of protocol, when compared to stuff like XMPP or IRC
 * 
 * By default, every message is sent through a 512-byte package, with the following structure:
 *
 * [messageNum][time][data]
 *
 * messageNum (int - 4 byte): number that indicates the type of message being sent.
 * time (time_t - 4 byte): time when the message is sent. 
 * NOTE: This program should be built ONLY on 32-bit machines, and does not handle the Year 2038 bug
 * 
 * data (any - 504 byte): the data
 */

namespace Protocol {
/**
 * maximum username length
 */
    static const int USERNAME_MAXLENGTH = 64;
    
/**
 * maximum server name length
 */
    static const int SERVERNAME_MAXLENGTH = 504;

/**
 * messageNum used when the user is signing up
 *
 * the data stucture is described below:
 * [userName][password]
 *
 * userName (char - 64 byte): the user name, maximum 64 chars, not including NULL
 * password (char - 64 byte): the password hash, using SHA512
 */
    static const int userSignup = 11;

/**
 * messageNum used when the user's signup is successful
 *
 * the data structure is descibed below:
 * [userId]
 *
 * userId (int - 4 byte): the generated userId
 */
    static const int userSignupSuccess = 12;

/**
 * messageNum used when the user's signup failed
 *
 * the data structure is described below:
 * [message]
 *
 * message (char - 504 byte): the message why it is failed.
 */
    static const int userSignupFail = 13;

/**
 * messageNum used when the user's login failed
 *
 * the data structure is described below:
 * [userName][password]
 *
 * userName (char - 64 byte): the user name, maximum 64 chars, not including NULL
 * password (char - 64 byte): the password hash, using SHA512
 */
 	static const int userLogin = 14;

/**
 * messageNum used when the user's login is successful
 *
 * the data structure is described below:
 * [userId]
 *
 * userId (int - 4 byte): the userId of my
 */
 	static const int userLoginSuccess = 15;

/**
 * messageNum used when the user's login failed
 *
 * the data structure is described below:
 * [message]
 *
 * message (char - 504 byte): the message why it is failed.
 */
 	static const int userLoginFail = 16;

/**
 * messageNum used when the user wants to logout
 *
 * the data structure is described below:
 * [userId]
 *
 * userId (int - 4 byte): the userId requesting the logout
 *
 * after this package is sent, both the client and the server should close their own sockets.
 */
 	static const int userLogout = 99;

/**
 * messageNum used when sending message
 * 
 * The data structure is as follows:
 * [senderId][receiverId][offset][message]
 *
 * senderId (int - 4 byte): the userId of the sender
 * receiverId (int - 4 byte): the userId of the receiver
 * offset (char - 1 byte): '1' (0x31) indicates that there is a next packet that contains the next part of the message, 
 * 						   '0' (0x30) indicates otherwise
 * message (any - 494 byte): the message
 *
 * Since C operates on null-terminated string,
 * If the last package (offset = 0) received by the receiver does not contain a null (\0),
 * the client/server should add it automatically.
 *
 * PRO TIP:
 *  - The package should be accepted first by the server, and then the time is 'injected' by the server.
 *  - The server should generate the appropriate messageId (16 byte) to mark the message, which is described below:
 *  [senderId][messageTime][receiverId][receiverType][empty]
 *
 * 	senderId (int - 4 byte): the userId of the sender
 * 	messageTime (time_t - 4 byte): the time when the message is sent
 * 	receiverId (int - 4 byte): the userId of the receiver
 * 	receiverType (char - 1 byte): the type of the receiver. 'G' for group, 'U' for user.
 * 	empty (char - 3 byte): contains NULL ('\0'), not currently used
 */
	static const int messageSend = 31;

/**
 * messageNum used when a message is read by the client
 *
 * The data structure is as follows:
 * [messageId]
 *
 * messageId (messageId - 16 byte): the messageId
 */
	static const int messageRead = 33;

/**
 * messageNum used when sending received message to the client
 * 
 * The data structure is described below:
 * [messageId][offset][message][empty]
 *
 * messageId (messageId - 16 byte): the messageId
 * offset (char - 1 byte): '1' (0x31) indicates that there is a next packet that contains the next part of the message, 
 * 						   '0' (0x30) indicates otherwise
 * empty (char - 1 byte): filled with NULL '\0'						   
 * message (any - 486 byte): the message, may not be null-terminated
 */
	static const int messageRecv = 35;

/**
 * messageNum used when creating groups
 * The data structure is as follows:
 * [creatorId][name][description]
 *
 * creatorId (int - 4 byte): the userId of the creator. Becomes the group master
 * name (char - 65 byte): the name of the group, max is 64 characters (not including \0)
 * description (char - 445 byte): the description of the group, max is 444 characters (not including \0)
 */
	static const int groupCreate = 51;

/**
 * messageNum used when the group creation is successful
 *
 * The data structure is as follows:
 * [groupId][masterId]
 *
 * groupId (int - 4 byte): the generated groupId
 * masterId (int - 4 byte): the userId of the room master
 */
	static const int groupCreateSuccess = 52;

/**
 * messageNum used when the group cration failed
 *
 * the data structure is as follows:
 * [message]
 *
 * message (char - 504 byte): the message explaining why the group creation failed
 */
	static const int groupCreateFail = 53;

/**
 * messageNum used when requesting to join a group
 *
 * the data structure is as follows:
 * [userId][groupName]
 *
 * userId (int - 4 byte): the joining userId
 * groupName (char - 64 byte): the name of the group
 */
	static const int groupJoin = 54;

/**
 * messageNum used when successfully joined to a group
 *
 * the data structure is as follows:
 * [groupId]
 *
 * groupId (int - 4 byte): the joined groupId
 */
	static const int groupJoinSuccess = 55;

/**
 * messageNum used when failed to join a group
 *
 * the data structure is as follows:
 * [message]
 *
 * message (char - 500 byte): reason of failed join
 */
	static const int groupJoinFail = 56;

/**
 * messageNum used when a user requesting to leave a group
 *
 * the data structure is as follows:
 * [groupId][userId][leaveType][message]
 *
 * groupId (int - 4 byte): the groupId
 * userId (int - 4 byte): the leaving userId
 * leaveType (char - 1 byte): 'K' for kick, 'L' for self-leaving
 * message (char - 495 byte): reason of leaving, null-terminated. may be NULL if empty
 */
	static const int groupLeave = 57;

/**
 * messageNum used when the leave request is successfully responded
 *
 * no data
 */
	static const int groupLeaveSuccess = 58;

/**
 * messageNum used when the leave request is failed (due to... what?)
 *
 * data structure:
 * [message]
 *
 * message (char - 504 bytes): the message explaining why it failed.
 */
	static const int groupLeaveFail = 59;

/**
 * messageNum used when sending notifications to members of the group,
 * e.g. the name of members in the group
 *
 * The data structure is as follows:
 * [groupId][recvId][offset][message]
 *
 * groupId (int - 4 byte): target groupId
 * recvId (int - 4 byte): userId of the receiver
 * offset (char - 1 byte): '1' indicates that the message is continued, 
 * message (any - 494 byte): the message
 */
	static const int groupNotif = 63;

/**
 * messageNum used when requesting the list of group registered in the server
 *
 * no data structure; we can assume that the data is empty.
 */
	static const int groupQueryList = 65;

/**
 * messageNum used when sending information about a group
 *
 * the data structure is described below:
 * [groupId][memberCount][creationTime][groupName][groupMasterName]
 *
 * groupId (int - 4 byte): target groupId
 * memberCount (int - 4 byte): number of members in the group.
 * creationTime (time_t - 4 byte): time of group creation
 * groupName (char - 64 byte): name of group, not null-terminated
 * groupMasterName (char - 64 byte): name of the group master
 */
	static const int groupInfo = 67;

/**
 * messageNum used when changing the room master.
 *
 * Only the server/the current room master that can do this.
 *
 * The data structure is as follows:
 * [groupId][nextMasterId]
 *
 * groupId (int - 4 byte): the group that is going to be changed
 * nextMasterId (int - 4 byte): the user that is going to be the next room master
 */
	static const int groupChangeMaster = 70;

/**
 * messageNum used when the room master is changed successfully.
 *
 * The data structure is as follows
 * [groupId][newMasterId]
 *
 * groupId (int - 4 byte): the groupId
 * newMasterId (int - 4 byte): the new room master
 */
	static const int groupChangeMasterSuccess = 71;

/**
 * messageNum used when the room master failed to be changed
 *
 * The data structure is as follows
 * [groupId][message]
 *
 * groupId (int - 4 byte): the groupId
 * message (char - 500 byte): the message, NULL terminated, explaining the reason
 */
	static const int groupChangeMasterFail = 72;

/**
 * messageNum used to request the name of the server
 *
 * no data structure.
 */
	static const int serverNameRequest = 101;

/**
 * messageNum used to reply the serverNameRequest with the serverName
 *
 * the data structure is as follows:
 * [message]
 *
 * message (char - 504 byte): the server name
 */
	static const int serverNameResponse = 103;
};

#endif