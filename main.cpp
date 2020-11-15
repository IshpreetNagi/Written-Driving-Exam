//Last Updated: Nov.11, 2020
//Written By: Ishpreet Nagi

#include <iostream> //adding in all my libraries
#include <bits/stdc++.h>
using namespace std;

void title() //this function is to just display the title screen to greet the user to the program
{
    cout << "\t\t\t\t\t\t      Welcome To...\n" << endl; //message for the user
    cout << "\t\t\t\t\t _____       _        _______        _   " << endl; //some art to make my code look a bit more appealing
    cout << "\t\t\t\t\t|  __ \\     (_)      |__   __|      | |  " << endl;
    cout << "\t\t\t\t\t| |  | |_ __ ___   _____| | ___  ___| |_ " << endl;
    cout << "\t\t\t\t\t| |  | | '__| \\ \\ / / _ \\ |/ _ \\/ __| __|" << endl;
    cout << "\t\t\t\t\t| |__| | |  | |\\ V /  __/ |  __/\\__ \\ |_ " << endl;
    cout << "\t\t\t\t\t|_____/|_|  |_| \\_/ \\___|_|\\___||___/\\__|" << endl;
    cout << "\n\t\t\t\t     IN COLLARBRATION WITH: AAAAAAAA1 DRIVING SCHOOL" << endl;
}

int randomizer() //this is the function that holds mostly all the code that allows for the exam questions stored in the text file to be chosen randomly and then displayed on the screen to the user
{
    //A brief rundown of this code works as I understand it can be rather confusing to interpret what is being done

    //Essentially the way this code works is that I have all the possible exam questions in one text file,
    //to display them I open up the file and read lines in the file without displaying them on screen as a way to
    //skip those lines. Then once I have skipped the number of lines I want, I would have arrived at the number of
    //lines in the file that hold the question I want to display, then I read those lines and display them on screen,
    //to display them I make the code read up to those divider lines I have put in the file that is made up of dashes, ‘---’. The way
    //the randomizer works is that the number of lines I have to skip to get to each question is put into a vector array
    //from where they are randomly selected. Then that skip number is put into the loop so that many lines of the file
    //can be skipped without being displayed so I can arrive at the lines in the file where the question I want to display
    //is being held. Then I make the code read up to the dash divider in between questions and display those numbers
    //of lines. Right under the dash line divider I have the answer to each question, once the code hits the dashed
    //line it stops reading, but I have one more for loop that will read the one line under the dash, collect the
    //answer, store it into a variable and send it to the Exam function so it can be compared with the answer the user
    //entered and see if they entered in the correct answer to that question.

    //Since I have to display 10 questions and have 21 questions in total in the file, I have made it so once a
    //question has been displayed, it can not be displayed again. The way I do this is once a random number to skip
    //lines is selected before it is sent to the for loop where it would actually be used, it is compared to an array
    //which holds all the skip values that have already been displayed. If the value is chosen is equal to the value
    //in the array, the code will randomly select a new skip value. However, if the skip value does not equal to value on the
    //array, the code will keep going and send that skip value to the for loop but also add that skip value to the data
    //file from which the int array used for checking previously displayed questions is filled from.

    string checkline; //declaring the string variable
    int check[10]; //declaring the int array

    for (int a=0;a<9;a++) //this is the the for loop that goes through all the spots in the int array and makes them equal to zero
    {
        check[a] = 0; //makes the spot in the int array equal to zero
    }

    ifstream readcheck; //declares the stream type, which in this case is ifstream, and the stream variable name
    readcheck.open("CHECK.DAT", ios::in); //opens the text file and sets the stream operation mode

    assert(!readcheck.fail()); //the failsafe that would terminate the program if the file I am trying to open fails

    while(readcheck) //this is the while loop that will read till the end of the text file
    {
        getline(readcheck,checkline); //reads the entire line in the file and sets it into the string variable so it can be used
        if(readcheck)
        {
            for(int k=0;k<9;k++) //this is the for loop that takes the number from each line in the text file and stores it into the int array
            {
                readcheck >> check[k]; //takes the number from the file line and puts it into the array, however if the lines in the file ends but the for loop keeps going, the rest of the numbers in the array, after from where the numbers that had been stored in it from the file have ended, are left as 0
            }
        }
    }
    readcheck.close(); //closes the file

    vector<int>list{2,14,26,38,51,64,76,88,101,114,126,139,152,165,179,192,205,218,230,243,256}; //this is the vector array that holds all the values tat that should be skipped in the file, thus resulting in the file being read from a specific point

    lookagain: //when told to goto this line, the code will start running from this point
    srand (time(NULL));
    int index = rand()%list.size(); //randomly selects a index spot in the array in relation to the size of the array and stores that spot value in the int variable
    int numskip = list[index]; //takes that index spot in the array and extracts the value being held at that index spot and stores that value in the int variable

    for(int i=0;i<9;i++) //this is the for loop that will run through all the index spots in the checking array and see if the skip value chosen randomly has already been displayed
    {
        if(numskip == check[i]) //checks the skip value to see if it matches up with a value in the array which stores all the skips values that have already been displayed
        {
            goto lookagain; //tells the code to start reading from that point
        }
    }

    ofstream obj; //declares the stream type, which in this case is ofstream, and the stream variable name
    obj.open("CHECK.DAT", ios::app); //opens the text file and sets the stream operation mode
    assert(!obj.fail()); //the failsafe that would terminate the program if the file I am trying to open fails
    obj << numskip << endl; //stores the skip value into the data file that holds all the questions that have already been displayed and the same file which fills the check int array
    obj.close(); //closes the file

    return(numskip); //returns the numskip value back to the function from where this function was called
}

