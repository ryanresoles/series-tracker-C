/**********************************************************************/
/*  pa2.h                                                             */
/*  C Header File                                                     */
/*                                                                    */
/*  Template for Problem Set 02                                       */
/*                                                                    */
/*  This file should only contain the function definitions of         */
/*      the function calls in the C program file.                     */
/*                                                                    */
/**********************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//structure definition of an episode
typedef struct allEpisodes{
	int episode_number;
	int season_number;
	char title[128];
	struct allEpisodes *nextEpisode;
}episode;

//structure definition of a series
typedef struct allSeries{
	int index;
	char title[128];
	int num_episodes;
	struct allSeries *nextSeries; //self-referential pointer for succeeding series
	episode *episodes; //pointer to a list of episodes
}series;

//printMenu function
//returns the choice of the user
int printMenu(){
	int choice;
	printf("\n\t+-----------------------------------+\n");
	printf("\t+ 1. Add Series                     +\n");
	printf("\t+ 2. Add Episode to a Series        +\n");
	printf("\t+ 3. View All                       +\n");
	printf("\t+ 4. Delete All Series              +\n");
	printf("\t+ 5. Exit                           +\n");
	printf("\t+-----------------------------------+\n");
	printf("\t Choice: ");
	scanf("%d", &choice);

	return choice;
}

/************************************************************************/
/* Define your functions below!                                         */
/************************************************************************/

//function for adding series
void addSeries(series **seriesPtr){
	//temporary storage
	char title[128];
	series *temp;
	series *temp2;

	printf("\n");
	printf("\tEnter series title: ");
	//code for string input with spaces
	getchar();
	fgets(title, 128, stdin);
	for(int a=0; a<strlen(title); a++){
		if(title[a] == '\n'); title[a] == ' ';
	}

	if(*seriesPtr==NULL){
		//automatically adds at head
		temp = (series *)malloc(sizeof(series));
		temp->index = 1;
		strcpy(temp->title, title);
		temp->num_episodes = 0;
		temp->nextSeries = NULL;
		temp->episodes = NULL;

		//adds temporary list to the main linked list
		*seriesPtr = temp;
	}
	else{
		//for setting index
		int counter = 2;

		//traverses through the linked list
		temp = *seriesPtr;
		while(temp->nextSeries  != NULL){
			temp = temp->nextSeries;
			counter++;
		}

		//node to be inserted
		temp2 = (series*) malloc (sizeof(series));
		temp2->index = counter;
		strcpy(temp2->title,title);
		temp2->num_episodes = 0;
		temp2->nextSeries = NULL;
		temp2->episodes = NULL;

		//adds temporary list to the main linked list
		temp->nextSeries = temp2;

	}
	printf("\tNumber of episodes initially set to zero (0).\n");
	printf("\n");
	printf("\tSeries successfully added!\n");
}


void addEpisode(series **seriesPtr){
	//for asking episode index
	int choice = 0;

	//for traversing later in the list
	series *temp;
	episode *temp2;
	episode *temp3;

	//for the temporary episode details
	char title[128];
	int season, episode2;

	printf("\n");
	if(*seriesPtr == NULL) printf("\tNo series yet. Add a series first!\n");
	else{
		printf("\tRecorded series: \n");
		printf("\n");
		//traverses through the list and prints each instance
		temp = *seriesPtr;
		while(temp != NULL){
			printf("\t[%d] %s", temp->index, temp->title);
			temp = temp->nextSeries;
		}
		printf("\n");
		printf("\tWhich series: ");
		scanf("%d", &choice);
		printf("\n");
		temp = *seriesPtr;
		while(temp != NULL && temp->index != choice){
			temp = temp->nextSeries;
		}
		if(temp->index == choice){
			printf("\n");
			printf("\tEnter episode title: ");
			getchar();
			fgets(title, 128, stdin);
			for(int a=0; a<strlen(title); a++){
				if(title[a] == '\n'); title[a] == ' ';
			}
			printf("\tEnter season number: ");
			scanf("%d", &season);
			printf("\tEnter episode number: ");
			scanf("%d", &episode2);

			//executes if there are no episodes yet
			if(temp->episodes == NULL){
				//copies data to the node
				temp2 = (episode *) malloc (sizeof(episode));
				strcpy(temp2->title, title);
				temp2->season_number = season;
				temp2->episode_number = episode2;
				temp2->nextEpisode = NULL;

				temp->episodes = temp2;
			}else{
				//traverses through existing episode list
				temp3 = temp->episodes;
				while(temp3->nextEpisode != NULL){
					temp3 = temp3->nextEpisode;
				}
				temp2 = (episode *) malloc (sizeof(episode));
				strcpy(temp2->title, title);
				temp2->season_number = season;
				temp2->episode_number = episode2;
				temp2->nextEpisode = NULL;

				//stores the temp node to the next pointer
				temp3->nextEpisode = temp2;
			}
			printf("\n");
			printf("\tEpisode successfully added!\n");

		}else printf("\tChoice not within the set of series. Please try again.\n");
	}
}

