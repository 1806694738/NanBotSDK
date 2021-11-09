#pragma once
#ifndef PCH_H

#include "pch.h"


#endif



//标签信息
struct nt_Label {
	int ID;//ID
	string name;//名称
	int praise;//赞数量

};


//群成员资料
struct nt_GroupMemberData {
	string name;//昵称
	string card;//名片
	string title;//活跃头衔
	string intogroup;//进群时间
	string speak;//最后发言时间
	string _title;//当前头衔
	int perm;//权限
	string city;//城市
	bool Friend;//是否好友
	string FriendNote;//好友备注
};

//资料卡
struct nt_Data
{
	string name;//昵称
	string note;//备注
	string email;//邮箱
	int age;//年龄
	int gender;//性别
	int level;//等级
	string state;//国家
	string provinces;//省份
	string city;//城市
	long long praise;//赞
	
	string signature;//签名
	list< nt_Label> loops;//圈圈赞
	list< nt_Label> label;//标签
};


//好友列表信息
struct nt_FriendsList
{
	string QQ;
	string name;//昵称
	string note;//备注
	string email;//邮箱
};


//机器人状态
struct nt_Robot_State
{
	int Receive;//接收消息数
	int Send;//发送消息数
	int Rate;//速率
	int Time;//在线时长

};


//HTTP结构
struct nt_http 
{
	string msg;
	int code;
	string head;
};


//群成员列表信息
struct nt_GroupMemberList
{
	string QQ;//QQ号
	int age;//年龄
	string name;//昵称
	string card;//名片
	string phone;//手机
	string email;//邮箱
	string note;//备注
	string active;//活跃等级
	string intogroup;//进群时间
	string speak;//最后发言时间
	string title;//头衔
	string titletime;//头衔到期时间
};

//群列表信息
struct nt_GroupList {
	string group;//群号
	string groupname;//群名
	string notice;//群公告
	int grouplevel;//群等级
	int numpeople;//当前人数
	int biggpeople;//最大人数
	string groupman;//群主QQ
	string intogroup;//进群时间

};

//群资料信息
struct nt_GroupData {
	string groupname;//群名
	string groupman;//群主QQ
	int numpeople;//当前人数
	int biggpeople;//最大人数
	string Label;//群标签
	list<string> admin;//管理员列表
};


struct  Group_Msg_text
{

	string qq;
	string group;
	string msgId;
	string msgNo;
	string msg;

};