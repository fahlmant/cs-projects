#include <iostream>
#include <string>
#include <cmath>

using namespace std;
int i;
int j;

int question(){
 
  string input_run;
  string yes ("y");
  string no ("n");  
  cout << "Do you want to find the summation for the function?(y,n)" << endl;
  cin >> input_run;
  if(input_run.compare(yes)==0)
  {
     i = 1;
  }   
  else if(input_run.compare(no)==0)
  {
     cout<<"Goodbye"<<endl;
     i = 0;
  }
}

int looptype(){

  string input_loop;
  string f ("f");
  string w ("w");

  if(i == 1)
  {
        cout << "For loop or while loop? (f [for],w [while])" << endl;
  	cin >> input_loop;
	  if(input_loop.compare(f)==0)
	  {
  	      j = 0;	
  	  }  
	  else if (input_loop.compare(w)==0)
	  {
	     j = 1;
	  }
   }
   else if(i == 0)
   {
       return 0;
   }   

}

int floop()
{
   int n;
   int sum;
   int ifive;
   cout << "The function is (x^5 + 10) from 1 to n. Please insert a number n" << endl;
   cin >> n;
   
   for(int i = 1; i <= n; i++)
   { 
      ifive = (((i*i) * i)*i)*i;
      sum += (ifive + 10);
   }
   
   cout << sum << endl;   
}

int wloop()
{
   int i = 1;
   int n;
   int sum;
   cout << "The function is (x^5 + 10) from 1 to n. Please insert a number n" << endl;
   cin >> n;

   while (i <= n)
   {
      sum += (pow(i,5) + 10);
      i++; 
   }
   
   cout << sum << endl;


}

int main(){
	
	int x;	
   	cout << "Enter a nubmer x " << endl;
	cin >> x;
	int f = (pow(x,5) + 10);
	cout << " The function evaluated at " << x << " is " << f << endl;

	i = 1;	
	while(i==1)
	{
	   looptype();
	   if( j == 0)
	   {
	      floop();
	   }
	   else if (j == 1)
	   {
	      wloop();
	   }
	   question();  
	}

}
