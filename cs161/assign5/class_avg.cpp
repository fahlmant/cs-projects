#include <iostream>
#include <stdlib.h>
#include <stdio.h>
 
using namespace std;

void check_letter(char letter, int num, double &score, int &final_check);
double quiz(int num);
double test(int num);
double assignment(int num);
double lab(int num);
double final(int &final_check);
double calc_avg(int sum, int num);
void print_class_avg(int arg_count, double &score, int &final_check);
void print_error_message();
int check_num(int num);

int main(int argc, char *argv[]){
	
	double score = 0;	
	int num,  sum, final_check = 0;
	if(argc >= 9){
		for(int i = 0; i < argc; i++){
			for(int j = 0; j < 2; j++){
				if(i < argc - 1){
					if( argv[i+1][0] == '1' && argv[i+1][1] == '0'){
						num = 58;
					}			
					else{num = argv[i+1][0];}
				}
				else {num = 0;}
				check_letter(argv[i][j], num, score, final_check);
			}
		}
	}
	else{print_error_message();}
	print_class_avg(argc, score, final_check);
	return 0;
}
		


void check_letter(char letter, int number, double &score, int &final_check)
{		
	int num = number - 48, x;
	int checker = check_num(num);
	if(letter == 'q'){
		if(checker == 1){
			score += quiz(num);
		}
		else {print_error_message();}
	}
	else if(letter == 't'){
	    if(checker == 1){
			score += test(num);
		}
		else{print_error_message();}
	}
	else if(letter == 'a' && checker == 1){
		if(checker == 1){
            score += assignment(num);
        }
        else{print_error_message();}
	}
	else if(letter == 'l' && checker == 1){
		if(checker == 1){
            score += lab(num);
        }
        else{print_error_message();}
	}
	else if(letter == 'f'){
		score += final(final_check);
	}
}

int check_num(int num){

	if(num > 10 || num <= 0){
	
		return 0;
	}
	else if(num <= 10 && num > 0){

		return 1;
	}
}

double quiz(int num){

	int quizzes[num], sum = 0;
	double weight = .1, avg, final;
	for(int i = 0; i < num; i++){
		cout << "Quiz " << i + 1 << ": " << endl;
		cin >> quizzes[i];
		sum += quizzes[i];
	}
	avg = calc_avg(sum, num);
	final = avg * weight; 
	return final;
		
}

double test(int num){

	int tests[num], sum = 0;
	double weight = .25, avg, final;
	for(int i = 0; i < num; i++){
		cout << "Test " << i + 1 << ": " << endl;
		cin >> tests[i];
		sum += tests[i];
	}
	avg = calc_avg(sum, num);
	final = avg * weight;
	return final;
}

double assignment(int num){

	int assignments[num], sum = 0;
	double avg, weight = .4, final;
	for(int i = 0; i < num; i++){
		cout << "Assignment " << i + 1 << ": " << endl;
		cin >> assignments[i];
		sum += assignments[i];
	}
	avg = calc_avg(sum, num);
	final = avg * weight;
	return final;
	
}

double lab(int num){

	int labs[num];
	double weight = .1, final = 0, score = 0, sum = 0, total = 0;
	total = 10 * num;
	for(int i = 0; i < num; i++){
		cout << "Lab " << i + 1 << ": " << endl;
		cin >> labs[i];
		sum += labs[i];
	}
	score = (sum/total) * 100;
	final = score * weight;
	return final;
}

double final(int &final_check)
{
	int sum;
	double weight = .15, final;
	cout << "Final: " << endl;
	cin >> sum;
	final = sum * weight;
	final_check = 1;
	return final;
}

double calc_avg(int sum, int num){

	double avg = (sum/num);
	return avg;
}

void print_error_message()
{
	cout << "This is not valid " << endl;
}
	
void print_class_avg(int arg_count, double &score, int &final_check)
{
	double total;
	if(final_check == 1){
		total = score;
		cout << "Final Grade: " << total << endl; 
	}
	else{
		total = (score/85) * 100;
		cout << "Final Grade: " << total << endl;
	}
	
}
