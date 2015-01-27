class Court : public Room{
	
	public:
		Court(){
		
			name = "Courtyard";
			check = 0;
			stat = 0;
			object1 = "jewel";
			objCheck = 1;
			jewelCheck = 1;
			jewelGet = 0;
		}
		string object1;
		int objCheck;
		int jewelCheck;
		int stat;
		int jewelGet;
		void lookObj();

};

void Court::lookObj()
{
	if(stat == 0)
	{
		cout << "The jewel is glowing. It looks like you need to wear something to grab it" << endl;
	}
	else
		cout << "It's a jewel" << endl;
}