string DisplayQuestions() //This is the void function I use to open the file and read the questions stored in it
{
    //The full explanation to how this function works together with the randomizer function, and a little of how this function works is explained at the top of the randomizer function

    string pline, ans; //declares my string variables

    int numskip = randomizer(); //calls the randomizer function and stores the value the function returns in the int variable

    ifstream display; //declares the stream type, which in this case is ifstream, and the stream variable name
    display.open("CarTestQuestions_Input.txt", ios::in); //opens the text file and sets the stream operation mode

    assert(!display.fail()); //the failsafe that would terminate the program if the file I am trying to open fails

    for (int i=0;i<numskip;i++) //this is the for loop that would take the skip number that has been received from the randomizer function and skips that many lines in the file to get to the lines where the question is being stored
    {
        getline(display,pline); //reads the entire line in the file and sets it into the string variable
    }
    while(pline != "-------------------------------------------------------------------------") //this loop then displays all the lines from the file on screen until it hits the dashed divider line
    {
        getline(display,pline); //reads the entire line in the file and sets it into the string variable
        cout << pline << endl; //displays on screen the string variable where the contents of the file line are being held
    }
    for (int i=0;i<1;i++) //this is the for loop that will only read the one line after the dashed divider line to get the answer to the question it just displayed
    {
        getline(display,ans); //reads the entire line in the file and sets it into the string variable
    }

    display.close(); //closes the file

    return(ans); //returns the ans value back to the function from where this function was called
}

void box(int num) //this just displays the question boxes that tell the user what question they are doing, I send the function the number I want that the box should display, the function collects it and then displays it in the box
{
    cout << " ------------- " << endl; //messages for the user
    cout << "| QUESTION " << num << "  |" << endl;
    cout << " ------------- \n" << endl;
}

string useranswer() //this is the char function that actually allows the user to enter their answer for a question
{
    string answer; //declares the string variable

    do{ //begins the do-while loop that would allow for the user to enter the option again if they enter an illegal input
        cout << "\nYOUR ANSWER: "; cin >> answer; //tells the user what they need to enter and then stores the input in the variable
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower); //converts whatever string value the user entered into lowercase to make it easier for the code to work with it
        if(answer != "a" && answer != "b" && answer != "c" && answer != "d")
        {
            cout << "\nPLEASE CHOOSE BETWEEN THE GIVEN OPTIONS." << endl; //error message
        }
    } while(answer != "a" && answer != "b" && answer != "c" && answer != "d"); //the requirement that once met, will cause the do-while loop to repeat, thus not letting them exit the loop until they have entered the correct input

    return(answer); //returns whatever answer the user enters back to the function from where this function was called
}

void checkmark() //this is just a function that displays a check mark to the user when they enter a right answer to let the user know they have entered the right answer
{
    cout << "         /" << endl; //messages for the user
    cout << "        /" << endl;
    cout << "       /" << endl;
    cout << "      /" << endl;
    cout << "\\    /" << endl;
    cout << " \\  /" << endl;
    cout << "  \\/" << endl;
}

void x() //this function displays a big X on screen when the user enters an incorrect answer to let the user know they have entered the incorrect answer
{
    cout << " \\     /" << endl; //message for the user
    cout << "  \\   /" << endl;
    cout << "   \\ /" << endl;
    cout << "    X    " << endl;
    cout << "   / \\" << endl;
    cout << "  /   \\" << endl;
    cout << " /     \\" << endl;
}

struct USER_INFORMATION //this just a structure that holds all the variables that will store the users personal information
{
    string name, number, address, code; //declaring all my string variables
    int day, month, year; //declaring all my int variables
};

