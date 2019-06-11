#pragma once

#include "client_ver.h"
#include "singleton.h"

#include <memory>
#include <map>

namespace norm_dll {
typedef struct job_names {
	std::string name;
	std::string name_type;
} job_names;

class norm;
class ProxySession final : public Singleton<ProxySession> {
private:
    std::shared_ptr<norm_dll::norm> c_state;

    struct CSession {
        /* Class layout. Can be found in the <ClientDate>.h files.*/
        SESSION_DATA
    };

    CSession* c_session = reinterpret_cast<CSession*>(SESSION_PTR);
	// TODO: rename lpVariables.
    lpGetTalkType GetTalkType = reinterpret_cast<lpGetTalkType>(GETTALKTYPE_FN);
    lpRecalcAveragePingTime RecalcAveragePingTime = reinterpret_cast<lpRecalcAveragePingTime>(RECALCAVERAGEPINGTIME_FN);
    bool hooked = false;

    ProxySession() {}
    static PGETTALKTYPE_FN;
    static void __fastcall proxyRecalcAveragePingTime(void* this_obj, DWORD EDX, unsigned long a1);
	std::map<int, job_names> job_map = {{0, {"Novice", "novice"}},
                                      	  {1, {"Swordman", "swordsman"}},
                                      	  {2, {"Magican", "mage"}},
                                      	  {3, {"Archer", "archer"}},
                                      	  {4, {"Acolyte", "acolyte"}},
                                      	  {5, {"Merchant", "merchant"}},
                                      	  {6, {"Thief", "thief"}},
                                      	  {7, {"Knight", "knight"}},
                                      	  {8, {"Priest", "priest"}},
                                      	  {9, {"Wizard", "wizard"}},
                                      	  {10, {"Blacksmith", "blacksmith"}}};
										  // TODO add all jobs to list

public:
    ProxySession(token) {}
    ~ProxySession() {}

    void hook(std::shared_ptr<norm_dll::norm> c_state);
    ULONG get_average_ping_time();
    ULONG get_aid();
    ULONG get_gid();
    int get_exp();
    int get_level();
    int get_next_exp();
    int get_joblevel();
    int get_jobnextexp();
    int get_jobexp();
	int get_skillpoints();
	const std::string& get_name();
	const std::string& get_job_type();

	template<typename T>
	const T& get_job() {}

	template<>
	const int& get_job<int>()
	{
	    	return this->c_session->job;
	}

	template<>
	const std::string& get_job<std::string>()
	{
		return this->job_map[this->get_job<int>()].name;
	}
};
} // norm_dll

