struct Day{
	Day * next;
	std::vector<std::string> agenda;
	int number_date;
};

class Calander{
public:
	void lookup_day(int date);
	void add(int date,int agenda_item);
	void remove(int date, int agenda_item);
	void lookup_week(int date);
private:
	Day * head;
};