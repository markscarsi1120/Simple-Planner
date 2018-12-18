#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
struct Day{
public:
	Day(int date);
	Day * next;
	std::vector<std::string> agenda;
	int number_date;
};

class Cal{
public:
	Cal();
	~Cal();
	Day * lookup_day(int date);
	void add_day(Day * date);
	void add_agenda_item(int number, std::string agenda_item);
	void remove_agenda(Day * date, int agenda_item);
	void lookup_week(int date);
	void print(Day * date);
	void concluding_write(std::string name);
private:
	Day * head;
};