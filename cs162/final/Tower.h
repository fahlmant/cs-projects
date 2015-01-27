
class Tower: public Room{

    public:
        Tower()
        {
			name = "Tower";
            check = 0;
            stat = 1;
	     	object1 = "crowbar";
            object2 = "glove";
    		objCheck = 1;
		    objCheck2 = 1;
		    gloveCheck = 0;
			stat1 = 0;
			stat2 = 0;
       }
		int objCheck;
		int objCheck2;
		int gloveCheck;
		int stat1;
		int stat2;
		string object1;
        string object2;
        void lookObj();
	 	void lookObj2();
		
};

void Tower::lookObj()
{
	cout << "It's a crowbar " << endl;
}

void Tower::lookObj2()
{
	if(stat == 1)
	{
		cout << "The glove is up on a shelf just out of your reach. You need to be slightly taller. " << endl;
	}
	else
		cout << "The glove is right at your height. " << endl;
}