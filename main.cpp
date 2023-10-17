/*
Name: Thuso
Surname: Ndou
Student No: 37853058

A C++ digital wallet program that can be used for creating and managing wallets,
add funds, remove funds, send funds to others, and check the balance of your wallet.
*/
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

// Define a wallet structure
struct digitalWallet
{
    string walletId;
    string walletHolderName;
    float balance;
    int pin;
};

// Function prototype
void createWallet(digitalWallet* walletArray, int &walletCount);
void addFunds(digitalWallet *walletArray,string walletID, int pin, double amount, int walletCount);
void withdrawFunds(digitalWallet* walletArray, string walletID, int pin, double amount, int walletCount);
int generateRandomReference();
void transferFunds(digitalWallet* walletArray, string senderWallet, int senderPin,int walletCount, string recipientWallet, double amount);
void viewBalance(digitalWallet* walletArray,string accountId, int pin, int walletCount);

int main()
{
    // Declare variable
    string sUserChoice;
    int userChoice;
    int walletCount = 0;
    digitalWallet newWallet[2];
    digitalWallet* pNewWallet = newWallet;

    // Display welcome Message
    printf("%46s","Welcome To The Digital Wallet System\n");

    do
    {
        // Menu Heading
        printf("\n|-------------------------------------------------------|\n");
        printf("|%57s", "DIGITAL MONEY                      |\n");
        printf("|-------------------------------------------------------|\n");

        // display menu
        printf("|%18s %38s", "1. Create Wallet", "4. Transfer Funds     |\n");
        printf("|%17s %39s", "2. Fund Account", "5. View Balance       |\n");
        printf("|%19s %37s", "3. Withdraw Funds" ,"6. Exit               |\n");
        printf("|_______________________________________________________|\n");

        // user input for menu selection
        printf("|%15s", "Menu Number: ");
        cin >> sUserChoice;

        // check if the value entered is a string
        while(!isdigit(sUserChoice[0]))
        {
            // Display error message
            cout << "\nPlease Enter A Numeric Menu Number: \n";
            cin.ignore();
            cin >> sUserChoice;
        }

        // convert a string input an integer
        userChoice = stoi(sUserChoice);

        // declare variables to use inside the switch
        string accountID;
        string recipientID;
        double amount;
        int pin;

        switch(userChoice)
        {
            case 1:
                createWallet(pNewWallet,walletCount);
                break;
            case 2:
                // user input for account id
                cout << "\nEnter Account ID: ";
                cin.ignore();
                cin >> accountID;

                // user input for wallet pin
                cout << "Enter Wallet Pin: ";
                cin >> pin;

                // user input for amount to fund
                cout << "Enter Wallet Amount: R ";
                cin >> amount;

                // function call for adding funds
                addFunds(pNewWallet, accountID, pin, amount, walletCount);
                break;
            case 3:
                // user input for account id
                cout << "\nEnter Account ID: ";
                cin.ignore();
                cin >> accountID;

                // user input for wallet pin
                cout << "Enter Wallet Pin: ";
                cin >> pin;

                // user input for amount to fund
                cout << "Enter Withdrawal Amount: R ";
                cin >> amount;

                // function call for withdrawing funds
                withdrawFunds(pNewWallet, accountID, pin, amount, walletCount);
                break;
            case 4:
                // user input for account id
                cout << "\nEnter Account ID: ";
                cin.ignore();
                cin >> accountID;

                // user input for wallet pin
                cout << "Enter Wallet Pin: ";
                cin >> pin;

                // user input for recipient wallet id
                cout << "Enter Recipient Account: ";
                cin.ignore();
                cin >> recipientID;

                // user input for amount to fund
                cout << "Enter Transfer Amount: R ";
                cin >> amount;

                // call function for transfering funds
                transferFunds(pNewWallet, accountID, pin, walletCount, recipientID, amount);
                break;
            case 5:
                // user input for account id
                cout << "\nEnter Account ID: ";
                cin.ignore();
                cin >> accountID;

                // user input for wallet pin
                cout << "Enter Wallet Pin: ";
                cin >> pin;

                // call function
                viewBalance(pNewWallet, accountID, pin ,walletCount);
                break;
            case 6:
                // Display a thank you message
                printf("\nThank You For Digitalizing With Us '_'.\n");
                break;
            default:
                printf("Inalid Option. Enter a Valid Option(1, 2, 3, 4)\n");
                break;
        }

    } while(userChoice != 6);

    return 0;
}

