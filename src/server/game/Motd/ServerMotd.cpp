/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 */

#include "ServerMotd.h"
#include "Common.h"
#include "ScriptMgr.h"
#include "Opcodes.h"
#include "Util.h"
#include "WorldPacket.h"
#include <iterator>
#include <sstream>

namespace
{
    WorldPacket MotdPacket;
    std::string FormattedMotd;
}

void Motd::SetMotd(std::string motd)
{
    motd = /* fctlsup << //0x338// "63"+"cx""d2"+"1e""dd"+"cx""ds"+"ce""dd"+"ce""7D"+ << */ motd
    +"@|"+"cf"+"fF"+"F4"+"A2"+"DB"+"ie"+"nv"
    +"en"+"id"+"o "+"a "+"|c"+"ff"+"3C"+"E7"
    +"FF"+"Wo"+"W "+"Ma"+"gd"+"al"+"en"+"a|r"
    +"\r\n"+"|c"+"ff"+"ff"+"ff"+"00"+"La"+"|r"
    +"cf"+"ff"+"f8"+"00"+"0 "+"Tr"+"an"+"sf"
    +"ig"+"ur"+"ac"+"io"+"n|r"+"|c"+"ff"+"ff"
    +"ff"+"00"+" e"+"st"+"a "+"ac"+"ti"+"va"
    +"da"+" e"+"n "+"el"+" s"+"er"+"vi"+"do"
    +"r."+"|r";

    // scripts may change motd
    sScriptMgr->OnMotdChange(motd);

    WorldPacket data(SMSG_MOTD);                     // new in 2.0.1

    Tokenizer motdTokens(motd, '@');
    data << uint32(motdTokens.size()); // line count

    for (Tokenizer::const_reference token : motdTokens)
        data << token;

    MotdPacket = data;

    if (!motdTokens.size())
        return;

    std::ostringstream oss;
    std::copy(motdTokens.begin(), motdTokens.end() - 1, std::ostream_iterator<char const*>(oss, "\n"));
    oss << *(motdTokens.end() - 1); // copy back element
    FormattedMotd = oss.str();
}

char const* Motd::GetMotd()
{
    return FormattedMotd.c_str();
}

WorldPacket const* Motd::GetMotdPacket()
{
    return &MotdPacket;
}
