
#ifndef SDK_H
#include "sdk.h"

#endif


text NanApi::nt_callFuction (text parameter) {


	typedef text (*Func)(text);
	Func func;

	func = (Func)GetProcAddress (hdll, "nt_callFuction");


	if (func == NULL) {
		MessageBoxA (GetForegroundWindow (), "��̬���ӿ�ָ������\"nt_callFuction\"������", "��ʾ", 0);
		return"";


	}

	return func (parameter);
}


NanApi::NanApi ()
{

	hdll = LoadLibrary ("ntapi.dll");
	if (hdll == NULL)
	{
		MessageBoxA (GetForegroundWindow (), "Ŀ�궯̬���ӿ����ʧ�ܡ�ntapi.dll��", "��ʾ", 0);

	}
}


NanApi::~NanApi ()
{

	FreeLibrary (hdll);
}


/*
	��������:OutPut

	���ܸ���:�����־

	��������:1

	�����б�:

		1.
			����:text �ı�
			����:val
			˵��:�������


	����ֵ:��

	ע������:��

	ʹ��˵��:�ڿ����־���һ������

*/
void NanApi::OutPut (text val) {

	json j;

	j.Add ("func", "OutPut");
	j.Add ("tk", tk);
	j.Add ("val", val);
	string s = j.ToString ();
	//MessageBoxA(GetForegroundWindow(), s.c_str(), "��ʾ", 0);
	j.Clear ();
	nt_callFuction (s.c_str ());

}