bool fillininfo(USER_INFORMATION &info) //creates the function that lets the user enter in their information, I send the the function the structure information like the variable I am using to deal with it as a reference so it can be accessed in the function from which this function was called
{
    cout << "\nEnter your FULL NAME: "; getline(cin,info.name); //tells the user what they need to enter and then stores their input in the name string variable in the structure

    cout << endl; //creates a space in between texts

    do{ //begins the do-while loop that would allow for the user to enter the option again if they enter an illegal input
        cout << "Enter your birth YEAR: "; cin >> info.year; //tells the user what they need to enter and then stores the input in the year int variable in the structure
        if(info.year <= 0 || info.year > 2020)
        {
            cout << "INVALID ENTRY, ENTER AGAIN" << endl; //error message
        }
    } while(info.year <= 0 || info.year > 2020); //the requirement that once met, will cause the do-while loop to repeat, thus not letting them exit the loop until they have entered the correct input

    cout << endl; //creates a space in between texts

    do{ //begins the do-while loop that would allow for the user to enter the option again if they enter an illegal input
        cout << "(ex. 10 or 03)" << endl;
        cout << "Enter your birth MONTH: "; cin >> info.month; //tells the user what they need to enter and then stores the input in the month int variable in the structure
        if(info.month <= 0 || info.month > 12)
        {
            cout << "INVALID ENTRY, ENTER AGAIN" << endl; //error message
        }
    } while(info.month <= 0 || info.month > 12); //the requirement that once met, will cause the do-while loop to repeat, thus not letting them exit the loop until they have entered the correct input

    cout << endl; //creates a space in between texts

    do{ //begins the do-while loop that would allow for the user to enter the option again if they enter an illegal input
        cout << "(ex. 23 or 07)" << endl;
        cout << "Enter your birth DAY: "; cin >> info.day; //tells the user what they need to enter and then stores the input in the day int variable in the structure
        cin.ignore();
        if(info.day <= 0 || info.day > 31)
        {
            cout << "INVALID ENTRY, ENTER AGAIN" << endl; //error message
        }
    } while(info.day <= 0 || info.day > 31); //the requirement that once met, will cause the do-while loop to repeat, thus not letting them exit the loop until they have entered the correct input

    cout << "\nEnter your PHONE NUMBER: "; getline(cin,info.number); //tells the user what they need to enter and then stores the input in the number string variable in the structure
    cout << "\nEnter your ADDRESS: "; getline(cin,info.address); //tells the user what they need to enter and then stores the input in the address string variable in the structure
    cout << "\nEnter your POSTAL CODE: "; getline(cin,info.code); //tells the user what they need to enter and then stores the input in the code string variable in the structure
}

void failed(USER_INFORMATION &info, int num) //creates the function that lets the user enter in their information, I send the the function the structure information like the variable I am using to deal with it as a reference, I am also sending it a number which the function collects and stores the num int variable
{
    cout << " -----------------" << endl; //message for the user
    cout << "| EXAM TERMINATED |" << endl;
    cout << " -----------------" << endl;

    cout << "\nNAME: " << info.name << endl; //displays the user's name on screen by pulling it from the name string variable in the structure

    cout << "\nRESULT: FAILED" << endl; //messages for the user
    cout << "\nREASON:" << endl;
    cout << "Since you exceeded your 4 wrong question threshold, you have failed the G1 knowledge" << endl;
    cout << "examination, therefore the exam was terminated." << endl;

    ofstream obj; //declares the stream type, which in this case is ofstream, and the stream variable name
    obj.open("CarTestQuestions_Input.txt", ios::app); //opens the text file and sets the stream operation mode

    assert(!obj.fail()); //the failsafe that would terminate the program if the file I am trying to open fails

    obj << "\n" << info.name << endl; //stores the value held in the name string variable in the structure into the text file
    obj << "BORN: " << info.year << " - " << info.month << " - " << info.day << endl; //stores the values held in the year,month, and day int variable in the structure into the text file
    obj << "PHONE NUMBER: " << info.number << endl; //stores the value held in the number string variable in the structure into the text file
    obj << "ADDRESS: " << info.address << endl; //stores the value held in the address string variable in the structure into the text file
    obj << "POSTAL CODE: " << info.code << endl; //stores the value held in the code string variable in the structure into the text file
    if(num == 2)
    {
        obj << "EXAM STATUS: COMPLETE" << endl; //stores the message into the file
    }
    else
    {
        obj << "EXAM STATUS: INCOMPLETE" << endl; //stores the message into the file
    }
    obj << "EXAM RESULT: FAILED" << endl; //stores the message into the file
    obj << "*******************************************" << endl; //stores the message into the file

    obj.close(); //closes the file
}

void disclaimer() //this function just holds the text for a disclaimer screen that would pop up before the person does the exam to let them know about the rules and instructions on how to do the test
{
    cout << " -------------- " << endl; //messages for the user
    cout << "| INSTRUCTIONS |" << endl;
    cout << " -------------- " << endl;

    cout << "\nYou will be presented with 10 questions in total." << endl; //messages for the user
    cout << "\nThe questions will be randomly chosen from a set number of questions and will be displayed" << endl;
    cout << "in a random order every time the test is attempted." << endl;
    cout << "\nYou will be given 4 options with the question, please enter in the letter that corresponds" << endl;
    cout << "with the answer you want to enter. After entering you will be prompted if you entered it correct or" << endl;
    cout << "wrong along with the correct answer if you happen to chose incorrectly." << endl;
    cout << "\nYou will be given the opportunity to answer 4 questions incorrectly, however on your fifth incorrect" << endl;
    cout << "answer the code will terminate and you will have failed the G1 knowledge test." << endl;
    cout << "Read the questions carefully and take your time in answering as there is no set time limit." << endl;
    cout << "\nGood Luck!\n" << endl;

    cout << " ------------ " << endl; //messages for the user
    cout << "| DISCLAIMER |" << endl;
    cout << " ------------ " << endl;

    cout << "\nThis exam must be done completely independently, without the help of external sources." << endl; //messages for the user
    cout << "\nWhile writing the exam, you are not allowed to: " << endl;
    cout << "\n- Look at your phone" << endl;
    cout << "- Communicate with other examinees" << endl;
    cout << "- Look at the screen of other examinees" << endl;
    cout << "- Use unauthorized materials, prepared answers, written notes, or concealed information" << endl;
    cout << "- Taking an exam for another person or having someone else take the exam for you" << endl;

    cout << "\nFound committing any of the acts listed above will result in an automatic failure and temporary suspension," << endl; //messages for the user
    cout << "from rewriting the exam." << endl;
}

