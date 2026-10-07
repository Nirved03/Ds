/**Railway reservation system */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINS 5
#define MAX_SEATS 10

/* =========================================================
   TRAIN STRUCTURE
   ========================================================= */

typedef struct
{
    int trainNo;
    char trainName[50];
    char source[30];
    char destination[30];
    int seats[MAX_SEATS];
    int availableSeats;
} Train;


/* =========================================================
   PASSENGER LINKED LIST
   ========================================================= */

typedef struct Passenger
{
    int pnr;
    char name[50];
    int age;
    char gender[10];

    int trainNo;
    int seatNo;

    float fare;
    char status[20];

    struct Passenger *next;

} Passenger;


/* =========================================================
   WAITING LIST QUEUE
   ========================================================= */

typedef struct WaitingPassenger
{
    int pnr;
    char name[50];
    int age;
    char gender[10];
    int trainNo;

    struct WaitingPassenger *next;

} WaitingPassenger;


/* =========================================================
   CANCELLATION STACK
   ========================================================= */

typedef struct Cancellation
{
    int pnr;
    char name[50];
    int trainNo;
    int seatNo;

    struct Cancellation *next;

} Cancellation;


/* =========================================================
   GLOBAL VARIABLES
   ========================================================= */

Train trains[MAX_TRAINS] =
{
    {12928, "Vadodara Express", "Vadodara", "Mumbai",
     {0}, MAX_SEATS},

    {12929, "Gujarat Express", "Ahmedabad", "Mumbai",
     {0}, MAX_SEATS},

    {19034, "Gujarat Queen", "Ahmedabad", "Vadodara",
     {0}, MAX_SEATS},

    {12009, "Shatabdi Express", "Mumbai", "Ahmedabad",
     {0}, MAX_SEATS},

    {22953, "Mumbai Express", "Mumbai", "Ahmedabad",
     {0}, MAX_SEATS}
};

Passenger *passengerHead = NULL;

WaitingPassenger *front = NULL;
WaitingPassenger *rear = NULL;

Cancellation *top = NULL;

int nextPNR = 1001;


/* =========================================================
   FUNCTION: FIND TRAIN
   ========================================================= */

int findTrain(int trainNo)
{
    int i;

    for (i = 0; i < MAX_TRAINS; i++)
    {
        if (trains[i].trainNo == trainNo)
        {
            return i;
        }
    }

    return -1;
}


/* =========================================================
   FUNCTION: DISPLAY ALL TRAINS
   ========================================================= */

void displayTrains()
{
    int i;

    printf("\n");
    printf("====================================================================\n");
    printf("                         AVAILABLE TRAINS\n");
    printf("====================================================================\n");

    printf("%-10s %-22s %-15s %-15s %-10s\n",
           "Train No",
           "Train Name",
           "Source",
           "Destination",
           "Seats");

    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < MAX_TRAINS; i++)
    {
        printf("%-10d %-22s %-15s %-15s %-10d\n",
               trains[i].trainNo,
               trains[i].trainName,
               trains[i].source,
               trains[i].destination,
               trains[i].availableSeats);
    }

    printf("====================================================================\n");
}


/* =========================================================
   FUNCTION: SEARCH TRAIN
   ========================================================= */

void searchTrain()
{
    char source[30];
    char destination[30];

    int found = 0;
    int i;

    printf("\nEnter Source: ");
    scanf("%29s", source);

    printf("Enter Destination: ");
    scanf("%29s", destination);

    printf("\n================ SEARCH RESULT ================\n");

    for (i = 0; i < MAX_TRAINS; i++)
    {
        if (strcmp(trains[i].source, source) == 0 &&
            strcmp(trains[i].destination, destination) == 0)
        {
            printf("\nTrain Number : %d", trains[i].trainNo);
            printf("\nTrain Name   : %s", trains[i].trainName);
            printf("\nSource       : %s", trains[i].source);
            printf("\nDestination  : %s", trains[i].destination);
            printf("\nAvailable    : %d\n", trains[i].availableSeats);

            found = 1;
        }
    }

    if (!found)
    {
        printf("\nNo train found between these stations.\n");
    }
}


/* =========================================================
   FUNCTION: SORT TRAINS
   Bubble Sort
   ========================================================= */

void sortTrains()
{
    int i, j;

    Train temp;

    for (i = 0; i < MAX_TRAINS - 1; i++)
    {
        for (j = 0; j < MAX_TRAINS - i - 1; j++)
        {
            if (trains[j].trainNo > trains[j + 1].trainNo)
            {
                temp = trains[j];

                trains[j] = trains[j + 1];

                trains[j + 1] = temp;
            }
        }
    }

    printf("\nTrains sorted successfully by Train Number.\n");

    displayTrains();
}


