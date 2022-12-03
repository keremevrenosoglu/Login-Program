#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

/** 
 * isStrongPassword will be used to check if the user entered 
 * password meets the criteria.
 */
bool isStrongPassword(const char * username, const char * password) {
    /** 
     * Variables that will be used to aid in determining if password
     * is valid are not are listed and initialized below.
     */
	int index = 0;
	int currConsec = 0;
	int maxConsec = 0;
	bool hasUpper = false;
	bool hasLower = false;
	bool hasDigit = false;
	bool hasUsername = false;
	
    /** 
     * If the password is less than 8 characters it is already 
     * invalid and the function will return false.
     */
	if (strlen(password) < 8) {
	    return false;
	}
	
    /** 
     * while loop traverses through each character of the password
     * string in order to handle essentially the rest of the checks.
     * index mimics the current index of the char array and is incremented
     * each time through the loop as the means by which the program moves
     * from one character to the next.
     */
	while (*(password + index) != '\0') {
        /** 
         * If any of the characters are non-alphanumerical, the function 
         * will return false. For any character that is found that is
         * uppercase, lowercase, or a digit, the appropriate boolean
         * variable is set to true.
         */
	    if (!isalnum(*(password + index))) {
	        return false;
	    }
	    if (isupper(*(password + index))) {
	        hasUpper = true;
	    }
	    if (islower(*(password + index))) {
	        hasLower = true;
	    }
	    if (isdigit(*(password + index))) {
	        hasDigit = true;
	    }
	    
        /** 
         * Each time that the current char that is being checked is a
         * letter, the variable currConsec is incremented as a holder 
         * of the current number of consecutive letters that have been
         * found. When it is not a letter, this number is set back to 0.
         * If the current streak is bigger than the max, the max is set
         * to the current.
         */
	    if (isalpha(*(password + index))) {
	        currConsec++;
	        
	        if (currConsec > maxConsec) {
	            maxConsec = currConsec;
	        }
	    }
	    else{
	        currConsec = 0;
	    }
	    
	    /** 
         * Starting from the current index of the password, there is a check 
         * ensure the username is not there in the password. There must be
         * enough characters left after the current index of the password to
         * match the username for this to even be possible. Compares characters
         * from the username and password only while the end of either has not 
         * been reached. Once a char is found that does not match, hasUsername
         * will be false for the time being and the loop can be broken from.
         * But if there is a string in the password that matches the username,
         * hasUsername will be left as true and the if statement below will
         * make the function return false.
         */
	    for (int i = 0; strlen(password) - index >= strlen(username) && i < strlen(username) && *(password + index + i) != '\0'; i++) {
	        if (tolower(*(username + i)) != tolower(*(password + index + i))) {
	            hasUsername = false;
	            break;
	        }
	        
	        hasUsername = true;
	    }
	    if (hasUsername) {
	        return false;
	    }
	    
	    index++;
	}
	
	/** 
     * If it has passed all checks, the function can return true.
     */
    if (hasUpper && hasLower && hasDigit && maxConsec >= 4) {
        return true;
    }
}

/** 
 * isStrongDefaultPassword is similar to the function above but has
 * a maximum number of characters and doesn't need to check for the 
 * consecutive letters.
 */
bool isStrongDefaultPassword(const char* username, const char* password) {
    int index = 0;
	bool hasUpper = false;
	bool hasLower = false;
	bool hasDigit = false;
	bool hasUsername = false;
	
	/** 
     * if statement altered to also return false if the length 
     * is greater than 15.
    */
	if (strlen(password) < 8 || strlen(password) > 15) {
	    return false;
	}
	
	while (*(password + index) != '\0') {
	    if (!isalnum(*(password + index))) {
	        return false;
	    }
	    if (isupper(*(password + index))) {
	        hasUpper = true;
	    }
	    if (islower(*(password + index))) {
	        hasLower = true;
	    }
	    if (isdigit(*(password + index))) {
	        hasDigit = true;
	    }
	    
	  
	    for (int i = 0; strlen(password) - index >= strlen(username) && i < strlen(username) && *(password + index + i) != '\0'; i++) {
	        if (tolower(*(username + i)) != tolower(*(password + index + i))) {
	            hasUsername = false;
	            break;
	        }
	        
	        hasUsername = true;
	    }
	    if (hasUsername) {
	        return false;
	    }
	    
	    index++;
	}
	
    if (hasUpper && hasLower && hasDigit) {
        return true;
    }
}

/** 
 * generateDefaultPassword will generate random passwords until 
 * it reaches one that meets the criteria set in isStrongDefaultPassword.
 * This cycle is works through the outer do-while loop.
 */
void generateDefaultPassword(char * default_password, const char * username) {
    do {
        /** 
        * Length of the password is set to a random number between the minimum 
        * 8 and max 15.
        */
        int randLength = (rand() % (15 - 8 + 1)) + 8;	
        
        /** 
        * Random char is generated for each index of the password until the
        * length is met. Uses a do-while loop to ensure this value will be
        * a letter or number rather than other non-allowed character before
        * moving on. Null terminator is added after the password to mark the end.
        */
        for (int i = 0; i < randLength; i++) {
            do {
                *(default_password + i) = (rand() % (122 - 48 + 1)) + 48;
            } while (!isalnum(*(default_password + i)));
        }
        
        *(default_password + randLength) = '\0';
    } while (!isStrongDefaultPassword(username, default_password));   
    
}

int main(void) 
{
    /** 
    * Random number generator seeded at the start. Strings declared
    * for the username, user-entered password, and default generated password.
    */
    srand(time(0));

    char user[50];
    char enteredPass[50];
    char defaultPass[16];
    int counter = 0;
    
    /** 
    * User is asked to enter a username and password until a password is
    * used that passes isStrongPassword's requirements.
    */
    do {
        printf("Enter username: ");
        scanf("%s", user);
        printf("Enter new password: ");
        scanf("%s", enteredPass);
        
        if (isStrongPassword(user, enteredPass)) {
            printf("Strong password!\n");
        }
        else{
            printf("Your password is weak. Try again!\n");
        }
    } while (!isStrongPassword(user, enteredPass));
    
    /** 
    * generateDefaultPassword is then called to get a default password
    * that meets the default password checks.
    */
    generateDefaultPassword(defaultPass, user);
    
    /** 
    * It is printed below, with a counter variable to move from
    * one char to the next.
    */
    printf("Generating a default password...\n");
    printf("Generated default password: ");
    
    while (*(defaultPass + counter) != '\0') {
        printf("%c", *(defaultPass + counter));
        counter++;
    }
    printf("\n");
    
	return 0;
}

