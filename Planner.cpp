#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Cal.h"
int day_to_int(std::string day){
   std::vector <char> holder;
   for (unsigned int index = 0; index < day.size();index++){
      if (day[index]!= '/' && day[index] > 58 && day[index] < 48){
         return 0;
      }
      if (day[index]!= '/'){
         holder.push_back(day[index]);
      }
   }
   std::string str(holder.begin(),holder.end());
   std::stringstream ss(str);
   int date_as_int;
   ss >> date_as_int;
   return date_as_int;
}
int main (int argc, char* argv[])
   {
   std::fstream file;
   file.open("planner.txt", std::ios::in | std::ios::out);
   std::string name;
   getline(file,name);
   if (name.size() < 1 ){
      file.clear();
      std::cout << "Welcome to Daily Planner, please enter your name: " 
                << std::endl;
      std::cin >> name;
      file << name;
      file.close();
   }
   std::cout << "Welcome " << name << std::endl;
   std::string lookup_date;
   std::string curr;
   Cal cal;
   int day_on;
   int day_as_int = 0;
   while (getline(file,curr)){
      if (day_to_int(curr)!=0){
         day_on = day_to_int(curr);
         Day * current_day = new Day(day_on);
         cal.add_day(current_day);
      }
      else{
         cal.add_agenda_item(day_on,curr);
      }
   }
   std::string operation;   
   while (operation != "q" && operation != "Q")
      {
      std::cout << "Search for specific day (SD), specific week (SW), " 
                << std::endl << "add an item (A), delete an item (D), " 
                << "or quit (Q)" << std::endl;
      std::cin >> operation;
      if (operation == "SD" || operation == "sd" || 
          operation == "sD" || operation == "Sd"){
         std::cout << "Which day would you like to look at?"<< std::endl;
         std::cin >> lookup_date;
         day_as_int = day_to_int(lookup_date);
         Day  * found = cal.lookup_day(day_as_int);
         cal.print(found);
      }
      if (operation == "SW" || operation == "sw" || 
          operation == "sW" || operation == "Sw"){
         std::cout << "What is the beginning day of the desired week?" << std::endl;
         std::cin >> lookup_date;
         day_as_int = day_to_int(lookup_date);
         cal.lookup_week(day_as_int);
      }
      if (operation == "A" || operation == "a"){
         std::cout << "Which day would you like to append to?" << std::endl;
         std::cin >> lookup_date;
         day_as_int = day_to_int(lookup_date);
         Day* found = cal.lookup_day(day_as_int);
         if (found !=NULL){
            cal.print(found);
         }
         else{
            Day * new_day = new Day(day_as_int);
            cal.add_day(new_day);
         }
         std::cout << "What would you like to add to your agenda on " 
                   << lookup_date << std::endl;    
         std::string agenda_item;
         std::cin >> agenda_item;
         cal.add_agenda_item(day_as_int,agenda_item);
      }
      if (operation == "D" || operation == "d"){
         std::cout << "Which day would you like to delete from?" << std::endl;
         std::cin >> lookup_date;
         day_as_int = day_to_int(lookup_date);
         Day * found = cal.lookup_day(day_as_int);
         cal.print(found);
         int deleted_item;
         std::cout << "Which item would you like to delete from " << std::endl;
         std::cout << "your agenda on " << lookup_date;
         std::cin >> deleted_item;
         cal.remove_agenda(found,deleted_item);
      }
   }
   cal.concluding_write(name);
   return 0;
}