#pragma once

#define MAX_CLIENTS 250
#define MAX_SERVERS 10

#define SERVER_ID 255

#define ID_DEBUGTEXT 100 // 64
#define ID_NEWPLAYER 101 // 65
//#define ID_NEWPLAYERCOLOURS 102 // 66
#define ID_CHAT 103 // 67
#define ID_POSITION 104 // 68
#define ID_NEWPLAYERUPDATE 105 // 69
#define ID_PLAYERDISCONNECTED 106 // 6A
#define ID_MOVEPOSITION 107 // 6B
#define ID_LOOKQUATERNION 108 // 6C
#define ID_FACEDIRECTION 109 // 6D
#define ID_ACTIONFLAGS 110 // 6E
#define ID_EMOTE 111 // 6F
#define ID_WORLDINFO 112 // 70
#define ID_REQUESTMAPINFO 113 // 71
#define ID_ATTACK 114 // 72
#define ID_PLAYERMAPCHANGE 115 // 73
#define ID_VALIDATENAME 116 // 74
#define ID_PLAYERDATA 117 // 75
#define ID_BIO 118 // 76
#define ID_KICK 119 // 77
#define ID_ITEMDROP 120 // 78
#define ID_ITEMPICKUP 121 // 79
#define ID_ITEMEQUIP 122 // 7A
#define ID_ITEMUNEQUIP 123 // 7B
#define ID_IMREADY 124 // 7C
#define ID_EVENT 125 // 7D
#define ID_INFO 126 // 7E
#define ID_ACKNOWLEDGE 127 // 7F
#define ID_DENIED 128 // 80
#define ID_CRITTEROWNAGE 129 // 81
#define ID_CRITTERINFO 130 // 82
#define ID_CRITTERTARGETEDINFO 131 // 83
#define ID_UNITOWNAGE 132 // 84
#define ID_UNITINFO 133 // 85
#define ID_UNITTARGETEDINFO 134 // 86
#define ID_OBJECTOWNAGE 135 // 87
#define ID_OBJECTINFO 136 // 88
#define ID_OBJECTTARGETEDINFO 137 // 89
#define ID_UPDATESKILLS 138 // 8A
#define ID_UPDATEPET 139 // 8B
#define ID_UPDATEHP 140 // 8C
#define ID_PLAYERINFO 141 // 8D
#define ID_PLAYERTARGETEDINFO 142 // 8E
#define ID_ITEMSTASH 143 // 8F
#define ID_FINDPLAYER 144 // 90
#define ID_CRITTERINFOONEWAY 145 // 91

#define ID_LOGON 200 // C8
#define ID_CREATEACCOUNT 201 // C9
#define ID_LOADCHAR 202 // CA
#define ID_CREATECHAR 203 // CB
#define ID_DELETECHAR 204 // CC
#define ID_EDITCHAR 205 // CD
#define ID_EDITACCOUNT 206 // CE
#define ID_SAVEITEM 207 // CF
#define ID_GODSPEAK 208 // D0
#define ID_FORCELOGOUT 209 // D1
#define ID_MAINTENANCE 210 // D2
#define ID_VIOLATION 211 // D3

#define ID_SERVERUPDATE 247 // F7
#define ID_REQUESTPLAYERDATA 248 // F8
#define ID_TOKENCONNECTED 249 // F9
#define ID_TOKENDISCONNECTED 250 // FA
#define ID_SERVERLIST 251 // FB
#define ID_SERVERCONNECTED 252 // FC
#define ID_IMASERVER 253 // FD

#define TOKEN_NULL 254 // FE

typedef unsigned char OwnerToken;


enum ACKNOWLEDGE
{
    ACK_ITEMDROPPED,
    ACK_ITEMPICKED,
    ACK_OBJECTOWNED,
    ACK_UNITOWNED,
    ACK_CRITTERCREATED
};


enum NETWORKINFO
{
    INFO_MODON,
    INFO_MODOFF,
    INFO_YOURBLOCKED,
    INFO_YOURUNBLOCKED,
    INFO_PARTYREQUEST,
    INFO_PARTYINVITE,
    INFO_PARTYACCEPTED,
    INFO_PARTYJOINED,
    INFO_PARTYKICK,
    INFO_PARTYLEAVE,
    INFO_PARTYALREADY,
    INFO_PARTYINVITEACCEPTED
};


enum NETWORKEVENT
{
    EVENT_EARTHQUAKE,
    EVENT_MASSBLOCK
};
