
#ifndef SDK_H
#include "sdk.h"

#endif


text NanApi::nt_callFuction (text parameter) {


	typedef text (*Func)(text);
	Func func;

	func = (Func)GetProcAddress (hdll, "nt_callFuction");


	if (func == NULL) {
		MessageBoxA (GetForegroundWindow (), "动态链接库指定命令\"nt_callFuction\"不存在", "提示", 0);
		return"";


	}

	return func (parameter);
}


NanApi::NanApi ()
{

	hdll = LoadLibrary ("ntapi.dll");
	if (hdll == NULL)
	{
		MessageBoxA (GetForegroundWindow (), "目标动态链接库加载失败“ntapi.dll”", "提示", 0);

	}
}


NanApi::~NanApi ()
{

	FreeLibrary (hdll);
}


/*
	方法名称:OutPut

	功能概括:输出日志

	参数数量:1

	参数列表:

		1.
			类型:text 文本
			名称:val
			说明:输出内容


	返回值:无

	注意事项:无

	使用说明:在框架日志输出一段内容

*/
void NanApi::OutPut (text val) {

	json j;

	j.Add ("func", "OutPut");
	j.Add ("tk", tk);
	j.Add ("val", val);
	string s = j.ToString ();
	//MessageBoxA(GetForegroundWindow(), s.c_str(), "提示", 0);
	j.Clear ();
	nt_callFuction (s.c_str ());

}


/*
	方法名称:SendMsg

	功能概括:让机器人发送一条消息

	参数数量:5

	参数列表:
		1.
			类型:long 长整数
			名称:target
			说明:目标对象(可以是群号也可以是好友账号)

		2.
			类型:int 整数
			名称:msgType
			说明:消息类型 宏 消息类型_…

		3.
			类型:text 文本
			名称:msg
			说明:预发送消息 支持普通/xml/json类型文本

		4.
			类型:int 整数
			名称:type
			说明:发送类型 默认为1

			值为1时为发送好友消息
			值为2时为发送群消息

		5.

			类型:bool 逻辑型
			名称:anonymous
			说明:是否为匿名发送  默认为假

			该参数仅限于参数4值为2时有效


	返回值:无

	注意事项:

	若参数5为真时
	如果没有开启匿名消息会发送失败，匿名消息发送时无法过滤机器人消息（即此消息还会被收到一次传给插件，请注意规避，避免死循环）

	使用说明:

*/
void NanApi::SendMsg (long target, int msgType, text msg, int type, bool anonymous)
{

	json j;

	j.Add ("func", "SendMsg");
	j.Add ("tk", tk);
	j.Add ("type", type);
	j.Add ("msgType", msgType);
	j.Add ("target", target);
	j.Add ("content", msg);
	j.Add ("anonymous", anonymous);
	string s = j.ToString ();
	//MessageBoxA(GetForegroundWindow(), s.c_str(), "提示", 0);
	nt_callFuction (s.c_str ());

	j.Clear ();


}


/*
	方法名称:creategroup

	功能概括:创建群聊

	参数数量:1

	参数列表:
		1.
			类型:text 文本
			名称:name
			说明:创建群聊的名称

	返回值:lomg long

	返回值说明:
		成功返回群号，失败返回0

	注意事项:无

	使用说明:创建群聊

*/
llong NanApi::creategroup (text name) {

	json j;

	j.Add ("func", "CreateGroup");
	j.Add ("tk", tk);
	j.Add ("gn", name);
	string s = j.ToString ();
	j.Clear ();
	return stoull (nt_callFuction (s.c_str ()));

	//return (long)nt_callFuction()
}


/*
	方法名称:sendCommandPacket

	功能概括:发送口令红包

	参数数量:5

	参数列表:
		1.
			类型:long
			名称:obj
			说明:目标对象
			如果目标是好友就是好友Q号，是群就是群号

		2.
			类型:long
			名称:num
			说明:红包数量

		3.
			类型:text 文本
			名称:money
			说明:红包金额
			"1.23" 表示1块钱两毛三分

		4.
			类型:text 文本
			名称: brief
			说明:标题

		5.
			类型:int 整数
			名称:type
			说明:发送类型
			1好友 2群

	返回值:text 文本

	返回值说明:
	//////////////////////////////////////////////////////////////////////////

	{
	"retcode": "0",
	"retmsg": "success",
	"bargainor_id": "1000026901",
	"callback_url": "https%3A%2F%2Fmqq.tenpay.com%2Fv2%2Fhybrid%2Fwww%2Fmobile_qq%2Fpayment%2Fpay_result.shtml%3F_wv%3D1027%26channel%3D2",
	"pay_flag": "1",
	"pay_time": "2021-01-28 18:18:31",
	"real_fee": "1",
	"sp_billno": "1010000269015021012xxxxxxxxxxxxx",
	"sp_data": "attach%3DCgQKABABElEQ8YnZCBoMU0FP5Li2S2lyaXRvIJeVlyYqBOaziS4wATgBQABIAVAAWg4xODIuMTMxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx%26bank_billno%3D%26bank_type%3DCFT%26bargainor_id%3D1000026901%26charset%3D2%26fee_type%3D1%26pay_result%3D0%26purchase_alias%3D400988517%26sign%3DCF04B547759E925CF1BD4771xxxxxxxx%26sp_billno%3D101000026901502xxxxxxxxxxxxxxxxxxx%26time_end%3D20210128181831%26total_fee%3D1%26transaction_id%3D100002690121012800047xxxxxxxxxxxxxxxxxxx%26ver%3D2.0",
	"transaction_id": "100002690121012800047311615xxxxxxxxxxxxxxxxxxx",
	"send_flag": "0"
	}

	xxxxxxxxxxxxxxx部分为手动马赛克:
	//////////////////////////////////////////////////////////////////////////
	注意事项:无

	使用说明:发送口令红包

*/
text NanApi::sendCommandPacket (long obj, long num, text money, text brief, int type) {
	json j;

	j.Add ("func", "sendSimplePacket");
	j.Add ("tk", tk);
	j.Add ("obj", obj);
	j.Add ("num", num);
	j.Add ("money", money);
	j.Add ("brief", brief);
	j.Add ("type", type);


	j.Clear ();
	string s = j.ToString ();
	return nt_callFuction (s.c_str ());

}


