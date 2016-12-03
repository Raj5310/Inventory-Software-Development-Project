//Programmer: Raj Pokhrel

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include<algorithm>
using namespace std;

//prototype the functions
//input data from the file
bool get_data(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost);
//sort the data using shell short
void sort(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost);
//Ask the user for Part Number
string get_target();
//Use the Part Number to do the binary search
int bin_search(string key, const vector<string>& part_number);
//If the Part Number is not on the file ask user for more data
void get_more_data(char& class_in, int& part_ohb_in, double& part_cost_in);
//insert all the data to the file
void insert_data(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost, string part_in, char class_in, int part_ohb_in, double part_cost_in);
//Display the result 
void display(const vector <string>& part_number, const vector <char>& part_class, const vector <int>& part_ohb, const vector <double>& part_cost, int finder);
// Display number of searches
void print_stats(int searches, int good, int bad);
//Store the new data to the file
void put_data(const vector <string>& part_number, const vector <char>& part_class, const vector <int>& part_ohb, const vector <double>& part_cost);
template <class CType>
void swapper(CType& a, CType & b)
{
	CType temp;
	temp = a;
	a = b;
	b = temp;
}


int main()
{

	vector<string>part_number;
	vector<char>part_class;
	vector<int> part_ohb;
	vector<double>part_cost;
	bool openfile;
	string target;
	char class_in;
	int ohb_in;
	double cost_in;
	int find_name, num_search = 0,num_view = 0 , num_adds = 0 ;

	//check and see if the file opens or not
	openfile = get_data(part_number, part_class, part_ohb, part_cost);

	//if the file fails to open display cannot open the file
	if (!openfile) 
	{
		cout << "Cannot open the file";
	}
	//else continue on the next function
	else
	{
		//sort the data in order using parts file
		sort(part_number, part_class, part_ohb, part_cost);	
		do
		{	//Ask the user for Parts Numbers 
			target = get_target();	
			//Continue to ask for Parts Number until the user enters Done
			if (target != "Done")
			{
				//search to see if the file contains the user input
				find_name = bin_search(target, part_number);
				//add 1 everytime you do the search
				num_search++;

				if (find_name != -1)
				{
					//call the display function
					display(part_number, part_class, part_ohb, part_cost, find_name);
					num_view++;
				}

				else
				{
					cout << "The Part is not on the file" << endl;
					//call get more data function
					get_more_data(class_in, ohb_in, cost_in);
					//call insert data
					insert_data(part_number, part_class, part_ohb, part_cost, target ,class_in,ohb_in,cost_in);
					num_adds++;
					cout << "This Part is added" <<"\n" <<endl;
				}
			}
	} while (target != "Done");
	//call the put data funtion 
	put_data(part_number, part_class, part_ohb, part_cost);
	//call the print status function
	print_stats(num_search, num_view, num_adds);
	} 	
}

		
bool get_data(vector<string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost)
{
	bool status = true;
	string item_name;
	char item_class;
	int item_ohb;
	double item_cost;
	// Create and open the data file
	ifstream inputfile;
	inputfile.open("parts.txt");
	//Check if the file will open or not
	if (inputfile.fail())
	{
		status = false;
		cout << "Cannot open the file";
	}
	else
	{
		status = true;
		//input the data into the vector
		while (inputfile >> item_name >> item_class >> item_ohb >> item_cost)
		{
				part_number.push_back(item_name);
				part_class.push_back(item_class);
				part_ohb.push_back(item_ohb);
				part_cost.push_back(item_cost);		
		}
	}
	//close the file
	inputfile.close();
	return status;
}
void sort(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost)
{

		//Sort all the on the file in order using shell sort
		int i, j, increment;
		string temp_name;
		char temp_class;
		int temp_ohb;
		double temp_cost;
		increment = 3;

		while (increment > 0)
		{
			for (i = 0; i < part_number.size(); i++)
			{
				j = i;
				temp_name = part_number[i];
				temp_class = part_class[i];
				temp_ohb = part_ohb[i];
				temp_cost = part_cost[i];
				while ((j >= increment) && (part_number[j - increment]> temp_name))
				{
					swapper(part_number[j], part_number[j - increment]);
					swapper(part_class[j], part_class[j - increment]);
					swapper(part_ohb[j], part_ohb[j - increment]);
					swapper(part_cost[j], part_cost[j - increment]);
					j = j - increment;
				}
				part_number[j] = temp_name;
				part_class[j] = temp_class;
				part_ohb[j] = temp_ohb;
				part_cost[j] = temp_cost;
			}
			if (increment / 2 != 0)
				increment = increment / 2;
			else if (increment == 1)
				increment = 0;
			else
				increment = 1;
			
		}
}

string get_target()
{
	string target_name;
	//Get user input
	cout << "Enter the part number to search for and enter done if you want to stop "<<endl;
	cin >> target_name;
	return target_name;
}