void Exam() //this is the function that actually holds all the code for running the exam, it calls the other functions that are vital to its operation
{
    string uans[10]; //declares my string arrays
    string rans[10];
    int strike = 4, correct = 0, score = 0; //declares my int variables and sets them all the starting variable that is needed

    USER_INFORMATION info; //accesses the structure and creates a variable which could be used to access the variables in the structure and enter values into them

    cout << " -------------- " << endl; //message for the user
    cout << "| DRIVING EXAM |" << endl;
    cout << " -------------- " << endl;

    cout << "\nPLEASE FILL IN THE FOLLOWING INFORMATION: " << endl; //message for the user

    fillininfo(info); //calls the fillininfo function and sends it the structure variable that it needs to be able to access the variables within the structure and enter values into them
    cout << endl; //creates a space between texts
    system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
    system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

    disclaimer(); //calls the disclaimer function to start running

    while(true) //this while true loop doesn't actually loop as I have put a break statement at the end of it, but rather allows me to exit out of the loop and not let the rest of the code in the loop run whenever I need to
    {
        cout << endl; //creates a space between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        box(1); //calls the box function to begin running and sends it the value that I want it to display in the box
        rans[0] = DisplayQuestions(); //calls the DisplayQuestions function to start running and then stores whatever value it returns into that specific string array index
        uans[0] = useranswer(); //calls the useranswer function to start running and then stores whatever value it returns into that specific string array index

        if(uans[0] == rans[0])
        {
            score += 10; //adds a value of 10 to the int variable
            correct += 1; //adds a value of 1 to the int variable
            cout << endl; //creates a space in between texts
            checkmark(); //calls the checkmark function to start running
        }
        else
        {
            strike -= 1; //subtracts a value of 1 from the int variable
            cout << endl; //creates a space in between texts
            x(); //calls the x function to begin running
            cout << endl; //creates a space in between texts
            cout << "CORRECT ANSWER: " << rans[0] << endl; //displays the correct answer to the user on the screen
            cout << strike << " more mistakes allowed" << endl; //lets the user know how many more questions they can get wrong before the exam terminates and they fail
        }

        cout << endl; //creates a space in between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        box(2); //calls the box function to begin running and sends it the value that I want it to display in the box
        rans[1] = DisplayQuestions(); //calls the DisplayQuestions function to start running and then stores whatever value it returns into that specific string array index
        uans[1] = useranswer(); //calls the useranswer function to start running and then stores whatever value it returns into that specific string array index

        if(uans[1] == rans[1])
        {
            score += 10; //adds a value of 10 to the int variable
            correct += 1; //adds a value of 1 to the int variable
            cout << endl; //creates a space in between texts
            checkmark(); //calls the checkmark function to start running
        }
        else
        {
            strike -= 1; //subtracts a value of 1 from the int variable
            cout << endl; //creates a space in between texts
            x(); //calls the x function to begin running
            cout << endl; //creates a space in between texts
            cout << "CORRECT ANSWER: " << rans[1] << endl; //displays the correct answer to the user on the screen
            cout << strike << " more mistakes allowed" << endl; //lets the user know how many more questions they can get wrong before the exam terminates and they fail
        }

        cout << endl; //creates a space in between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        box(3); //calls the box function to begin running and sends it the value that I want it to display in the box
        rans[2] = DisplayQuestions(); //calls the DisplayQuestions function to start running and then stores whatever value it returns into that specific string array index
        uans[2] = useranswer(); //calls the useranswer function to start running and then stores whatever value it returns into that specific string array index

        if(uans[2] == rans[2])
        {
            score += 10; //adds a value of 10 to the int variable
            correct += 1; //adds a value of 1 to the int variable
            cout << endl; //creates a space in between texts
            checkmark(); //calls the checkmark function to start running
        }
        else
        {
            strike -= 1; //subtracts a value of 1 from the int variable
            cout << endl; //creates a space in between texts
            x(); //calls the x function to begin running
            cout << endl; //creates a space in between texts
            cout << "CORRECT ANSWER: " << rans[2] << endl; //displays the correct answer to the user on the screen
            cout << strike << " more mistakes allowed" << endl; //lets the user know how many more questions they can get wrong before the exam terminates and they fail
        }

        cout << endl; //creates a space in between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        box(4); //calls the box function to begin running and sends it the value that I want it to display in the box
        rans[3] = DisplayQuestions(); //calls the DisplayQuestions function to start running and then stores whatever value it returns into that specific string array index
        uans[3] = useranswer(); //calls the useranswer function to start running and then stores whatever value it returns into that specific string array index

        if(uans[3] == rans[3])
        {
            score += 10; //adds a value of 10 to the int variable
            correct += 1; //adds a value of 1 to the int variable
            cout << endl; //creates a space in between texts
            checkmark(); //calls the checkmark function to start running
        }
        else
        {
            strike -= 1; //subtracts a value of 1 from the int variable
            cout << endl; //creates a space in between texts
            x(); //calls the x function to begin running
            cout << endl; //creates a space in between texts
            cout << "CORRECT ANSWER: " << rans[3] << endl; //displays the correct answer to the user on the screen
            cout << strike << " more mistakes allowed" << endl; //lets the user know how many more questions they can get wrong before the exam terminates and they fail
        }

        cout << endl; //creates a space in between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        box(5); //calls the box function to begin running and sends it the value that I want it to display in the box
        rans[4] = DisplayQuestions(); //calls the DisplayQuestions function to start running and then stores whatever value it returns into that specific string array index
        uans[4] = useranswer(); //calls the useranswer function to start running and then stores whatever value it returns into that specific string array index

        if(uans[4] == rans[4])
        {
            score += 10; //adds a value of 10 to the int variable
            correct += 1; //adds a value of 1 to the int variable
            cout << endl;//creates a space in between texts
            checkmark(); //calls the checkmark function to start running
        }
        else
        {
            strike -= 1; //subtracts a value of 1 from the int variable
            cout << endl; //creates a space in between texts
            x(); //calls the x function to begin running
            cout << endl; //creates a space in between texts
            cout << "CORRECT ANSWER: " << rans[4] << endl; //displays the correct answer to the user on the screen
            if(strike < 0)
            {
                cout << endl; //creates a space in between texts
                system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
                system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
                failed(info, 1); //calls the failed function to start running, sends it the structure variable that it needs to be able to access the variables within the structure and enter values into them, and the number 1
                break; //breaks out of the while true loop
            }
            cout << strike << " more mistakes allowed" << endl; //lets the user know how many more questions they can get wrong before the exam terminates and they fail
        }

        cout << endl; //creates a space in between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        box(6); //calls the box function to begin running and sends it the value that I want it to display in the box
        rans[5] = DisplayQuestions(); //calls the DisplayQuestions function to start running and then stores whatever value it returns into that specific string array index
        uans[5] = useranswer(); //calls the useranswer function to start running and then stores whatever value it returns into that specific string array index

        if(uans[5] == rans[5])
        {
            score += 10; //adds a value of 10 to the int variable
            correct += 1; //adds a value of 1 to the int variable
            cout << endl; //creates a space in between texts
            checkmark(); //calls the checkmark function to start running
        }
        else
        {
            strike -= 1; //subtracts a value of 1 from the int variable
            cout << endl; //creates a space in between texts
            x(); //calls the x function to begin running
            cout << endl; //creates a space in between texts
            cout << "CORRECT ANSWER: " << rans[5] << endl; //displays the correct answer to the user on the screen
            if(strike < 0)
            {
                cout << endl; //creates a space in between texts
                system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
                system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
                failed(info, 1); //calls the failed function to start running, sends it the structure variable that it needs to be able to access the variables within the structure and enter values into them, and the number 1
                break; //breaks out of the while true loop
            }
            cout << strike << " more mistakes allowed" << endl; //lets the user know how many more questions they can get wrong before the exam terminates and they fail
        }

        cout << endl; //creates a space in between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        box(7); //calls the box function to begin running and sends it the value that I want it to display in the box
        rans[6] = DisplayQuestions(); //calls the DisplayQuestions function to start running and then stores whatever value it returns into that specific string array index
        uans[6] = useranswer(); //calls the useranswer function to start running and then stores whatever value it returns into that specific string array index

        if(uans[6] == rans[6])
        {
            score += 10; //adds a value of 10 to the int variable
            correct += 1; //adds a value of 1 to the int variable
            cout << endl; //creates a space in between texts
            checkmark(); //calls the checkmark function to start running
        }
        else
        {
            strike -= 1; //subtracts a value of 1 from the int variable
            cout << endl; //creates a space in between texts
            x(); //calls the x function to begin running
            cout << endl; //creates a space in between texts
            cout << "CORRECT ANSWER: " << rans[6] << endl; //displays the correct answer to the user on the screen
            if(strike < 0)
            {
                cout << endl; //creates a space in between texts
                system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
                system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
                failed(info, 1); //calls the failed function to start running, sends it the structure variable that it needs to be able to access the variables within the structure and enter values into them, and the number 1
                break; //breaks out of the while true loop
            }
            cout << strike << " more mistakes allowed" << endl; //lets the user know how many more questions they can get wrong before the exam terminates and they fail
        }

        cout << endl; //creates a space in between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        box(8); //calls the box function to begin running and sends it the value that I want it to display in the box
        rans[7] = DisplayQuestions(); //calls the DisplayQuestions function to start running and then stores whatever value it returns into that specific string array index
        uans[7] = useranswer(); //calls the useranswer function to start running and then stores whatever value it returns into that specific string array index

        if(uans[7] == rans[7])
        {
            score += 10; //adds a value of 10 to the int variable
            correct += 1; //adds a value of 1 to the int variable
            cout << endl; //creates a space in between texts
            checkmark(); //calls the checkmark function to start running
        }
        else
        {
            strike -= 1; //subtracts a value of 1 from the int variable
            cout << endl; //creates a space in between texts
            x(); //calls the x function to begin running
            cout << endl; //creates a space in between texts
            cout << "CORRECT ANSWER: " << rans[7] << endl; //displays the correct answer to the user on the screen
            if(strike < 0)
            {
                cout << endl; //creates a space in between texts
                system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
                system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
                failed(info, 1); //calls the failed function to start running, sends it the structure variable that it needs to be able to access the variables within the structure and enter values into them, and the number 1
                break; //breaks out of the while true loop
            }
            cout << strike << " more mistakes allowed" << endl; //lets the user know how many more questions they can get wrong before the exam terminates and they fail
        }

        cout << endl; //creates a space in between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        box(9); //calls the box function to begin running and sends it the value that I want it to display in the box
        rans[8] = DisplayQuestions(); //calls the DisplayQuestions function to start running and then stores whatever value it returns into that specific string array index
        uans[8] = useranswer(); //calls the useranswer function to start running and then stores whatever value it returns into that specific string array index

        if(uans[8] == rans[8])
        {
            score += 10; //adds a value of 10 to the int variable
            correct += 1; //adds a value of 1 to the int variable
            cout << endl; //creates a space in between texts
            checkmark(); //calls the checkmark function to start running
        }
        else
        {
            strike -= 1; //subtracts a value of 1 from the int variable
            cout << endl; //creates a space in between texts
            x(); //calls the x function to begin running
            cout << endl; //creates a space in between texts
            cout << "CORRECT ANSWER: " << rans[8] << endl; //displays the correct answer to the user on the screen
            if(strike < 0)
            {
                cout << endl; //creates a space in between texts
                system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
                system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
                failed(info, 1); //calls the failed function to start running, sends it the structure variable that it needs to be able to access the variables within the structure and enter values into them, and the number 1
                break; //breaks out of the while true loop
            }
            cout << strike << " more mistakes allowed" << endl; //lets the user know how many more questions they can get wrong before the exam terminates and they fail
        }

        cout << endl; //creates a space in between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        box(10); //calls the box function to begin running and sends it the value that I want it to display in the box
        rans[9] = DisplayQuestions(); //calls the DisplayQuestions function to start running and then stores whatever value it returns into that specific string array index
        uans[9] = useranswer(); //calls the useranswer function to start running and then stores whatever value it returns into that specific string array index

        if(uans[9] == rans[9])
        {
            score += 10; //adds a value of 10 to the int variable
            correct += 1; //adds a value of 1 to the int variable
            cout << endl; //creates a space in between texts
            checkmark(); //calls the checkmark function to start running
        }
        else
        {
            strike -= 1; //subtracts a value of 1 from the int variable
            cout << endl; //creates a space in between texts
            x(); //calls the x function to begin running
            cout << endl; //creates a space in between texts
            cout << "CORRECT ANSWER: " << rans[9] << endl; //displays the correct answer to the user on the screen
            if(strike < 0)
            {
                cout << endl; //creates a space in between texts
                system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
                system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
                failed(info, 2); //calls the failed function to start running, sends it the structure variable that it needs to be able to access the variables within the structure and enter values into them, and the number 1
                break; //breaks out of the while true loop
            }
            cout << strike << " more mistakes allowed" << endl; //lets the user know how many more questions they can get wrong before the exam terminates and they fail
        }

        cout << endl; //creates a space in between texts
        system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

        cout << " ---------------" << endl; //messages for the user
        cout << "| EXAM COMPLETE |" << endl;
        cout << " ---------------" << endl;

        cout << "\nNAME: " << info.name << endl; //displays the user's name on screen by pulling it from the name string variable in the structure

        cout << "\nRESULT: PASSED" << endl; //stores the message into the file

        cout << "\nSCORE: " << correct << "/10" << "          PERCENTAGE: " << score << "%" << endl; //displays the correct and score values on screen with some messages for the user

        ofstream obj5; //declares the stream type, which in this case is ofstream, and the stream variable name
        obj5.open("CarTestQuestions_Input.txt", ios::app); //opens the text file and sets the stream operation mode

        assert(!obj5.fail()); //the failsafe that would terminate the program if the file I am trying to open fails

        obj5 << "\n" << info.name << endl; //stores the value held in the name string variable in the structure into the text file
        obj5 << "BORN: " << info.year << " - " << info.month << " - " << info.day << endl; //stores the value held in the name string variable in the structure into the text file
        obj5 << "PHONE NUMBER: " << info.number << endl; //stores the value held in the number string variable in the structure into the text file
        obj5 << "ADDRESS: " << info.address << endl; //stores the value held in the address string variable in the structure into the text file
        obj5 << "POSTAL CODE: " << info.code << endl; //stores the value held in the code string variable in the structure into the text file
        obj5 << "EXAM STATUS: COMPLETE" << endl; //stores the message into the file
        obj5 << "EXAM RESULT: PASSED" << endl; //stores the message into the file
        obj5 << "SCORE: " << correct << "/10" << endl; //stores the correct value into the file with some messages
        obj5 << "PERCENTAGE: " << score << "%" << endl; //stores the score into the file with some messages
        obj5 << "*******************************************" << endl; //stores the message into the file

        obj5.close(); //closes the file

        break; //breaks out of the while true loop
    }

    ofstream cleanfile; //declares the stream type, which in this case is ofstream, and the stream variable name
    cleanfile.open("CHECK.DAT", ios::trunc); //opens the text file and sets the stream operation mode to trunc, which clears all the contents of the file
    cleanfile << "\n" << endl;
    cleanfile.close(); //closes the file

    cout << endl; //creates a space in between texts
    system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
    system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
}

