/*
	协议
*/

STRUCT(db2gs)
{

};

STRUCT(OneMsgBoardData)
{
	Member(Int64, guid);
	Member(ByteArray, active_data);
};

STRUCT(PreloadMsgBoardData)
{
	Member(int, begin);
	Member(int, cnt);
	VectorMember(OneMsgBoardData, MsgBoardDatas);
};

STRUCT(SavedMsgBoardData)
{
	VectorMember(OneMsgBoardData, MsgBoardDatas);
};

// GS-DB,请求生成激活码
STRUCT(GS2DBGenerateActivateCode)
{
	// 激活码类型(1:公用,2:单用)
	Member(int, type);
	// 活动ID(activate_code_reward.csv)
	Member(int, config_id);
	// 数量
	Member(int, num);
	// 持续时间
	Member(int, life_time);
	// 分组ID
	Member(int, group_id);
};


STRUCT(PFamWarCommonData)
{
	Member(int, guid);
	Member(ByteArray, msgbin);
};

STRUCT(PFamWarPreloadCommon)
{
	Member(int, guid);
	Member(int, cnt);
};
STRUCT(PFamWarPreloadData)
{
	Member(int, guid);	// gs发送给db的guid
	Member(int, last);	// 是否是最后一个
	VectorMember(PFamWarCommonData, all);
};
STRUCT(PFamWarSaveCommon)
{
	VectorMember(PFamWarCommonData, all);
};
