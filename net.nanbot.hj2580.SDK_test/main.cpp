
#ifndef SDK_H
#include "sdk.h"
NanApi nt;
#include "GroupFunc.h"
#endif









/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//建立插件信息，请修改此子程序相关参数，此处请不要放置任何多余代码 此子程序请勿删除
text _stdcall GenerateInfo() {

	


	
	json json;
	json.AddEmptySubObject("info");
	json["info"].Add("name","class群管系统");//插件名称

	json["info"].Add("author","test");//插件作者

	json["info"].Add("verindex","1.0");//插件内部版本

	json["info"].Add("vername","1.0");//插件显示版本

	json["info"].Add("id","net.nanbot.hj2580.SDK_test");//插件ID
	//插件文件名必须以 插件ID.nt.dll 进行命名，以上例子的文件名就应为 net.nanbot.hj2580.SDK_test.nt.dll

	json["info"].Add("url","");// 请输入HTTP地址，当用户点击“联系作者”后会跳转到该地址 
	//此项尚未启用，填不填关系不大

	json["info"].Add("describe","这是一个测试插件");
	// 支持HTML和多行
	json["info"].Add("priority", NanBot_PRIORITY_GIVE);
	 
	json["info"].Add("bg","");
	// 显示的背景图片文件名，请在初始化中将背景图片写到 “\webui\imgs\”文件夹中；如“net.nanbot.test.jpg”
	json.AddEmptySubObject("sdk");
	json["sdk"].Add("ver",1);

	


	json.AddEmptySubObject ("event");                
	json["event"].Add("group", true);		//群事件 
	json["event"].Add("frame",true);			//框架和插件事件 
	json["event"].Add("verify",true);		//验证事件 
	json["event"].Add("friend",true);		//好友事件 
	json["event"].Add("provisional",true);	//临时事件 
	json["event"].Add("other",true);			//其他事件 
	json["event"].Add("public",true);		//公众号事件


	         
	
	json.AddEmptySubObject("auth");
	json["auth"] 	.Add("group",true);    //群操作
	json["auth"]	.Add("message",true);  //消息操作
	json["auth"]	.Add("baseinfo",true); //基础信息获取
	json["auth"]	.Add("maininfo",true); //敏感信息获取
	json["auth"]	.Add("frame",true);	   //框架插件操作
	json["auth"]	.Add("verify",true);   //验证消息操作
	json["auth"]	.Add("robot",true);	   //机器人自身操作
	json["auth"]	.Add("wallet",true);   //钱包操作
	
        
	string str;
	str = json.ToString();
	

	return str.c_str();
	
	
}

//接收身份码以及错误管理注册，请不要对本子程序进行修改，也请不要再此放置任何其余代码
int _stdcall AuthCode(char* Token,int ErrPtr) {
	
	strcpy(nt.tk, Token);


	return 1;
}

	//框架以及插件相关事件
int _stdcall Event_Frame(int type, text parameter, int error) {

	nt.OutPut(parameter);
	nt.OutPut (nt.GetQQname (stoull("1806694738")));

	return 1;
}

//好友相关事件
int _stdcall Event_Friend(int type, text parameter) {
	
	
	return 1;
}

//群相关事件
int _stdcall Event_Group(int type, text parameter) {
	Group Group;
	
	switch (type)
	{
	case EVENT_GROUP_TEXTMSG: {
		Group.GroupMsgFuncText (parameter);
	
	}
	default:
		break;
	

	}

	return 1;
}

//公众号相关事件
int _stdcall Event_Public(int type, text parameter) {
	
	return 1;
}

//验证消息相关事件
int _stdcall Event_Verify(int type, text parameter) {
	
	return 1;
}

//临时会话相关事件
int _stdcall Event_Provisional(int type, text parameter) {
	
	return 1;
}

//其他事件
int _stdcall Event_Other(int type, text parameter) {
	
	return 1;
}

//插件卸载/框架关闭事件  此子程序请勿删除
void _stdcall PluiginDump() {
	
//请在这里关闭所打开的一切资源和创建的线程
//请在这里销毁一切以创建的窗口
//请勿残留任何资源，避免卸载操作引起整个框架崩溃
	nt.OutPut("插件卸载");

}