/*
	��������:SendMsg

	���ܸ���:�û����˷���һ����Ϣ

	��������:5

	�����б�:
		1.
			����:long ������
			����:target
			˵��:Ŀ�����(������Ⱥ��Ҳ�����Ǻ����˺�)

		2.
			����:int ����
			����:msgType
			˵��:��Ϣ���� �� ��Ϣ����_��

		3.
			����:text �ı�
			����:msg
			˵��:Ԥ������Ϣ ֧����ͨ/xml/json�����ı�

		4.
			����:int ����
			����:type
			˵��:�������� Ĭ��Ϊ1

			ֵΪ1ʱΪ���ͺ�����Ϣ
			ֵΪ2ʱΪ����Ⱥ��Ϣ

		5.

			����:bool �߼���
			����:anonymous
			˵��:�Ƿ�Ϊ��������  Ĭ��Ϊ��

			�ò��������ڲ���4ֵΪ2ʱ��Ч


	����ֵ:��

	ע������:

	������5Ϊ��ʱ
	���û�п���������Ϣ�ᷢ��ʧ�ܣ�������Ϣ����ʱ�޷����˻�������Ϣ��������Ϣ���ᱻ�յ�һ�δ����������ע���ܣ�������ѭ����

	ʹ��˵��:

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
	//MessageBoxA(GetForegroundWindow(), s.c_str(), "��ʾ", 0);
	nt_callFuction (s.c_str ());

	j.Clear ();


}


/*
	��������:creategroup

	���ܸ���:����Ⱥ��

	��������:1

	�����б�:
		1.
			����:text �ı�
			����:name
			˵��:����Ⱥ�ĵ�����

	����ֵ:lomg long

	����ֵ˵��:
		�ɹ�����Ⱥ�ţ�ʧ�ܷ���0

	ע������:��

	ʹ��˵��:����Ⱥ��

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
	��������:sendCommandPacket

	���ܸ���:���Ϳ�����

	��������:5

	�����б�:
		1.
			����:long
			����:obj
			˵��:Ŀ�����
			���Ŀ���Ǻ��Ѿ��Ǻ���Q�ţ���Ⱥ����Ⱥ��

		2.
			����:long
			����:num
			˵��:�������

		3.
			����:text �ı�
			����:money
			˵��:������
			"1.23" ��ʾ1��Ǯ��ë����

		4.
			����:text �ı�
			����: brief
			˵��:����

		5.
			����:int ����
			����:type
			˵��:��������
			1���� 2Ⱥ

	����ֵ:text �ı�

	����ֵ˵��:
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

	xxxxxxxxxxxxxxx����Ϊ�ֶ�������:
	//////////////////////////////////////////////////////////////////////////
	ע������:��

	ʹ��˵��:���Ϳ�����

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
	��������:SendTempMsg

	���ܸ���:������ʱ��Ϣ

	��������:4

	�����б�:
		1.
			����:long ������
			����:group
			˵��:Ⱥ��

		1.
			����:long ������
			����:qq
			˵��:QQ��

		1.
			����:text �ı�
			����:content
			˵��:��Ϣ����

		1.
			����:int ����
			����:type
			˵��:��Ϣ���� �� ��Ϣ��ʽ_��

	����ֵ:��

	����ֵ˵��:

	ע������:��

	ʹ��˵��:����Ⱥ��ʱ��Ϣ

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
	��������:sendExclusivePacket

	���ܸ���:����ƴ�������

	��������:4

	�����б�:
		1.
			����:long
			����:group
			˵��:Ŀ��Ⱥ��

		2.
			����:long
			����:num
			˵��:�������

		3.
			����:text
			����:money
			˵��:������
			"1.23" ��ʾ1��Ǯ��ë����
		4.
			����:text
			����:brief
			˵��:�������

	����ֵ:text

	����ֵ˵��:
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

	xxxxxxxxxxxxxxx����Ϊ�ֶ�������:
	//////////////////////////////////////////////////////////////////////////

	ע������:��

	ʹ��˵��:����ƴ�������

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
	��������:sendSimplePacket

	���ܸ���:������ͨ���

	��������:6

	�����б�:
		1.
			����:long
			����:obj
			˵��:Ŀ�����
			���Ŀ���Ǻ��Ѿ��Ǻ���Q�ţ���Ⱥ����Ⱥ��

		2.
			����:long
			����:num
			˵��:�������

		3.
			����:text �ı�
			����:money
			˵��:������
			"1.23" ��ʾ1��Ǯ��ë����

		4.
			����:text �ı�
			����: brief
			˵��:����

		5.
			����:int ����
			����:type
			˵��:��������
			1���� 2Ⱥ 3Ⱥ��ʱ�Ự
		6.
			����:long
			����:group
			˵��:��ʱȺ��
			�����������ΪȺ��ʱ�Ự(3)��Ч�ұ��봫��

	����ֵ:text �ı�

	����ֵ˵��:
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

	xxxxxxxxxxxxxxx����Ϊ�ֶ�������:
	//////////////////////////////////////////////////////////////////////////
	ע������:��

	ʹ��˵��:������ͨ���

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
	��������:SendVoice

	���ܸ���:��������

	��������:4

	�����б�:
		1.
			����:int
			����:type
			˵��:��������
			1Ϊ���� 2ΪȺ
		2.
			����:long
			����:target
			˵��:Ŀ�����
			���ѵ�QQ�Ż���Ⱥ��

		3.
			����:text
			����:content
			˵��:��������
			������ ������ַ / ��������·�� / �ѻ�����data\image�е��ļ� / ����Base64(���Ƽ�)
		4.
			����:int
			����:time
			˵��:����ʱ��
			��λ���룬����������߹̶�������������縺��������ֵ���󣩣�����ȷ����ֵ���ܵ��������޷�����

	����ֵ:��

	����ֵ˵��:

	ע������:

	���������� amr ��ʽ���� amr ��ʽ�޷����ͣ�������ת��

	ʹ��˵��:
	����һ��������Ϣ��ָ������
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
	��������:sendSimplePacket

	���ܸ���:�����������

	��������:6

	�����б�:
		1.
			����:long
			����:obj
			˵��:Ŀ�����
			���Ŀ���Ǻ��Ѿ��Ǻ���Q�ţ���Ⱥ����Ⱥ��

		2.
			����:long
			����:num
			˵��:�������

		3.
			����:text �ı�
			����:money
			˵��:������
			"1.23" ��ʾ1��Ǯ��ë����

		4.
			����:text �ı�
			����: brief
			˵��:����

		5.
			����:int ����
			����:type
			˵��:��������
			1���� 2Ⱥ

	����ֵ:text �ı�

	����ֵ˵��:
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

	xxxxxxxxxxxxxxx����Ϊ�ֶ�������:
	//////////////////////////////////////////////////////////////////////////
	ע������:��

	ʹ��˵��:�����������

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
	��������:sendSimplePacket1

	���ܸ���:����ר����

	��������:6

	�����б�:
		1.
			����:long
			����:obj
			˵��:Ŀ�����
			���Ŀ���Ǻ��Ѿ��Ǻ���Q�ţ���Ⱥ����Ⱥ��

		2.
			����:long
			����:obj
			˵��:�������

		3.
			����:text �ı�
			����:money
			˵��:������
			"1.23" ��ʾ1��Ǯ��ë����

		4.
			����:text �ı�
			����: brief
			˵��:����

		5.
			����:int ����
			����:type
			˵��:��������
			1���� 2Ⱥ 3Ⱥ��ʱ�Ự
		6.
			����:long
			����:group
			˵��:��ʱȺ��
			�����������ΪȺ��ʱ�Ự(3)��Ч�ұ��봫��

	����ֵ:text �ı�

	����ֵ˵��:
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

	xxxxxxxxxxxxxxx����Ϊ�ֶ�������:
	//////////////////////////////////////////////////////////////////////////
	ע������:��

	ʹ��˵��:����ר����

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
	��������:TransferAccounts

	���ܸ���:����ת��

	��������:3

	�����б�:
		1.
			����:long
			����:obj
			˵��:Ŀ�����

		2.
			����:text
			����:money
			˵��:���
			"1.23" ��ʾ1��Ǯ��ë����

		3.
			����:text
			����:brief
			˵��:ת��˵��

	����ֵ:text

	����ֵ˵��:

	ע������:

	ʹ��˵��:��ĳ�����ѽ���ת�ˣ�����Json�ı�

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
	��������:GetP_skey

	���ܸ���:ȡp_skey

	��������:0

	�����б�:


	����ֵ:text

	����ֵ˵��:����ֵΪjson

	ע������:

	ʹ��˵��:��ȡ�ѵ�¼�˺ŵ�P_skey��

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
	��������:GetQQname

	���ܸ���:ȡQQ�ǳ�

	��������:1

	�����б�:
		1.
			����:llong
			����:QQ
			˵��:QQ��

	����ֵ:text

	����ֵ˵��:�����ǳ�

	ע������:

	ʹ��˵��:�ǿ��API��ģ������ͨ�� HTTP���ļ� ��ʽͨ��HTTPЭ���ȡĳ�������QQ�ǳ�

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
	��������:GetSummaryCard

	���ܸ���:ȡ�������Ͽ�

	��������:1

	�����б�:
		1.
			����:llong
			����:QQ
			˵��:QQ��

	����ֵ:nt_Data

	����ֵ˵��:����nt_Data�ṹ��

	ע������:

	ʹ��˵��:

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
	��������:GetFriendList

	���ܸ���:ȡ�����б�

	��������:��

	�����б�:


	����ֵ:list<nt_FriendsList>

	����ֵ˵��:

	ע������:

	ʹ��˵��:

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
	��������:Getskey

	���ܸ���:ȡskey

	��������:0

	�����б�:


	����ֵ:text

	����ֵ˵��:����ֵΪjson

	ע������:

	ʹ��˵��:��ȡ�ѵ�¼�˺ŵ�skey��

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
	��������:GetRobotName

	���ܸ���:ȡ�������ǳ�

	��������:��

	�����б�:


	����ֵ:text

	����ֵ˵��:

	ע������:

	ʹ��˵��:

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
	��������:GetRobotQQ

	���ܸ���:ȡ�������˺�

	��������:��

	�����б�:


	����ֵ:text

	����ֵ˵��:

	ע������:

	ʹ��˵��:

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
	��������:GetRobotStatus

	���ܸ���:ȡ������״̬

	��������:

	�����б�:


	����ֵ:nt_Robot_State

	����ֵ˵��:

	ע������:

	ʹ��˵��:��ȡ�����˵�������Ϣ����������ʱ�����շ����ʣ��շ�����

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
	��������:GetFrameVer

	���ܸ���:ȡ��ܰ汾

	��������:��

	�����б�:


	����ֵ:text

	����ֵ˵��:

	ע������:

	ʹ��˵��:

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
	��������:GetGroupMemberList
	
	���ܸ���:ȡȺ��Ա�б�
	
	��������:1
	
	�����б�:
		1.
			����:llong
			����:group
			˵��:Ⱥ��
			
	����ֵ:list<nt_GroupMemberList>
	
	����ֵ˵��:��ȡĳ��Ⱥ������Ⱥ��Ա
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:GetGroupMemberInfo
	
	���ܸ���:ȡȺ��Ա��Ϣ
	
	��������:2
	
	�����б�:
		1.
			����:llong
			����:group
			˵��:Ⱥ��
		2.
			����:llong
			����:QQ
			˵��:QQ��
					
						
			
	����ֵ:nt_GroupMemberData
	
	����ֵ˵��:ĳ��Ⱥ��Ⱥ��Ա������Ϣ
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:GetGroupList
	
	���ܸ���:ȡȺ�б�
	
	��������:��
	
	�����б�:
	
			
	����ֵ:list<nt_GroupList> 
	
	����ֵ˵��:��ȡ�����˵�Ⱥ�б�
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:GetGroupInfo

	���ܸ���:ȡȺ��Ϣ

	��������:1

	�����б�:
		1.
			����:llong
			����:group
			˵��:Ⱥ��

	����ֵ:nt_GroupData

	����ֵ˵��:��ȡĳ��Ⱥ��������Ϣ����������Ա�б�

	ע������:

	ʹ��˵��:

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
	��������:HttpCurl 
	
	���ܸ���:��ҳ����Curl
	
	��������:7
	
	�����б�:
		1.
			����:text
			����:url
			˵��:�����ַ
		2.
			����:int
			����:get
			˵��:����ʽ
			0 GET��1 �ı���POST��2 �ֽڼ���POST��Ĭ��Ϊ0
		3.
			����:text
			����:posttext
			˵��:POST����
				����Ϊ1ʱ����	
		4.
			����:text
			����:post
			˵��:POST����_ʮ�������ı�
			����Ϊ2ʱ����
		5.
			����:text
			����:Cookies
			˵��:Cookies
		6.
			����:text
			����:UserAgent
			˵��:UserAgent
		7.
			����:text
			����:Header
			˵��:����Header
	
	����ֵ:nt_http
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:InviteFriendInGroup 
	
	���ܸ���:������ѽ�Ⱥ
	
	��������:2
	
	�����б�:
		1.
			����:llong 
			����:group
			˵��:Ⱥ��
		2.
			����:list<llong> 
			����:QQ
			˵��:Ŀ���������
					
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:LikeLable 
	
	���ܸ���:�ñ�ǩ����
	
	��������:2
	
	�����б�:
		1.
			����:llong
			����:QQ
			˵��:QQ��
		2.
			����:llong
			����:ID
			˵��:��ǩID
					
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetMsgSpeed
	
	���ܸ���:�÷���Ƶ������
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetFriendName
	
	���ܸ���:�ú��ѱ�ע
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:FriendEventProcessing
	
	���ܸ���:�ú�����֤��Ϣ����
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetBirthday
	
	���ܸ���:�û����˳�������
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetCover
	
	���ܸ���:�û����˷���
	
	��������:
	
	�����б�:
		1.
			����:
			����: content
			˵��:������ ͼƬ��ַ / ��������·�� / �ѻ�����data\image�е��ļ� / ͼƬBase64(���Ƽ�)
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetNick
	
	���ܸ���:�û������ǳ�
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetSign
	
	���ܸ���:�û�����ǩ��
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetAvatar
	
	���ܸ���:�û�����ͷ��
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetSex
	
	���ܸ���:�û������Ա�
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:ShowAlert
	
	���ܸ���:�ÿ�ܶԻ���
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:�ڿ���е���һ���Ի��򣬶Ի�����Ҫ�û��ֶ�ȷ��
	
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
	��������:ShowTips
	
	���ܸ���:�ÿ����ʾ��
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:�ڿ�ܽ���ײ�����һ����ʾ����ʾ����Զ��رգ������û���һ���ܿ���
	
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
	��������:Favorite
	
	���ܸ���:����Ƭ����
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:ShutUpAnonymous
	
	���ܸ���:��������Ա����
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetAnonymousSwitch
	
	���ܸ���:���������쿪��
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:LikeIt
	
	���ܸ���:��ȦȦ����
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:ShutUpGroup 
	
	���ܸ���:��ȫȺ����
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:ShutUp
	
	���ܸ���:��Ⱥ��Ա����
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetGroupCard
	
	���ܸ���:��Ⱥ��Ա��Ƭ
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:KickMember
	
	���ܸ���:��Ⱥ��Ա�Ƴ�
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetAdminStatus
	
	���ܸ���:��Ⱥ����Ա״̬
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetGroupName
	
	���ܸ���:
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:setGroupCardRule
	
	���ܸ���:��Ⱥ�ǳƹ���
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:ExitGroup
	
	���ܸ���:��Ⱥ�˳����ɢ
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetGroupNotifyType
	
	���ܸ���:��Ⱥ��Ϣ���ѷ�ʽ
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:setLuckyChar
	
	���ܸ���:��Ⱥ�����ַ�����
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:GroupEventProcessing
	
	���ܸ���:��Ⱥ��֤��Ϣ����
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetHonestSwitch
	
	���ܸ���:��̹��˵����
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:touchTwice
	
	���ܸ���:��ͷ��˫��
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:DrawGroupMsg
	
	���ܸ���:����Ϣ����
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:setEssence
	
	���ܸ���:
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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
	��������:SetMemberTitle
	
	���ܸ���:��ר��ͷ��
	
	��������:
	
	�����б�:
		1.
			����:
			����:
			˵��:
			
	����ֵ:
	
	����ֵ˵��:
	
	ע������:
	
	ʹ��˵��:
	
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