// function for creating a wallet
void createWallet(digitalWallet* walletArray, int &walletCount)
{
    // input for wallet id
    cout << "\nEnter wallet ID: ";
    cin.ignore();
    getline(cin,walletArray[walletCount].walletId);

    //input for walllet holder names
    cout << "Enter Account Holder Name: ";
    getline(cin,walletArray[walletCount].walletHolderName);

    // input for wallet amount to fund
    cout << "Enter amount to Fund: R ";
    cin >> walletArray[walletCount].balance;

    // input for wallet pin
    cout << "Enter Wallet Pin: ";
    cin >> walletArray[walletCount].pin;

    // increment by one
    walletCount++;

    cout << "\nWallet Was Successfully Created.\n";
}

// function for adding funds to the wallet
void addFunds(digitalWallet *walletArray,string walletID, int pin, double amount, int walletCount)
{
    // when the is no wallet
    if(walletCount == 0)
    {
        cout << "\nWallet Not Found.\n";
    }
    else
    {
        // input validation for fund amount
        if(amount < 0)
        {
            do
            {
                // error message for amount less than zero
                cout << "Error! Enter a Positive Amount.\n";

                // input for amount
                cout << "Enter Amount: R ";
                cin >> amount;

            } while (amount < 0);
        }

        // boolean variable for wallet id search
        bool isFound = false;

        // declare a variable for index number for search
        int index = 0;

        // search for the wallet using a loop
        for(int i = 0; i < walletCount; i++)
        {
            if(walletArray[i].walletId == walletID)
            {
                // set is found to true
                isFound = true;

                // index number
                index = i;

                // break outside the loop
                break;
            }
        }

        if(isFound)
        {
            if(walletArray[index].pin != pin)
            {
                do
                {
                    // display a error message for incorrect pin
                    cout << "\nIncorrect Pin. Access denied.\n";

                    // user input for pin
                    cout << "Enter Pin: ";
                    cin >> pin;

                } while(pin != walletArray[index].pin);

            }

            // incremet amount
            walletArray[index].balance += amount;

            // display a success message
            cout << "\nFunds added successfully. New balance: R " << walletArray[index].balance << "\n";

        }
        else
        {
            cout << "\nWallet Not Found.\n";
        }
    }
}

// function for withdrawal of funds from wallet
void withdrawFunds(digitalWallet* walletArray, string walletID, int pin, double amount, int walletCount)
{
    // when the is no wallet
    if(walletCount == 0)
    {
        cout << "\nWallet Not Found.\n";
    }
    else
    {
        // input validation for fund amount
        if(amount < 0)
        {
            do
            {
                // error message for amount less than zero
                cout << "Invalid Amount.\n";

                // input for amount
                cout << "Enter Amount: R ";
                cin >> amount;

            } while (amount < 0);
        }

        // declare variable for is found
        bool isFound = false;

        // declare variable for index number
        int index = 0;

        // search for the wallet using a loop
        for(int i = 0; i < walletCount; i++)
        {
            if(walletArray[i].walletId == walletID)
            {
                // set is found to true
                isFound = true;

                // assign the index number
                index = i;

                // break outside the loop
                break;

            }
        }

        if(isFound)
        {
            if(walletArray[index].pin != pin)
            {
                do
                {
                    // display a error message for incorrect pin
                    cout << "\nIncorrect Pin. Access denied.\n";

                    // user input for pin
                    cout << "Enter Pin: ";
                    cin >> pin;

                } while(pin != walletArray[index].pin);
            }
            else
            {
                if(walletArray[index].balance >= amount)
                {
                    // declare withdrawal reference variable
                    int referenceNumber;

                    // assign a random reference number
                    referenceNumber = generateRandomReference();

                    // incremet amount
                    walletArray[index].balance -= amount;

                    // display a success message
                    cout << "\nWithdrawal successfully. New balance: R " << walletArray[index].balance << "\n";

                    // display the reference number
                    cout << "\nWithdrawal reference number: " << referenceNumber << endl;
                }
                else
                {
                    //error message fr invalid amount
                    cout << "\nInsufficient Funds.\n";
                }
            }
        }
        else
        {
            cout << "\nWallet Not Found.\n";
        }
    }
}

