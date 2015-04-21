/****************************************************
*  SearchFunction
*  This function used to search data from business name,
*  address, type, closet BTS, Closet MRT and show result
*  on monitor.
*  Created by Naruesorn Sampanpaisarn
*    4 December 2012
*
*
****************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"



void searchByName(BUSINESS_T business[],int businessCount);
void searchByaddress(BUSINESS_T business[],int businessCount);
void searchByBusinessType(BUSINESS_T business[],int businessCount);
void searchByBTS(BUSINESS_T business[],int businessCount);
void searchByMRT(BUSINESS_T business[],int businessCount);
void displayData(BUSINESS_T business);
void dataError();


void searchFunction(BUSINESS_T business[],int businessCount) // search function
    {
    int  searchNum = 0;     // declare for store number
    int checkLoop = 1;     // declare for loop
    char input[32];        // declare for store data input
    printf("*****************************************************\n");
    printf("*****************************************************\n");
    printf("**                                                 **\n");
    printf("**  Search By  Enter                               **\n");
    printf("**         1  Name of Business                     **\n");
    printf("**         2  Street Name                          **\n");
    printf("**         3  Street Number                        **\n");
    printf("**         4  Nearest BTS                          **\n");
    printf("**         5  Nearest MRT                          **\n");
    printf("**         6  Exit From search                     **\n");
    printf("**                                                 **\n");
    printf("*****************************************************\n");
    printf("*****************************************************\n");
    while (checkLoop != 0)
        {
        printf("Enter number for Search :"); // get data from user
        fgets(input,32, stdin);
        sscanf(input,"%d",&searchNum); 
        switch (searchNum)
            {
            case 1:
                searchByName(business,businessCount);
                // call function search by name
                break;
            case 2:
                searchByaddress(business,businessCount);
                // call function searchby street name
                break;
            case 3:
                searchByBusinessType(business,businessCount);
                // call function search by type of business
                break;
            case 4:
                searchByBTS(business,businessCount);
                // call function search by BTS
                break;
            case 5:
                searchByMRT(business,businessCount);
                // call function search by MRT
                break;
            case 6:
                checkLoop = 0;
                // exit function Search
            default:
                dataError(); // print data error message
                break;
            }
        }
   }


void searchByName(BUSINESS_T business[],int businessCount) // Function for search by name
    {
    char businessName[50];      // declare for name of business
    int i;                      // declare for loop
    int j;                      // declare for loop
    int checkLoop = 1;          // declare for check loop
    int matchingNameCount = 0;  // declare for count matching name
 
    printf("Enter Name of Business : ");
    fgets(businessName,32, stdin);     // get data from user
    businessName[strlen(businessName)-1]='\0'; // set last character to blank
    for (i=0;i<strlen(businessName); i++)
        {
        tolower(businessName[i]);      // set all alphabet to small alphabet
        }

    for (j=0; j<businessCount; j++)
        {
        if(strstr(business[j].name,businessName) != NULL) // check string in name
            {
            displayData(business[j]); // if matching show result
            matchingNameCount++;      // add count of matching
            }
        }

    if(matchingNameCount == 0)        // condition for not matching
        {
        printf("*********************************");
        printf(" Not Found name matching"); // display message
        printf("*********************************");
        }
    }


void searchByaddress(BUSINESS_T business[],int businessCount) // Function for search by address
    {
    char address[32];         // declare for address of business
    int checkLoop = 1;        // declear for check loop
    int i;                    // declare for loop
    int j;                    // declare for loop
    int matchingaddressCount = 0;   // decleare for count matching address
    printf("Enter Name or Number of Street : ");
    fgets(address,32,stdin);        // get data from user
    address[strlen(address)-1] = '\0'; // set last character to blank

    for (i=0;i<strlen(address); i++)
        {
        tolower(address[i]);  // set all alphabet to small alphabet
        }

    for (j=0; j<businessCount; j++)
        {
        if(strstr(business[j].address,address) != NULL)
            {
            displayData(business[j]);  // if matching show result
            matchingaddressCount++;    // add count of matching
            }
        }
    if (matchingaddressCount == 0)     // condition for not matching
        {
        printf("*********************************");
        printf(" Not Found address matching"); // display message
        printf("*********************************");
        }
    }


void searchByBusinessType(BUSINESS_T business[],int businessCount)
     // Function for search by type of business
    {
    int businessType;           // declare for type of business
    int checkLoop = 1;          // declare for check loop
    int j;                      // declare for loop
    int businessTypeCount=0;    // declare for count matching business type
    char input[32];             // declare for input
    printf("****************************");
    printf("Business type ");
    printf(" 1  is hotel");
    printf(" 2  is Restaurant");
    printf(" 3  is Bar");
    printf(" 4  is Travel Agency");
    printf(" 5  is Spa");
    printf(" 6  is Shop");
    printf("****************************");
    while (checkLoop != 0)
        {
        printf("type number of business type: ");
        fgets(input,32,stdin);
        sscanf(input,"%d",&businessType);
        if((businessType < 7) && (businessType>0))
         // condition for check correct number
            {
            checkLoop = 0; // set equal to zero for end this loop
            }
        else
            {
            dataError();   // show data incorrect message
            }
        }
    for (j=0; j<businessCount; j++)
        {
        if (businessType == business[j].type) // check matching business type
            {
            displayData(business[j]);         // if matching show result
            businessTypeCount++;              // add count of matching
            }
        }
    if(businessTypeCount == 0) // condition for not matching
        {
        printf("*********************************");
        printf("Not found business type matching"); // display message
        printf("*********************************");
        }
    }


void searchByMRT(BUSINESS_T business[],int businessCount)
    // Function for search by nearest MRT station
    {
    int MRTstationNum;          // declare for number of MRT station
    int MRTMatchingCount=0;     // declare for count matching station
    int MRTstationAmount = 19;  // declare for max station
    int j;                      // declare for loop
    int i;                      // declare for loop
    char input[32];             // declare for input data
    for(i=0;i<MRTstationAmount;i++)
        {
        printf(" %2d. %s\n",i,mrtStation[i]);
        }
    printf("****************************");
    printf(" Enter number of station :");
    fgets(input,32,stdin);                 // get data from user
    sscanf(input,"%d",&MRTstationNum);     // keep in MRTstation variable
    if (MRTstationNum > MRTstationAmount)  // condition check correct number
        {
        dataError();   // show error message
        }
        for(j=0;j<businessCount;j++)
            {
            if(MRTstationNum == business[j].mrt) // check matching station
                {
                    displayData(business[j]);    // if matching show result
                    MRTMatchingCount++;          // add count of matching
                }
            }
    if(MRTMatchingCount == 0) // condition for not matching
        {
        printf("*********************************");
        printf("Not found MRT station matching"); // show message
        printf("*********************************");
        }
    }


void searchByBTS(BUSINESS_T business[],int businessCount)
    // Function for search by nearest MRT station
    {
    int BTSstationNum;          // declare for number of MRT station
    int BTSMatchingCount=0;     // declare for count matching station
    int BTSstationAmount = 31;  // declare for max station
    int j;                      // declare for loop
    int i;                      // declare for loop
    char input[32];             // declare for input data
    for(i=0;i<BTSstationAmount;i++)
        {
        printf(" %2d. %s\n",i,btsStation[i]);
        }
    printf("****************************");
    printf(" Enter number of station :");
    fgets(input,32,stdin);                  // get data from user
    sscanf(input,"%d",&BTSstationNum);
    if (BTSstationNum > BTSstationAmount)   // condition check corect number
        {
        dataError();        // show error message
        }
    for(j=0;j<businessCount;j++)
        {
        if(BTSstationNum == business[j].bts) // check matching station
        {
        displayData(business[j]);   // if matching show result
        BTSMatchingCount++;         // add count of matching
        }
    }
    if(BTSMatchingCount == 0)
        {
        printf("*********************************");
        printf("Not found BTS station matching");
        printf("*********************************");
        }
    }


void displayData(BUSINESS_T business) // display data function
    {

    printf("Name of business : %s",business.name);
    printf("address : %s",business.address);
    printf("added date: %d/%d/%d",business.date.day,business.date.month,business.date.year);
    printf("Phone number : %s",business.phoneNumber);
    printf("Website :%s",business.website);
    printf(" BTS station: %s",btsStation[business.bts]);
    printf(" MRT station: %s",mrtStation[business.mrt]);
    printf(" type of business: %s",businessType[business.type]);
    printf(" rating : %d star",business.rating);
    }
void dataError() // display error message
    {
    printf("***********************\n");
    printf("****               ****\n");
    printf("** Please try again  **\n");
    printf("****               ****\n");
    printf("***********************\n");
    }


