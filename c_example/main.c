#include <stdio.h>
#include "FamarkCloudAPI-C.h"

int main()
{
    char domainName[100], userName[100], password[100];
    printf("\nDomain Name:");
    scanf_s("%99s", domainName, 100);
    printf("\nUser Name:");
    scanf_s("%99s", userName, 100);
    printf("\nPassword:");
    scanf_s("%99s", password, 100);
    char credData[1000] = "{\"DomainName\": \"";
    int credSize = sizeof(credData);
    strcat_s(credData, credSize, domainName);
    strcat_s(credData, credSize, "\", \"UserName\": \"");
    strcat_s(credData, credSize, userName);
    strcat_s(credData, credSize, "\", \"Password\": \"");
    strcat_s(credData, credSize, password);
    strcat_s(credData, credSize, "\"}");

    //Connect action call
    char* sessionData = famark_api_post_data("/Credential/Connect", credData, NULL);

    struct json_object* sessionObject = json_tokener_parse(sessionData);
    const char* sessionId = json_object_get_string(sessionObject);

    if (sessionId) {
        printf("Session Id: %s\n", sessionId);
    }
    else {
        return -1;
    }

    printf("Do you want to create new record (y/n) \n");
    char userResp = getch();
    //clearing new lines from input buffer
    while (getchar() != '\n');

    while (userResp == 'y' || userResp == 'Y')
    {
       char firstName[100], lastName[100], phone[100], email[100];
        printf("\nEnter FirstName:");
        fgets( firstName, 100, stdin);
        firstName[strcspn(firstName, "\n")] = 0;
        printf("\nEnter LastName:");
        fgets(lastName, 100, stdin);
        lastName[strcspn(lastName, "\n")] = 0;
        printf("\nEnter Phone:");
        fgets( phone, 100, stdin);
        phone[strcspn(phone, "\n")] = 0;
        printf("\nEnter Email:");
        fgets( email, 100, stdin);
        email[strcspn(email, "\n")] = 0;
        char profileData[1000] = "{\"FirstName\": \"";
        strcat_s(profileData, sizeof(profileData), firstName);
        strcat_s(profileData, sizeof(profileData), "\", \"LastName\": \"");
        strcat_s(profileData, sizeof(profileData), lastName);
        strcat_s(profileData, sizeof(profileData), "\", \"Email\": \"");
        strcat_s(profileData, sizeof(profileData), email);
        strcat_s(profileData, sizeof(profileData), "\", \"Phone\": \"");
        strcat_s(profileData, sizeof(profileData), phone);        
        strcat_s(profileData, sizeof(profileData), "\"}");
        //Calling CreateRecord action on System_Profile entity of System solution
        char* recordData = famark_api_post_data("/Business_Contact/CreateRecord", profileData, sessionId);

        struct json_object* recordObject = json_tokener_parse(recordData);
        const char* recordId = json_object_get_string(recordObject);

        free(recordData);

        if (recordId) {
            printf("Created Record Id: %s\n", recordId);
            //Login to your famark cloud domain to see the newly created record under System => Profile
            printf("Do you want to create more profile record (y/n)? \n");
        }
        else {
            printf("Do you want to try again (y/n)? \n");
        }
        userResp = getch();
    }

    //Calling RetrieveMultipleRecords action on the Hospital_Doctor entity
    char data[] = "{\"Columns\": \"FullName, Phone, Email, Business_ContactId\"}";
    char* records = famark_api_post_data("/Business_Contact/RetrieveMultipleRecords", data, sessionId);
    struct json_object* recordObjects = json_tokener_parse(records);

    int numRecords = json_object_array_length(recordObjects);
    printf("\nNumber of Records = %d\n", numRecords);

    struct json_object* tmp;
    for (int i = 0; i < numRecords; i++) {
        // Set in tmp the json_object of the secu_code array at index i
        tmp = json_object_array_get_idx(recordObjects, i);
        printf("%d ", i + 1);
        printf("%s\n", json_object_to_json_string(tmp));
    }

    free(records);

// Updating records by taking input from user
    printf("Do you want to update new record (y/n) \n");
    char userUpdateResp = getch();
    //clearing new lines from input buffer
    while (getchar() != '\n');

    while (userUpdateResp == 'y' || userUpdateResp == 'Y')
    {
        char contactId[100],firstName[100], lastName[100], phone[100], email[100];
        printf("\nEnter Business_ContactId:");
        fgets( contactId, 100, stdin);
        contactId[strcspn(contactId, "\n")] = 0;
        printf("\nEnter FirstName:");
        fgets( firstName, 100, stdin);
        firstName[strcspn(firstName, "\n")] = 0;
        printf("\nEnter LastName:");
        fgets(lastName, 100, stdin);
        lastName[strcspn(lastName, "\n")] = 0;
        printf("\nEnter Phone:");
        fgets( phone, 100, stdin);
        phone[strcspn(phone, "\n")] = 0;
        printf("\nEnter Email:");
        fgets( email, 100, stdin);
        email[strcspn(email, "\n")] = 0;
        char profileData[1000] = "{\"FirstName\": \"";
        strcat_s(profileData, sizeof(profileData), firstName);
        strcat_s(profileData, sizeof(profileData), "\", \"Business_ContactId\": \"");
        strcat_s(profileData, sizeof(profileData), contactId);
        strcat_s(profileData, sizeof(profileData), "\", \"LastName\": \"");
        strcat_s(profileData, sizeof(profileData), lastName);
        strcat_s(profileData, sizeof(profileData), "\", \"Email\": \"");
        strcat_s(profileData, sizeof(profileData), email);
        strcat_s(profileData, sizeof(profileData), "\", \"Phone\": \"");
        strcat_s(profileData, sizeof(profileData), phone);        
        strcat_s(profileData, sizeof(profileData), "\"}");

        //Calling CreateRecord action on System_Profile entity of System solution
        char* recordData = famark_api_post_data("/Business_Contact/UpdateRecord", profileData, sessionId);

        struct json_object* recordObject = json_tokener_parse(recordData);
        const char* recordId = json_object_get_string(recordObject);

        free(recordData);

        if (recordId) {
            printf("Update Record Id: %s\n", recordId);
            //Login to your famark cloud domain to see the updated record under System => Profile
            printf("Do you want to Update more profile record (y/n)? \n");
        }
        else {
            printf("Do you want to try again (y/n)? \n");
        }
        userUpdateResp = getch();
    }


    // Deleting records by taking input from user
    printf("Do you want to delete new record (y/n) \n");
    char userDeleteResp = getch();
    //clearing new lines from input buffer
    while (getchar() != '\n');

    while (userDeleteResp == 'y' || userDeleteResp == 'Y')
    {
        char contactId[100];
        printf("\nEnter ContactId:");
        fgets( contactId, 100, stdin);
        contactId[strcspn(contactId, "\n")] = 0;
        char profileData[1000] = "{\"Business_ContactId\": \"";
        strcat_s(profileData, sizeof(profileData), contactId);              
        strcat_s(profileData, sizeof(profileData), "\"}");
        //Calling CreateRecord action on System_Profile entity of System solution
        char* recordData = famark_api_post_data("/Business_Contact/DeleteRecord", profileData, sessionId);

        struct json_object* recordObject = json_tokener_parse(recordData);
        const char* recordId = json_object_get_string(recordObject);

        free(recordData);
        
        printf("Do you want to delete new record (y/n) \n");
        userDeleteResp = getch();
    }
    return 0;
}