void Personinfo(char* ans) //this function houses the code for searching the text file and finding the exam results of an examinee, this function also collects the variable sent to it as a pointer so it can be used
{
    while(true) //this while true allows the entire code to be run as long as the user wants to continue searching the file for names
    {
        cout << " ----------------------------- " << endl; //messages for the user
        cout << "| EXAMINEE INFORMATION FINDER |" << endl;
        cout << " ----------------------------- " << endl;
        cout << "\nHere you can find the results and information regarding the person who has written the" << endl;
        cout << "G1 knowledge exam." << endl;
        cout << "\nNOTE: If nothing is displayed then it means the name you have entered can not" << endl;
        cout << "      be found in the database." << endl;

        string person, fileline; //declares my string variables

        cout << "\nEnter EXAMINEE NAME: "; //tells the user what they need to enter
        getline(cin,person); //stores the input if the user into the string variable
        cout << endl; //creates space in between texts

        ifstream read; //declares the stream type, which in this case is ifstream, and the stream variable name
        read.open("CarTestQuestions_Input.txt", ios::in); //opens the text file and sets the stream operation mode

        assert(!read.fail()); //the failsafe that would terminate the program if the file I am trying to open fails

        for(int f=0;f<267;f++)
        {
            getline(read,fileline); //reads the entire line in the file and sets it into the string variable
        }

        while(!read.eof()) //reads until the the end of the text file
        {
            getline(read,fileline); //reads the entire line in the file and sets it into the string variable so it can be used

            if(person == fileline)
            {
                while(fileline != "*******************************************") //reads the lines on the file until it reaches the line where it is full of that many stars, which is what I have inserted into the file at the end of each persons information as way to divide the information up
                {
                    getline(read,fileline); //reads the entire line in the file and sets it into the string variable so it can be used
                    cout << fileline << endl; //displays on screen the string variable where the contents of the file line are being held
                }
                break; //breaks out of the while loop
            }
        }
        read.close(); //closes the file
        cout << endl; //creates a space in between texts

        cout << "Y = Search Again" << endl; //messages for the user
        cout << "N = Return to Main Menu" << endl;

        do{ //begins the do-while loop that would allow for the user to enter the option again if they enter an illegal input
            cout << "Would you like to search again: "; cin >> *ans; //tells the user what they need to enter and then stores their input in the pointer
            cin.ignore();
            *ans = tolower(*ans); //sets whatever character the user enters into lowercases to make it easier for the code
            if(*ans != 'y' && *ans != 'n')
            {
                cout << "SELECT BETWEEN Y or N." << endl; //error message
            }
        } while(*ans != 'y' && *ans != 'n'); //the requirement that once met, will cause the do-while loop to repeat, thus not letting them exit the loop until they have entered the correct input

        if(*ans == 'n')
        {
            system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
            break; //breaks out of the while true loop
        }
        system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
    }
}

