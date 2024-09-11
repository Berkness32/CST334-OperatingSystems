
#include "student_code.h"
#include "stdlib.h"


/***********
 * Strings *
 ***********/

/**
 * This function takes in a c-string and returns it's length.  It **does not** use the strlen(...) function in string.h
 * @param str The string that we will be finding the length of.  It will be null terminated
 * @return The lenght of the inpurt string
 */
int get_str_length(char* str) {
  // todo
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  // Question: How do we know that we've gotten to the end of a c-string?

  int count = 0;

  while (*str != '\0') {
    count++;
    str++;
  }

  return count; //    :)
}

/**
 * Returns a pointer to a copy of the original string.  It **does not** use strcpy or any related function (but may use strlen)
 * @param str An input string that is null terminated
 * @return a new char* that copies the input string str
 */
char* copy_str(char* str) {
  // todo
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0

  int length = get_str_length(str);

    char* new_str = (char*)malloc((length + 1) * sizeof(char));

    if (new_str == NULL) {
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        new_str[i] = str[i];
    }

    new_str[length] = '\0';

    return new_str;
}

/**
 * Truncates a string to a the given length, not including the null terminator.  If the given length is longer than the original string the original string is returned unchanged.
 * @param str A null-terminated input string
 * @param new_length The length of the output string.
 */
void truncate_string(char* str, int new_length) {
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  // todo
	
	if (get_str_length(str) <= new_length) {
		return;
	}

	str[new_length] = '\0';	
}

/**
 * Converts a given string, str, to all uppercase letters
 * @param str A null-terminated input string
 */
void to_uppercase(char* str) {
  // todo
 
	int length = get_str_length(str);
	for (int i = 0; i < length; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] -= 32;
		} 
	}

}

/**
 * Converts a given string, str, to all lowercase letters
 * @param str A null-terminated input string
 */
void to_lowercase(char* str) {
  // todo

	int length = get_str_length(str);
	for (int i = 0; i < length; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] += 32;
		}
	}
}

/**
 * Finds the index of the first usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the first usage of the target character in the string
 */
int find_first_index(char* str, char target) {
  // todo
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  	
	int length = get_str_length(str);
	for (int i = 0; i < length; i++) {
		if (str[i] == target) {
			return i;
		}
	}
	return -1;
}

/**
 * Finds the index of the last usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the last usage of the target character in the string
 */
int find_last_index(char* str, char target) {
  // todo
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0

	int last = -1;
	int length = get_str_length(str);
	for (int i = 0; i < length; i++) {
		if (str[i] == target) {
			last = i;
			last++;
		}
	}
	return last;
}


/**************
 * Structures *
 **************/
/**
 * Create a new person object and return the object
 * @param first_name The first name of the new person as a null-terminated string
 * @param last_name The last name of the new person as a null-terminated string
 * @param age The age of the person as an int
 * @return A Person struct containing the new person
 */
Person person_make_new(char* first_name, char* last_name, int age) {
  // todo
	Person new_person;

	int fLength = get_str_length(first_name);
	int lLength = get_str_length(last_name);

	for (int i = 0; i < fLength; i++) {
		new_person.first_name[i] = first_name[i];
	}
	new_person.first_name[fLength] = '\0';

	for (int i = 0; i < lLength; i++) {
		new_person.last_name[i] = last_name[i];
	}
	new_person.last_name[lLength] = '\0';

	new_person.age = age;

	return new_person;
}
/**
 * Return a string containing the full name and age of the person in the format "First Last (age)"
 * @param person The person to get the relevant string for
 * @return A string containing the name of the person
 */
char* person_to_string(Person person) {
  // todo
  // hint: sprintf

	char* total = (char*)malloc(200 * sizeof(char));
    	if (total == NULL) {
        	return NULL;
    	}
	sprintf(total, "%s %s (%d)", person.first_name, person.last_name, person.age);
	return total;
}

/**
 * A function to create a new empty group
 * @param group_name A null-terminuated string to name the new group
 * @return A new Group struct
 */
Group group_make_new(char* group_name) {
  // todo

	Group new_group;
	int length = get_str_length(group_name);

	for (int i = 0; i < length; i++) {
		new_group.group_name[i] = group_name[i];
	}
	new_group.group_name[length] = '\0';
	

	// Array is not initialized here but it might initialize in the header file?
	

	new_group.num_members = 0;

	return new_group;
}

/**
 * A function to find the total number of people in the group
 * @param group A Group struct that contains some number of people
 * @return The number of users in the group
 */
int num_people_in_group(Group group) {
  // todo
  
  return group.num_members;
}
/**
 * Get the number of free spaces remaining in the group
 * @param group A Group struct that contains some number of people
 * @return The number of free spaces in the group
 */
