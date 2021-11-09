
class GroupMsgText
{
public:
	GroupMsgText ();
	~GroupMsgText ();
	void GroupMsgFuncText (text parameter);
	


private:
	inline void GroupMsgTextParse (text parameter,Group_Msg_text *Msg);
	bool GroupMsgTextFuzzy (string Group, string Msg);
};

class Group:public GroupMsgText
{
public:
	Group ();
	~Group ();
	

private:

};

GroupMsgText::GroupMsgText ()
{
}

GroupMsgText::~GroupMsgText ()
{
}

Group::Group ()
{
}

Group::~Group ()
{
}


 void GroupMsgText::GroupMsgFuncText (text parameter) {
	 Group_Msg_text *Msg = new  Group_Msg_text;
	 GroupMsgTextParse (parameter, Msg);


	 std::regex  *exp = new std::regex;
	 *exp = "^µãÔŞ\\s*(\\d+)$";
	 std::smatch result;
	 if (std::regex_match (Msg->msg, result,*exp)) {

		 nt.Favorite (stoull (result[1].str ()), 1);

		 
	 }

	delete Msg;
	delete exp;
}

 inline void GroupMsgText::GroupMsgTextParse (text parameter,Group_Msg_text *Msg) {
	 json j;
	 j.Parse (parameter);
	 Msg->qq = j ("qq");
	 Msg->group = j ("group");
	 Msg->msgId = j ("msgId");
	 Msg->msgNo = j ("msgNo");
	 Msg->msg = j ("msg");

 }
 
 
 bool GroupMsgText::GroupMsgTextFuzzy (string Group,string Msg) {
	 
	 fstream *fst = new fstream;
	 fst->open ("config.class", ios::in);
	 string *str = new string;
	 *fst >> *str;
	 fst->close ();
	 delete fst;
	 json *j = new json;
	 j->Parse (*str);
	 delete str;
	 for (int i = 0;i< (&(*j)["Class"]["Group"][Group]["fuzzy"])->GetArraySize ();i++) {
		 string *Ask = new string;
		 (&(*j)["Class"]["Group"][Group]["fuzzy"][i])->Get ("Ask", *Ask);
		 if (Msg.find (*Ask) != string::npos)
		 {
			 string *Reply = new string;
			 (&(*j)["Class"]["Group"][Group]["fuzzy"][i])->Get ("Reply", *Reply);
			 nt.SendMsg (stoull (Group), 2, Reply->c_str ());
			 delete j;
			 delete Ask;
			 delete Reply;
			 return true;
		 }
	 } 
	 return false;
 }