int bin_search(string key, const vector<string>& part_number)
{
	
	//compare the user input to the part number using binary search
	int last = part_number.size() - 1;
	int first = 0;
	int position;
	position = (last + first) / 2;
	
	while (last >= first && part_number[position] != key)
	{

		if (part_number[position] < key)
		{
			first = position + 1;
		}
		else if (part_number[position]>key)
		{
			last = position - 1;
		}
		position = (last + first) / 2;

	}
	if (part_number[position] != key)
	{
		position = -1;
	}
	return position;
}

void get_more_data(char& class_in, int& part_ohb_in, double& part_cost_in)
{
	//Ask user to enter Part class
	cout << "Enter the part class: ";
	cin >> class_in;
	//Ask user to enter on hand balance
	cout << "Enter the amound of item: ";
	cin >> part_ohb_in;
	//Ask user to enter Part cost
	cout << "Enter the cost of the item: ";
	cin >> part_cost_in;
}

void insert_data(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb,vector <double>& part_cost, string part_in, char class_in, int part_ohb_in, double part_cost_in)
{
	int i;
	i= part_number.size() - 1,
	//Add a new cell in the vector
	part_number.resize(part_number.size() + 1);
	part_class.resize(part_class.size() + 1);
	part_ohb.resize(part_ohb.size() + 1);
	part_cost.resize(part_cost.size() + 1);
	
	//inset the part number, class, on hand balance, and cost in the right place
	while (i >= 0 && part_in < part_number[i])

	{
		part_number[i + 1] = part_number[i];
		part_class[i + 1] = part_class[i];
		part_ohb[i + 1] = part_ohb[i];
		part_cost[i + 1] = part_cost[i];
		i--;
	}
	part_number[i + 1] = part_in; 
	part_class[i + 1] = class_in;
	part_ohb[i + 1] = part_ohb_in;
	part_cost[i + 1] = part_cost_in;

}

void display(const vector <string>& part_number, const vector <char>& part_class, const vector <int>& part_ohb, const vector <double>& part_cost, int finder)
{
	double sum = 0;
	cout << fixed << setprecision(2);
	//find the sum 
	sum = (part_cost[finder] * part_ohb[finder]);
	//Display the output such the number of parts, cost, and others
	cout << "There are " << part_ohb[finder] << " of th Part Number " << part_number[finder] << " in invertory" << endl;
	cout << "It is a class " << part_class[finder] << " part. The cost is $" << part_cost[finder] << endl;
	cout<< "The value of that inventory is $"<< sum << "\n"<<endl;

}

void print_stats(int searches, int good, int bad)
{
	//print the status of the search
	cout << "Total number of searches " << searches<<endl;
	cout << "Total number of successful searches " << good<<endl;
	cout << "Total number of bad searches " << bad << endl;
}

void put_data(const vector <string>& part_number, const vector <char>& part_class, const vector <int>& part_ohb, const vector <double>& part_cost)
{
	//open the parts file 
	fstream inputfile;
	inputfile.open("parts.txt");

	//input the new data to the parts file
		for (int i = 0; i < part_number.size(); i++)
		{
			inputfile << part_number[i] << " " << part_class[i] << " " << part_ohb[i] << " " << part_cost[i] << endl;
		}
		//close the file
		inputfile.close();
}

/*

Enter the part number to search for and enter done if you want to stop
P-10659
There are 17 of th Part Number P-10659 in invertory
It is a class B part. The cost is $88.97
The value of that inventory is $1512.49

Enter the part number to search for and enter done if you want to stop
P-11754
There are 27 of th Part Number P-11754 in invertory
It is a class B part. The cost is $15.23
The value of that inventory is $411.21

Enter the part number to search for and enter done if you want to stop
P-22757
There are 12 of th Part Number P-22757 in invertory
It is a class B part. The cost is $47.19
The value of that inventory is $566.28

Enter the part number to search for and enter done if you want to stop
P-10032
The Part is not on the file
Enter the part class: C
Enter the amound of item: 123
Enter the cost of the item: 45.00
This Part is added

Enter the part number to search for and enter done if you want to stop
P-32477
The Part is not on the file
Enter the part class: A
Enter the amound of item: 12
Enter the cost of the item: 156.00
This Part is added

Enter the part number to search for and enter done if you want to stop
P-41444
The Part is not on the file
Enter the part class: D
Enter the amound of item: 88
Enter the cost of the item: 12.00
This Part is added

Enter the part number to search for and enter done if you want to stop
P-41444
There are 88 of th Part Number P-41444 in invertory
It is a class D part. The cost is $12.00
The value of that inventory is $1056.00

Enter the part number to search for and enter done if you want to stop
Done
Total number of searches 7
Total number of successful searches 4
Total number of bad searches 3
Press any key to continue . . .

*/