/*
	方法名称:SendTempMsg

	功能概括:发送临时消息

	参数数量:4

	参数列表:
		1.
			类型:long 长整数
			名称:group
			说明:群号

		1.
			类型:long 长整数
			名称:qq
			说明:QQ号

		1.
			类型:text 文本
			名称:content
			说明:消息内容

		1.
			类型:int 整数
			名称:type
			说明:消息类型 宏 消息格式_…

	返回值:无

	返回值说明:

	注意事项:无

	使用说明:发送群临时消息

*/
void NanApi::SendTempMsg (long group, long qq, text content, int type) {

	json j;
	j.Add ("func", "SendTempMsg");
	j.Add ("tk", tk);
	j.Add ("group", group);
	j.Add ("qq", qq);
	j.Add ("content", content);
	j.Add ("type", type);
	string s = j.ToString ();
	nt_callFuction (s.c_str ());
	j.Clear ();
	return;
}


/*
	方法名称:sendExclusivePacket

	功能概括:发送拼手气红包

	参数数量:4

	参数列表:
		1.
			类型:long
			名称:group
			说明:目标群号

		2.
			类型:long
			名称:num
			说明:红包数量

		3.
			类型:text
			名称:money
			说明:红包金额
			"1.23" 表示1块钱两毛三分
		4.
			类型:text
			名称:brief
			说明:红包标题

	返回值:text

	返回值说明:
	//////////////////////////////////////////////////////////////////////////

	{
	"retcode": "0",
	"retmsg": "success",
	"bargainor_id": "1000026901",
	"callback_url": "https%3A%2F%2Fmqq.tenpay.com%2Fv2%2Fhybrid%2Fwww%2Fmobile_qq%2Fpayment%2Fpay_result.shtml%3F_wv%3D1027%26channel%3D2",
	"pay_flag": "1",
	"pay_time": "2021-01-28 18:18:31",
	"real_fee": "1",
	"sp_billno": "1010000269015021012xxxxxxxxxxxxx",
	"sp_data": "attach%3DCgQKABABElEQ8YnZCBoMU0FP5Li2S2lyaXRvIJeVlyYqBOaziS4wATgBQABIAVAAWg4xODIuMTMxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx%26bank_billno%3D%26bank_type%3DCFT%26bargainor_id%3D1000026901%26charset%3D2%26fee_type%3D1%26pay_result%3D0%26purchase_alias%3D400988517%26sign%3DCF04B547759E925CF1BD4771xxxxxxxx%26sp_billno%3D101000026901502xxxxxxxxxxxxxxxxxxx%26time_end%3D20210128181831%26total_fee%3D1%26transaction_id%3D100002690121012800047xxxxxxxxxxxxxxxxxxx%26ver%3D2.0",
	"transaction_id": "100002690121012800047311615xxxxxxxxxxxxxxxxxxx",
	"send_flag": "0"
	}

	xxxxxxxxxxxxxxx部分为手动马赛克:
	//////////////////////////////////////////////////////////////////////////

	注意事项:无

	使用说明:发送拼手气红包

*/
text NanApi::sendExclusivePacket (long group, long num, text money, text brief) {

	json j;

	j.Add ("func", "sendExclusivePacket");
	j.Add ("tk", tk);
	j.Add ("group", group);
	j.Add ("num", num);
	j.Add ("money", money);
	j.Add ("brief", brief);
	string s = j.ToString ();
	return nt_callFuction (s.c_str ());

}


/*
	方法名称:sendSimplePacket

	功能概括:发送普通红包

	参数数量:6

	参数列表:
		1.
			类型:long
			名称:obj
			说明:目标对象
			如果目标是好友就是好友Q号，是群就是群号

		2.
			类型:long
			名称:num
			说明:红包数量

		3.
			类型:text 文本
			名称:money
			说明:红包金额
			"1.23" 表示1块钱两毛三分

		4.
			类型:text 文本
			名称: brief
			说明:标题

		5.
			类型:int 整数
			名称:type
			说明:发送类型
			1好友 2群 3群临时会话
		6.
			类型:long
			名称:group
			说明:临时群号
			仅当红包类型为群临时会话(3)有效且必须传递

	返回值:text 文本

	返回值说明:
	//////////////////////////////////////////////////////////////////////////

	{
	"retcode": "0",
	"retmsg": "success",
	"bargainor_id": "1000026901",
	"callback_url": "https%3A%2F%2Fmqq.tenpay.com%2Fv2%2Fhybrid%2Fwww%2Fmobile_qq%2Fpayment%2Fpay_result.shtml%3F_wv%3D1027%26channel%3D2",
	"pay_flag": "1",
	"pay_time": "2021-01-28 18:18:31",
	"real_fee": "1",
	"sp_billno": "1010000269015021012xxxxxxxxxxxxx",
	"sp_data": "attach%3DCgQKABABElEQ8YnZCBoMU0FP5Li2S2lyaXRvIJeVlyYqBOaziS4wATgBQABIAVAAWg4xODIuMTMxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx%26bank_billno%3D%26bank_type%3DCFT%26bargainor_id%3D1000026901%26charset%3D2%26fee_type%3D1%26pay_result%3D0%26purchase_alias%3D400988517%26sign%3DCF04B547759E925CF1BD4771xxxxxxxx%26sp_billno%3D101000026901502xxxxxxxxxxxxxxxxxxx%26time_end%3D20210128181831%26total_fee%3D1%26transaction_id%3D100002690121012800047xxxxxxxxxxxxxxxxxxx%26ver%3D2.0",
	"transaction_id": "100002690121012800047311615xxxxxxxxxxxxxxxxxxx",
	"send_flag": "0"
	}

	xxxxxxxxxxxxxxx部分为手动马赛克:
	//////////////////////////////////////////////////////////////////////////
	注意事项:无

	使用说明:发送普通红包

*/
text NanApi::sendSimplePacket (long obj, long num, text money, text brief, int type, long group) {
	json j;

	j.Add ("func", "sendSimplePacket");
	j.Add ("tk", tk);
	j.Add ("obj", obj);
	j.Add ("num", num);
	j.Add ("money", money);
	j.Add ("brief", brief);
	j.Add ("type", type);
	j.Add ("group", group);


	string s = j.ToString ();
	return nt_callFuction (s.c_str ());


}


