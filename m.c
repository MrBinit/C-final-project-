//final project 
#include <stdio.h>
#include <stdlib.h> // allocate memory
#include <time.h>   //used for time
#include <string.h>

struct patient
{
    int identity;
    char patient_Name[50];
    char patient_Address[50];
    char disease[50];
    char date[12];
} p;

struct doctor
{
    int identity;
    char name[50];
    char address[50];
    char specialize[50];
    char date[12];
} d;

FILE *fp; // file pointer

// Now using function

void admit_Patient()
{
    char cdate[12];
    time_t t = time(NULL); // time_t is the special variable that comes wiht the header time. h
    // pointer to struct
    struct tm tm = *localtime(&t); // local time

    sprintf(cdate, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // sprint used for string print
                                                                              // sprintf(myDate, "%d/%2d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // sprint used for string print

    strcpy(p.date, cdate);

    fp = fopen("patient.txt", "ab"); //	Open for append in binary mode. Data is added to the end of the file. // ab unclear

    printf("Enter Patient id: ");
    scanf("%d", &p.identity);

    printf("Enter Patient name: ");
    fflush(stdin);        // fflush is used to immediately flush out the contents of an output stream.
    fgets(p.patient_Name,250,stdin); // gets used for string. ease to take char
    //gets(p.patient_Name);

    printf("Enter Patient Address: ");
    fflush(stdin);
    fgets(p.patient_Address,250,stdin);
    //gets(p.patient_Address);

    printf("Enter Patient Disease: ");
    fflush(stdin);
    fgets(p.disease,250,stdin);
    //gets(p.disease);

    printf("\nThe patient have been successfully added");

    fwrite(&p, sizeof(p), 1, fp); // write
    fclose(fp);
}

void patient_List()
{

    system("cls"); // done to clear to previous contains
    printf("** Patient List **\n\n\n");
    printf("%-10s %-30s %-30s %-20s %s\n", "Identity", "Patient Name", "Address", "Disease", "Date"); // 10 spaces before the string state is printed
    printf("------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("patient.txt", "rb"); 

    while (fread(&p, sizeof(p), 1, fp) == 1) // one by one check. if equal to 1 it means it is found in the record.
    {
        printf("%-10d %-50s %-90s %-110s %s", p.identity, p.patient_Name, p.patient_Address, p.disease, p.date);
    }

    fclose(fp); // close the file.
}

void discharge_Patient()
{
    int identity, f = 0;
    system("cls"); // done to clear to previous contains
    printf("** Discharge Patient **\n\n");
    printf("Enter Patient identity to discharge: ");
    scanf("%d", &identity);

    FILE *ft; // file pointer

    fp = fopen("patient.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&p, sizeof(p), 1, fp) == 1) // reading the patient read one by one.  // checking with 1. which means if there is patient then the condition will work.
    {
        // condition
        if (identity == p.identity) // if both identity matches.
        {
            f = 1;
        }
        else
        {
            fwrite(&p, sizeof(p), 1, ft); // if the identity doesnt matches then write in temp file.
        }
    }

    if (f == 1)
    {
        printf("\n\nThe patient have been successfully discharged.");
    }
    else
    {
        printf("\n\nNot found :(");
    }

    fclose(fp);
    fclose(ft);

    remove("patient.txt");             // removes older patient txt
    rename("temp.txt", "patient.txt"); // newly made temp.txt name changed into patient txt.
}

void add_Doctor()
{

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(d.date, myDate);

    int f = 0;

    system("cls"); // done to clear to previous contains
    printf("** Add Doctor **\n\n");

    fp = fopen("doctor.txt", "ab"); // ab stands for append binary. 

    printf("Enter Doctor id: ");
    scanf("%d", &d.identity);

    printf("Enter Doctor Name: ");
    fflush(stdin);
    fgets(d.name,250,stdin);

    printf("Enter Doctor Address: ");
    fflush(stdin);
    fgets(d.address,250,stdin);

    printf("Doctor Specialize in: ");
    fflush(stdin);
    fgets(d.specialize,250,stdin);

    printf("Doctor Added Successfully\n\n");

    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
}

void doctor_List()
{
    system("cls"); // done to clear to previous contains
    printf(" ** Doctor List **\n\n");

    printf("%-10s %-30s %-30s %-30s %s\n", "Identity", "Name", "Address", "Specialize", "Date"); 
    printf("----------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("doctor.txt", "rb");
    while (fread(&d, sizeof(d), 1, fp) == 1)
    {
       printf("%-10d %-50s %-90s %-110s %s", d.identity, d.name, d.address, d.specialize, d.date);
       
    }

    fclose(fp);
}

int main()
{

    int choice;

    system("cls"); // done to clear to previous contains
    printf("Welcome to Civil Hospital:) :)\n\n");
    printf("**Civil Hospital Management System **\n");
    printf("1.To Add Newly Admitted Patient\n");
    printf("2.To See Current Patient List\n");
    printf("3.To Discharge Current Patient\n");
    printf("4.To Add New Doctor\n");
    printf("5.To See Currently Available Doctors List\n");
    printf("0.Exit\n\n");
    printf("Enter your choice in integer: ");
    scanf("%d", &choice);

    switch (choice) // using switch case
    {
    case 0:
        exit(0);

    case 1:
        admit_Patient();
        break;

    case 2:
        patient_List();
        break;

    case 3:
        discharge_Patient();
        break;

    case 4:
        add_Doctor();
        break;

    case 5:
        doctor_List();
        break;

    default: // if nothing
        printf("Invalid Choice.\n");
    }

    return 0;
}
