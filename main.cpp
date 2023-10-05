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
        // search for the wallet using a loop
        for(int i = 0; i < walletCount; i++)
        {
            if(walletArray[i].walletId == walletID)
            {
                // incremet amount
                walletArray[i].balance += amount;

                // display a success message
                cout << "\nFunds added successfully. New balance: R " << walletArray[i].balance << "\n";

                // break outside the loop
                break;
            }
            else if(walletArray[i].walletId == walletID && walletArray[i].pin != pin)
            {
                do
                {
                    // display a error message for incorrect pin
                    cout << "\nIncorrect Pin. Access denied.\n";

                    // user input for pin
                    cout << "Enter Pin: ";
                    cin >> pin;

                } while(pin != walletArray[i].pin);


                // break outside the loop
                break;
            }
            else
            {
                cout << "\nWallet Not Found.\n";
            }
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
                cout << "Error! Enter a Positive Amount.\n";

                // input for amount
                cout << "Enter Amount: R ";
                cin >> amount;

            } while (amount < 0);
        }
        // search for the wallet using a loop
        for(int i = 0; i < walletCount; i++)
        {
            if(walletArray[i].walletId == walletID)
            {
                if(walletArray[i].balance >= amount)
                {
                    // declare withdrawal reference variable
                    int referenceNumber;

                    // assign a random reference number
                    referenceNumber = generateRandomReference();

                    // incremet amount
                    walletArray[i].balance -= amount;

                    // display a success message
                    cout << "\nWithdrawal successfully. New balance: R " << walletArray[i].balance << "\n";

                    // display the reference number
                    cout << "\nWithdrawal reference number: " << referenceNumber << endl;

                    // break outside the loop
                break;
                }
                else
                {
                    //error message fr invalid amount
                    cout << "\nInsufficient Funds.\n";
                }
            }
            else if(walletArray[i].walletId == walletID && walletArray[i].pin != pin)
            {
                do
                {
                    // display a error message for incorrect pin
                    cout << "\nIncorrect Pin. Access denied.\n";

                    // user input for pin
                    cout << "Enter Pin: ";
                    cin >> pin;

                } while(pin != walletArray[i].pin);


                // break outside the loop
                break;
            }
            else
            {
                cout << "\nWallet Not Found.\n";
            }
        }
    }
}

// function for generating random numbers for withdrawal reference
int generateRandomReference()
{
    // declare a random number variable
    int randomNumber;

    // generate a random number
    randomNumber = 1000000000 + rand() % 9999999999;

    // return the generated number
    return randomNumber;
}

// Function to transfer funds to another wallet
void transferFunds(digitalWallet* walletArray, string senderWallet, int senderPin, int walletCount,string recipientWallet, double amount)
{
    // search for the wallet using a loop
        for(int i = 0; i < walletCount; i++)
        {
            if(walletArray[i].walletId == senderWallet && walletArray[i].pin == senderPin)
            {
                if(walletArray[i].pin != senderPin)
                {
                    do
                    {
                        // display a error message for incorrect pin
                        cout << "\nIncorrect Pin. Access denied.\n";

                        // user input for pin
                        cout << "Enter Pin: ";
                        cin >> senderPin;

                    } while(senderPin != walletArray[i].pin);
                }

                //search for recipient wallet id
                for(int j = 0; j < walletCount; j++)
                {
                    if(recipientWallet == walletArray[j].walletId)
                    {
                        if(walletArray[i].balance >= amount)
                        {
                            // decrement sender wallet balance by amount
                            walletArray[i].balance -= amount;

                            // increment recipient balance by 1
                            walletArray[j].balance += amount;

                            // display success message
                            cout << "Transfer Successful. New Balance: R" << walletArray[i].balance << endl;

                            //break of the loop
                            break;
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
}

// Function to display wallet balance
void viewBalance(digitalWallet* walletArray,string accountId, int pin, int walletCount)
{
    // declare a bool variable to work as a flag value
    bool isFound = false;

    for(int i = 0; i < walletCount; i++)
    {
        if(accountId == walletArray[i].walletId)
        {
            // when the wallet is found and the pin matches
            if(pin == walletArray[i].pin)
            {
                // display the balance
                printf("Balance: R%.2f", walletArray[i].balance);

                // set is found to true
                isFound = true;

                // print an empty line
                printf("\n");

                // break of the loop
                break;
            }
            // when the wallet is found but the pin does not match
            else
            {
                do
                {
                    // prompt the pin again
                    cout << "Invalid Pin. Enter Again: ";
                    cin >> pin;

                } while(pin != walletArray[i].pin);

                // display the balance
                printf("Balance: R%.2f", walletArray[i].balance);

                // set is found to true
                isFound = true;

                // break out of the loop
                break;
            }
        }
    }

    // if the wallet is not found display an error message
    if(!isFound)
    {
        printf("Wallet Not Found\n");
    }
}