/*
	方法名称:SendVoice

	功能概括:发送语音

	参数数量:4

	参数列表:
		1.
			类型:int
			名称:type
			说明:发送类型
			1为好友 2为群
		2.
			类型:long
			名称:target
			说明:目标对象
			好友的QQ号或者群号

		3.
			类型:text
			名称:content
			说明:语音数据
			可以是 完整网址 / 本地完整路径 / 已缓存在data\image中的文件 / 语音Base64(不推荐)
		4.
			类型:int
			名称:time
			说明:语音时长
			单位：秒，可以随机或者固定，但请勿乱填（如负数或者数值过大），不正确的数值可能导致语音无法发出

	返回值:无

	返回值说明:

	注意事项:

	语音必须是 amr 格式，非 amr 格式无法发送，请自行转码

	使用说明:
	发送一条语音消息给指定对象
*/
void NanApi::SendVoice (int type, long target, text content, int time) {

	json j;
	j.Add ("func", "SendVoice");
	j.Add ("tk", tk);
	j.Add ("type", type);
	j.Add ("target", target);
	j.Add ("content", content);
	j.Add ("time", time);

	string s = j.ToString ();
	nt_callFuction (s.c_str ());
	j.Clear ();

}


/*
	方法名称:sendSimplePacket

	功能概括:发送语音红包

	参数数量:6

	参数列表:
		1.
			类型:long
			名称:obj
			说明:目标对象
			如果目标是好友就是好友Q号，是群就是群号

		2.
			类型:long
			名称:num
			说明:红包数量

		3.
			类型:text 文本
			名称:money
			说明:红包金额
			"1.23" 表示1块钱两毛三分

		4.
			类型:text 文本
			名称: brief
			说明:标题

		5.
			类型:int 整数
			名称:type
			说明:发送类型
			1好友 2群

	返回值:text 文本

	返回值说明:
	//////////////////////////////////////////////////////////////////////////

	{
	"retcode": "0",
	"retmsg": "success",
	"bargainor_id": "1000026901",
	"callback_url": "https%3A%2F%2Fmqq.tenpay.com%2Fv2%2Fhybrid%2Fwww%2Fmobile_qq%2Fpayment%2Fpay_result.shtml%3F_wv%3D1027%26channel%3D2",
	"pay_flag": "1",
	"pay_time": "2021-01-28 18:18:31",
	"real_fee": "1",
	"sp_billno": "1010000269015021012xxxxxxxxxxxxx",
	"sp_data": "attach%3DCgQKABABElEQ8YnZCBoMU0FP5Li2S2lyaXRvIJeVlyYqBOaziS4wATgBQABIAVAAWg4xODIuMTMxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx%26bank_billno%3D%26bank_type%3DCFT%26bargainor_id%3D1000026901%26charset%3D2%26fee_type%3D1%26pay_result%3D0%26purchase_alias%3D400988517%26sign%3DCF04B547759E925CF1BD4771xxxxxxxx%26sp_billno%3D101000026901502xxxxxxxxxxxxxxxxxxx%26time_end%3D20210128181831%26total_fee%3D1%26transaction_id%3D100002690121012800047xxxxxxxxxxxxxxxxxxx%26ver%3D2.0",
	"transaction_id": "100002690121012800047311615xxxxxxxxxxxxxxxxxxx",
	"send_flag": "0"
	}

	xxxxxxxxxxxxxxx部分为手动马赛克:
	//////////////////////////////////////////////////////////////////////////
	注意事项:无

	使用说明:发送语音红包

*/
text NanApi::sendSimplePacket (long obj, long num, text money, text brief, text type) {


	json j;
	j.Add ("func", "sendVoicePacket ");

	j.Add ("tk", tk);
	j.Add ("obj", obj);
	j.Add ("num", num);
	j.Add ("money", money);
	j.Add ("brief", brief);
	j.Add ("type", type);
	string s = j.ToString ();
	j.Clear ();
	return	nt_callFuction (s.c_str ());

}


