/**********************************************************************/
/*  pa2.c                                                             */
/*  C Program File                                                    */
/*                                                                    */
/*  Template for Problem Set 02                                       */
/*                                                                    */
/*  This file should only contain the function calls to the           */
/*      functions you created in the header file.                     */
/*                                                                    */
/**********************************************************************/

//include statements
#include "pa2.h"


//main program
int main(){
	series *seriesPtr = NULL;
	int choice;

	do{
		choice = printMenu();
		switch(choice){
			case 1:
				//add series
				/***********************************************
				Call a function here that adds a series to the
				linkedlist being pointed by seriesPtr.
				The order of the series does not matter.
				Define your function at pa2.h.
				***********************************************/
				addSeries(&seriesPtr);
				break;
			case 2:
				//add episode to a series
				/***********************************************
				Call a function here that adds an episode to a
				series. Order of episodes does not matter.
				Define your function at pa2.h.
				***********************************************/
				addEpisode(&seriesPtr);
				break;
			case 3:
				//view all
				/***********************************************
				Call a function here prints all the series
				followed by their respective episodes.
				Define your function at pa2.h.
				***********************************************/
				viewAll(&seriesPtr);
				break;
			case 4:
				//delete a series
				/***********************************************
				Call a function here deletes all the series
				added and their respective episodes.
				Define your function at pa2.h.
				***********************************************/
				deleteAll(&seriesPtr);
				break;
			case 5:
				//free nodes before exit
				exitAndDelete(&seriesPtr);
				printf("\n\t Goodbye!\n\n");
				break;
			default:
				printf("\n\t Invalid Choice!\n");
				break;
		}//end of switch
	}while(choice!=5);


	return 0;
}//end of main