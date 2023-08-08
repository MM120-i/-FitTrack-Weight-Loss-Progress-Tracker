/***************************************
* 22Fa - Programming Assignment 2 *
* Author: Marufuzzaman Mahim
* Email: mm120@my.yorku.ca
* EECS username: mm120
* Yorku student #: 218146712
****************************************/

#include <stdio.h>
#include <ctype.h>  // for tolower()
#include <string.h>
#include <stdlib.h>

#define SIZE 48
#define fieldLength 258

struct db_type
{
   char name[fieldLength];
   
   int age;

   int height;   // cm
   float bmi;
   char status[fieldLength] ;
};

 
char prompt_menu(void);
void enterNew(struct db_type * pArr[]);  
void init_list(struct db_type * pArr[]); 
void displayDB(struct db_type * pArr[]);   
void sortDB(struct db_type * pArr[]);
void updateRecord(struct db_type * pArr[]); 
void removeRecord(struct db_type * pArr[]);
void clearDB(struct db_type * pArr[]);

int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
        
         case 's': sortDB(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
        
         case 'u': updateRecord(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("(U)pdate record\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay database\t|\n");
  
    printf("|    %-20s","(Q)uit");
    printf("*Case Insensitive*\t\t\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
    //scanf("%s", s);  
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
	 
 }
}


void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

/* delete all the records in the database */
void clearDB(struct db_type * pArr[]){
   char yn[3];
   printf("are you sure to clear database? (y) or (n)? ");
    
   fgets(yn,3,stdin);
   
   // complete the function by calling init_list();
   if(strcmp("y\n", yn) == 0){

      init_list(pArr);
   }
}


/* input items into the database */
/* hint: need malloc */
void enterNew(struct db_type * pArr[SIZE])
{  

   float denominator, weight, var;
   int x = 0, length = 0;
   struct db_type *database = (struct db_type*) malloc(sizeof(database));
   char n[fieldLength];
   for(x; *(pArr + x) != NULL; x++);

   const float UnderWeight = 18.5;
   const float Normal = 24.999;
   const float OverWeight = 29.999;
   const float ObeseI = 34.999;
   const float ObeseII = 39.999;

   *(pArr + x) = database;

   printf("name: "); 
   
   scanf("%[^\n]s", n);

   printf("age: ");

   scanf("%d", &((*database).age));

   printf("height (cm): ");

   scanf("%d", &((*database).height));
   
   denominator = (((*database).height / 100.0) * ((*database).height / 100.0));

   printf("weight (kg): ");

   scanf("%f", &weight);

   getchar();

   (*database).bmi = weight / denominator;
   
   strcpy((*database).name, n);

   var = (*database).bmi;
   length = strlen((*database).status);

   if(UnderWeight > var){

      switch (length){

         case 0: strcpy((*(database)).status, "Underweight"); break;
         default: strcat((*(database)).status, " -> Underweight"); break;    
      }
   }
   else if(Normal > var){

      switch (length){

         case 0: strcpy((*(database)).status, "Normal"); break;
         default: strcat((*(database)).status, " -> Normal"); break;    
      }
   }
   else if(OverWeight > var){

      switch (length){

         case 0: strcpy((*(database)).status, "Overweight"); break;
         default: strcat((*(database)).status, " -> Overweight"); break;
      } 
   }
   else if(ObeseI > var){

      switch (length){

         case 0: strcpy((*(database)).status, "Obese I"); break;
         default: strcat((*(database)).status, " -> Obese Class I"); break;
      }
   }
   else if(ObeseII > var){

      switch (length){
         case 0: strcpy((*(database)).status, "Obese II"); break;
         default: strcat((*(database)).status, " -> Obese Class II"); break;
      }
   }
   else{

       switch (length){
         case 0: strcpy((*(database)).status, "Obese III"); break;
         default: strcat((*(database)).status, " -> Obese Class III"); break;
      }
   }
}


/* remove an existing item from the database */
void removeRecord (struct db_type * pArr[])	
{
   char n[fieldLength];  
   printf("enter full name to remove: ");
   fgets(n, fieldLength, stdin);
   n[strlen(n) - 1] = '\0';
   int index = 0, flag = 0, j = 0, temp = 0;

   while(SIZE > index){

      if(*(pArr + index) == NULL){

         break;
      }
      else{

         temp = strcmp((*(pArr + index))->name, n);
         switch(temp){

            case 0:

               *(pArr + index) = NULL;
               printf("record [%s] removed successfully.\n", n);
               flag = 7; j = index;
            break;
            default: break;
         }
      }

      index = index + 1;
   }

   switch (flag){

     case 7:
        
      while((SIZE - 1) > j){
         
         *(pArr + j) = *(pArr + j + 1);
         j++;
      }
      break;

     case 0: printf("Record not found!\n"); break;
     default: break;
   }
}

/* display all the records in the database. Generate output with the same formaing as the sample output 
 use \t to align well
*/
void displayDB(struct db_type * pArr[]){
  
  int t, x = 0;
  printf("===============================\n");
  for (t=0; t <SIZE ; t++)
  {
     if( pArr[t] != NULL)
     {
        x = x + 1;

        printf("\nname:\t%s\n", (*(*(pArr + t))).name);  
        printf("age:\t%d\n", (*(*(pArr + t))).age);
        printf("height:\t%d\n", (*(*(pArr + t))).height);
        printf("BMI:\t%.1f\n", (*(*(pArr + t))).bmi);
        printf("status:\t%s\n", (*(*(pArr + t))).status);
     } 
  }

  printf("\n========== %d records ==========", x);
}


 /* modify (update weight of) an existing member */
void updateRecord (struct db_type * pArr[]){

   char n[fieldLength];

   printf("Enter full name to search: ");
   fgets(n, fieldLength, stdin);
   n[strlen(n) - 1] = '\0';

   int index = 0, flag = 0, temp = 0, length = 0;
   float w, d, var; 

   const float UnderWeight = 18.5;
   const float Normal = 24.999;
   const float OverWeight = 29.999;
   const float ObeseI = 34.999;
   const float ObeseII = 39.999;
   
   while(SIZE > index){

      if(*(pArr + index) != NULL) {

         d = ((*(*(pArr + index))).height / 100.0) * ((*(*(pArr + index))).height / 100.0);
         temp = strcmp((*(pArr + index))->name, n);

         switch(temp){

            case 0: 
            
               printf("\nRecord found! Enter new weight (kg): ");
               scanf("%f", &w); fgetc(stdin);
               printf("record [%s] updated successfully!\n", n);
               flag = 7; (*(*(pArr + index))).bmi = w / d;
               length = strlen((*(*(pArr + index))).status);
               var = (*(*(pArr + index))).bmi;

               if(UnderWeight > var){

                   switch (length){
                     case 0: strcat((*(*(pArr + index))).status, " -> Underweight"); break;
                     default: break;
                  }
               }
               else if(Normal > var){

                  switch (length){
                     case 0: strcat((*(*(pArr + index))).status, " -> Normal"); break;
                     default: break;
                  }
               }
               else if(OverWeight > var){

                  switch (length){ 
                     case 0: strcat((*(*(pArr + index))).status, " -> Overweight"); break;
                     default: break;
                  } 
               }
               else if(ObeseI > var){

                  switch (length){
                     case 0: strcat((*(*(pArr + index))).status, " -> Obese I"); break;
                     default: break;
                  }
               }
               else if(ObeseII > var){

                  switch (length){
                     case 0: strcat((*(*(pArr + index))).status, " -> Obese II"); break;
                     default: break;
                  }
               }
               else{

                  switch (length){ 
                     case 0: strcat((*(*(pArr + index))).status, " -> Obese III"); break;
                     default: break;
                  }
               }
               
            break; 
            default: break;
         }
      }
      else if(*(pArr + index) == NULL){break;}
      index++;
   }

   switch(flag){

      case 0: printf("Record not found!\n"); break;

      default: break;
   }
}

// sort the records, either by name or BMI. Prompt user for choice
void sortDB(struct db_type * pArr[])
{
   char chr[10];
   printf("sort by name (n) or BMI (b)? ");
   fgets(chr, 3, stdin);
   chr[strlen(chr) - 1] = '\0';

   int var = 0;

   if(strcmp("b", chr) == 0) var = 1;
   
   else if(strcmp("n", chr) == 0) var = 2;
   
   switch(var){

      case 1: // bmi

         for(int index = 0; SIZE > index; ++index){
            for(int index2 = 0; (SIZE - 1 - index) > index2; ++index2){
               if(*(pArr + index2 + 1)){
                  if((*(*(pArr + index2 + 1))).bmi < (*(*(pArr + index2))).bmi){

                    struct db_type *x = *(pArr + index2);
                    *(pArr + index2) = *(pArr + index2 + 1);
                    *(pArr + index2 + 1) = x;
                  }
               }
            }
         }
      break;

      case 2: // name

         for(int index = 0; SIZE > index; ++index){
            for(int index2 = 0; (SIZE - 1 - index) > index2; ++index2){
               if(*(pArr + index2 + 1)){

                  int tmp = strcmp((*(*(pArr + index2))).name, (*(*(pArr + index2 + 1))).name);
                  if(0 < tmp){

                    struct db_type *y = *(pArr + index2);
                    *(pArr + index2) = *(pArr + index2 + 1);
                    *(pArr + index2 + 1) = y;
                  }
               }
            }
         }

      break;
      default: break;
   }
}



