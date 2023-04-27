#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int n;
double root[100];
struct user_t
{
    char name[100];
    double time;
    double latitude;
    double longitude;
    double altitude;
};

struct distance
{
    char name[100];
    double distance;
};
struct distance position[100];

void print(struct user_t user)
{
    printf("\nName of user:\n%s", user.name);
    printf("\nCurrent time:\n%lf", user.time);
    printf("\nlongitude of user:\n%lf", user.longitude);
    printf("\nlatitude of user:\n%lf", user.latitude);
    printf("\naltitude of user:\n%lf", user.altitude);
}
struct user_t scan_user(struct user_t user)
{
    printf("Enter the name of the user:\n");
    scanf("%s", user.name);
    printf("Enter the current time:\n");
    scanf("%lf", &user.time);
    printf("Enter the longitude:\n");
    scanf("%lf", &user.longitude);
    printf("Enter the latitude:\n");
    scanf("%lf", &user.latitude);
    printf("Enter the altitude:\n");
    scanf("%lf", &user.altitude);
    return user;
}

void fill_data(struct user_t other_users[])
{
    FILE *fp1;
    char c[1000];
    fp1 = fopen("otheruser.txt", "r");
    if (fp1 == NULL)
    {
        printf("Source file could not be found\n");
    }
    fscanf(fp1, "%[^\n]", c);
    n = atoi(c);
    for (int i = 0; i < n; i++)
    {
        if (feof(fp1))
        {
            printf("End of file:\n");
            break;
        }
        fscanf(fp1, "%s", other_users[i].name);
        fscanf(fp1, "%s", c);
        char *ptr;
        other_users[i].time = strtod(c, &ptr);
        fscanf(fp1, "%s", c);
        other_users[i].longitude = strtod(c, &ptr);
        fscanf(fp1, "%s", c);
        other_users[i].latitude = strtod(c, &ptr);
        fscanf(fp1, "%s", c);
        other_users[i].altitude = strtod(c, &ptr);
    }
    fclose(fp1);
}

void positions(struct user_t our_user, struct user_t other_user[])
{
    our_user = scan_user(our_user);
    double long1 = our_user.longitude;
    double lat1 = our_user.latitude;
    double alt1 = our_user.altitude;
    for (int i = 0; i < n; i++)
    {
        strcpy(position[i].name, other_user[i].name);
        double long2 = other_user[i].longitude;
        double lat2 = other_user[i].latitude;
        double alt2 = other_user[i].altitude;
        double distance = (((lat1 - lat2) * (lat1 - lat2)) + ((long1 - long2) * (long1 - long2)) + ((alt1 - alt2) * (alt1 - alt2)));
        double x = 0.5;
        root[i] = pow(distance, x);
    }
    for (int i = 0; i < n; i++)
    {
        position[i].distance = root[i];
    }
}

struct user_t min_distance(struct user_t other_users[])
{
    int pos = 0;
    double min = root[0];
    for (int i = 0; i < n; i++)
    {
        if (position[i].distance < min)
        {
            min = position[i].distance;
            pos = i;
        }
    }
    return other_users[pos];
}

int main()
{
    struct user_t our_user, other_user[100], minimum;
    fill_data(other_user);
    positions(our_user, other_user);
    minimum = min_distance(other_user);
    print(minimum);
    return 0;
}