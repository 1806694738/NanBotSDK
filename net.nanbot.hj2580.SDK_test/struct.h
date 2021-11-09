#pragma once
#ifndef PCH_H

#include "pch.h"


#endif



//��ǩ��Ϣ
struct nt_Label {
	int ID;//ID
	string name;//����
	int praise;//������

};


//Ⱥ��Ա����
struct nt_GroupMemberData {
	string name;//�ǳ�
	string card;//��Ƭ
	string title;//��Ծͷ��
	string intogroup;//��Ⱥʱ��
	string speak;//�����ʱ��
	string _title;//��ǰͷ��
	int perm;//Ȩ��
	string city;//����
	bool Friend;//�Ƿ����
	string FriendNote;//���ѱ�ע
};

//���Ͽ�
struct nt_Data
{
	string name;//�ǳ�
	string note;//��ע
	string email;//����
	int age;//����
	int gender;//�Ա�
	int level;//�ȼ�
	string state;//����
	string provinces;//ʡ��
	string city;//����
	long long praise;//��
	
	string signature;//ǩ��
	list< nt_Label> loops;//ȦȦ��
	list< nt_Label> label;//��ǩ
};


//�����б���Ϣ
struct nt_FriendsList
{
	string QQ;
	string name;//�ǳ�
	string note;//��ע
	string email;//����
};


//������״̬
struct nt_Robot_State
{
	int Receive;//������Ϣ��
	int Send;//������Ϣ��
	int Rate;//����
	int Time;//����ʱ��

};


//HTTP�ṹ
struct nt_http 
{
	string msg;
	int code;
	string head;
};


//Ⱥ��Ա�б���Ϣ
struct nt_GroupMemberList
{
	string QQ;//QQ��
	int age;//����
	string name;//�ǳ�
	string card;//��Ƭ
	string phone;//�ֻ�
	string email;//����
	string note;//��ע
	string active;//��Ծ�ȼ�
	string intogroup;//��Ⱥʱ��
	string speak;//�����ʱ��
	string title;//ͷ��
	string titletime;//ͷ�ε���ʱ��
};

//Ⱥ�б���Ϣ
struct nt_GroupList {
	string group;//Ⱥ��
	string groupname;//Ⱥ��
	string notice;//Ⱥ����
	int grouplevel;//Ⱥ�ȼ�
	int numpeople;//��ǰ����
	int biggpeople;//�������
	string groupman;//Ⱥ��QQ
	string intogroup;//��Ⱥʱ��

};

//Ⱥ������Ϣ
struct nt_GroupData {
	string groupname;//Ⱥ��
	string groupman;//Ⱥ��QQ
	int numpeople;//��ǰ����
	int biggpeople;//�������
	string Label;//Ⱥ��ǩ
	list<string> admin;//����Ա�б�
};


struct  Group_Msg_text
{

	string qq;
	string group;
	string msgId;
	string msgNo;
	string msg;

};