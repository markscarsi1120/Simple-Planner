#include "Cal.h"

Day::Day(int date){
	number_date = date;
}
Cal::Cal(){
	head = NULL;
}
Cal::~Cal(){
	Day * temp = head;
	while (temp != NULL){
		temp = temp->next;
		delete temp;
	}
}
Day * Cal::lookup_day(int date){
	Day * temp = head;
	while (temp != NULL){
		if (temp->number_date != date){
			temp = temp->next;
		}
		else{
			return temp;
		}
	}
	return NULL;
}

void Cal::print(Day * date){
    for (unsigned int index = 0; index < date->agenda.size();index++){
		std::cout << index+1 << ": " << date->agenda[index]<<std::endl;
	}
}

void Cal::add_day(Day * add){
	Day * temp = head;
	if (temp == NULL){
		head = add;
		add->next = NULL;
	}
	else if (add->number_date < temp->number_date){
		head = add;
		add->next = temp;
	}
	else{
       while (temp != NULL){
	      if (temp->number_date < add->number_date && temp->next == NULL){
		     temp->next = add;
		     add->next = NULL;
		  }
		  if (temp->number_date < add->number_date && 
		  	  temp->next->number_date > add->number_date){
			 add->next = temp->next;
			 temp->next = add;
		  }
		  temp = temp->next;
	   }
	}	
}

void Cal::add_agenda_item(int number, std::string agenda_item){
   Day * date = lookup_day(number);
   date->agenda.push_back(agenda_item);
}
void Cal::remove_agenda(Day * date, int agenda_item){
   if (date != NULL){
      date->agenda.erase(date->agenda.begin()+agenda_item-1);
      if (date->agenda.size()==0){
      	delete date;
      }
   }
}
void Cal::lookup_week(int date){
   Day * found = lookup_day(date);
   Day * temp =  found;
   if (found !=NULL) {
      while (temp != NULL){
         if (temp->next != NULL){
      		if (temp->number_date <= 70000+found->number_date){
      			std::cout << temp->number_date << std::endl;
      			print(temp);
      		}
      	 }
      	 temp = temp->next;
      }
   }   
}
void Cal::concluding_write(std::string name){
	std::ofstream final_in("temp.txt");
    final_in << name << "\n";
    Day* temp = head;
	while (temp!=NULL){
		std::stringstream ss;
		ss << temp->number_date;
		std::string date_string = ss.str();
		final_in << date_string.substr(0,2)+"/"+date_string.substr(2,2)+
		        "/"+date_string.substr(4,4) << "\n";
		for (unsigned int index = 0; index < temp->agenda.size(); index++){
			final_in << temp->agenda[index] << "\n";
		}
		temp = temp -> next;
	}
    remove("planner.txt");
    rename("temp.txt","planner.txt");
}