void AnswerKey() //this function holds the code that displays all the possible exam questions and their respective answers on screen
{
    string displayline; //declares the string variable

    cout << " ------------ " << endl; //messages for the user
    cout << "| ANSWER KEY |" << endl;
    cout << " ------------ " << endl;

    cout << "\nBelow you will find all the possible questions that may come up in the G1 examination, they" << endl; //messages for the user
    cout << "are of course in particular order as the question will come up in the exam in a random order." << endl;
    cout << "\nNOTE: You can find the answer to each question below the line of '-'.\n\n" << endl;

    ifstream answers; //declares the stream type, which in this case is ifstream, and the stream variable name
    answers.open("CarTestQuestions_Input.txt", ios::in); //opens the text file and sets the stream operation mode

    assert(!answers.fail()); //the failsafe that would terminate the program if the file I am trying to open fails

    for(int x=0;x<267;x++) //the for loop that will read the set number of lines in the file which I have entered into the for loop
    {
        getline(answers,displayline); //reads the entire line in the file and sets it into the string variable so it can be used
        cout << displayline << endl; //displays on screen the string variable where the contents of the file line are being held
    }

    answers.close(); //closes the file

    cout << endl; //creates the space in between texts
    system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
    system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
}

void Handbook() //this function opens the review file and displays all the handbook information within it which I have already entered into the file
{
    string printline; //declares the string variable

    cout << " ------------------ " << endl; //message for the user
    cout << "| DRIVERS HANDBOOK |" << endl;
    cout << " ------------------ " << endl;

    cout << "\nIf you would like to review some final things before attempting the exam, you can" << endl; //messages for the user
    cout << "read the drivers handbook here.\n" << endl;

    cout << "NOTE: I was unable to put in the entire book as that would have been too much for this" << endl; //messages for the user
    cout << "project but I have tried to put as much as I could and made sure to put in the info that" << endl;
    cout << "will be tested on the exam.\n\n" << endl;

    ifstream review; //declares the stream type, which in this case is ifstream, and the stream variable name
    review.open("REVIEW.txt", ios::in); //opens the text file and sets the stream operation mode

    assert(!review.fail()); //the failsafe that would terminate the program if the file I am trying to open fails

    while(!review.eof()) //reads till the end of the file
    {
        getline(review,printline); //reads the entire line in the file and sets it into the string variable so it can be used
        cout << printline << endl; //displays on screen the string variable where the contents of the file line are being held
    }

    review.close(); //closes the file
    cout << endl; //creates the space in between texts
    system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
    system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
}