/* =========================================================
   FUNCTION: CALCULATE FARE
   ========================================================= */

float calculateFare(int age)
{
    if (age < 5)
    {
        return 0;
    }
    else if (age <= 12)
    {
        return 150;
    }
    else if (age >= 60)
    {
        return 200;
    }
    else
    {
        return 300;
    }
}


/* =========================================================
   FUNCTION: ADD PASSENGER TO LINKED LIST
   ========================================================= */

void addPassenger(int pnr,
                  char name[],
                  int age,
                  char gender[],
                  int trainNo,
                  int seatNo,
                  float fare)
{
    Passenger *newNode;
    Passenger *temp;

    newNode = (Passenger *)malloc(sizeof(Passenger));

    if (newNode == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    newNode->pnr = pnr;

    strcpy(newNode->name, name);

    newNode->age = age;

    strcpy(newNode->gender, gender);

    newNode->trainNo = trainNo;

    newNode->seatNo = seatNo;

    newNode->fare = fare;

    strcpy(newNode->status, "CONFIRMED");

    newNode->next = NULL;


    if (passengerHead == NULL)
    {
        passengerHead = newNode;
    }
    else
    {
        temp = passengerHead;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}


/* =========================================================
   FUNCTION: ADD PASSENGER TO WAITING QUEUE
   ========================================================= */

void enqueueWaiting(int pnr,
                    char name[],
                    int age,
                    char gender[],
                    int trainNo)
{
    WaitingPassenger *newNode;

    newNode = (WaitingPassenger *)
              malloc(sizeof(WaitingPassenger));

    if (newNode == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    newNode->pnr = pnr;

    strcpy(newNode->name, name);

    newNode->age = age;

    strcpy(newNode->gender, gender);

    newNode->trainNo = trainNo;

    newNode->next = NULL;


    if (rear == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;

        rear = newNode;
    }
}


/* =========================================================
   FUNCTION: ADD CANCELLATION TO STACK
   ========================================================= */

void pushCancellation(int pnr,
                      char name[],
                      int trainNo,
                      int seatNo)
{
    Cancellation *newNode;

    newNode = (Cancellation *)
              malloc(sizeof(Cancellation));

    if (newNode == NULL)
    {
        return;
    }

    newNode->pnr = pnr;

    strcpy(newNode->name, name);

    newNode->trainNo = trainNo;

    newNode->seatNo = seatNo;

    newNode->next = top;

    top = newNode;
}


/* =========================================================
   FUNCTION: BOOK TICKET
   ========================================================= */

void bookTicket()
{
    int trainNo;
    int index;

    char name[50];
    char gender[10];

    int age;

    int pnr;

    float fare;

    int seatNo = -1;

    int i;


    printf("\nEnter Train Number: ");
    scanf("%d", &trainNo);

    index = findTrain(trainNo);

    if (index == -1)
    {
        printf("\nTrain not found!\n");
        return;
    }


    printf("Enter Passenger Name: ");
    scanf("%49s", name);

    printf("Enter Age: ");
    scanf("%d", &age);

    printf("Enter Gender: ");
    scanf("%9s", gender);


    pnr = nextPNR++;

    fare = calculateFare(age);


    /* CHECK AVAILABLE SEAT */

    if (trains[index].availableSeats > 0)
    {
        for (i = 0; i < MAX_SEATS; i++)
        {
            if (trains[index].seats[i] == 0)
            {
                seatNo = i + 1;

                trains[index].seats[i] = 1;

                break;
            }
        }


        trains[index].availableSeats--;


        addPassenger(pnr,
                     name,
                     age,
                     gender,
                     trainNo,
                     seatNo,
                     fare);


        printf("\n");
        printf("==================================================\n");
        printf("             TICKET BOOKED SUCCESSFULLY\n");
        printf("==================================================\n");

        printf("PNR Number     : %d\n", pnr);
        printf("Passenger Name : %s\n", name);
        printf("Age            : %d\n", age);
        printf("Gender         : %s\n", gender);

        printf("Train Number   : %d\n", trainNo);
        printf("Train Name     : %s\n",
               trains[index].trainName);

        printf("Source         : %s\n",
               trains[index].source);

        printf("Destination    : %s\n",
               trains[index].destination);

        printf("Seat Number    : %d\n", seatNo);

        printf("Fare           : Rs. %.2f\n", fare);

        printf("Status         : CONFIRMED\n");

        printf("==================================================\n");
    }
    else
    {
        enqueueWaiting(pnr,
                       name,
                       age,
                       gender,
                       trainNo);

        printf("\n");
        printf("==================================================\n");
        printf("               NO SEATS AVAILABLE\n");
        printf("==================================================\n");

        printf("PNR Number     : %d\n", pnr);
        printf("Passenger      : %s\n", name);
        printf("Status         : WAITING\n");

        printf("Passenger added to Waiting List.\n");

        printf("==================================================\n");
    }
}


/* =========================================================
   FUNCTION: SEARCH PASSENGER BY PNR
   ========================================================= */

Passenger *findPassenger(int pnr)
{
    Passenger *temp = passengerHead;

    while (temp != NULL)
    {
        if (temp->pnr == pnr)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}


/* =========================================================
   FUNCTION: DISPLAY PNR DETAILS
   ========================================================= */

void searchPNR()
{
    int pnr;

    Passenger *p;


    printf("\nEnter PNR Number: ");
    scanf("%d", &pnr);


    p = findPassenger(pnr);


    if (p == NULL)
    {
        printf("\nPassenger not found.\n");
        return;
    }


    printf("\n");
    printf("==================================================\n");
    printf("                 PASSENGER DETAILS\n");
    printf("==================================================\n");

    printf("PNR Number     : %d\n", p->pnr);
    printf("Passenger Name : %s\n", p->name);
    printf("Age            : %d\n", p->age);
    printf("Gender         : %s\n", p->gender);
    printf("Train Number   : %d\n", p->trainNo);
    printf("Seat Number    : %d\n", p->seatNo);
    printf("Fare           : Rs. %.2f\n", p->fare);
    printf("Status         : %s\n", p->status);

    printf("==================================================\n");
}


/* =========================================================
   FUNCTION: MOVE WAITING PASSENGER TO CONFIRMED
   ========================================================= */

void processWaitingPassenger(int trainNo,
                             int seatNo)
{
    WaitingPassenger *temp;

    Passenger *newPassenger;


    if (front == NULL)
    {
        return;
    }


    if (front->trainNo != trainNo)
    {
        return;
    }


    temp = front;

    front = front->next;


    if (front == NULL)
    {
        rear = NULL;
    }


    newPassenger =
        (Passenger *)malloc(sizeof(Passenger));


    if (newPassenger == NULL)
    {
        return;
    }


    newPassenger->pnr = temp->pnr;

    strcpy(newPassenger->name,
           temp->name);

    newPassenger->age = temp->age;

    strcpy(newPassenger->gender,
           temp->gender);

    newPassenger->trainNo = trainNo;

    newPassenger->seatNo = seatNo;

    newPassenger->fare =
        calculateFare(temp->age);

    strcpy(newPassenger->status,
           "CONFIRMED");


    newPassenger->next =
        passengerHead;

    passengerHead =
        newPassenger;


    printf("\n");
    printf("==================================================\n");
    printf("             WAITING LIST UPDATED\n");
    printf("==================================================\n");

    printf("Passenger %s is now CONFIRMED.\n",
           temp->name);

    printf("PNR Number : %d\n",
           temp->pnr);

    printf("Seat Number: %d\n",
           seatNo);

    printf("==================================================\n");


    free(temp);
}


/* =========================================================
   FUNCTION: CANCEL TICKET
   ========================================================= */

void cancelTicket()
{
    int pnr;

    Passenger *temp;
    Passenger *previous = NULL;

    int index;

    int trainNo;
    int seatNo;


    printf("\nEnter PNR Number: ");
    scanf("%d", &pnr);


    temp = passengerHead;


    while (temp != NULL &&
           temp->pnr != pnr)
    {
        previous = temp;

        temp = temp->next;
    }


    if (temp == NULL)
    {
        printf("\nPassenger not found.\n");
        return;
    }


    trainNo = temp->trainNo;

    seatNo = temp->seatNo;


    index = findTrain(trainNo);


    if (index != -1)
    {
        trains[index].seats[seatNo - 1] = 0;

        trains[index].availableSeats++;
    }


    pushCancellation(temp->pnr,
                     temp->name,
                     temp->trainNo,
                     temp->seatNo);


    printf("\n");
    printf("==================================================\n");
    printf("              TICKET CANCELLED\n");
    printf("==================================================\n");

    printf("PNR       : %d\n", temp->pnr);
    printf("Passenger : %s\n", temp->name);
    printf("Seat      : %d\n", temp->seatNo);

    printf("==================================================\n");


    /*
       REMOVE PASSENGER FROM LINKED LIST
    */

    if (previous == NULL)
    {
        passengerHead = temp->next;
    }
    else
    {
        previous->next = temp->next;
    }


    free(temp);


    /*
       CHECK WAITING LIST
    */

    if (front != NULL &&
        front->trainNo == trainNo)
    {
        processWaitingPassenger(trainNo,
                                seatNo);

        trains[index].seats[seatNo - 1] = 1;

        trains[index].availableSeats--;
    }
}


/* =========================================================
   FUNCTION: DISPLAY CONFIRMED PASSENGERS
   ========================================================= */

void displayPassengers()
{
    Passenger *temp = passengerHead;


    if (temp == NULL)
    {
        printf("\nNo confirmed passengers.\n");
        return;
    }


    printf("\n");
    printf("==================================================\n");
    printf("              CONFIRMED PASSENGERS\n");
    printf("==================================================\n");


    while (temp != NULL)
    {
        printf("\nPNR        : %d", temp->pnr);
        printf("\nName       : %s", temp->name);
        printf("\nTrain No   : %d", temp->trainNo);
        printf("\nSeat No    : %d", temp->seatNo);
        printf("\nFare       : Rs. %.2f", temp->fare);
        printf("\nStatus     : %s", temp->status);

        printf("\n------------------------------------------");

        temp = temp->next;
    }

    printf("\n");
}


/* =========================================================
   FUNCTION: DISPLAY WAITING LIST
   ========================================================= */

void displayWaitingList()
{
    WaitingPassenger *temp = front;

    int position = 1;


    if (temp == NULL)
    {
        printf("\nWaiting List is empty.\n");
        return;
    }


    printf("\n");
    printf("==================================================\n");
    printf("                  WAITING LIST\n");
    printf("==================================================\n");


    while (temp != NULL)
    {
        printf("\nPosition : %d", position);
        printf("\nPNR      : %d", temp->pnr);
        printf("\nName     : %s", temp->name);
        printf("\nTrain No : %d", temp->trainNo);
        printf("\nStatus   : WAITING");

        printf("\n------------------------------------------");


        position++;

        temp = temp->next;
    }

    printf("\n");
}


/* =========================================================
   FUNCTION: DISPLAY SEATS
   ========================================================= */

void displaySeats()
{
    int trainNo;
    int index;
    int i;


    printf("\nEnter Train Number: ");
    scanf("%d", &trainNo);


    index = findTrain(trainNo);


    if (index == -1)
    {
        printf("\nTrain not found.\n");
        return;
    }


    printf("\n");
    printf("==================================================\n");
    printf("              SEAT AVAILABILITY\n");
    printf("==================================================\n");

    printf("Train Number : %d\n",
           trains[index].trainNo);

    printf("Train Name   : %s\n",
           trains[index].trainName);

    printf("\n");


    for (i = 0; i < MAX_SEATS; i++)
    {
        if (trains[index].seats[i] == 0)
        {
            printf("Seat %2d : AVAILABLE\n",
                   i + 1);
        }
        else
        {
            printf("Seat %2d : BOOKED\n",
                   i + 1);
        }
    }


    printf("\nAvailable Seats: %d\n",
           trains[index].availableSeats);

    printf("==================================================\n");
}


/* =========================================================
   FUNCTION: DISPLAY CANCELLATION HISTORY
   ========================================================= */

void displayCancellationHistory()
{
    Cancellation *temp = top;


    if (temp == NULL)
    {
        printf("\nNo cancellation history.\n");
        return;
    }


    printf("\n");
    printf("==================================================\n");
    printf("             CANCELLATION HISTORY\n");
    printf("==================================================\n");


    while (temp != NULL)
    {
        printf("\nPNR       : %d",
               temp->pnr);

        printf("\nPassenger : %s",
               temp->name);

        printf("\nTrain No  : %d",
               temp->trainNo);

        printf("\nSeat No   : %d",
               temp->seatNo);

        printf("\n------------------------------------------");


        temp = temp->next;
    }

    printf("\n");
}


/* =========================================================
   FUNCTION: MAIN
   ========================================================= */

int main()
{
    int choice;


    do
    {
        printf("\n\n");
        printf("==================================================\n");
        printf("          RAILWAY RESERVATION SYSTEM\n");
        printf("==================================================\n");

        printf("1.  Display All Trains\n");
        printf("2.  Search Train\n");
        printf("3.  Sort Trains\n");
        printf("4.  Book Ticket\n");
        printf("5.  Cancel Ticket\n");
        printf("6.  Search Passenger by PNR\n");
        printf("7.  Display Confirmed Passengers\n");
        printf("8.  Display Waiting List\n");
        printf("9.  Display Seat Availability\n");
        printf("10. Cancellation History\n");
        printf("11. Exit\n");

        printf("==================================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
                displayTrains();
                break;


            case 2:
                searchTrain();
                break;


            case 3:
                sortTrains();
                break;


            case 4:
                bookTicket();
                break;


            case 5:
                cancelTicket();
                break;


            case 6:
                searchPNR();
                break;


            case 7:
                displayPassengers();
                break;


            case 8:
                displayWaitingList();
                break;


            case 9:
                displaySeats();
                break;


            case 10:
                displayCancellationHistory();
                break;


            case 11:
                printf("\nThank you for using Railway Reservation System!\n");
                break;


            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    }
    while (choice != 11);


    return 0;
}