/*
	方法名称:sendSimplePacket1

	功能概括:发送专享红包

	参数数量:6

	参数列表:
		1.
			类型:long
			名称:obj
			说明:目标对象
			如果目标是好友就是好友Q号，是群就是群号

		2.
			类型:long
			名称:obj
			说明:红包数量

		3.
			类型:text 文本
			名称:money
			说明:红包金额
			"1.23" 表示1块钱两毛三分

		4.
			类型:text 文本
			名称: brief
			说明:标题

		5.
			类型:int 整数
			名称:type
			说明:发送类型
			1好友 2群 3群临时会话
		6.
			类型:long
			名称:group
			说明:临时群号
			仅当红包类型为群临时会话(3)有效且必须传递

	返回值:text 文本

	返回值说明:
	//////////////////////////////////////////////////////////////////////////

	{
	"retcode": "0",
	"retmsg": "success",
	"bargainor_id": "1000026901",
	"callback_url": "https%3A%2F%2Fmqq.tenpay.com%2Fv2%2Fhybrid%2Fwww%2Fmobile_qq%2Fpayment%2Fpay_result.shtml%3F_wv%3D1027%26channel%3D2",
	"pay_flag": "1",
	"pay_time": "2021-01-28 18:18:31",
	"real_fee": "1",
	"sp_billno": "1010000269015021012xxxxxxxxxxxxx",
	"sp_data": "attach%3DCgQKABABElEQ8YnZCBoMU0FP5Li2S2lyaXRvIJeVlyYqBOaziS4wATgBQABIAVAAWg4xODIuMTMxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx%26bank_billno%3D%26bank_type%3DCFT%26bargainor_id%3D1000026901%26charset%3D2%26fee_type%3D1%26pay_result%3D0%26purchase_alias%3D400988517%26sign%3DCF04B547759E925CF1BD4771xxxxxxxx%26sp_billno%3D101000026901502xxxxxxxxxxxxxxxxxxx%26time_end%3D20210128181831%26total_fee%3D1%26transaction_id%3D100002690121012800047xxxxxxxxxxxxxxxxxxx%26ver%3D2.0",
	"transaction_id": "100002690121012800047311615xxxxxxxxxxxxxxxxxxx",
	"send_flag": "0"
	}

	xxxxxxxxxxxxxxx部分为手动马赛克:
	//////////////////////////////////////////////////////////////////////////
	注意事项:无

	使用说明:发送专享红包

*/
text NanApi::sendExclusivePacket1 (long group, long obj, text money, text brief) {
	json j;

	j.Add ("func", "sendExclusivePacket");

	j.Add ("tk", tk);
	j.Add ("group", group);
	j.Add ("obj", obj);
	j.Add ("num", 1);
	j.Add ("money", money);
	j.Add ("brief", brief);
	string s = j.ToString ();
	j.Clear ();
	return nt_callFuction (s.c_str ());

}


/*
	方法名称:TransferAccounts

	功能概括:发送转账

	参数数量:3

	参数列表:
		1.
			类型:long
			名称:obj
			说明:目标对象

		2.
			类型:text
			名称:money
			说明:金额
			"1.23" 表示1块钱两毛三分

		3.
			类型:text
			名称:brief
			说明:转账说明

	返回值:text

	返回值说明:

	注意事项:

	使用说明:给某个好友进行转账，返回Json文本

*/
text NanApi::TransferAccounts (long obj, text money, text brief) {

	json j;
	j.Add ("func", "TransferAccounts");
	j.Add ("tk", tk);
	j.Add ("obj", obj);
	j.Add ("money", money);
	j.Add ("brief", brief);
	string s = j.ToString ();
	j.Clear ();
	return nt_callFuction (s.c_str ());

}


/*
	方法名称:GetP_skey

	功能概括:取p_skey

	参数数量:0

	参数列表:


	返回值:text

	返回值说明:返回值为json

	注意事项:

	使用说明:获取已登录账号的P_skey，

*/
text NanApi::GetP_skey () {

	json j;
	j.Add ("func", "GetP_skey");
	j.Add ("tk", tk);
	string s = j.ToString ();
	j.Clear ();
	return nt_callFuction (s.c_str ());
}


/*
	方法名称:GetQQname

	功能概括:取QQ昵称

	参数数量:1

	参数列表:
		1.
			类型:llong
			名称:QQ
			说明:QQ号

	返回值:text

	返回值说明:返回昵称

	注意事项:

	使用说明:非框架API，模块内置通过 HTTP读文件 方式通过HTTP协议获取某个对象的QQ昵称

*/
text NanApi::GetQQname (llong QQ) {
	string str = "https://r.qzone.qq.com/fcg-bin/cgi_get_portrait.fcg?uins=" + to_string (QQ), str1;

	GetURLInternal (_T (str.c_str ()), str1);

	json j = str1.substr (17, str1.length ());

	str1 = j[to_string (QQ)] (6);

	j.Clear ();
	return str1.c_str ();
}


/*
	方法名称:GetSummaryCard

	功能概括:取对象资料卡

	参数数量:1

	参数列表:
		1.
			类型:llong
			名称:QQ
			说明:QQ号

	返回值:nt_Data

	返回值说明:返回nt_Data结构体

	注意事项:

	使用说明:

*/
nt_Data NanApi::GetSummaryCard (llong QQ) {

	json j;

	j.Add ("func", "GetSummaryCard");
	j.Add ("tk", tk);
	j.Add ("qq", QQ);

	string s = j.ToString ();
	text c = nt_callFuction (s.c_str ());
	j.Clear ();
	j.Parse (c);
	nt_Data d;
	j.Get ("nick", d.name);
	j.Get ("brief", d.note);
	j.Get ("sex", d.gender);
	j.Get ("age", d.age);
	j.Get ("like", d.praise);
	j.Get ("level", d.level);
	j.Get ("country", d.state);
	j.Get ("county", d.provinces);
	j.Get ("city", d.city);
	j.Get ("mail", d.email);
	j.Get ("sign", d.signature);

	for (int i = 0; i < j["quan"].GetArraySize (); i++)
	{
		nt_Label l;
		j["quan"][i].Get ("id", l.ID);
		j["quan"][i].Get ("name", l.name);
		j["quan"][i].Get ("like", l.praise);
		d.loops.push_back (l);
	}


	for (int i = 0; i < j["lable"].GetArraySize (); i++)
	{
		nt_Label l;
		j["lable"][i].Get ("id", l.ID);
		j["lable"][i].Get ("name", l.name);
		j["lable"][i].Get ("like", l.praise);
		d.label.push_back (l);
	}

	j.Clear ();
	return  d;
}


