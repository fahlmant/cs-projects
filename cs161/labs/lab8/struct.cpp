#include <iostream>
#include <string> 
#define NUM_MOVIES 5

using namespace std;

class Movie
{
public:
	void set_title(string title_to_set)
	{
		title = title_to_set;
	}
	void set_rating(string rating_to_set)
	{
		rating = rating_to_set;

	}
	void set_genre(string genre_to_set)
	{
		genre = genre_to_set;
	}
	void set_count(int count)
	{
		copies = count;
	}
	void get_title()
	{
		string title_to_set;
		cout << "Enter Title: " << endl;
		cin >> title_to_set;
		set_title(title_to_set);
	}
	void get_rating()
	{
		string rating_to_get;
		cout << "Enter Rating " << endl;
		cin >> rating_to_get;
		set_rating(rating_to_get);
		
	}
	void get_genre()
	{
		string genre_to_get;
		cout << "Enter Genre: " << endl;
		cin >> genre_to_get;
		set_genre(genre_to_get);
		
	}
	void get_count()
	{
		int count;
		cout << "Number of Copies: " << endl;
		cin >> count;	
		set_count(count);
	}
	void show_movie_info()
	{
		cout << "Title: " << title << endl;
		cout << "Rating " << rating << endl;
		cout << "Genre: " << genre << endl;
		cout << "Copies: " << copies << endl;
	}
	void rent_movie()
	{	
		copies = copies - 1;
	}

private:
	string title;
	int copies;
	string rating;
	string genre;
};

/***void set_movies(movie_record &record);
void get_movies(movie_record &record, string &genre);
void which_movies_to_view(string &genre); 
void get_movie_info(movie_record &record);
void movie_for_info(int &choice);
void rent_movie(movie_record &record);
***/

void add_movie_info(Movie redbox[]);
void read_info(Movie redbox[]);
int main()
{
	int choice, choice2, rent_check;
	string genre;
	Movie redbox[NUM_MOVIES];
	add_movie_info(redbox);
	read_info(redbox);	

/***	for(int i = 0; i < 5; i++)
	{
		set_movies(record[i]);
	}
	which_movies_to_view(genre);
	for(int i = 0; i < 5; i++)
	{
		get_movies(record[i], genre);		
	}
	movie_for_info(choice2);
	get_movie_info(record[choice2]);
	cout << "Do you want to rent it? (1 for yes, anything for no)" << endl;
	cin >> rent_check;
	if(rent_check == 1)
	{
		cout << "Rented: " << record[choice2].title << endl;
		cout << "Copies " << record[choice2].copies << endl;
		rent_movie(record[choice2]);
		cout << "Copies: " << record[choice2].copies << endl;
	}
	else
	{
		return 0;
	}***/
	return 0;
	
}

void add_movie_info(Movie redbox[])
{
	string title, rating, genre;
	int count;
	for(int i = 0; i < NUM_MOVIES; i++)
	{
		redbox[i].get_title();
		redbox[i].get_rating();
		redbox[i].get_genre();
		redbox[i].get_count();
	}
}

void read_info(Movie redbox[])
{
	for(int i = 0; i < NUM_MOVIES; i++)
	{
		redbox[i].show_movie_info();
		cout << endl;
	}

}
/***
void set_movies(movie_record &record)
{
	cout << "Movie Title: " << endl;
	cin >> record.title;
	cout << "Number of copies: " << endl;
	cin >> record.copies;
	cout << "Rating: " << endl;
	cin >> record.rating;
	cout << "Description: " << endl;
	cin >> record.descript;
	cout << "Genre: "<< endl;
	cin >> record.genre;
}

void which_movies_to_view(string &genre)
{
	cout << "What's the Genre of the movie you want to view?" << endl;
	cin >> genre;
}

void get_movies(movie_record &record, string &genre)
{
	if(record.genre.compare(genre) == 0)
	{
		cout << "Titles: " <<  record.title << endl;
	}
}

void movie_for_info(int &choice)
{
	cout << "What's the index of the movie you want info on?" << endl;
	cin >> choice;
}

void get_movie_info(movie_record &record)
{	
	cout << "Title: " << record.title << endl;	
	cout << "Number of Copies: " << record.copies << endl;
	cout << "Rating: " << record.rating << endl;
	cout << "Description: " << record.descript << endl;
	cout << "Genre: " << record.genre << endl;

}

void rent_movie(movie_record &record)
{
	record.copies -= 1;
}
***/