void bibliography() //this functions mainly just displays on screen the sources where I got the exam questions and information in the handbook section of the program
{
    cout << " -------------- " << endl; //message for the user
    cout << "| BIBLIOGRAPHY |" << endl;
    cout << " -------------- " << endl;

    cout << "\nAll the exam questions and the drivers handbook shown in this project are not pieces of" << endl; //message for the user
    cout << " my work, I did not think of the questions nor the information shown in the drivers handbook." << endl;

    cout << "\nThis work is properties of their own respective creators, I will be linking where I got" << endl; //message for the user
    cout << "each thing below as a way to credit them." << endl;

    cout << "\nEXAM QUESTIONS: https://www.g1.ca/" << endl; //message for the user

    cout << "\nDRIVERS HANDBOOK: https://www.ontario.ca/document/official-mto-drivers-handbook\n\n" << endl; //message for the user

    system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
    system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
}

int main()
{
    system("color F1"); //changes the color of the background and the text

    title(); //calls the title function to start running
    cout << endl; //creates the space in between texts
    system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
    system("CLS"); //clears the screen and allows for the new content to be displayed cleanly

    while(true) //the while true loop that will keep on running the code until the user chooses to exit out of the entire program, until then no matter what option you choose, you will come back to this menu and it will keep on allowing you to choose a different option
    {
        int select, access; //declares my int variables
        char ans; //declares my char variables

        cout << " ----------- " << endl; //messages for the user
        cout << "| MAIN MENU |" << endl;
        cout << " ----------- " << endl;

        cout << "\nINSTRUCTIONS: Enter in the number that corresponds with the task you would like to do today.\n" << endl; //message for the user

        cout << " _________ " << endl; //messages for the user
        cout << "| G1 EXAM |\n" << endl;
        cout << "1 --> WRITE G1 KNOWLEDGE EXAM\n" << endl;

        cout << " ___________________ " << endl; //messages for the user
        cout << "| RESTRICTED ACCESS |\n" << endl;
        cout << "2 --> EXAMINEE INFORMATION FINDER" << endl;
        cout << "3 --> ANSWER KEY\n" << endl;

        cout << " _____________ " << endl; //messages for the user
        cout << "| EXAM REVIEW |\n" << endl;
        cout << "4 --> DRIVERS HANDBOOK\n" << endl;

        cout << " _______ " << endl; //messages for the user
        cout << "| EXTRA |\n" << endl;
        cout << "5 --> BIBLIOGRAPHY" << endl;
        cout << "6 --> TERMINATE PROGRAM\n" << endl;

        do{ //begins the do-while loop that would allow for the user to enter the option again if they enter an illegal input
            cout << "YOUR SELECTION: "; cin >> select; //tells the user what they need to enter and then stores the input in the variable
            cin.ignore();
            if(select <= 0 || select > 6)
            {
                cout << "MAKE YOUR CHOICE BETWEEN THE PROVIDED OPTIONS." << endl; //error message
            }
        } while(select <= 0 || select > 6); //the requirement that once met, will cause the do-while loop to repeat, thus not letting them exit the loop until they have entered the correct input

        if(select == 1)
        {
            system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
            Exam(); //calls the Exam function to start running
        }
        else if(select == 2)
        {
            cout << "\n(CODE = 17689)" << endl; //message for the user
            cout << "ENTER ACCESS CODE: "; cin >> access; //tells the user what they need to enter and then stores the input in the variable
            cin.ignore();

            if(access == 17689)
            {
                cout << "\n***ACCESS GRANTED***\n" << endl; //message for the user
                system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
                system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
                Personinfo(&ans); //calls the Personinfo function to start running and sends the ans variable to it as a reference where it can be collect, made into a pointer and then used in the function
            }
            else
            {
                cout << "\n***ACCESS DENIED***\n" << endl; //message for the user
                system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
                system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
            }
        }
        else if(select == 3)
        {
            cout << "\n(CODE = 34986)" << endl; //message for the user
            cout << "ENTER ACCESS CODE: "; cin >> access; //tells the user what they need to enter and then stores the input in the variable
            cin.ignore();

            if(access == 34986)
            {
                cout << "\n***ACCESS GRANTED***\n" << endl; //message for the user
                system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
                system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
                AnswerKey(); //calls the AnswerKey function to start running
            }
            else
            {
                cout << "\n***ACCESS DENIED***\n" << endl; //message for the user
                system("pause"); //pauses the screen so the user gets a chance to properly look at everything before they can press a button to keep moving
                system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
            }
        }
        else if(select == 4)
        {
            system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
            Handbook(); //calls the Handbook function to start running
        }
        else if(select == 5)
        {
            system("CLS"); //clears the screen and allows for the new content to be displayed cleanly
            bibliography(); //calls the bibliography function to start running
        }
        else
        {
            break; //breaks out of the while true loop
        }
    }
    cout << "\nThank you for visiting us today, we hope you had nice experience!" << endl; //message for the user
    cout << "Have a great day!" << endl;
    return 0; //terminates the program
}
