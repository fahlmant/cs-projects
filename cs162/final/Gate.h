class Gate : public Room
{
	public:
		Gate()
		{
			name = "Gate room";
			object1 = "gate";
		}
		string object1;
		void lookObj();
};

void Gate::lookObj()
{
	cout << "It's a gate with a keyhole. It leads to the outside world! " << endl;
}