// Created by Reece Kassiram-Brennan (w1728853) | Numbers Game CW | Object Orientated Programming

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#define MIN_LIST 1
#define MAX_LIST 10
#define MIN_VALUE 100
#define MAX_VALUE 999

void intro() 
{
    cout << "Welcome to the Numbers Game\n You will be given numbers 1 - 10 and will have to calculate a random number between 100 - 999\n you will be able to use 4 operations which are; + , - , * , /\n";
}

class Number
{

        protected:

            int chosenNumber;
            

        public:
            
            Number(int num) : chosenNumber(num)// constructor for number class
            {

            }

            virtual int getValue() 
            {
               return chosenNumber;
            }

            virtual bool isSplittable()
            {
               return false;
            }

            virtual void split(vector<Number*> &myNumbers, int position)
            {

            }

            virtual void printMe(bool checkTop)
            {
            
            }
};

class givenNumber : public Number
{
    public:

        givenNumber(int num) : Number(num) // initialises the number constructor
        {

        }

        int getValue() override
        {
            return chosenNumber;
        }

        bool isSplittable() override
        {
            return false;
        }

        void split(vector<Number*>& myNumbers, int position) override
        {

        }

        void printMe(bool checkTop) override
        {
            cout << chosenNumber;
        }
};

class compositeNumber : public Number
{

    Number* split1;
    Number* split2;
    char operation;

    public:

        compositeNumber(int num, Number* component1, Number* component2, char Op) : Number(num), split1(component1), split2(component2), operation(Op) // constructor for making a composite number
        {

        }

        int getValue() override
        {
            return chosenNumber;
        }

        bool isSplittable() override
        {
            return true;
        }

        void split(vector<Number*>& myNumbers, int position) override
        {
            myNumbers.push_back(split1);
            myNumbers.push_back(split2);
        }

        void printMe(bool checkTop) override
        {

            if (checkTop)
            {
               cout << chosenNumber << " = ";
            }
            cout << "(";
            split1->printMe(false);
            cout << operation;
            split2->printMe(false);
            cout << ")";


        }
};

class NumberList
{
    vector<Number*> numbersList; // vector containing my list of numbers
    int targetNumber; 


    public:
        NumberList() // constructor which makes a new instance of the NumberList class
        {
            for (int i = MIN_LIST; i <= MAX_LIST; i++) // numberslist starts at 1 (MIN_LIST) and goes to 10 (MAX_LIST)
            {
                numbersList.push_back(new givenNumber(i)); //pushes back numbers to the end of the list
            }

            targetNumber = rand() % 899 + 100; // makes a random target number between 100 to 999
            cout << "Target number is " << targetNumber << endl;

                
        }

        void getTarget()
        {
            vector<Number*> tempNumberList;
            int tempNum;
            int tempNum2;
            int target = 0;

            for (int i = 0; i < numbersList.size(); i++)
            {
                tempNumberList.push_back(numbersList[i]);
            }

            tempNum = rand() % tempNumberList.size(); // generates a random number between 0 and the size of the list
            target = tempNumberList[tempNum]->getValue(); // sets the target number inside the list
            tempNumberList.erase(tempNumberList.begin() + tempNum); // erases the number the target will set as

            while (target < 100 || target > 999)
            {
                tempNum2 = rand() % 4; // indicates number of operations we have

                switch (tempNum2)
                {
                    case 0: // adding a random number from target
                        if (target < 999)
                        {
                            tempNum = rand() % tempNumberList.size();
                            target += tempNum;
                            tempNumberList.erase(tempNumberList.begin() + tempNum);
                        }
                        break;

                    case 1: // subtracting a random number from target
                        if (target > 100)
                        {
                            tempNum = rand() % tempNumberList.size();

                            if (target > tempNum)
                            {
                                target -= tempNum;
                                tempNumberList.erase(tempNumberList.begin() + tempNum);
                            }
                            
                        }
                        break;

                    case 2: // multiplying a random number from target
                        if (target < 999)
                        {
                            tempNum = rand() % tempNumberList.size();
                            target *= tempNum;
                            tempNumberList.erase(tempNumberList.begin() + tempNum);
                        }
                        break;

                    case 3: // dividing a random number from target
                        if (target > 100)
                        {
                            tempNum = rand() % tempNumberList.size();
                            
                            if (target % tempNum == 0) // no remainders
                            {
                                target /= tempNum;
                                tempNumberList.erase(tempNumberList.begin() + tempNum);
                            }
                            
                        }
                        break;
                }

            }
        }
        
        void add(int x, int y)
        {
            int position1;
            int position2;
            for (int i = 0; i < numbersList.size(); i++) //iterates through the list
            {
                if (numbersList[i]->getValue() == x) // if x is found in the list
                {
                    position1 = i;
                    break;
                }
            }
            for (int i = 0; i < numbersList.size(); i++)
            {

                if (numbersList[i]->getValue() == y && i != position1)
                {
                    position2 = i;
                    break;
                }
            }
            numbersList.push_back(new compositeNumber(numbersList[position1] -> getValue() + numbersList[position2] -> getValue(), numbersList[position1], numbersList[position2], '+')); // creates a new composite number of x and y and sets the three variables        
            numbersList.erase(numbersList.begin() + position1);
            numbersList.erase(numbersList.begin() + position2 - (position1 < position2));
        }


