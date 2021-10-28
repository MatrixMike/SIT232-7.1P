#include "splashkit.h"

#include <string>

#include <vector>

using namespace std;
using std::vector;

/*
prints parameter prompt and returns user input as a integer
 */
int read_integer(string prompt) {
  write_line(prompt);
  string str = read_line();
  while (not is_integer(str)) {
    write_line(prompt);
    string str = read_line();
  }
  return convert_to_integer(str);
}

/*
prints parameter prompt and returns user input as a integer
 */
int read_integer(string prompt, int min, int max) {
  int result = read_integer(prompt);
  while (result < min or result > max) {
    write_line("Enter integer between (range) " + to_string(min) + " And " + to_string(max));
    result = read_integer(prompt);
  }
  return result;
}

//prints prompts returns string (input)
string read_String(string prompt) {
  write_line(prompt);
  string str = read_line();
  return str;
}

struct knigth_data {
  string name;
  int age;
  vector < string > quests;
};

enum knight_update_option {
  UPDATE_AGE,
  UPDATE_NAME,
  ADD_QUEST,
  DELETE_QUEST,
  FINISH_UPDATE
};

enum update_kingdom_option {
  ADD,
  QUERY,
  DELETE,
  DISPLAY,
  FINISH
};

struct kingdom_data {
  string name;
  vector < knigth_data > knights;
};

void write_knight(knigth_data knight) {
  write_line("Hello " + knight.name + "Aged :" + to_string(knight.age));
  write_line("==Quests");
  int size = knight.quests.size();
  for (int i = 0; i < size; i++) {
    write_line("*" + knight.quests[i]);
  }
}

knight_update_option read_knight_update_option() {
  int result;
  write_line("==UPDATE KNIGHT==");
  write_line("1===Updat ename");
  write_line("2==Updat age");
  write_line("3==Add quest");
  write_line("4==delete quest");
  write_line("5==Finish update");
  result = read_integer("Select option : ");
  return static_cast < knight_update_option > (result - 1);
}

update_kingdom_option read_update_kigdom_option() {
  int result;
  write_line("==UPDATE KINGDOM==");
  write_line("1==Add knight");
  write_line("2==Query knight");
  write_line("3==Delete knight");
  write_line("4==Display details");
  write_line("5==Finish");

  result = read_integer("Select option : ");
  return static_cast < update_kingdom_option > (result - 1);
}

void update_knight(knigth_data & knight) {
  knight_update_option option;
  do {

    option = read_knight_update_option();
    int size_1;
    int size;
    string quest_to_delete;
    switch (option) {
    case UPDATE_NAME:
      knight.name = read_String("Enter new name : ");
      break;;
    case UPDATE_AGE:
      knight.age = read_integer("Enter new age : ");
      break;;
    case ADD_QUEST:
      knight.quests.push_back(read_String("Enter new quest : "));
      break;;
    case DELETE_QUEST:
      write_line("==Quests==");
      size = knight.quests.size();
      for (int i = 0; i < size; i++) {
        write_line("*" + knight.quests[i]);
      }
      size_1 = knight.quests.size();
      quest_to_delete = read_String("Enter quest to delete");
      for (int i = 0; i < size_1; i++) {
        if (quest_to_delete == knight.quests[i]) {
          knight.quests[i] = knight.quests[knight.quests.size() - 1];
          knight.quests.pop_back();
        }
      }
      break;;

    case FINISH_UPDATE:
      break;
    default:
      write_line("Enter a valid option please....");;
    }
  }
  while (option != FINISH_UPDATE);
}

knigth_data read_knight() {
  knigth_data result;
  result.name = read_String("Enter name : ");
  result.age = read_integer("Enter age : ");
  return result;
}
void add_knight(kingdom_data & kingdom) {
  knigth_data new_knight;
  new_knight = read_knight();
  kingdom.knights.push_back(new_knight);
}

void write_kingdom(const kingdom_data & kingdom) {
  write_line("============");
  write_line(kingdom.name);
  write_line("==Knights==");
  int size = kingdom.knights.size();
  for (int i = 0; i < size; i++) {
    write_knight(kingdom.knights[i]);
  }
  write_line("============");
}

void delete_knight(kingdom_data & kingdom, int index) {
  int size = kingdom.knights.size();
  if (index >= 0 and index < size) {
    int last_index = kingdom.knights.size() - 1;
    kingdom.knights[index] = kingdom.knights[last_index];
    kingdom.knights.pop_back();
  }
}

kingdom_data read_kingdom() {
  kingdom_data result;
  result.name = read_String("Enter kingdom anme:");
  return result;
}

int select_knight(const kingdom_data & kingdom) {
  int result;
  write_line("==Select Knight==");
  int size = kingdom.knights.size();
  for (int i = 0; i < size; i++) {
    string write_string = to_string(i + 1) + ") " + kingdom.knights[i].name;
    write_line(write_string);
  }
  //do{
  result = read_integer("Enter knight number :", 0, size);
  //}
  //while(result!=0);

  return result;
}

void update_kigdom(kingdom_data & kingdom) {
  update_kingdom_option option;
  do {

    option = read_update_kigdom_option();
    switch (option) {
    case ADD:
      add_knight(kingdom);
      break;;
    case DELETE:
      int i;
      i = select_knight(kingdom);
      if (i > 0) {
        delete_knight(kingdom, i - 1);
      }
      break;;
    case QUERY:
      int x;
      x = select_knight(kingdom);
      if (x > 0) {
        write_knight(kingdom.knights[x - 1]);
      }
      break;;
    case DISPLAY:
      write_kingdom(kingdom);
      break;;
    case FINISH:
      break;
    default:
      write_line("Enter a valid option please....");;
    }
  }
  while (option != FINISH);
}

int main() {
  kingdom_data my_kingdom = read_kingdom();
  add_knight(my_kingdom);
  add_knight(my_kingdom);
  write_kingdom(my_kingdom);
  delete_knight(my_kingdom, 1);
  write_kingdom(my_kingdom);
  update_kigdom(my_kingdom);
  return 0;
}