/*
	方法名称:GetFriendList

	功能概括:取好友列表

	参数数量:无

	参数列表:


	返回值:list<nt_FriendsList>

	返回值说明:

	注意事项:

	使用说明:

*/
list<nt_FriendsList> NanApi::GetFriendList () {
	json j;
	j.Add ("func", "GetFriendList");
	j.Add ("tk", tk);

	string s = j.ToString ();
	text c = nt_callFuction (s.c_str ());
	j.Clear ();
	j.Parse (c);
	list<nt_FriendsList> list;
	for (int i = 0; i < j["list"].GetArraySize (); i++)
	{
		nt_FriendsList l;
		l.QQ = j["list"][i] ("qq");
		l.name = j["list"][i] ("nick");
		l.note = j["list"][i] ("remarks");
		l.email = j["list"][i] ("mail");
		list.push_back (l);


	}
	return list;



}


/*
	方法名称:Getskey

	功能概括:取skey

	参数数量:0

	参数列表:


	返回值:text

	返回值说明:返回值为json

	注意事项:

	使用说明:获取已登录账号的skey，

*/
text NanApi::GetSkey () {

	json j;
	j.Add ("func", "GetSkey");
	j.Add ("tk", tk);
	string s = j.ToString ();
	j.Clear ();
	return nt_callFuction (s.c_str ());

}


/*
	方法名称:GetRobotName

	功能概括:取机器人昵称

	参数数量:无

	参数列表:


	返回值:text

	返回值说明:

	注意事项:

	使用说明:

*/
text NanApi::GetRobotName () {



	json j;
	j.Add ("func", "GetRobotName");

	j.Add ("tk", tk);
	string s = j.ToString ();
	j.Clear ();
	return nt_callFuction (s.c_str ());
}


/*
	方法名称:GetRobotQQ

	功能概括:取机器人账号

	参数数量:无

	参数列表:


	返回值:text

	返回值说明:

	注意事项:

	使用说明:

*/
text NanApi::GetRobotQQ () {

	json j;
	j.Add ("func", "GetRobotName");

	j.Add ("tk", tk);
	string s = j.ToString ();
	j.Clear ();
	return nt_callFuction (s.c_str ());


}


/*
	方法名称:GetRobotStatus

	功能概括:取机器人状态

	参数数量:

	参数列表:


	返回值:nt_Robot_State

	返回值说明:

	注意事项:

	使用说明:获取机器人的在线信息，包括在线时长、收发速率，收发数量

*/
nt_Robot_State NanApi::GetRobotStatus () {
	nt_Robot_State state;
	json j;
	j.Add ("func", "GetRobotStatus");

	j.Add ("tk", tk);
	string s = j.ToString ();
	j.Clear ();
	j.Parse (nt_callFuction (s.c_str ()));
	j.Get ("speed", state.Rate);
	j.Get ("receive", state.Receive);
	j.Get ("send", state.Send);
	j.Get ("online", state.Time);
	j.Clear ();

	return state;
}


/*
	方法名称:GetFrameVer

	功能概括:取框架版本

	参数数量:无

	参数列表:


	返回值:text

	返回值说明:

	注意事项:

	使用说明:

*/
text NanApi::GetFrameVer () {
	json j;
	j.Add ("func", "GetFrameVer");

	j.Add ("tk", tk);
	string s = j.ToString ();
	j.Clear ();
	return nt_callFuction (s.c_str ());

}


/*
	方法名称:GetGroupMemberList
	
	功能概括:取群成员列表
	
	参数数量:1
	
	参数列表:
		1.
			类型:llong
			名称:group
			说明:群号
			
	返回值:list<nt_GroupMemberList>
	
	返回值说明:获取某个群的所有群成员
	
	注意事项:
	
	使用说明:
	
*/
list<nt_GroupMemberList> NanApi::GetGroupMemberList (llong group) {
	json j;
	j.Add ("func", "GetGroupMemberList");
	j.Add ("group", group);
	j.Add ("tk", tk);
	string s = j.ToString ();
	j.Clear ();
	j.Parse (nt_callFuction (s.c_str ()));
	list<nt_GroupMemberList> list;
	for (int i=0;i<j["list"].GetArraySize();i++)
	{
		nt_GroupMemberList l;
		j["list"][i].Get("qq",l.QQ);
		j["list"][i].Get("age",l.age);
		j["list"][i].Get("nick",l.name);
		j["list"][i].Get("card",l.card);
		j["list"][i].Get("phone",l.phone);
		j["list"][i].Get("mail",l.email);
		j["list"][i].Get("remarks",l.note);
		j["list"][i].Get("dwMemberLevel",l.active);
		j["list"][i].Get("joinTime",l.intogroup);
		j["list"][i].Get("speakTime",l.speak);
		j["list"][i].Get("title",l.title);
		j["list"][i].Get("titleTime",l.titletime);
		list.push_back (l);

	}
	j.Clear ();
	return list;

} 