void viewAll(series **seriesPtr){
	printf("\n");
	series *temp;
	episode *temp2;

	//prompts user that list is still empty
	if(*seriesPtr == NULL) printf("\tNo series yet. Add a series first!\n");
	//executs if there is at least one series in the list
	else{
		printf("\tRecorded series:\n");
		printf("\n");
		temp = *seriesPtr;

		//traverses through the list
		while(temp != NULL){
			printf("\tSeries number %d: \n", temp->index);
			printf("\t\t%s", temp->title);
			
			//traverses through episodes
			if(temp->episodes != NULL){
				temp2 = temp->episodes;
				while(temp2 != NULL){
					printf("\t\t\t[Season %d, Episode %d] %s", temp2->season_number, temp2->episode_number, temp2->title);
					temp2 = temp2->nextEpisode;
				}
			}temp = temp->nextSeries;
		}
	}
}

void deleteAll(series **seriesPtr){
	//used to delete nodes individually
	series *temp = *seriesPtr;
	episode *temp2;
	char choice;

	//nested if else for y/n choice
	printf("\tYou are deleting all recorded series.\n");
	printf("\tAre you sure you want to continue? (y/n): ");
	scanf(" %c", &choice);
	choice = tolower(choice);
	if(choice == 'y'){
		printf("\tAre you really sure? (y/n): ");
		scanf(" %c", &choice);
		choice = tolower(choice);
		if(choice == 'y'){
			printf("\tReally really sure? (y/n): ");
			scanf(" %c", &choice);
			choice = tolower(choice);
			if(choice == 'y'){
				if(temp == NULL) printf("\tNothing to delete.\n");
				else{
					//traverses through the main list
					while(*seriesPtr != NULL){
						if((*seriesPtr)->episodes != NULL){
							while((*seriesPtr)->episodes != NULL){
								temp2 = (*seriesPtr)->episodes;
								(*seriesPtr)->episodes = (*seriesPtr)->episodes->nextEpisode;
								free(temp2);
							}
						}
						printf("\tDeleting episodes of %s...\n", (*seriesPtr)->title);
						printf("\t%s deleted!\n", (*seriesPtr)->title);
						temp = *seriesPtr;
						*seriesPtr = (*seriesPtr)->nextSeries;
						free(temp);
					}
					printf("\tSuccessfully deleted all recorded series!\n");
				}
			}else if(choice == 'n') printf("\tDeletion cancelled.\n");
			else printf("\tInvalid choice.\n");
		}else if(choice == 'n') printf("\tDeletion cancelled.\n");
		else printf("\tInvalid choice.\n");
	}else if(choice == 'n') printf("\tDeletion cancelled.\n");
	else printf("\tInvalid choice.\n");
}

void exitAndDelete(series **seriesPtr){
	//delete before exiting
	series *temp = *seriesPtr;
	episode *temp2;

	while(*seriesPtr != NULL){
		if((*seriesPtr)->episodes != NULL){
			while((*seriesPtr)->episodes != NULL){
				temp2 = (*seriesPtr)->episodes;
				(*seriesPtr)->episodes = (*seriesPtr)->episodes->nextEpisode;
				free(temp2);
			}
		}
		temp = *seriesPtr;
		*seriesPtr = (*seriesPtr)->nextSeries;
		free(temp);
	}
}