
#ifndef SDK_H
#include "sdk.h"
NanApi nt;
#include "GroupFunc.h"
#endif









/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//���������Ϣ�����޸Ĵ��ӳ�����ز������˴��벻Ҫ�����κζ������ ���ӳ�������ɾ��
text _stdcall GenerateInfo() {

	


	
	json json;
	json.AddEmptySubObject("info");
	json["info"].Add("name","classȺ��ϵͳ");//�������

	json["info"].Add("author","test");//�������

	json["info"].Add("verindex","1.0");//����ڲ��汾

	json["info"].Add("vername","1.0");//�����ʾ�汾

	json["info"].Add("id","net.nanbot.hj2580.SDK_test");//���ID
	//����ļ��������� ���ID.nt.dll �����������������ӵ��ļ�����ӦΪ net.nanbot.hj2580.SDK_test.nt.dll

	json["info"].Add("url","");// ������HTTP��ַ�����û��������ϵ���ߡ������ת���õ�ַ 
	//������δ���ã�����ϵ����

	json["info"].Add("describe","����һ�����Բ��");
	// ֧��HTML�Ͷ���
	json["info"].Add("priority", NanBot_PRIORITY_GIVE);
	 
	json["info"].Add("bg","");
	// ��ʾ�ı���ͼƬ�ļ��������ڳ�ʼ���н�����ͼƬд�� ��\webui\imgs\���ļ����У��硰net.nanbot.test.jpg��
	json.AddEmptySubObject("sdk");
	json["sdk"].Add("ver",1);

	


	json.AddEmptySubObject ("event");                
	json["event"].Add("group", true);		//Ⱥ�¼� 
	json["event"].Add("frame",true);			//��ܺͲ���¼� 
	json["event"].Add("verify",true);		//��֤�¼� 
	json["event"].Add("friend",true);		//�����¼� 
	json["event"].Add("provisional",true);	//��ʱ�¼� 
	json["event"].Add("other",true);			//�����¼� 
	json["event"].Add("public",true);		//���ں��¼�


	         
	
	json.AddEmptySubObject("auth");
	json["auth"] 	.Add("group",true);    //Ⱥ����
	json["auth"]	.Add("message",true);  //��Ϣ����
	json["auth"]	.Add("baseinfo",true); //������Ϣ��ȡ
	json["auth"]	.Add("maininfo",true); //������Ϣ��ȡ
	json["auth"]	.Add("frame",true);	   //��ܲ������
	json["auth"]	.Add("verify",true);   //��֤��Ϣ����
	json["auth"]	.Add("robot",true);	   //�������������
	json["auth"]	.Add("wallet",true);   //Ǯ������
	
        
	string str;
	str = json.ToString();
	

	return str.c_str();
	
	
}

//����������Լ��������ע�ᣬ�벻Ҫ�Ա��ӳ�������޸ģ�Ҳ�벻Ҫ�ٴ˷����κ��������
int _stdcall AuthCode(char* Token,int ErrPtr) {
	
	strcpy(nt.tk, Token);


	return 1;
}

	//����Լ��������¼�
int _stdcall Event_Frame(int type, text parameter, int error) {

	nt.OutPut(parameter);
	nt.OutPut (nt.GetQQname (stoull("1806694738")));

	return 1;
}

//��������¼�
int _stdcall Event_Friend(int type, text parameter) {
	
	
	return 1;
}

//Ⱥ����¼�
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

//���ں�����¼�
int _stdcall Event_Public(int type, text parameter) {
	
	return 1;
}

//��֤��Ϣ����¼�
int _stdcall Event_Verify(int type, text parameter) {
	
	return 1;
}

//��ʱ�Ự����¼�
int _stdcall Event_Provisional(int type, text parameter) {
	
	return 1;
}

//�����¼�
int _stdcall Event_Other(int type, text parameter) {
	
	return 1;
}

//���ж��/��ܹر��¼�  ���ӳ�������ɾ��
void _stdcall PluiginDump() {
	
//��������ر����򿪵�һ����Դ�ʹ������߳�
//������������һ���Դ����Ĵ���
//��������κ���Դ������ж�ز�������������ܱ���
	nt.OutPut("���ж��");

}