int free_spaces_in_group(Group group) {
  // todo
  //
  int freeSpaces = 50 - group.num_members;
  return freeSpaces;
}

/**
 * Add a person to the group if possible and return the total number of free space in the group. Otherwise return -1.
 * @param group A group struct that contains some number of people
 * @param person_to_add The person to add to the group
 * @return The number of free spaces after add the new person, -1 if the group was already full
 */
int add_person(Group* group, Person* person_to_add) {
  // todo
  // Question: Say we have already added a person to the group and try to add them again.  What should be we do?  Where can we check what the expected behavior is?
  //

	if (free_spaces_in_group(*group) < 51) {

		for (int i = 0; i < group->num_members + 1; i++) {
		    if (group->group_members[i]->first_name == person_to_add->first_name) {
        		    return -1;
    		    }
		}


		group->group_members[group->num_members] = person_to_add;
		group->num_members++;

		return free_spaces_in_group(*group);
	}
	return -1;
}

/**
 * Remove a person from the group if they are in the group, otherwise return -1
 * @param group A Group struct that contains some number of people
 * @param person_to_remove A person to remove from the group
 * @return The number of people remaining in the group, -1 if the person was not in the group
 */
int remove_person(Group* group, Person* person_to_remove) {
  // todo
  
    int index = -1;
    for (int i = 0; i < group->num_members; i++) {
        if (group->group_members[i] == person_to_remove) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return group->num_members;
    }

    for (int i = index; i < group->num_members - 1; i++) {
        group->group_members[i] = group->group_members[i + 1];
    }

    group->num_members--;

  return group->num_members;
}



/*
 * Caesar Cipher
 */
/**
 * Shift a character 'left' by the shift amount by subtracting the shift size.
 *  e.g. 'a' with a shift_size = 1 will become 'z'
 * @param input_char
 * @param shift_size
 * @return
 */
char shift_left(char input_char, int shift_size) {
  // todo

    to_lowercase(&input_char);
    
    if (shift_size == 0) {
	    return input_char;
    }

    if (input_char < '/') {
	    return input_char;
    }

    input_char -= shift_size;

    if (input_char < 'a') {
        input_char += 26; 
    }

    return input_char;
}

/**
 * Shift a character 'right' by the shift amount by subtracting the shift size.
 *  e.g. 'z' with a shift_size = 1 will become 'a'
 * @param input_char
 * @param shift_size
 * @return
 */
char shift_right(char input_char, int shift_size) {
  // todo
    
    to_lowercase(&input_char);

    if (shift_size == 0) {
	    return input_char;
    }

    if (input_char < '/') {
	    return input_char;
    }

    input_char += shift_size;

    if (input_char > 'z') {
        input_char -= 26; 
    }

    return input_char; 
}

/**
 * Encrypts a string using a given shift.  Note: All characters should be converted to lowercase
 * @param input_str
 * @param shift_size
 * @return
 */
char* encrypt_caesar(char* input_str, int shift_size) {
  // todo
  
	int length = get_str_length(input_str);
	char* encrypted_str = (char*)malloc((length + 1) * sizeof(char));

	for (int i = 0; i < length; i++) {
		encrypted_str[i] = shift_left(input_str[i], shift_size);
	}
	encrypted_str[length] = '\0';

	return encrypted_str;
}

/**
 * Decrypts a string using a given shift.  Note: All characters should be converted to lowercase
 * @param input_str
 * @param shift_size
 * @return
 */
char* decrypt_caesar(char* input_str, int shift_size) {
  // todo


	int length = get_str_length(input_str);
	char* decrypted_str = (char*)malloc((length + 1) * sizeof(char));


	for (int i = 0; i < length; i++) {
		decrypted_str[i] = shift_right(input_str[i], shift_size);
	}
	decrypted_str[length] = '\0';

	return decrypted_str;
}

/*
 * General substitution Cipher
 */

/**
 * Returns true if a given encryption key has a valid decryption key.
 * @param encryption_key
 * @return
 */
bool is_reversible(int* encryption_key) {
  // todo
  return false;
}

/**
 * Generates a decryption key based on the encryption key, if one exists.  Otherwise returns NULL
 * @param encryption_key
 * @return
 */
int* get_decryption_key(int* encryption_key) {
  // todo
  return NULL;
}

/**
 * Takes the input string and the encryption key and encrypts the input string in place
 * @param input_str
 * @param encryption_key
 */
void encrypt_substitution(char* input_str, int* encryption_key) {
  // todo
  return;
}

/**
 * Takes an encrypted input string and a decryption key and decrypts a string in place
 * @param input_str
 * @param decryption_key
 */
void decrypt_substitution(char* input_str, int* decryption_key) {
  // todo
  return;
}