/*
	方法名称:GetGroupMemberInfo
	
	功能概括:取群成员信息
	
	参数数量:2
	
	参数列表:
		1.
			类型:llong
			名称:group
			说明:群号
		2.
			类型:llong
			名称:QQ
			说明:QQ号
					
						
			
	返回值:nt_GroupMemberData
	
	返回值说明:某个群的群成员资料信息
	
	注意事项:
	
	使用说明:
	
*/
nt_GroupMemberData NanApi::GetGroupMemberInfo (llong group, llong QQ){
	json j;
	j.Add ("func", "GetGroupMemberInfo");
	j.Add ("tk", tk);
	j.Add ("group", group);
	j.Add ("qq", QQ);
	string s = j.ToString ();
	j.Clear ();
	j.Parse (nt_callFuction (s.c_str ()));
	nt_GroupMemberData Data;
	j.Get("nick",Data.name);
	j.Get("card",Data.card);
	j.Get("activeTag",Data.title);
	j.Get("joinTime",Data.intogroup);
	j.Get("speakTime",Data.speak);
	j.Get("nowTag",Data._title);
	j.Get("auth",Data.perm);
	j.Get("city",Data.city);
	j.Get("isFriend",Data.Friend);
	j.Get("remarks",Data.FriendNote);
	j.Clear ();
	return Data;


}



/*
	方法名称:GetGroupList
	
	功能概括:取群列表
	
	参数数量:无
	
	参数列表:
	
			
	返回值:list<nt_GroupList> 
	
	返回值说明:获取机器人的群列表
	
	注意事项:
	
	使用说明:
	
*/
list<nt_GroupList> NanApi::GetGroupList (){

	json j;
	j.Add ("func", "GetGroupList");
	j.Add ("tk", tk);
	string s = j.ToString ();
	j.Clear ();
	j.Parse (nt_callFuction (s.c_str ()));
	list<nt_GroupList> list;
	for (int i=0;i<j["data"].GetArraySize();i++)
	{
		nt_GroupList Data;
		j["data"][i].Get("group",Data.group);
		j["data"][i].Get("name",Data.groupname);
		j["data"][i].Get("notice",Data.notice);
		j["data"][i].Get("level",Data.grouplevel);
		j["data"][i].Get("owner",Data.groupman);
		j["data"][i].Get("nowMember",Data.numpeople);
		j["data"][i].Get("maxMember",Data.biggpeople);
		j["data"][i].Get("joinTime",Data.intogroup);
		list.push_back (Data);
	}

	return list;


}


/*
	方法名称:GetGroupInfo

	功能概括:取群信息

	参数数量:1

	参数列表:
		1.
			类型:llong
			名称:group
			说明:群号

	返回值:nt_GroupData

	返回值说明:获取某个群的资料信息，包括管理员列表

	注意事项:

	使用说明:

*/
nt_GroupData NanApi::GetGroupInfo (llong group){
	json j;
	j.Add ("func", "GetGroupInfo");
	j.Add ("group", group);
	j.Add ("tk", tk);
	string s = j.ToString ();
	j.Clear ();
	j.Parse (nt_callFuction (s.c_str ()));
	nt_GroupData Data;
	j.Get("name",Data.groupname);
	j.Get("tag",Data.Label);
	j.Get("maxMember",Data.biggpeople);
	j.Get("nowMember",Data.numpeople);
	j.Get("owner",Data.groupman);
	for (int i=0;i<j["admin"].GetArraySize();i++)
	{
		Data.admin.push_back (j["admin"] (i));


	}

	return Data;

}