        void subtract(int x, int y)
        {
            int position1;
            int position2;
            for (int i = 0; i < numbersList.size(); i++) //iterates through the list
            {
                if (numbersList[i]->getValue() == x) // if x is found in the list
                {
                    position1 = i;
                    break;
                }
            }
            for (int i = 0; i < numbersList.size(); i++)
            {

                if (numbersList[i]->getValue() == y && i != position1)
                {
                    position2 = i;
                    break;
                }
            }
            numbersList.push_back(new compositeNumber(numbersList[position1]->getValue() - numbersList[position2]->getValue(), numbersList[position1], numbersList[position2], '-')); // creates a new composite number of x and y and sets the three variables
            numbersList.erase(numbersList.begin() + position1);
            numbersList.erase(numbersList.begin() + position2 - (position1 < position2));
        }

        void multiply(int x, int y)
        {
            int position1;
            int position2;
            for (int i = 0; i < numbersList.size(); i++) //iterates through the list
            {
                if (numbersList[i]->getValue() == x) // if x is found in the list
                {
                    position1 = i;
                    break;
                }
            }
            for (int i = 0; i < numbersList.size(); i++)
            {

                if (numbersList[i]->getValue() == y && i != position1)
                {
                    position2 = i;
                    break;
                }
            }
            numbersList.push_back(new compositeNumber(numbersList[position1]->getValue() * numbersList[position2]->getValue(), numbersList[position1], numbersList[position2], '*')); // creates a new composite number of x and y and sets the three variables
            numbersList.erase(numbersList.begin() + position1);
            numbersList.erase(numbersList.begin() + position2 - 1);
        }

        void divide(int x, int y)
        {
            int position1;
            int position2;
            for (int i = 0; i < numbersList.size(); i++) //iterates through the list
            {
                if (numbersList[i]->getValue() == x) // if x is found in the list
                {
                    position1 = i;
                    break;
                }
            }
            for (int i = 0; i < numbersList.size(); i++)
            {

                if (numbersList[i]->getValue() == y && i != position1)
                {
                    position2 = i;
                    break;
                }
            }
            numbersList.push_back(new compositeNumber(numbersList[position1]->getValue() / numbersList[position2]->getValue(), numbersList[position1], numbersList[position2], '/')); // creates a new composite number of x and y and sets the three variables
            numbersList.erase(numbersList.begin() + position1);
            numbersList.erase(numbersList.begin() + position2 - 1);
        }

        void split(int x)
        {
            int position1;
            bool isFound = false;

            for (int i = 0; i < numbersList.size(); i++) //iterates through the list
            {
                if (numbersList[i]->getValue() == x) // if x is found in the list
                {
                    position1 = i;
                    isFound = true;
                    if (numbersList[i]->isSplittable())
                    {
                       numbersList[i]->split(numbersList, position1);
                       delete numbersList[i];
                       numbersList.erase(numbersList.begin() + i);
                       return;
                    }
                }
            }
            if (isFound)
            {
                cout << "Number chosen is not splittable!!!" << endl;
                return;
            }

            cout << "Number was not found" << endl;


        }

        bool checkNumber(int x)
        {
            bool isNumList = false; // sets the variable isNumList to false by default
            for (int i = 0; i < numbersList.size(); i++) //iterates through the list
            {
                if (numbersList[i]->getValue() == x) // if x is found in the list
                {
                    isNumList = true; // set the variable isNumList to true 
                    break; // breaks out of the for loop
                }
            }

            return isNumList;
        }

        void print()
        {
            for (int i = 0; i < numbersList.size(); i++) //iterates through the list
            {
                numbersList[i]->printMe(true);
                if (i != numbersList.size())
                {
                    cout << ", ";
                }
            }
        }

        bool targetFound()
        {
            bool isNumList = false; // sets the variable isNumList to false by default
            for (int i = 0; i < numbersList.size(); i++) //iterates through the list
            {
                if (numbersList[i]->getValue() == targetNumber) // if target number is found in the list
                {
                    isNumList = true; // set the variable isNumList to true 
                    break; // breaks out of the for loop
                }
            }

            return isNumList;
        }
};

bool inputs(NumberList* numlist)
{
    int nums1;
    int nums2;
    string operation;
    cout << "Select 2 numbers you want to use from the list and type the operation you wish to use..." << endl;
    cin >> operation;
    if (operation == "quit")
    {
        return true;
    }
    cin >> nums1;
    if (operation == "add" || operation == "subtract" || operation == "multiply" || operation == "divide")
    {
        cin >> nums2;

        if (numlist->checkNumber(nums1) && numlist->checkNumber(nums2))
        {

            if (operation == "add")
            {
                numlist->add(nums1, nums2);
            }

            if (operation == "subtract")
            {
                if (nums1 > nums2)
                {
                    numlist->subtract(nums1, nums2);
                }
                else
                {
                    cout << "Number cannot be negative" << endl;
                }
            }

            if (operation == "multiply")
            {
                numlist->multiply(nums1, nums2);
            }

            if (operation == "divide")
            {
                if (nums1 % nums2 == 0)
                {
                    numlist->divide(nums1, nums2);
                }
                else
                {
                    cout << "Number cannot be divided" << endl;
                }
            }
        }
        else 
        {
            cout << "Number not found!!!" << endl;
        }
    }
    else if (operation == "split")
    {
        numlist->split(nums1);
    }

    

    return false;
}

int main()
{
    srand(time(NULL)); // makes sure it always generates a new random number
    bool isQuit = false;
    while (true)
    {
        intro();
        NumberList* listNum = new NumberList();
        while (true)
        {
            listNum->print();
            isQuit = inputs(listNum);
            if (isQuit)
            {
                cout << "You have Quit, Goodbye" << endl;
                break;
            }

            if (listNum->targetFound())
            {
                cout << "YOU WIN!!!" << endl;
                break;
            }
        }

        if (isQuit)
        {
            break;
        }
    }
}
