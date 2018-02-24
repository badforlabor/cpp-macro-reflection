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


