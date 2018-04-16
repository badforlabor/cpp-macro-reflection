using System;
using System.Collections.Generic;

public class PBasePlayerInfo
{
    public Int64 PlayerId;
    public int HeadId;
    public int Level;
    public int Vip;
    public string PlayerName;
    public int Fight;
}
public class PFamWarSimpleInfoOne
{
    public int CityId;
    public Int64 WinnerFamily;
    public string WinnerFamilyName;
    public Int64 ChairmanPlayerId;
    public string ChairmanName;
    public int ChairmanHead;
    public int ChairmanLevel;
    public int AttackFamilyCnt;
    public Int64 LastSetChairmanTime;
}
public class PFamWarSimpleInfo
{
    public List<PFamWarSimpleInfoOne> AllInfo;
    public List<int> MyCities;
    public int MyAuth;
}
public class PFamWarDetailedInfo
{
    public PFamWarSimpleInfoOne CityInfo;
    public Int64 MyFamilyId;
    public List<PFamWarTeamInfo> AllTeamInfo;
}
public class PFamWarTeamInfo_Player
{
    public Int64 PlayerId;
    public int HeadId;
    public string PlayerName;
}
public class PFamWarTeamInfo
{
    public Int64 FamilyId;
    public string FamilyName;
    public Int64 FightAbility;
    public int Liveness;    // 活跃值
    public List<PFamWarTeamInfo_Player> Players;
}
public class PFamWarCityId
{
    public int cityid;
}
public class PMyUsedCard
{
    public List<int> UsedCards;
    public int CityId;
    public List<int> CityCards;
}
public class PAllMyUsedCard
{
    public List<PMyUsedCard> AllCityCards;
}

public class PSimpleGameCard
{
    public int card_sid_;
    public int card_star_;
    public int card_rank_;
    public int card_level;
}
public class PSimpleGameCardWithHp
{
    public PSimpleGameCard Card;
    public int hp_percent;
}
public class PFamWarLineup
{
    public PFamWarTeamInfo_Player player;
    public int FightAbility;
    public List<PSimpleGameCard> cards;
}
public class PFamWarOneBattle
{
    public int guid;
    public PFamBattleTeamInfo Team0;
    public PFamBattleTeamInfo Team1;
    public int WinnerIdx;
    public string RecordGUID;
}
public class PFamWarMeritPoint
{
    public int HeadId;
    public string PlayerName;
    public int Point;
}
public class PFamWarFamilyBattle
{
    public int CityId;
    public int BattleIdx;
    public int BattleMaxCnt;
    public List<PFamWarOneBattle> AllBattles;
    public List<PFamWarMeritPoint> Team0;
    public List<PFamWarMeritPoint> Team1;
    public int FamilyFightAbility0;
    public string FamilyName0;
    public int FamilyFightAbility1;
    public string FamilyName1;
    public int WinnerIdx;	// 胜利方：team0，还是team1
}
public class PFamWarCityBattleSimpleInfo
{
    public int CityId;
    public int BattleTotalCount;
}
public class PFamWarCityBattleSimpleInfoList
{
    public List<PFamWarCityBattleSimpleInfo> AllCities;
}
public class PFamBattleTeamInfo
{
    public PFamWarTeamInfo_Player Player;
    public int PlayerLevel;
    public int FightAblitity;
    public List<PSimpleGameCardWithHp> Cards;
}
public class PFamWarMeritPointDetail
{
    public PBasePlayerInfo Base;
    public int OldMerit;
    public int AllMerit;
}
public class PFamWarMeritPointDetailList
{
    public List<PFamWarMeritPointDetail> All;
    public Int64 LastUnSetChairmanTime;
}
public class PBroadcastFamWarStage
{
    public int StateId;
    public Int64 NextStageTime;
    public Int64 CurStageBeginTime;
    public int MyAuth;
}
public class PFamRewardInfo
{
    public int cityid;
    public int reward;
    public int extra;
    public int got;
};

public class PFamMyCity
{
    public int cityid;
    public int status;
}
public class PFamMyCityList
{
    public List<PFamMyCity> AllCities;
}
public class PFamWarInspireMsg
{
    public Int64 FamilyId;
    public string PlayerName;
    public int InspireType;
}
public class PFamWarInspireMsgAll
{
    public int CityId;
    public List<PFamWarInspireMsg> AllMsg;
}
public class PFamWarInspireInfo
{
    public List<int> FourInpire;
    public PFamWarInspireMsgAll AllMsg;
}

public class PFamMeritPoint
{
    public int Point;
};

public class PFamDeclareWarRet
{
    public int ErrorCode;
}
public class PFamBroadcastChairman
{
    public int CityId;
    public Int64 ChairmanPlayerId;
    public string ChairmanName;
    public int ChairmanHead;
    public int ChairmanLevel;
    public Int64 LastSetChairmanTime;
}