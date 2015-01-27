class Throne : public Room{

	public:
		Throne()
		{
			name = "Throneroom";
			check = 0;
			stat = 0;
			object1 = "crown";
			objCheck = 1;
			crownCheck = 1;
			crownGet = 0;

		}
		string object1;
		int objCheck;
		int crownCheck;
		int stat;
		int crownGet;
		void lookObj();
};

void Throne::lookObj()
{
	if(stat == 0)
	{
		cout << "There is a crown in a large glass case" << endl;
	}
	else
		cout << "It's a crown" << endl;

}