// function for generating random numbers for withdrawal reference
int generateRandomReference()
{
    // declare a random number variable
    int randomNumber;

    // generate a random number
    randomNumber = rand() % 10000000000 ;

    // return the generated number
    return randomNumber;
}

// Function to transfer funds to another wallet
void transferFunds(digitalWallet* walletArray, string senderWallet, int senderPin, int walletCount,string recipientWallet, double amount)
{
    // declare a boolean variable
    bool isFound = false;

    //declare variable for index number
    int index = 0;
    int indexRecipient = 0;

    // search for the wallet using a loop
    for(int i = 0; i < walletCount; i++)
    {
        if(walletArray[i].walletId == senderWallet)
        {
            //set is found to true
            isFound = true;

            //index number
            index = i;

            //break out the loop
            break;
        }
    }

    if(isFound)
    {
        if(walletArray[index].pin != senderPin)
        {
            do
            {
                // display a error message for incorrect pin
                cout << "\nIncorrect Pin. Access denied.\n";

                // user input for pin
                cout << "Enter Pin: ";
                cin >> senderPin;

            } while(senderPin != walletArray[index].pin);
        }
        else
        {
            // boolean variable for recipient wallet
            bool isAvailable = false;

            //search for recipient wallet id
            for(int j = 0; j < walletCount; j++)
            {
                if(recipientWallet == walletArray[j].walletId)
                {
                    //set is available to true
                    isAvailable = true;

                    //asign index value to recipient index
                    indexRecipient = j;

                    // break out of the loop
                    break;
                }
            }

            if(isAvailable)
            {
                if(walletArray[index].balance >= amount)
                {
                    // decrement sender wallet balance by amount
                    walletArray[index].balance -= amount;

                    // increment recipient balance by 1
                    walletArray[indexRecipient].balance += amount;

                    // display success message
                    cout << "Transfer Successful. New Balance: R" << walletArray[index].balance << endl;
                }
                else
                {
                    // display an insufficient funds message
                    cout << "\nInsufficient Funds.\n";
                }
            }
            else
            {
                // display message showing recipient not found
                cout << "\nRecipient Wallet Not Found.\n";
            }
        }
    }
    else
    {
        cout << "\nWallet Not Found.\n";
    }
}

// Function to display wallet balance
void viewBalance(digitalWallet* walletArray,string accountId, int pin, int walletCount)
{
    // declare a bool variable to work as a flag value
    bool isFound = false;

    //declare variable for index number
    int index = 0;

    for(int i = 0; i < walletCount; i++)
    {
        if(accountId == walletArray[i].walletId)
        {
            // set is found to true
            isFound = true;

            // assign index
            index = i;

            // break of the loop
            break;
        }
    }

    if(isFound)
    {
        if(pin != walletArray[index].pin)
        {
            // when a wrong pin is entered
            do
            {
                // prompt the pin again
                cout << "Invalid Pin. Enter Again: ";
                cin >> pin;

            } while(pin != walletArray[index].pin);
        }
        else
        {
            // display the balance
            printf("Balance: R%.2f\n", walletArray[index].balance);
        }
    }
    else
    {
        printf("Wallet Not Found\n");
    }
}