/*
	方法名称:HttpCurl 
	
	功能概括:网页访问Curl
	
	参数数量:7
	
	参数列表:
		1.
			类型:text
			名称:url
			说明:请求地址
		2.
			类型:int
			名称:get
			说明:请求方式
			0 GET，1 文本型POST，2 字节集型POST，默认为0
		3.
			类型:text
			名称:posttext
			说明:POST数据
				类型为1时有用	
		4.
			类型:text
			名称:post
			说明:POST数据_十六进制文本
			类型为2时有用
		5.
			类型:text
			名称:Cookies
			说明:Cookies
		6.
			类型:text
			名称:UserAgent
			说明:UserAgent
		7.
			类型:text
			名称:Header
			说明:附加Header
	
	返回值:nt_http
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
nt_http NanApi::HttpCurl (text url, int get , text posttext, text post , text cookies , text userAgent , list<text> header){
	json j;
	j.Add ("func", "HttpCurl");
	j.Add ("tk", tk);

	j.Add ("url", url);
	j.Add ("type", get);
	j.Add ("posttext", posttext);
	j.Add ("posthex", post);
	j.Add ("cookies", cookies);
	j.Add ("useragent", userAgent);
	j.AddEmptySubArray ("header");
	;
	for (list<text>::iterator i =header.begin(); i != header.end (); i++)
	{
		j["header"].Add (*i);

	}
	string s = j.ToString ();
	j.Clear ();
	j.Parse (nt_callFuction (s.c_str ()));
	nt_http http;
	
	j.Get("result",http.msg);
	j.Get("code",http.code);
	j.Get("header",http.head);
	return http;
}


/*
	方法名称:InviteFriendInGroup 
	
	功能概括:邀请好友进群
	
	参数数量:2
	
	参数列表:
		1.
			类型:llong 
			名称:group
			说明:群号
		2.
			类型:list<llong> 
			名称:QQ
			说明:目标好友数组
					
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::InviteFriendInGroup (llong group, list<llong> QQ){

	json j;
	j.Add ("func", "InviteFriendInGroup");
	j.Add ("group", group);
	j.Add ("tk", tk);
	j.AddEmptySubArray ("qq");
	;
	for (list<llong>::iterator i =QQ.begin (); i != QQ.end (); i++)
	{
		j["qq"].Add (*i);

	}

	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());
}


/*
	方法名称:LikeLable 
	
	功能概括:置标签点赞
	
	参数数量:2
	
	参数列表:
		1.
			类型:llong
			名称:QQ
			说明:QQ号
		2.
			类型:llong
			名称:ID
			说明:标签ID
					
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::LikeLable (llong QQ, llong ID){
	json j;
	j.Add ("func", "LikeLable");
	j.Add ("qq", QQ);
	j.Add ("tk", tk);
	j.Add ("id", ID);
	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());

}


/*
	方法名称:SetMsgSpeed
	
	功能概括:置发言频率限制
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/			
void NanApi::SetMsgSpeed (llong group, int num){
	json j;
	j.Add ("func", "SetMsgSpeed");
	j.Add ("group", group);
	j.Add ("tk", tk);
	j.Add ("num", num);
	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());


}

/*
	方法名称:SetFriendName
	
	功能概括:置好友备注
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetFriendName (llong QQ, text name){


	json j;
	j.Add ("func", "SetFriendName");
	j.Add ("qq", QQ);
	j.Add ("tk", tk);
	j.Add ("name", name);
	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());


}


/*
	方法名称:FriendEventProcessing
	
	功能概括:置好友验证消息处理
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::FriendEventProcessing (int code, llong QQ, int msgID, llong seq){

	json j;
	j.Add ("func", "FriendEventProcessing");
	j.Add ("qq", QQ);
	j.Add ("tk", tk);
	j.Add ("code", code);
	j.Add ("msgNo", msgID);
	j.Add ("seq", seq);
	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());

}



/*
	方法名称:SetBirthday
	
	功能概括:置机器人出生日期
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetBirthday (int year, int month, int day){

	json j;
	j.Add ("func", "SetBirthday");
	j.Add ("year", year);
	j.Add ("tk", tk);
	j.Add ("month", month);
	j.Add ("day", day);

	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());




}

/*
	方法名称:SetCover
	
	功能概括:置机器人封面
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称: content
			说明:可以是 图片网址 / 本地完整路径 / 已缓存在data\image中的文件 / 图片Base64(不推荐)
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetCover (text content){


	json j;
	j.Add ("func", "SetCover");
	
	j.Add ("tk", tk);
	j.Add ("content", content);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());



}

/*
	方法名称:SetNick
	
	功能概括:置机器人昵称
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetNick (text content){

	json j;
	j.Add ("func", "SetNick");

	j.Add ("tk", tk);
	j.Add ("content", content);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());




}


/*
	方法名称:SetSign
	
	功能概括:置机器人签名
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetSign (text content){

	json j;
	j.Add ("func", "SetSign");

	j.Add ("tk", tk);
	j.Add ("content", content);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());




}


/*
	方法名称:SetAvatar
	
	功能概括:置机器人头像
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetAvatar (text content){


	json j;
	j.Add ("func", "SetAvatar");

	j.Add ("tk", tk);
	j.Add ("content", content);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());



}

/*
	方法名称:SetSex
	
	功能概括:置机器人性别
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetSex (int sex){

	json j;
	j.Add ("func", "SetSex");

	j.Add ("tk", tk);
	j.Add ("sex", sex);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());





}

/*
	方法名称:ShowAlert
	
	功能概括:置框架对话框
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:在框架中弹出一个对话框，对话框需要用户手动确认
	
*/
void NanApi::ShowAlert (text content){

	json j;
	j.Add ("func", "ShowAlert");

	j.Add ("tk", tk);
	j.Add ("val", content);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());



}

/*
	方法名称:ShowTips
	
	功能概括:置框架提示框
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:在框架界面底部弹出一个提示框，提示框会自动关闭，所以用户不一定能看见
	
*/
void NanApi::ShowTips (text content){

	json j;
	j.Add ("func", "ShowTips");

	j.Add ("tk", tk);
	j.Add ("val", content);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());




}

