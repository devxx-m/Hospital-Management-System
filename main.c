#include <stdio.h>
#include <string.h>
#include <strings.h>

struct Patient {
    char name[50];
    int id;
    float age;
    char disease[100];
};

struct hospital {
    char name[50];
    char city[50];
    int availableBeds;
    float bedPrice;
    float rating;
    struct Patient p;
};

void hospitalData();
void patientData();
void bedsPrice(struct hospital hospitals[], int n);
void availableBeds(struct hospital hospitals[], int n);
void sortByName(struct hospital hospitals[], int n);
void rating(struct hospital hospitals[], int n);
void hospitalByCity(struct hospital hospitals[], int n);
void addHospital();
void clearInputBuffer();

struct hospital hptl[100];
struct Patient pt[100];

int count = 0;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice = 0;

    printf("*** HOSPITAL MANAGEMENT SYSTEM ***\n");

    do {
        printf("\n1. Printing hospital data\n");
        printf("2. Printing patient data\n");
        printf("3. Sort by bed price\n");
        printf("4. Sort by available beds\n");
        printf("5. Sort by name\n");
        printf("6. Sort by rating and reviews\n");
        printf("7. Print the hospital's name in a specific city\n");
        printf("8. Add hospital\n");
        printf("9. Exit\n");
        printf("\nEnter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            choice = 0;
        }

        switch (choice) {
            case 1:
                hospitalData();
                break;
            case 2:
                patientData();
                break;
            case 3:
                bedsPrice(hptl, count);
                hospitalData();
                break;
            case 4:
                availableBeds(hptl, count);
                hospitalData();
                break;
            case 5:
                sortByName(hptl, count);
                hospitalData();
                break;
            case 6:
                rating(hptl, count);
                hospitalData();
                break;
            case 7:
                hospitalByCity(hptl, count);
                break;
            case 8:
                addHospital();
                break;
            case 9:
                printf("\nExiting program. Thank you!\n");
                break;
            default:
                printf("\nInvalid option! Please try again.\n");
                break; 
        }

    } while (choice != 9);

    return 0;
}

void hospitalData() {
    if (count == 0) {
        printf("There is no data here\n");
        return;
    }
    
    printf("\n*** THE TABLE ***\n");
    printf("%-5s %-20s %-15s %-15s %-12s %-8s\n", "NO.", "HOSPITAL NAME", "CITY", "BED PRICE($)", "BEDS AVAIL.", "RATING");
    printf("========================================================================================\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-15s %-15.2f %-12d %-8.1f\n",
            i + 1,
            hptl[i].name,
            hptl[i].city,
            hptl[i].bedPrice,
            hptl[i].availableBeds,
            hptl[i].rating
        );
    }
    printf("========================================================================================\n");
}

void addHospital() {
    if (count >= 100) {
        printf("Database full!\n");
        return;
    }

    clearInputBuffer();
    printf("\nEnter hospital name: ");
    fgets(hptl[count].name, sizeof(hptl[count].name), stdin);
    hptl[count].name[strcspn(hptl[count].name, "\n")] = '\0';

    printf("Enter city: ");
    fgets(hptl[count].city, sizeof(hptl[count].city), stdin);
    hptl[count].city[strcspn(hptl[count].city, "\n")] = '\0';

    printf("Enter available beds: ");
    scanf("%d", &hptl[count].availableBeds);

    printf("Enter bed price: ");
    scanf("%f", &hptl[count].bedPrice);

    printf("Enter rating (out of 5): ");
    scanf("%f", &hptl[count].rating);

    printf("Enter patient ID: ");
    scanf("%d", &hptl[count].p.id);

    clearInputBuffer();
    printf("Enter patient name: ");
    fgets(hptl[count].p.name, sizeof(hptl[count].p.name), stdin);
    hptl[count].p.name[strcspn(hptl[count].p.name, "\n")] = '\0';

    printf("Enter patient age: ");
    scanf("%f", &hptl[count].p.age);

    clearInputBuffer();
    printf("Enter patient disease: ");
    fgets(hptl[count].p.disease, sizeof(hptl[count].p.disease), stdin);
    hptl[count].p.disease[strcspn(hptl[count].p.disease, "\n")] = '\0';

    count++;
    printf("\nHospital and patient added successfully!\n");
}

void patientData() {
    if (count == 0) {
        printf("No patient here!\n");
        return;
    }

    printf("\n*** Patient Data ****\n");

    int id;
    printf("Enter the patient id: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (id == hptl[i].p.id) {
            printf("Hospital: %s\n", hptl[i].name);
            printf("Patient name: %s\n", hptl[i].p.name);
            printf("Age: %.1f\n", hptl[i].p.age);
            printf("Disease: %s\n", hptl[i].p.disease);
            found = 1;
            break;
        }
    }

    !found ? printf("Patient with id %d not found\n", id) : 0;
}

void bedsPrice(struct hospital hospitals[], int n) {
    if (n == 0) {
        printf("There is no data to sort!\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (hospitals[j].bedPrice > hospitals[j + 1].bedPrice) {
                struct hospital aux = hospitals[j];
                hospitals[j] = hospitals[j + 1];
                hospitals[j + 1] = aux;
            }
        }
    }

    printf("\nSorted by bed price successfully!\n");
}

void availableBeds(struct hospital hospitals[], int n) {
    if (n == 0) {
        printf("There is no data to sort!\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (hospitals[j].availableBeds < hospitals[j + 1].availableBeds) {
                struct hospital temp = hospitals[j];
                hospitals[j] = hospitals[j + 1];
                hospitals[j + 1] = temp;
            }
        }
    }
    printf("\nSorted by available beds successfully!\n");
}

void sortByName(struct hospital hospitals[], int n) {
    if (n == 0) {
        printf("There is no data to sort!\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(hospitals[j].name, hospitals[j + 1].name) > 0) {
                struct hospital temp = hospitals[j];
                hospitals[j] = hospitals[j + 1];
                hospitals[j + 1] = temp;
            }
        }
    }
    printf("\nSorted by name successfully!\n");
}

void rating(struct hospital hospitals[], int n) {
    if (n == 0) {
        printf("There is no data to sort!\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (hospitals[j].rating < hospitals[j + 1].rating) {
                struct hospital aux = hospitals[j];
                hospitals[j] = hospitals[j + 1];
                hospitals[j + 1] = aux;
            }
        }
    }

    printf("\nSorted by rating successfully!\n");
}

void hospitalByCity(struct hospital hospitals[], int n) {
    if (n <= 0 || hospitals == NULL) {
        printf("\n[Error] No hospital data available in the system\n");
        return;
    }

    clearInputBuffer();
    char targetCity[50];
    printf("Enter city name: ");
    if (fgets(targetCity, sizeof(targetCity), stdin) == NULL) {
        printf("[Error] failed to read input\n");
        return;
    }
    targetCity[strcspn(targetCity, "\n")] = '\0';

    if (strlen(targetCity) == 0) {
        printf("City name cannot be empty\n");
        return;
    }

    int found = 0;
    printf("\nHospitals in %s:\n", targetCity);
    for (int i = 0; i < n; i++) {
        if (strcasecmp(hospitals[i].city, targetCity) == 0) {
            printf("- %s\n", hospitals[i].name);
            found = 1;
        }
    }
    !found ? printf("No hospitals found in the city\n") : 0;
}