 
class Closet : public Room {

    public:
        Closet()
        {
	    	name = "Closet";
            check = 0;
            stat = 1;
            stat2 = 1;
	     	object1 = "sword";
            object2 = "shield";
			objCheck = 1;
		    objCheck2 = 1;
    		swordCheck = 0;
	    	shieldCheck = 0;
        }
		int objCheck;
	    int objCheck2;
    	int swordCheck;
	    int shieldCheck;
	 	int stat2;
		string object1;
        string object2;
        void lookObj();
	 	void lookObj2();

};

void Closet::lookObj()
{
    if(stat = 1)
	{
		cout << "The sword is a small box that looks like it could break easily. " << endl;
	}
	else
		cout << "It's a sword. " << endl;
}

void Closet::lookObj2()
{
	if(stat2 == 1)
	{
		cout << "The shield is glowing. No matter how hard you try you can't touch it. There is a small, round slot that a jewel could fit in next to the shield. " << endl;
	}
	else
		cout << "It's a shield " << endl;
}