/* Enum definitions from the client */
typedef enum TALKTYPE {
    TT_NORMAL = 0x0,
    TT_BROADCAST = 0x1,
    TT_STAT = 0x2,
    TT_UNKNOWN = 0x3,
    TT_DISCONNECT_CHARACTER = 0x4,
    TT_DISCONNECT_ALL_CHARACTER = 0x5,
    TT_REQ_NUM_USER = 0x6,
    TT_MUSIC_ON_OFF = 0x7,
    TT_EFFECT_ON_OFF = 0x8,
    TT_MAP_POS = 0x9,
    TT_FRAMESKIP_ON_OFF = 0xa,
    TT_EFFECT_SOUND_ON_OFF = 0xb,
    TT_VOLUME = 0xc,
    TT_BVOLUME = 0xd,
    TT_HELP = 0xe,
    TT_REQ_WHISPER_LIST = 0xf,
    TT_REQ_WHISPER_STATE_EX = 0x10,
    TT_REQ_WHISPER_STATE_IN = 0x11,
    TT_REQ_WHISPER_PC_EX = 0x12,
    TT_REQ_WHISPER_PC_IN = 0x13,
    TT_IS_REDCELL = 0x14,
    TT_REQ_STAND = 0x15,
    TT_REQ_SIT = 0x16,
    TT_MAKE_CHATROOMMAKEWND = 0x17,
    TT_REQ_EXIT_ROOM = 0x18,
    TT_REQ_EXCHANGE_ITEM = 0x19,
    TT_REQ_MAKE_GROUP = 0x1a,
    TT_REQ_LEAVE_GROUP = 0x1b,
    TT_REQ_EXPEL_GROUP_MEMBER = 0x1c,
    TT_REQ_EMOTION_SURPRISE = 0x1d,
    TT_REQ_EMOTION_QUESTION = 0x1e,
    TT_REQ_EMOTION_DELIGHT = 0x1f,
    TT_REQ_EMOTION_THROB = 0x20,
    TT_REQ_EMOTION_SWEAT = 0x21,
    TT_REQ_EMOTION_AHA = 0x22,
    TT_REQ_EMOTION_FRET = 0x23,
    TT_REQ_EMOTION_ANGER = 0x24,
    TT_REQ_EMOTION_MONEY = 0x25,
    TT_REQ_EMOTION_THINK = 0x26,
    TT_REQ_EMOTION_SCISSOR = 0x27,
    TT_REQ_EMOTION_ROCK = 0x28,
    TT_REQ_EMOTION_WRAP = 0x29,
    TT_OPEN_TIP = 0x2a,
    TT_REMEMBER_WARPPOINT = 0x2b,
    TT_REQ_PK = 0x2c,
    TT_SKILL_SNAP_ON_OFF = 0x2d,
    TT_ATTACK_SNAP_ON_OFF = 0x2e,
    TT_ITEM_SNAP_ON_OFF = 0x2f,
    TT_REQ_ITEM_CREATE = 0x30,
    TT_REQ_MOVETO_MAP = 0x31,
    TT_NORMAL_FROM_CHATROOM = 0x32,
    TT_REQ_SAVE_CHAT = 0x33,
    TT_REQ_SAVE_CHAT_FROM_CHATROOM = 0x34,
    TT_MISS_EFFECT_ON_OFF = 0x35,
    TT_FIXED_CAMERA_ON_OFF = 0x36,
    TT_REQ_MAKE_GUILD = 0x37,
    TT_REQ_BREAK_GUILD = 0x38,
    TT_GUILD_CHAT = 0x39,
    TT_TEST_SHOW_IMAGE = 0x3a,
    TT_TESTPACKET = 0x3b,
    TT_FOG = 0x3c,
    TT_REQ_RESETSTATE = 0x3d,
    TT_REQ_RESETSKILL = 0x3e,
    TT_CHANGE_MAPTYPE = 0x3f,
    TT_TOGGLE_EMBLEM = 0x40,
    TT_TOGGLE_OBJLIGHT = 0x41,
    TT_REQ_EMOTION_THANKS = 0x42,
    TT_REQ_EMOTION_KEK = 0x43,
    TT_REQ_EMOTION_SORRY = 0x44,
    TT_REQ_EMOTION_SMILE = 0x45,
    TT_REQ_EMOTION_PROFUSELY_SWEAT = 0x46,
    TT_REQ_EMOTION_SCRATCH = 0x47,
    TT_REQ_EMOTION_BEST = 0x48,
    TT_REQ_EMOTION_STARE_ABOUT = 0x49,
    TT_REQ_EMOTION_HUK = 0x4a,
    TT_REQ_EMOTION_O = 0x4b,
    TT_REQ_EMOTION_X = 0x4c,
    TT_REQ_EMOTION_HELP = 0x4d,
    TT_REQ_EMOTION_GO = 0x4e,
    TT_REQ_EMOTION_BIGTHROB = 0x4f,
    TT_REQ_EMOTION_CRY = 0x50,
    TT_REQ_EMOTION_KIK = 0x51,
    TT_REQ_EMOTION_CHUP = 0x52,
    TT_REQ_EMOTION_CHUPCHUP = 0x53,
    TT_REQ_EMOTION_HNG = 0x54,
    TT_REQ_EMOTION_OK = 0x55,
    TT_SHOW_EMOTIONLIST = 0x56,
    TT_LOCALBROADCAST = 0x57,
    TT_HIDE = 0x58,
    TT_NAME_BALLOON = 0x59,
    TT_NAMELESS_BROADCAST = 0x5a,
    TT_NAMELESS_LOCALBROADCAST = 0x5b,
    TT_FONT = 0x5c,
    TT_SAVEMONEY = 0x5d,
    TT_LOADMONEY = 0x5e,
    TT_REMOVE = 0x5f,
    TT_SHIFT = 0x60,
    TT_RECALL_AID = 0x61,
    TT_RECALL_GID = 0x62,
    TT_FORCING_MOVE_AID = 0x63,
    TT_FORCING_MOVE_GID = 0x64,
    TT_BILLING_INFO = 0x65,
    TT_NAMELESS_BLUEBROADCAST = 0x66,
    TT_NAMELESS_BLUELOCALBROADCAST = 0x67,
    TT_REQ_AUTO_SAVE_CHAT = 0x68,
    TT_NOSHIFT_ON_OFF = 0x69,
    TT_AURA_ON_OFF = 0x6a,
    TT_SHOW_NAME_TYPE = 0x6b,
    TT_NOCTRL_ON_OFF = 0x6c,
    TT_DORIDORI_ON_OFF = 0x6d,
    TT_BINGBING_ON_OFF = 0x6e,
    TT_BANGBANG_ON_OFF = 0x6f,
    TT_SKILLFAIL_ON_OFF = 0x70,
    TT_NOTALKMSG_ON_OFF = 0x71,
    TT_SET1_ON_OFF = 0x72,
    TT_REQ_REPORT_CHAT = 0x73,
    TT_REQ_REPORT_CHAT_FROM_CHATROOM = 0x74,
    TT_CLIPMOUSE = 0x75,
    TT_LIGHTMAP = 0x76,
    TT_QUICKSPELL_ON_OFF = 0x77,
    TT_QUICKSPELL2_ON_OFF = 0x78,
    TT_QUICKSPELL3_ON_OFF = 0x79,
    TT_REQ_EMOTION_STARE = 0x7a,
    TT_REQ_EMOTION_HUNGRY = 0x7b,
    TT_REQ_EMOTION_COOL = 0x7c,
    TT_REQ_EMOTION_MERONG = 0x7d,
    TT_REQ_EMOTION_SHY = 0x7e,
    TT_REQ_EMOTION_GOODBOY = 0x7f,
    TT_REQ_EMOTION_SPTIME = 0x80,
    TT_REQ_EMOTION_SEXY = 0x81,
    TT_REQ_EMOTION_COMEON = 0x82,
    TT_REQ_EMOTION_SLEEPY = 0x83,
    TT_REQ_EMOTION_CONGRATULATION = 0x84,
    TT_REQ_EMOTION_HPTIME = 0x85,
    TT_BATTLE_ON_OFF = 0x86,
    TT_NOTRADE_ON_OFF = 0x87,
    TT_SIYEON_STATUS = 0x88,
    TT_SET2_ON_OFF = 0x89,
    TT_SYSTEM_CHECK_ON_OFF = 0x8a,
    TT_FRAME_ON_OFF = 0x8b,
    TT_WINDOW_ON_OFF = 0x8c,
    TT_SHOW_PVP_INFO = 0x8d,
    TT_CHECK_ID = 0x8e,
    TT_RC_ID = 0x8f,
    TT_RANDOM_LOADING_SCREEN_ON_OFF = 0x90,
    TT_REQ_BLACKSMITH = 0x91,
    TT_REQ_ALCHEMIST = 0x92,
    TT_NOTALKMSG2_ON_OFF = 0x93,
    TT_LEVEL = 0x94,
    TT_SP = 0x95,
    TT_HI = 0x96,
    TT_REQ_TAEKWON = 0x97,
    TT_AUTO_MSG_ON_OFF = 0x98,
    TT_REQ_EMOTION_SPARK = 0x99,
    TT_REQ_EMOTION_CONFUSE = 0x9a,
    TT_REQ_EMOTION_OHNO = 0x9b,
    TT_REQ_EMOTION_HUM = 0x9c,
    TT_REQ_EMOTION_BLABLA = 0x9d,
    TT_REQ_EMOTION_OTL = 0x9e,
    TT_REQ_EMOTION_DICE = 0x9f,
    TT_REQ_KILLER_RANK = 0xa0,
    TT_TRACEAI_ON_OFF = 0xa1,
    TT_HOMUN_WAIT = 0xa2,
    TT_HOMUN_USERAI_ON_OFF = 0xa3,
    TT_LOGINOUT_ON_OFF = 0xa4,
    TT_SET3_ON_OFF = 0xa5,
    TT_SHOPPING_ON_OFF = 0xa6,
    TT_REQ_MUNAK = 0xa7,
    TT_REQ_HUNTING = 0xa8,
    TT_REQ_DEATHKNIGHT = 0xa9,
    TT_REQ_EMOTION_LUV = 0xaa,
    TT_REQ_COLLECTOR = 0xab,
    TT_MINIGAME_ON_OFF = 0xac,
    TT_MER_USERAI_ON_OFF = 0xad,
    TT_REQ_EMOTION_MOBILE = 0xae,
    TT_REQ_EMOTION_MAIL = 0xaf,
    TT_REQ_EMOTION_ANTENNA0 = 0xb0,
    TT_REQ_EMOTION_ANTENNA1 = 0xb1,
    TT_REQ_EMOTION_ANTENNA2 = 0xb2,
    TT_REQ_EMOTION_ANTENNA3 = 0xb3,
    TT_COPY_NAME = 0xb4,
    TT_REQ_ACCEPT_INVITE_PARTY = 0xb5,
    TT_REQ_REFUSE_INVITE_PARTY = 0xb6,
    TT_REQ_INVITE_PARTY = 0xb7,
    TT_REQ_OPEN_EQUIPEDITEM_ONOFF = 0xb8,
    TT_BATTLECHAT_ON_OFF = 0xb9,
    TT_REQ_EMOTION_HUM2 = 0xba,
    TT_REQ_EMOTION_ABS = 0xbb,
    TT_REQ_EMOTION_OOPS = 0xbc,
    TT_REQ_EMOTION_SPIT = 0xbd,
    TT_REQ_EMOTION_ENE = 0xbe,
    TT_REQ_EMOTION_PANIC = 0xbf,
    TT_REQ_EMOTION_WHISP = 0xc0,
} TALKTYPE;
