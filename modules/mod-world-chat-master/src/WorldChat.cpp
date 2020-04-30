/*
<--------------------------------------------------------------------------->
- Developer(s): WiiZZy
- Complete: 100%
- ScriptName: 'World chat'
- Comment: Fully tested
<--------------------------------------------------------------------------->
*/

#include "ScriptMgr.h"
#include "Log.h"
#include "Player.h"
#include "Chat.h"
#include "Common.h"
#include "World.h"
#include "WorldSession.h"
#include "Config.h"
#include <unordered_map>

/* VERSION */
float ver = 1.1f;

/* Colors */
std::string WORLD_CHAT_ALLIANCE_BLUE = "|cff3399FF";
std::string WORLD_CHAT_HORDE_RED = "|cffCC0000";
std::string WORLD_CHAT_WHITE = "|cffFFC0C0";
std::string WORLD_CHAT_GREEN = "|cff00CC00";
std::string WORLD_CHAT_RED = "|cffFF0000";
std::string WORLD_CHAT_BLUE = "|cff6666FF";
std::string WORLD_CHAT_BLACK = "|cff000000";
std::string WORLD_CHAT_GREY = "|cff808080";

/* Class Colors */
std::string world_chat_ClassColor[11] =
{
    "|cffC79C6E", // WARRIOR
    "|cffF58CBA", // PALADIN
    "|cffABD473", // HUNTER
    "|cffFFF569", // ROGUE
    "|cffFFFFFF", // PRIEST
    "|cffC41F3B", // DEATHKNIGHT
    "|cff0070DE", // SHAMAN
    "|cff40C7EB", // MAGE
    "|cff8787ED", // WARLOCK
    "", // ADDED IN MOP FOR MONK - NOT USED
    "|cffFF7D0A", // DRUID
};

/* Class Icons */
std::string world_chat_ClassIcons[11] =
{
    "|TInterface\\icons\\INV_Sword_27.png:15|t", // WARRIOR
    "|TInterface\\icons\\INV_Hammer_01:15|t", // PALADIN
    "|TInterface\\icons\\INV_Weapon_Bow_07:15|t", // HUNTER
    "|TInterface\\icons\\INV_ThrowingKnife_04:15|t", // ROGUE
    "|TInterface\\icons\\INV_Staff_30:15|t", // PRIEST
    "|TInterface\\icons\\Spell_Deathknight_ClassIcon:15|t", // DEATHKNIGHT
    "|TInterface\\icons\\Spell_Nature_BloodLust:15|t", // SHAMAN
    "|TInterface\\icons\\INV_Staff_13:15|t", // MAGE
    "|TInterface\\icons\\Spell_Nature_FaerieFire:15|t", // WARLOCK
    "", // ADDED IN MOP FOR MONK - NOT USED
    "|TInterface\\icons\\Ability_Druid_Maul:15|t", // DRUID
};

/* Ranks */
std::string world_chat_GM_RANKS[4] =
{
    "Player",
    "MOD",
    "GM",
    "ADMIN",
};

/* BLIZZARD CHAT ICON FOR GM'S */
std::string world_chat_GMIcon = "|TINTERFACE/CHATFRAME/UI-CHATICON-BLIZZ:15|t";

/* COLORED TEXT FOR CURRENT FACTION || NOT FOR GMS */
std::string world_chat_TeamIcon[2] =
{
    "|TInterface\\pvpframe\\pvp-currency-alliance:17|t",
    "|TInterface\\pvpframe\\pvp-currency-horde:17|t"
};

class WorldChat_Config : public WorldScript
{
public: WorldChat_Config() : WorldScript("WorldChat_Config") { };
    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/WorldChat.conf";
            std::string cfg_file_2 = cfg_file + ".dist";

            sConfigMgr->LoadMore(cfg_file_2.c_str());
            sConfigMgr->LoadMore(cfg_file.c_str());
        }
    }
};

/* STRUCTURE FOR WorldChat map */
struct ChatElements
{
    uint8 chat = (sConfigMgr->GetBoolDefault("World_Chat.OnLogin.State", true)) ? 1 : 0; // CHAT DISABLED BY DEFAULT
};

/* UNORDERED MAP FOR STORING IF CHAT IS ENABLED OR DISABLED */
std::unordered_map<uint32, ChatElements>WorldChat;


class World_Chat : public CommandScript
{
public:
    World_Chat() : CommandScript("World_Chat") { }