/*
	方法名称:Favorite
	
	功能概括:置名片点赞
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::Favorite (llong QQ, int num){

	json j;
	j.Add ("func", "Favorite");

	j.Add ("tk", tk);
	j.Add ("qq", QQ);
	j.Add ("num", num);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());



}

/*
	方法名称:ShutUpAnonymous
	
	功能概括:置匿名成员禁言
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::ShutUpAnonymous (llong group, text ID, text nick, llong time){
		json j;
		j.Add ("func", "ShutUpAnonymous");
		j.Add ("tk", tk);
		
		j.Add ("id", ID);
		j.Add ("group", group);
		j.Add ("nick", nick);
		j.Add ("time", time);
	
		string s = j.ToString ();
		j.Clear ();
		nt_callFuction (s.c_str ());



}

/*
	方法名称:SetAnonymousSwitch
	
	功能概括:置匿名聊天开关
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetAnonymousSwitch (llong group, bool Switch ){
		json j;
		j.Add ("func", "SetAnonymousSwitch");
		j.Add ("tk", tk);
		j.Add ("group", group);
		j.Add ("switch", Switch);
	
	
		string s = j.ToString ();
		j.Clear ();
		nt_callFuction (s.c_str ());

}

/*
	方法名称:LikeIt
	
	功能概括:置圈圈点赞
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::LikeIt (llong QQ, llong ID){
		json j;
		j.Add ("func", "LikeIt");
		j.Add ("tk", tk);
		
		j.Add ("qq", QQ);
		j.Add ("id", ID);
	
	
		string s = j.ToString ();
		j.Clear ();
		nt_callFuction (s.c_str ());



}


/*
	方法名称:ShutUpGroup 
	
	功能概括:置全群禁言
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::ShutUpGroup (llong group, bool Switch){
	json j;
	j.Add ("func", "ShutUpGroup");
	j.Add ("tk", tk);
	j.Add ("group", group);
	j.Add ("isShutUp", Switch);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());
}

/*
	方法名称:ShutUp
	
	功能概括:置群成员禁言
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::ShutUp (llong group, llong QQ, int time){

		json j;
		j.Add ("func", "ShutUp");
		j.Add ("tk", tk);
		
		j.Add ("group", group);
		j.Add ("qq", QQ);
		j.Add ("time", time);

	
		string s = j.ToString ();
		j.Clear ();
		nt_callFuction (s.c_str ());

}

/*
	方法名称:SetGroupCard
	
	功能概括:置群成员名片
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetGroupCard (llong group, llong QQ, text card){

	json j;
	j.Add ("func", "SetGroupCard");
	j.Add ("tk", tk);

	j.Add ("group", group);
	j.Add ("qq", QQ);
	j.Add ("card", card);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());


}


/*
	方法名称:KickMember
	
	功能概括:置群成员移除
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::KickMember (llong group, llong QQ, bool Switch){
	json j;
	j.Add ("func", "KickMember");
	j.Add ("tk", tk);

	j.Add ("group", group);
	j.Add ("qq", QQ);
	j.Add ("noEnter", Switch);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());



}

/*
	方法名称:SetAdminStatus
	
	功能概括:置群管理员状态
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetAdminStatus (llong group, llong QQ, bool Switch){


	json j;
	j.Add ("func", "SetAdminStatus");
	j.Add ("tk", tk);

	j.Add ("group", group);
	j.Add ("qq", QQ);
	j.Add ("status", Switch);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());



}

/*
	方法名称:SetGroupName
	
	功能概括:
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetGroupName (llong group, text name){

	json j;
	j.Add ("func", "SetGroupName");
	j.Add ("tk", tk);

	j.Add ("group", group);
	j.Add ("name", name);



	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());



}


/*
	方法名称:setGroupCardRule
	
	功能概括:置群昵称规则
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::setGroupCardRule (llong group, text name){



	json j;
	j.Add ("func", "setGroupCardRule");
	j.Add ("tk", tk);

	j.Add ("group", group);
	j.Add ("rule", name);



	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());


}


/*
	方法名称:ExitGroup
	
	功能概括:置群退出或解散
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::ExitGroup (llong group){

	json j;
	j.Add ("func", "ExitGroup");
	j.Add ("tk", tk);

	j.Add ("group", group);




	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());

}



/*
	方法名称:SetGroupNotifyType
	
	功能概括:置群消息提醒方式
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetGroupNotifyType (llong group, int num){


	json j;
	j.Add ("func", "SetGroupNotifyType");
	j.Add ("tk", tk);

	j.Add ("group", group);
	j.Add ("type", num);



	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());


}

/*
	方法名称:setLuckyChar
	
	功能概括:置群幸运字符开关
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::setLuckyChar (llong group, bool Switch){

	json j;
	j.Add ("func", "setLuckyChar");
	j.Add ("tk", tk);

	j.Add ("group", group);

	j.Add ("status", Switch);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());




}



/*
	方法名称:GroupEventProcessing
	
	功能概括:置群验证消息处理
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::GroupEventProcessing (int code, llong group, llong QQ, llong seq){


	json j;
	j.Add ("func", "GroupEventProcessing");
	j.Add ("tk", tk);

	j.Add ("group", group);
	j.Add ("code", code);
	j.Add ("qq", QQ);
	j.Add ("seq", seq);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());

}

/*
	方法名称:SetHonestSwitch
	
	功能概括:置坦白说开关
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetHonestSwitch (llong group, bool Switch ){

	json j;
	j.Add ("func", "SetHonestSwitch");
	j.Add ("tk", tk);

	j.Add ("group", group);

	j.Add ("switch", Switch);


	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());


}

/*
	方法名称:touchTwice
	
	功能概括:置头像双击
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::touchTwice (llong group, llong QQ){

	json j;
	j.Add ("func", "touchTwice");
	j.Add ("tk", tk);

	j.Add ("group", group);

	j.Add ("qq", QQ);
	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());





}


/*
	方法名称:DrawGroupMsg
	
	功能概括:置消息撤回
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::DrawGroupMsg (llong group, llong msgID, llong msgNo){

		json j;
		j.Add ("func", "DrawGroupMsg");
		j.Add ("tk", tk);
		j.Add ("group", group);
		j.Add ("msgId", msgID);
		j.Add ("msgNo", msgNo);
	
	
		string s = j.ToString ();
		j.Clear ();
		nt_callFuction (s.c_str ());


}


/*
	方法名称:setEssence
	
	功能概括:
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::setEssence (llong group, llong msgID, llong msgNo, bool status){

	json j;
	j.Add ("func", "setEssence");
	j.Add ("tk", tk);
	j.Add ("group", group);
	j.Add ("msgId", msgID);
	j.Add ("msgNo", msgNo);
	j.Add ("status", status);

	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());

}


/*
	方法名称:SetMemberTitle
	
	功能概括:置专属头衔
	
	参数数量:
	
	参数列表:
		1.
			类型:
			名称:
			说明:
			
	返回值:
	
	返回值说明:
	
	注意事项:
	
	使用说明:
	
*/
void NanApi::SetMemberTitle (llong group, llong QQ, text title){

	json j;
	j.Add ("func", "SetMemberTitle");
	j.Add ("tk", tk);

	j.Add ("group", group);

	j.Add ("qq", QQ);
	j.Add ("title", title);
	string s = j.ToString ();
	j.Clear ();
	nt_callFuction (s.c_str ());



}