    static bool HandleWorldChatCommand(ChatHandler * pChat, const char * msg)
    {

        if (!sConfigMgr->GetBoolDefault("World_Chat.Enable", true)) {
            ChatHandler(pChat->GetSession()).PSendSysMessage("[WC] %sWorld Chat System is disabled.|r", WORLD_CHAT_RED.c_str());
            return true;
        }

        if (!*msg)
            return false;

        Player* player = pChat->GetSession()->GetPlayer();
        uint64 guid = player->GetGUID();

		if (!player->CanSpeak()){
			ChatHandler(pChat->GetSession()).PSendSysMessage("[WC] %sYou can't use World Chat while muted!|r", WORLD_CHAT_RED.c_str());
			return true;
		}

        if (!WorldChat[guid].chat) {
            ChatHandler(player->GetSession()).PSendSysMessage("[WC] %sWorld Chat is disabled. (.chat)|r", WORLD_CHAT_RED.c_str());
            return true;
        }

        char message[1024];


        SessionMap sessions = sWorld->GetAllSessions();

        for (SessionMap::iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
        {
            if (!itr->second)
                continue;
            if (!itr->second->GetPlayer())
            {
                continue;
            }
            if(!itr->second->GetPlayer()->IsInWorld())
            {
                continue;
            }


            Player* target = itr->second->GetPlayer();
            uint64 guid2 = target->GetGUID();

            if (WorldChat[guid2].chat == 1)
            {
                if (sConfigMgr->GetBoolDefault("World_Chat.CrossFactions", true)) {
                    if (player->IsGameMaster()) {
                        snprintf(message, 1024, "[Mundo][%s][%s%s|r]: %s%s|r", world_chat_GMIcon.c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                    }
                    else if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_DEVELOPER))
                        snprintf(message, 1024, "[Mundo][%sDEV|r][%s%s|r]: %s%s|r", world_chat_ClassColor[5].c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                    else
                        snprintf(message, 1024, "[Mundo] %s %s[%s%s|r]: %s%s|r", world_chat_TeamIcon[player->GetTeamId()].c_str(), world_chat_ClassIcons[player->getClass() - 1].c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                    ChatHandler(target->GetSession()).PSendSysMessage("%s", message);
                }
                else
                {
                    if (player->GetTeamId() == target->GetTeamId())
                    {
                        if (player->IsGameMaster()) {
                            snprintf(message, 1024, "[Mundo][%s][%s%s|r]: %s%s|r", world_chat_GMIcon.c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                        }
                        else if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_DEVELOPER))
                            snprintf(message, 1024, "[Mundo][%sDEV|r][%s%s|r]: %s%s|r", world_chat_ClassColor[5].c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                        else
                            snprintf(message, 1024, "[Mundo] %s [%s%s|r]: %s%s|r", world_chat_TeamIcon[player->GetTeamId()].c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                        ChatHandler(target->GetSession()).PSendSysMessage("%s", message);
                    }
                    else if (target->IsGameMaster()) {
                        if (player->IsGameMaster()) {
                            snprintf(message, 1024, "[Mundo][%s][%s%s|r]: %s%s|r", world_chat_GMIcon.c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                        }
                        else if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_DEVELOPER))
                            snprintf(message, 1024, "[Mundo][%sDEV|r][%s%s|r]: %s%s|r", world_chat_ClassColor[5].c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                        else
                            snprintf(message, 1024, "[Mundo] %s [%s%s|r]: %s%s|r", world_chat_TeamIcon[player->GetTeamId()].c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                        ChatHandler(target->GetSession()).PSendSysMessage("%s", message);
                    }
                }
            }
        }

        return true;
    }

    static bool HandleWorldChatHordeCommand(ChatHandler * pChat, const char * msg)
    {

        if (!sConfigMgr->GetBoolDefault("World_Chat.Enable", true)) {
            ChatHandler(pChat->GetSession()).PSendSysMessage("[WC] %sWorld Chat System is disabled.|r", WORLD_CHAT_RED.c_str());
            return true;
        }

        if (!*msg)
            return false;

        Player* player = pChat->GetSession()->GetPlayer();
        uint64 guid = player->GetGUID();

        if (!WorldChat[guid].chat) {
            ChatHandler(player->GetSession()).PSendSysMessage("[WC] %sWorld Chat is disabled. (.chat)|r", WORLD_CHAT_RED.c_str());
            return true;
        }

        char message[1024];


        SessionMap sessions = sWorld->GetAllSessions();

        for (SessionMap::iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
        {
            if (!itr->second)
                continue;
                
            if (!itr->second->GetPlayer())
            {
                continue;
            }
            if(!itr->second->GetPlayer()->IsInWorld())
            {
                continue;
            }


            Player* target = itr->second->GetPlayer();
            uint64 guid2 = target->GetGUID();

            if (WorldChat[guid2].chat == 1 && (target->GetTeamId() == TEAM_HORDE || target->IsGameMaster()))
            {
                if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_DEVELOPER))
                    snprintf(message, 1024, "[Mundo][%sDEV|r][%s%s|r]: %s%s|r", world_chat_ClassColor[5].c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                else
                    snprintf(message, 1024, "[Mundo][%s][%s%s|r]: %s%s|r", world_chat_GMIcon.c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                ChatHandler(target->GetSession()).PSendSysMessage("%s", message);
            }
        }

        return true;
    }

    static bool HandleWorldChatAllianceCommand(ChatHandler * pChat, const char * msg)
    {

        if (!sConfigMgr->GetBoolDefault("World_Chat.Enable", true)) {
            ChatHandler(pChat->GetSession()).PSendSysMessage("[WC] %sWorld Chat System is disabled.|r", WORLD_CHAT_RED.c_str());
            return true;
        }

        if (!*msg)
            return false;

        Player* player = pChat->GetSession()->GetPlayer();
        uint64 guid = player->GetGUID();

        if (!WorldChat[guid].chat) {
            ChatHandler(player->GetSession()).PSendSysMessage("[WC] %sWorld Chat is disabled. (.chat)|r", WORLD_CHAT_RED.c_str());
            return true;
        }

        char message[1024];


        SessionMap sessions = sWorld->GetAllSessions();

        for (SessionMap::iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
        {
            if (!itr->second)
                continue;
                
            if (!itr->second->GetPlayer())
            {
                continue;
            }
            if(!itr->second->GetPlayer()->IsInWorld())
            {
                continue;
            }


            Player* target = itr->second->GetPlayer();
            uint64 guid2 = target->GetGUID();

            if (WorldChat[guid2].chat == 1 && (target->GetTeamId() == TEAM_ALLIANCE || target->IsGameMaster()))
            {
                if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_DEVELOPER))
                    snprintf(message, 1024, "[Mundo][%sDEV|r][%s%s|r]: %s%s|r", world_chat_ClassColor[5].c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                else
                    snprintf(message, 1024, "[Mundo] %s [%s%s|r]: %s%s|r", world_chat_GMIcon.c_str(), world_chat_ClassColor[player->getClass() - 1].c_str(), player->GetName().c_str(), WORLD_CHAT_WHITE.c_str(), msg);
                ChatHandler(target->GetSession()).PSendSysMessage("%s",message);
            }
        }

        return true;
    }

    static bool HandleWorldChatOnCommand(ChatHandler* handler, const char* /*msg*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        uint64 guid = player->GetGUID();

        if (!sConfigMgr->GetBoolDefault("World_Chat.Enable", true)) {
            ChatHandler(player->GetSession()).PSendSysMessage("[WC] %sWorld Chat System is disabled.|r", WORLD_CHAT_RED.c_str());
            return true;
        }

        if (WorldChat[guid].chat) {
            ChatHandler(player->GetSession()).PSendSysMessage("[WC] %sWorld Chat is already visible.|r", WORLD_CHAT_RED.c_str());
            return true;
        }

        WorldChat[guid].chat = 1;

        ChatHandler(player->GetSession()).PSendSysMessage("[WC] %sWorld Chat is now visible.|r", WORLD_CHAT_GREEN.c_str());

        return true;
    };

    static bool HandleWorldChatOffCommand(ChatHandler* handler, const char* /*msg*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        uint64 guid = player->GetGUID();

        if (!sConfigMgr->GetBoolDefault("World_Chat.Enable", true)) {
            ChatHandler(player->GetSession()).PSendSysMessage("[WC] %sWorld Chat System is disabled.|r", WORLD_CHAT_RED.c_str());
            return true;
        }

        if (!WorldChat[guid].chat) {
            ChatHandler(player->GetSession()).PSendSysMessage("[WC] %sWorld Chat is already hidden.|r", WORLD_CHAT_RED.c_str());
            return true;
        }

        WorldChat[guid].chat = 0;

        ChatHandler(player->GetSession()).PSendSysMessage("[WC] %sWorld Chat is now hidden.|r", WORLD_CHAT_GREEN.c_str());

        return true;
    };

    std::vector<ChatCommand> GetCommands() const
    {
        static std::vector<ChatCommand> wcCommandTable =
        {
            { "on",      SEC_PLAYER,     false,     &HandleWorldChatOnCommand,      "" },
            { "off",     SEC_PLAYER,     false,    &HandleWorldChatOffCommand,       "" },
            { "",        SEC_PLAYER,     false,    &HandleWorldChatCommand,       "" },
        };
        static std::vector<ChatCommand> commandTable =
        {
            { "chat", SEC_PLAYER, true, NULL , "" , wcCommandTable},
            { "chath", SEC_MODERATOR, true, &HandleWorldChatHordeCommand , ""},
            { "chata", SEC_MODERATOR, true, &HandleWorldChatAllianceCommand , ""},
        };
        return commandTable;
    }
};

class WorldChat_Announce : public PlayerScript
{
public:

    WorldChat_Announce() : PlayerScript("WorldChat_Announce") {}

    void OnLogin(Player* player)
    {
        // Announce Module
        if (sConfigMgr->GetBoolDefault("World_Chat.Enable", true) && sConfigMgr->GetBoolDefault("World_Chat.Announce", true))
        {
            ChatHandler(player->GetSession()).SendSysMessage("El |cffff8000Chat Mundial |resta activado en el servidor.");
        }
    }
};

void AddSC_WorldChatScripts()
{
    new WorldChat_Announce;
    new WorldChat_Config;
    new World_Chat;
}
